import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Window 2.10
import "imports/ebikeDesign"
import "backend/EbikeData"

Window {
    id:win
    objectName:"win"
    width: Constants.width
    height: Constants.height
    visible: true
    ScreenForm {
        id: screen
    }
    signal qmlSignal(string key,string value)
    signal messageReceived(string data)
    Component.onCompleted:
    {
       win.messageReceived.connect(sendToPost);  
    }
    function sendToPost(data)
    {
       console.log("message has received")
    }
    
   
 //   visibility:Window.FullScreen;
    }
//        BrightnessContrast {
//            source: screen
//            anchors.fill: screen

//            brightness: Backend.brightness
//            contrast: 0.0
//        }

//        Item {
//            id: fpsCorner
//            visible: Backend.showFPS
//            enabled: visible

//            CustomLabel {
//                anchors.left: parent.left
//                anchors.top: parent.top
//                anchors.margins: 5
//                text: counter.fps + " FPS"
//                font.pixelSize: 26
//            }

//            FpsCounter {
//                id: counter
//            }
 //       }

//Window {
//    id: window
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("test")

//}

//      RedisInterface{
//          id: redis
//          serverUrl: "127.0.0.1:6379"
//          width: 800
//          height: 600
//       Component.onCompleted:init();


//       Label {
//           id: label2
//           objectName: "objNameL2"
//           x: 202
//           y: 91
//           width: 371
//           height: 58
//           color: "#f22c2c"
//           text: qsTr("Label")
//           style: Text.Normal
//           styleColor: "#f20d0d"
//           horizontalAlignment: Text.AlignHCenter
//           font.pointSize: 12
//           font.family: "Verdana"
//           verticalAlignment: Text.AlignVCenter
//       }
//      }

//      Timer{
//          id: timer
//          running: true
//          repeat: true
//          interval: 100
//          onTriggered: {

//              console.log(redis.getCurrentValue())

//              text1.text = redis.get("lihaoran")
//              label2.text = redis.get("kongyun")

//          }
//      }

//     Text {
//         width: 100
//         height: 30
//         id: text1
//         text:
//         {
//            "hello world----";//+redis.value();

//         }
//     }

//     ScreenForm {
//         id: screen
//    }
//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: window.height
//        width: window.width

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: window.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
//}
