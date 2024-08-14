import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import Qt.labs.platform
import "../global"


FluWindow {

    id: window
    windowIcon: "qrc:/res/images/favicon.ico"
    title: qsTr("AlwaysEnglish")
    width: 860
    height: 668
    minimumWidth: 668
    minimumHeight: 320

    launchMode: FluWindowType.SingleTask

    appBar: FluAppBar {
        icon: window.windowIcon
        title: window.title
        height: 30
        showDark: true
        darkClickListener: (button) => handleDarkChanged(button)
        closeClickListener: () => {
            dialog_close.open()
        }
        z: 7
    }

    Component.onDestruction: {
        FluRouter.exit()
    }

    FluNavigationView {
        id: nav_view
        width: parent.width
        height: parent.height
        displayMode: FluNavigationViewType.Open
        hideNavAppBar: true
        cellWidth: 150
        z: 999

        pageMode: FluNavigationViewType.Stack

        items: ItemsOriginal
        footerItems: ItemsFooter

        Component.onCompleted: {
            ItemsOriginal.navigationView = nav_view
            ItemsFooter.navigationView = nav_view
            setCurrentIndex(0)
        }
    }

    FluLoader {
        id: loader_reveal
        anchors.fill: parent
    }

    SystemTrayIcon {
        id: system_tray
        visible: true
        icon.source: "qrc:/res/images/favicon.ico"
        tooltip: "AlwaysEnglish"
        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: {
                    FluRouter.exit()
                }
            }
        }
        onActivated:
                (reason) => {
            if (reason === SystemTrayIcon.Trigger) {
                window.show()
                window.raise()
                window.requestActivate()
            }
        }
    }

    Timer {
        id: timer_window_hide_delay
        interval: 150
        onTriggered: {
            window.hide()
        }
    }

    FluContentDialog {
        id: dialog
        implicitWidth: 500
        title: qsTr("Warning")
        message: qsTr("The System dosen't have an English (US) input method insatlled\nThe softeare will be unavailable!\nPlease go to settings to install English (US) language.")
        buttonFlags: FluContentDialogType.PositiveButton
        positiveText: qsTr("go to install")
        onPositiveClicked: {
            ControlInputLayout.gotoLanguageSettings();
        }
    }

    FluContentDialog {
        id: dialog_close
        title: qsTr("Quit")
        message: qsTr("Are you sure you want to exit the program?")
        negativeText: qsTr("Minimize")
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton | FluContentDialogType.PositiveButton
        onNegativeClicked: {
            system_tray.showMessage(qsTr("Friendly Reminder"), qsTr("AlwaysEnglish is hidden from the tray, click on the tray to activate the window again"));
            timer_window_hide_delay.restart()
        }
        positiveText: qsTr("Quit")
        neutralText: qsTr("Cancel")
        onPositiveClicked: {
            FluRouter.exit(0)
        }
    }

    // Component.onCompleted: {
    //     var isEnglishInputInstalled = ControlInputLayout.isEnglishInputInstalled()
    //     if (!isEnglishInputInstalled) {
    //         dialog.open()
    //     }
    // }

    function changeDark() {
        FluTheme.darkMode = FluTheme.dark ? FluThemeType.Light : FluThemeType.Dark
    }

    function handleDarkChanged(button) {
        if (!FluTheme.animationEnabled || window.fitsAppBarWindows === false) {
            changeDark()
        } else {
            if (loader_reveal.sourceComponent) {
                return
            }
            loader_reveal.sourceComponent = com_reveal
            var target = window.containerItem()
            var pos = button.mapToItem(target, 0, 0)
            var mouseX = pos.x
            var mouseY = pos.y
            var radius = Math.max(distance(mouseX, mouseY, 0, 0), distance(mouseX, mouseY, target.width, 0), distance(mouseX, mouseY, 0, target.height), distance(mouseX, mouseY, target.width, target.height))
            var reveal = loader_reveal.item
            reveal.start(reveal.width * Screen.devicePixelRatio, reveal.height * Screen.devicePixelRatio, Qt.point(mouseX, mouseY), radius)
        }
    }
}
