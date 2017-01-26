import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    width: 400
    height: 400
    property alias listView1: listView1

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        Text {
            id: text1
            text: qsTr("Ввод данных по подстанции")
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }

        ListView {
            id: listView1
            width: 213
            height: 260
            Layout.fillHeight: false
            Layout.fillWidth: true
            model: testList
       delegate: Rectangle {
            height: 25
            width: 100
            Text { text: modelData }
            }
        }

    }
}
