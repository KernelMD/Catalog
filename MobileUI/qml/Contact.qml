import QtQuick 2.0
import com.KernelMD.Catalog.StorageManagerPlugin 1.0

Rectangle {
    property Contact contact
    property string title: contact.name

    Flickable {
        anchors.fill: parent
        contentWidth: parent.width

        Image {
            id: image

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: (contact.imageName != "") ? 50 * stack.pixelDensity : 0

            source: (contact.imageName != "") ?
                    StorageManager.cachePath + contact.imageName : ""
            fillMode: Image.Stretch
            sourceSize.height: height
            sourceSize.width: width
        }

        ListView {
            id: view

            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: image.top

            delegate: ListEntry {
                primaryText: text

                height: 20 * stack.pixelDensity
                width: parent.width
            }

            focus: true
            clip: true
            highlightMoveVelocity: 1000
            highlightMoveDuration: 500

            model: ListModel { id: model }
        }
    }
    Component.onCompleted: {
        header.headerText = title;
        for (var i in contact.addresses)
            view.model.append({"text": contact.addresses[i]});
        for (var i in contact.emails)
            view.model.append({"text": contact.emails[i]});
        for (var i in contact.phones)
            view.model.append({"text": contact.phones[i]});
        for (var i in contact.websites)
            view.model.append({"text": contact.websites[i]});
    }
}

