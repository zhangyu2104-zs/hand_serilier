import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 1.2
import Redis 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("test")



      RedisInterface{
          id: redis
          serverUrl: "127.0.0.1:6379"
          width: 800
          height: 600
       Component.onCompleted:init();


       Label {

           id: label2
           objectName: "objNameL2"
           x: 202
           y: 91
           width: 371
           height: 58
           color: "#f22c2c"
           text: qsTr("Label")
           style: Text.Normal
           styleColor: "#f20d0d"
           horizontalAlignment: Text.AlignHCenter
           font.pointSize: 12
           font.family: "Verdana"
           verticalAlignment: Text.AlignVCenter
       }
      }

      Timer{
          id: timer
          running: true
          repeat: true
          interval: 100
          onTriggered: {

              console.log(redis.getCurrentValue())



              text1.text = redis.get("lihaoran")

          }
      }
//  Button{
//             width: 100
//             height: 30
//             text: qsTr("点击")
//             onClicked: {
//                text = redis.get("lihaoran");
//             }
//         }

 Text {
     width: 100
     height: 30
     id: text1
     text:
     {
        "hello world----"+redis.value();

     }
 }


    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
