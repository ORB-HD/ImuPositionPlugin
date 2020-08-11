#ifndef IMUPOSITIONMODELEXTENTION_H_INCLUDED
#define IMUPOSITIONMODELEXTENTION_H_INCLUDED

#include <rbdl_wrapper.h>
#include <Qt3DRender>
#include <Qt3DCore>
#include "util.h"

using namespace RigidBodyDynamics::Math;

class ImuPositionModelExtension : public WrapperExtension {
	private:
		float imu_size; 
		QColor imu_color;

		Qt3DRender::QMesh* imu_mesh;

		std::vector<std::string> imu_segments;
		std::vector<Vector3d> imu_positions;

		std::vector<Qt3DCore::QEntity*> imu_visuals;
	public:
		ImuPositionModelExtension(QColor color, float size);

		std::string getExtensionName();
		void update(float current_time);
		Qt3DCore::QEntity* getVisual();

		void addImuPosition(const std::string& segment_name, const Vector3d& position);

		const std::vector<std::string>& getImuSegments() { return imu_segments; }
		const std::vector<Vector3d>& getImuPositions() { return imu_positions; }
};

#endif
