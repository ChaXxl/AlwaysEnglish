import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0

FluLauncher {
    id: app

    // 改变夜间模式时保存设置
    Connections{
        target: FluTheme
        function onDarkModeChanged(){
            SettingsHelper.saveDarkMode(FluTheme.darkMode)
        }
    }

    Component.onCompleted: {
        FluApp.init(app)

        FluApp.useSystemAppBar = true

        FluApp.windowIcon = "qrc:/res/images/logo.ico"

        FluTheme.darkMode = FluThemeType.System

        FluTheme.animationEnabled = true

        FluRouter.routes = {
            "/":"qrc:/qml/window/MainWindow.qml",
        }
        FluRouter.navigate("/")
    }
}
