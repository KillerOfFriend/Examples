import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../widgets"

ApplicationWindow {
    id: mainWindow
    visible: true

    title: qsTr("File Manager")
    width: 640
    height: 480

    //---------------------------------------------------------------------
    // Actions
    //---------------------------------------------------------------------
    ActionGroup {
        id: viewActions
        exclusive: true

        Action {
            id: iconViewAction
            checkable: true
            text: qsTr("Icon")
            onTriggered: viewLoader.source = checked ? "qrc:/qml/widgets/FsIconView.qml" : ""
        }
        Action {
            id: tableViewAction
            checkable: true
            text: qsTr("Table")
            onTriggered: viewLoader.source = checked ? "qrc:/qml/widgets/FsTableView.qml" : ""
        }
        Action { id: listViewAction
            checkable: true
            text: qsTr("List")
            onTriggered: viewLoader.source = checked ? "qrc:/qml/widgets/FsListView.qml" : ""
        }
    }
    //---------------------------------------------------------------------
    // Menu
    //---------------------------------------------------------------------
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("View")

            MenuItem { action: iconViewAction }
            MenuItem { action: tableViewAction }
            MenuItem { action: listViewAction }
        }
    }
    //---------------------------------------------------------------------
    // Content Area
    //---------------------------------------------------------------------
    ColumnLayout {
        //---------------------------------------------------------------------
        id: mainColumnLayout
        anchors.fill: parent
        spacing: 5
        anchors.topMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        //---------------------------------------------------------------------
        RowLayout {
            //anchors.top: parent.top
            width: parent.width

            spacing: 5
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            TextField {
                id: pathEdit

                Layout.fillWidth: true
                height: 30
                readOnly: true
            }

            Button {
                id: upButton

                Layout.preferredWidth: height
                width: 30; height: 30

                text: "Up"

                onClicked: DataSource.dirUp()
            }
        }
        //---------------------------------------------------------------------
        Item {
            Layout.alignment: Qt.AlignBottom
            Layout.fillWidth: true
            Layout.fillHeight: true

            Loader {
                id: viewLoader
                anchors.fill: parent
                focus: true
            }
        }
        //---------------------------------------------------------------------
    }

    Component.onCompleted: {
        pathEdit.text = DataSource.path()
        iconViewAction.trigger()
    }

    Connections {
        target: DataSource
        onPathChanged: pathEdit.text = inNewPath
    }
}
