#ifndef IMUPOSITIONPLUGIN_H_INCLUDED
#define IMUPOSITIONPLUGIN_H_INCLUDED

#include <QWidget>
#include <QString>

#include "toolkit_interfaces.h"
#include "toolkit_errors.h"
#include "util.h"

#include "ImuPositionModelExtention.h"

class ImuPositionPlugin : public QObject, public OptionalInterface {
	Q_OBJECT
	Q_INTERFACES(OptionalInterface)
	Q_PLUGIN_METADATA(IID OptionalInterface_iid FILE "metadata.json")
	public:
		ImuPositionPlugin();
		virtual ~ImuPositionPlugin();

		void init(ToolkitApp* app);

		ImuPositionModelExtention* loadImuPositionFile(QString path);

	private:
		ToolkitApp* parentApp;
		QAction* load_file_trigger;

		std::map<RBDLModelWrapper*, QString> model_file_map;

		float imu_size; 
		QColor imu_color;

		void loadImuPositionSettings();

	public slots:
		void action_load_data();
		void reload(RBDLModelWrapper *model);
};

#endif 
