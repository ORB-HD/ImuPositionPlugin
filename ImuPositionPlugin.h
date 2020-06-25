#ifndef IMUPOSITIONPLUGIN_H_INCLUDED
#define IMUPOSITIONPLUGIN_H_INCLUDED

#include <QWidget>

#include "toolkit_interfaces.h"

#include "ImuPositionModelExtention.h"


class ImuPositionPlugin : public QObject, public OptionalInterface {
	Q_OBJECT
	Q_INTERFACES(OptionalInterface)
	Q_PLUGIN_METADATA(IID OptionalInterface_iid FILE "metadata.json")

	public:
		ImuPositionPlugin();
		virtual ~ImuPositionPlugin();

		void init(ToolkitApp* app);

	private:
		ToolkitApp* parentApp;

	public slots:
};

#endif 
