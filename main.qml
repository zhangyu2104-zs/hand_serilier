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
    title: qsTr("Hello World")



      RedisInterface{
          id: redis
          serverUrl: "127.0.0.1:6379"
          width: 800
          height: 600
       Component.onCompleted:init();

      }
  Button{
             width: 100
             height: 30
             text: qsTr("点击")
             onClicked: {
                text = redis.get("lihaoran");
             }
         }

 Text {
     id: text1
     text:
     {
        //"hello world----";

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
