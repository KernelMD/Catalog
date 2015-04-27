#ifndef STORAGEMANAGERPLUGIN_PLUGIN_H
#define STORAGEMANAGERPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class StorageManagerPluginPlugin : public QQmlExtensionPlugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "com.KernelMD.Catalog.StorageManagerPlugin")

public:
	void registerTypes(const char *uri);
};

#endif // STORAGEMANAGERPLUGIN_PLUGIN_H

