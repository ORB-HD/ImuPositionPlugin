#include "ImuPositionModelExtention.h"

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>

using namespace Qt3DCore;
using namespace Qt3DRender;
using namespace Qt3DExtras;

ImuPositionModelExtention::ImuPositionModelExtention(QColor imu_color, float imu_size) : 
	imu_color(imu_color), 
	imu_size(imu_size), 
	WrapperExtention()
{
	imu_mesh.setSource(QUrl::fromLocalFile(findFile(QString("unit_sphere_medres.obj"))));
}

std::string ImuPositionModelExtention::getExtentionName() {
	return "ImuPositions";
}

void ImuPositionModelExtention::update(float current_time) {
	//nothing to update in sync with time
	return;
}

QEntity* ImuPositionModelExtention::getVisual() {
	if (model_parent != nullptr) {
		for (int i=0;i<imu_segments.size();i++) {
			imu_visuals.push_back(new QEntity);
			Qt3DCore::QEntity* imu_visual = imu_visuals[imu_visuals.size()-1];
			imu_visual->setProperty("Scene.ObjGroup", QVariant("IMU"));


			Qt3DExtras::QPhongAlphaMaterial* material = new Qt3DExtras::QPhongAlphaMaterial;
			material->setAmbient(imu_color);
			material->setAlpha((float)imu_color.alpha() / 255.);

			Qt3DCore::QTransform* position = new Qt3DCore::QTransform;
			position->setTranslation(QVector3D(imu_positions[i][0], imu_positions[i][1], imu_positions[i][2]));
			position->setScale(imu_size);

			imu_visual->addComponent(&imu_mesh);
			imu_visual->addComponent(position);
			imu_visual->addComponent(material);

			model_parent->addStaticVisual(imu_segments[i], imu_visual);
		}
	}
	//Visuals are added as static objects to the model, without using a single root
	return nullptr;
}

void ImuPositionModelExtention::addImuPosition(const std::string& segment_name, const Vector3d& position) {
	imu_segments.push_back(segment_name);
	imu_positions.push_back(position);
}
