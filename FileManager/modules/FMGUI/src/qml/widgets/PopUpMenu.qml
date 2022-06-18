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

            icon.color: "transparent"
            icon.source: "qrc:/img/copy_past.png"

            onTriggered: { helper.copy(targetObjectPath); }
        }

        Action {
            id: cutAction
            text: qsTr("cut")

            icon.color: "transparent"
            icon.source: "qrc:/img/cut.png"

            onTriggered: { helper.cut(targetObjectPath); }
        }

        Action {
            id: pasteAction
            text: qsTr("past")

            icon.color: "transparent"
            icon.source: "qrc:/img/copy_past.png"

            onTriggered: {
                if (helper.paste(DataSource.path()))
                    DataSource.setPath(DataSource.path());;
            }
        }

        Action {
            id: deleteAction
            text: qsTr("delete")

            icon.color: "transparent"
            icon.source: "qrc:/img/delete.png"

            onTriggered: {
                if (helper.remove(targetObjectPath))
                    DataSource.setPath(DataSource.path());
            }
        }
    }

    property string targetObjectPath: ""

    MenuItem { id: copyMenuItem; height: visible ? implicitHeight : 0;  action: copyAction }
    MenuItem { id: cutMenuItem; height: visible ? implicitHeight : 0;  action: cutAction }
    MenuItem { id: pasteMenuItem; height: visible ? implicitHeight : 0; action: pasteAction }
    MenuItem { id: deleteMenuItem; height: visible ? implicitHeight : 0;  action: deleteAction }

    Connections {
        target: popupMenu
        onAboutToShow: { pasteMenuItem.visible = !helper.bufferIsEmpty(); }
    }
}

