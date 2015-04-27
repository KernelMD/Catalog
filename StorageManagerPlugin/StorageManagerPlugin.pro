TEMPLATE = lib
TARGET = StorageManagerPlugin
QT += qml quick sql
CONFIG += qt plugin

DESTDIR = ../lib
TARGET = $$qtLibraryTarget($$TARGET)
uri = com.KernelMD.Catalog.StorageManagerPlugin

# Input
SOURCES += \
    storagemanagerplugin.cpp \
    src/StorageManager.cpp \
    src/AbstractCatalogEntry.cpp \
    src/CategoryCatalogEntry.cpp \
    src/CatalogModel.cpp \
    src/ContactModel.cpp \
    src/ContactEntry.cpp \
    src/CommodityCatalogEntry.cpp \
    src/Commodity.cpp \
    src/Contact.cpp \
    src/SyncManager.cpp

HEADERS += \
    storagemanagerplugin.h \
    include/StorageManager.h \
    include/AbstractCatalogEntry.h \
    include/CategoryCatalogEntry.h \
    include/CatalogModel.h \
    include/ContactModel.h \
    include/ContactEntry.h \
	include/CommodityCatalogEntry.h \
    include/Commodity.h \
    include/Contact.h \
    include/SyncManager.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
	# Form path, where qmldir file should be placed.
	qmldir_path = $$OUT_PWD
	qmldir_path = $$replace(qmldir_path,/StorageManagerPlugin,/imports/com/KernelMD/Catalog/StorageManagerPlugin)
	qmldir_path = $$replace(qmldir_path, /, $$QMAKE_DIR_SEP)
	# Create this path.
        mkpath($$qmldir_path)
	# Prepare qmldir copying
	copy_qmldir.target = $$qmldir_path/qmldir
	copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

