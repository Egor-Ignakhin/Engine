import QtQuick 2.0
import QtQuick.Controls 2.0


Rectangle {
    width: 200
    height: 300
    id:myButton
    signal clickSignal()

    Button{
        text: "Start Engine"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        onClicked: clickSignal;
    }
}
