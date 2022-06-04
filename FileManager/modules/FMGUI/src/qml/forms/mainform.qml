import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../widgets"

//window containing the application
ApplicationWindow {

    visible: true

    //title of the application
    title: qsTr("File Manager")
    width: 640
    height: 480

    //menu containing two menu items
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    //Content Area

    ColumnLayout {

        id: mainColumnLayout
        anchors.fill: parent
        spacing: 5
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        FsTableView {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }


}
