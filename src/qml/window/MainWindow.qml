import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
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
}
