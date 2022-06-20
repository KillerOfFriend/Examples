import QtQuick 2.12

Item {
    id: fsIconView

    PopUpMenu {
        id: veiwPopupMenu
    }

    Component {
        id: fsIconDelegate
        Item {
            width: gridView.cellWidth; height: gridView.cellHeight
            Column {
                anchors.horizontalCenter: parent.horizontalCenter

                Image {
                    id: objectImage
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 50; height: 50
                    fillMode: Image.Stretch
                    source: model.imageURL

                }

                Text {
                    text: model.name
                    width: gridView.cellWidth
                    height: parent.height - objectImage.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    //clip: true
                    maximumLineCount: 2
                    wrapMode: Text.Wrap
                }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: {
                    gridView.currentIndex = index

                    if(mouse.button & Qt.RightButton) {
                        veiwPopupMenu.targetObjectPath = model.objectpath
                        veiwPopupMenu.popup()
                    }
                }

                onDoubleClicked: {
                    if (mouse.button & Qt.LeftButton && model.type === "Dir")
                        DataSource.setPath(model.objectpath);
                }
            }


        }
    }

    Component {
        id: fsIconHighlightDelegate
        Rectangle {
            width: gridView.cellWidth; height: gridView.cellHeight
            color: "lightsteelblue"; radius: 5
            x: gridView.currentItem.x
            y: gridView.currentItem.y
            Behavior on x { SpringAnimation { spring: 4; damping: 0.2 } }
            Behavior on y { SpringAnimation { spring: 4; damping: 0.2 } }
        }
    }

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: 80; cellHeight: 80

        model: fsModel
        delegate: fsIconDelegate

        highlight: fsIconHighlightDelegate
        highlightFollowsCurrentItem: false
        focus: true
    }
}
