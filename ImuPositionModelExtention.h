#ifndef IMUPOSITIONMODELEXTENTION_H_INCLUDED
#define IMUPOSITIONMODELEXTENTION_H_INCLUDED

#include <rbdl_wrapper.h>

class ImuPositionModelExtention : public WrapperExtention {
	private:
		// Vars
		// 
		// int dof;
		// float max_time;
	public:
		ImuPositionModelExtention();

		// These Functions need to be implemented
		std::string getExtentionName();
		void update(float current_time);

		// Optional Model wrapper virtual functions
		// Qt3DCore::QEntity* getVisual();
		// void exportData();

		// Getter and Setter functions
		// int getDOF();
		// float getMaxTime();

};

#endif