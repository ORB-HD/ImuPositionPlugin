#include "ImuPositionPlugin.h"
#include <iostream>

#include <QFileDialog>
#include <QMessageBox>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <rbdl_wrapper.h>

#include <parser.hpp>

ImuPositionPlugin::ImuPositionPlugin() {
	parentApp = NULL;
}

ImuPositionPlugin::~ImuPositionPlugin() {
}

void ImuPositionPlugin::init(ToolkitApp* app) {
	//save reference to parent ToolkitApp 
	parentApp = app;

	load_file_trigger = new QAction("Load Imu Position");
	parentApp->addFileAction(load_file_trigger);

	connect(load_file_trigger, SIGNAL(triggered(bool)), this, SLOT(action_load_data()));

	QCommandLineOption imuposition_option( QStringList() << "imu" << "imuposition",
	                                 "Load ImuPosition files <file>", 
	                                 "file"
	                               );
	parentApp->addCmdOption(imuposition_option, [this](QCommandLineParser& parser){
		auto data_list = parser.values("imuposition");
		for (auto file : data_list) {
			ImuPositionModelExtention* ext;
			try {
				ext = loadImuPositionFile(file);
			} catch (RigidBodyDynamics::Errors::RBDLError& e){
				ToolkitApp::showExceptionDialog(e);
				delete ext;
			}
			if (parentApp->getLoadedModels()->size() != 0) {
				RBDLModelWrapper* rbdl_model = nullptr;

				if (parentApp->getLoadedModels()->size() == 1) {
					rbdl_model = parentApp->getLoadedModels()->at(0);
				} else {
					rbdl_model = parentApp->selectModel(nullptr);
				}

				if (rbdl_model != nullptr) {
					rbdl_model->addExtention(ext);
				} else {
					delete ext;
				}
			}
		}
		
	});

	loadImuPositionSettings();

	std::cout << "ImuPositionPlugin loaded" << std::endl;
}

void ImuPositionPlugin::loadImuPositionSettings() {
	parentApp->toolkit_settings.beginGroup("ImuPositionOptions");


	QVariant val = parentApp->toolkit_settings.value("imu.color");
	if (val.isNull()) {
		imu_color = QColor::fromRgbF(1., 0., 1., 1.);
		parentApp->toolkit_settings.setValue("imu.color", imu_color.rgba());
	} else {
		imu_color = QColor::fromRgba(val.toUInt());
	}
	parentApp->toolkit_settings.setType("imu.color", imu_color);

	val = parentApp->toolkit_settings.value("imu.size");
	if (val.isNull()) {
		imu_size = 0.1;
		parentApp->toolkit_settings.setValue("imu.size", imu_size);
	} else {
		imu_size = val.toFloat();
	}
	parentApp->toolkit_settings.setType("imu.size", imu_size);

	parentApp->toolkit_settings.endGroup();
}

void ImuPositionPlugin::action_load_data() {
	if (parentApp != NULL) {
		QFileDialog file_dialog (parentApp, "Select Imu Position File");

		file_dialog.setNameFilter(tr("Imu Position File (*.txt)"));
		file_dialog.setFileMode(QFileDialog::ExistingFile);

		ImuPositionModelExtention* ext;
		if (file_dialog.exec()) {
			QString filepath;
			try {
				filepath = file_dialog.selectedFiles().at(0);ext = loadImuPositionFile(filepath);
			} catch (RigidBodyDynamics::Errors::RBDLError& e){
				ToolkitApp::showExceptionDialog(e);delete ext;
			}if (parentApp->getLoadedModels()->size() != 0) {
				RBDLModelWrapper* rbdl_model = nullptr;

				if (parentApp->getLoadedModels()->size() == 1) {
					rbdl_model = parentApp->getLoadedModels()->at(0);
				} else {
					rbdl_model = parentApp->selectModel(nullptr);
				}

				if (rbdl_model != nullptr) {
					rbdl_model->addExtention(ext);
				} else {
					delete ext;
				}
			}
		}	
	} else {
		//should never happen
		throw RigidBodyDynamics::Errors::RBDLError("ImuPositionPlugin was not initialized correctly!");
	}
}

ImuPositionModelExtention* ImuPositionPlugin::loadImuPositionFile(QString path) {
	ImuPositionModelExtention* extention = new ImuPositionModelExtention(imu_color, imu_size);

	std::vector<std::string> names;
	std::vector<float> row_values;

	std::ifstream file(path.toStdString().c_str(), std::ios_base::in);
	aria::csv::CsvParser parser(file);
	parser.delimiter(' ');

	for (auto& row : parser) {
		if ( row.size() == 4 ) {
			std::string segment = row[0];
			Vector3d pos;
			for ( int i=0 ; i<3 ; i++ ) {
				pos(i) = QString::fromStdString(row[i+1]).toFloat();
			}
			extention->addImuPosition(segment, pos);
		}
	}

	return extention;
}
