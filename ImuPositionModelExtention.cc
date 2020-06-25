#include "ImuPositionModelExtention.h"

ImuPositionModelExtention::ImuPositionModelExtention() : WrapperExtention() 
{
}

std::string ImuPositionModelExtention::getExtentionName() {
	return "ImuPosition";
}

void ImuPositionModelExtention::update(float current_time) {
	//nothing to update in sync with time
}
