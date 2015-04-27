import QtQuick 2.0
import com.KernelMD.Catalog.StorageManagerPlugin 1.0

Rectangle {
    id: contactSelector

    property string title: qsTr("CONTACTS")

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
                view.currentIndex = index;
                var contact = StorageManager.GetContact(ident);

                stack.push({ "item": "qrc:/qml/Contact.qml",
                        "properties": { "contact": contact}
                           });
            }
        }

        model: StorageManager.GetContactList()

        clip: true
        focus: true
        highlightMoveVelocity: 1000
        highlightMoveDuration: 500
    }

    Component.onCompleted: header.headerText = contactSelector.title
}

