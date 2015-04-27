#include "storagemanagerplugin.h"
#include "include/CatalogModel.h"
#include "include/CategoryCatalogEntry.h"
#include "include/Commodity.h"
#include "include/CommodityCatalogEntry.h"
#include "include/Contact.h"
#include "include/ContactEntry.h"
#include "include/ContactModel.h"
#include "include/StorageManager.h"

#include <qqml.h>

static QObject* StorageManagerProvider(QQmlEngine* engine, QJSEngine* scriptEngine);

void StorageManagerPluginPlugin::registerTypes(const char *uri) {
	// @uri com.KernelMD.Catalog.StorageManagerPlugin
	qmlRegisterSingletonType<StorageManager>(uri, 1, 0,"StorageManager",
											 StorageManagerProvider);
	qmlRegisterType<CatalogModel>(uri, 1, 0, "CatalogModel");
	qmlRegisterUncreatableType<CategoryCatalogEntry>(uri, 1, 0, "CategoryEntry",
		"Should be loaded from DB.");
	qmlRegisterUncreatableType<CommodityCatalogEntry>(uri, 1, 0, "CommodityEntry",
		"Should be loaded from DB.");
	qmlRegisterUncreatableType<ContactEntry>(uri, 1, 0, "ContactEntry",
		"Should be loaded from DB.");
	qmlRegisterType<ContactModel>(uri, 1, 0, "ContactModel");
	qmlRegisterType<Commodity>(uri, 1, 0, "Commodity");
	qmlRegisterType<Contact>(uri, 1, 0, "Contact");
}

static QObject* StorageManagerProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
	Q_UNUSED(engine);
	Q_UNUSED(scriptEngine);

	return new StorageManager();
}
