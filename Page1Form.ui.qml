import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias sp_selector: sp_selector
    property alias station_selector: station_selector
    property alias res_selector: res_selector

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent


        RowLayout {
            id: rowLayout2
            width: 100
            height: 100

            Image {
                id: logo_drsk
                width: 100
                height: 100
                Layout.fillWidth: false
                source: "logo_drsk.gif"
            }

            Text {
                id: logo_text
                text: qsTr("Заполнение подстанций")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                Layout.fillWidth: true
                font.pixelSize: 30
            }
        }

        Text {
            id: sp_select_text
            text: qsTr("Выберите СП")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            verticalAlignment: Text.AlignVCenter
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 21
        }

        ComboBox {
            id: sp_selector
            height: 72
            clip: false
            rotation: 0
            textRole: ""
            transformOrigin: Item.Center
            Layout.fillHeight: true
            Layout.fillWidth: false
            anchors.right: parent.right
            anchors.left: parent.left
        }

        Text {
            id: res_select_text
            text: qsTr("Выберите РЭС")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pixelSize: 20
        }

        ComboBox {
            id: res_selector
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            id: station_select_text
            text: qsTr("Выберите Подстанцию")
            font.bold: false
            style: Text.Normal
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pixelSize: 20
        }

        ComboBox {
            id: station_selector
            Layout.fillHeight: true
            Layout.fillWidth: true
        }







    }

}
