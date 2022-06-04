import QtQuick 2.12

Item {
    id: fsIconView

    Component {
        id: fsIconDelegate
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            Column {
                anchors.fill: parent
                Image {
                    width: 60; height: 60;
                    fillMode: Image.Stretch
                    source: model.imageURL;
                    anchors.horizontalCenter: parent.horizontalCenter;
                }
                Text {
                    text: model.name;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    wrapMode: TextEdit.WordWrap;
                }
            }
        }
    }

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: 80; cellHeight: 80

        model: fsModel
        delegate: fsIconDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
}
