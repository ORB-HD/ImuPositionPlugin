#include "ImuPositionPlugin.h"
#include <iostream>

ImuPositionPlugin::ImuPositionPlugin() {
	parentApp = NULL;
}

ImuPositionPlugin::~ImuPositionPlugin() {
}

void ImuPositionPlugin::init(ToolkitApp* app) {
	//save reference to parent ToolkitApp 
	parentApp = app;

	std::cout << "ImuPositionPlugin loaded" << std::endl;
}
