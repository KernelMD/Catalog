TEMPLATE = subdirs

SUBDIRS += \
    StorageManagerPlugin \
    MobileUI

MobileUI.depends = StorageManagerPlugin
