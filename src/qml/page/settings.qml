import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0

FluScrollablePage{
    title: qsTr("Settings")

    FluFrame{
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 128
        padding: 10

        ColumnLayout{
            spacing: 5
            anchors{
                top: parent.top
                left: parent.left
            }
            FluText{
                text: qsTr("Dark Mode")
                font: FluTextStyle.BodyStrong
                Layout.bottomMargin: 4
            }
            Repeater{
                model: [{title:qsTr("System"),mode:FluThemeType.System},{title:qsTr("Light"),mode:FluThemeType.Light},{title:qsTr("Dark"),mode:FluThemeType.Dark}]
                delegate: FluRadioButton{
                    checked : FluTheme.darkMode === modelData.mode
                    text:modelData.title
                    clickListener:function(){
                        FluTheme.darkMode = modelData.mode
                    }
                }
            }
        }
    }

    FluFrame {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 50
        padding: 10
        FluCheckBox {
            text: qsTr("Sticky on Top")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: setWindowFlags(checked)
        }
    }

    function setWindowFlags(checked) {
        if (checked) {
            // 置顶的时候保留系统边框和窗口控制按钮
            flags = Qt.Window |
                    Qt.WindowStaysOnTopHint |
                    Qt.WindowTitleHint |
                    Qt.WindowSystemMenuHint |
                    Qt.WindowCloseButtonHint |
                    Qt.WindowMinMaxButtonsHint
        } else {
            flags = Qt.Window
        }
    }
}