import QtQuick 2.0
import QtQuick.Controls 2.12

import fsDBusAdapter 1.0

Menu {
    id: popupMenu

    FsDBusAdapter { id: helper }

    ActionGroup {
        id: fsActions
        exclusive: true

        Action {
            id: copyAction
            text: qsTr("copy")

            onTriggered: { helper.copy(targetObjectPath); }
        }

        Action {
            id: cutAction
            text: qsTr("cut")

            onTriggered: { helper.cut(targetObjectPath); }
        }

        Action {
            id: pasteAction
            text: qsTr("past")

            onTriggered: {
                if (helper.paste(DataSource.path()))
                    DataSource.setPath(DataSource.path());;
            }
        }

        Action {
            id: deleteAction
            text: qsTr("delete")

            onTriggered: {
                if (helper.remove(targetObjectPath))
                    DataSource.setPath(DataSource.path());
            }
        }
    }

    property string targetObjectPath: ""

    MenuItem {
        id: copyMenuItem

        height: visible ? implicitHeight : 0;
        action: copyAction

        icon.color: "transparent"
        icon.source: "qrc:/img/copy_past.png"
    }

    MenuItem {
        id: cutMenuItem

        height: visible ? implicitHeight : 0
        action: cutAction

        icon.color: "transparent"
        icon.source: "qrc:/img/cut.png"
    }

    MenuItem {
        id: pasteMenuItem

        height: visible ? implicitHeight : 0
        action: pasteAction

        icon.color: "transparent"
        icon.source: "qrc:/img/copy_past.png"
    }

    MenuItem {
        id: deleteMenuItem

        height: visible ? implicitHeight : 0
        action: deleteAction

        icon.color: "transparent"
        icon.source: "qrc:/img/delete.png"
    }

    Connections {
        target: popupMenu
        onAboutToShow: { pasteMenuItem.visible = !helper.bufferIsEmpty(); }
    }
}

