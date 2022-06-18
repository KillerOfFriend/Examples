import QtQuick 2.0
import QtQuick.Controls 2.12

import fsDBusAdapter 1.0

Menu {

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

            icon.source: "qrc:/img/cut.png"
            icon.color: "transparent"

            onTriggered: { helper.cut(targetObjectPath); }
        }

        Action {
            id: pasteAction
            text: qsTr("past")

            icon.source: "qrc:/img/copy_past.png"
            icon.color: "transparent"

            onTriggered: {
                if (helper.paste(DataSource.path()))
                    DataSource.setPath(DataSource.path());;
            }
        }

        Action {
            id: deleteAction
            text: qsTr("delete")

            icon.source: "qrc:/img/delete.png"
            icon.color: "transparent"

            onTriggered: {
                if (helper.remove(targetObjectPath))
                    DataSource.setPath(DataSource.path());
            }
        }
    }

    property string targetObjectPath: ""

    MenuItem { action: copyAction }
    MenuItem { action: cutAction }
    MenuItem { action: pasteAction }
    MenuItem { action: deleteAction }
}

