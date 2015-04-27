import QtQuick 2.0
import com.KernelMD.Catalog.StorageManagerPlugin 1.0

Rectangle {
    id: catalog

    property string title: "CATALOG"
    property int parentIdent: 0

    ListView {
        id: view

        anchors.fill: parent

        delegate: ListEntry {
            id: listEntry

            height: 20 * stack.pixelDensity
            width: parent.width

            iconPath: (iconName == "") ?
                        "" :
                        StorageManager.cachePath + iconName
            primaryText: name

            onClicked: {
                if (type == 0) // Should be enum, but...
                    stack.push({"item": "qrc:/qml/Catalog.qml",
                               "properties": {"parentIdent": ident}
                               });
                else
                    stack.push({"item": "qrc:/qml/Commodity.qml",
                               "properties": {"commodity":
                                       StorageManager.GetCommodity(ident)}
                               });
            }
        }

        model: StorageManager.GetCategoryContent(catalog.parentIdent)

        clip: true
        focus: true
        highlightMoveVelocity: 1000
        highlightMoveDuration: 500
    }

    Component.onCompleted: header.headerText = catalog.title
}

