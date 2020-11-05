/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Design Studio.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.10
import "imports/ebikeDesign"
import "imports/QtQuick/Studio/Components"
import "backend/EbikeData"
import QtQuick.Controls 2.3
import QtQuick.Timeline 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.2
import Redis 1.0
import TcpMoveToThread 1.0
import QmlThread 1.0

Item {
    id: testScreen
    width: Constants.width
    height: Constants.height
    property alias currentFrame: timeline.currentFrame
    
    
   // onQmlSignal:console.log("zheshi signal",message)
//     RedisInterface{
//       id:redisInterface1
//       //onBegin:doSomething()
//       Component.onCompleted:initredis();
//       Component.onDestruction:destroyobject();
       
//       function begin()
//       {
//         console.log("backend redis --create object is--")
//         redisInterface1.init()
//         redisInterface1.insertKey("uvc_out","0");
//       }
//       function destroyobject()
//       {
//         console.log("destroy object is--"+redisInterface1)
//         delete redisInterface1;
//       }
//    }
    //onBegin:console.log("1233")
 //   Connections{
 //      target:qmlrediscontrol
 //       onValueChanged:{
 //       console.log("this --"+qmlrediscontrol.value)
 //       }
 //   }
     Connections{
    target:qmlthread
   onDataChanged:{
            var tempdata = qmlthread.m_data
           // countShow.text = tempdata.toString();
           console.log("device temp=="+tempdata["temp"]+"--infrared_left=="+tempdata["infrared_left"])
    }
   }
   
   QmlThread{
    id:qmlthread
   }
   
   Connections{
        target: tcp
        onDataChanged:{
            countShow.text=tcp.m_data;  //此处连接了TcpMoveToThread类的信号，一旦数据改变，就改变message的内容
        }
    }

    TcpMoveToThread{
        id: tcp

    }
    Rectangle {
        id: leftButton
        x: 35
        y: 102
        width: 22
        height: 22
        color: "#00000000"
        radius: 11
        border.color: "#696969"

        Image {
            x: -9
            y: -9
            source: "images/arrow_left.png"
        }
    }

    Rectangle {
        id: rightButton
        x: 1225
        y: 102
        width: 22
        height: 22
        color: "#00000000"
        radius: 11
        border.color: "#696969"

        Image {
            x: -9
            y: -9
            source: "images/arrow_right.png"
        }
    }

    Rectangle {
        id: tripButton
        x: 590
        y: 102
        width: 100
        height: 24
        color: "#00000000"
        radius: 11
        border.color: "#696969"

        CustomLabel {
            color: "#ffffff"
            text: qsTr("End Trip")
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 18
        }
    }

    RowLayout {
        x: 1154
        y: 62

        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("Total")
            font.pixelSize: 20
        }

        CustomLabel {
            color: "#ffffff"
            text: (Backend.metricSystem ? "147.4" : "91.6")
            font.pixelSize: 24
        }

        CustomLabel {
            color: "#9d9d9d"
            text: (Backend.metricSystem ? "km" : "mi.")
            font.pixelSize: 20
        }
    }

Rectangle {
        id:inner
        x: 35
        y: 245
        width: 1212
        height: 300
       
   QtObject{
        id: attrs;
        property int  counter;
        property int  timer_off;
        Component.onCompleted: {
            attrs.counter = 10;
            attrs.timer_off = 0;
        }
    }
    
       GroupBox {
         title: "selecte_second"
         anchors.centerIn:parent
         id: groupBox
          width:600
         height:100
         RowLayout {
             ExclusiveGroup { id: tabPositionGroup }
             RadioButton {
                 text: "1s"
                 checked: true
                 id:first
                 exclusiveGroup: tabPositionGroup
                // anchors.left:parent.left
                 //anchors.leftMargin:35
                 Layout.alignment: Qt.AlignLeft
                 Layout.leftMargin: 35
                 
             }
             RadioButton {
                 text: "1.5s"
                 exclusiveGroup: tabPositionGroup
                 id:second
                Layout.alignment: Qt.AlignLeft
                 Layout.leftMargin: 50
             }
             RadioButton {
                 text: "2s"
                 exclusiveGroup: tabPositionGroup
                 id:third
                Layout.alignment: Qt.AlignLeft
                 Layout.leftMargin: 50
             }
             RadioButton {
                 text: "5s"
                 exclusiveGroup: tabPositionGroup
                  id:four
                  Layout.alignment: Qt.AlignLeft
                 Layout.leftMargin: 50
             }
             RadioButton {
                 text: "10s"
                 exclusiveGroup: tabPositionGroup
                  id:five
                  Layout.alignment: Qt.AlignLeft
                 Layout.leftMargin: 50
             }
         }
     }
//   Label{
//       anchors.top: groupBox.bottom
//     anchors.topMargin:  15
//       text: tabPositionGroup.current.value
//   }
       Text{
          id:countShow
       // anchors.horizontalCenter:countShow.horizontalCenter
        anchors.fill: parent
        anchors.margins: 50
       
          color:"blue"
          font.pixelSize:40
          width: 120
          height: 70
          text:"READY!"
       }
    Timer{
        id:countDown;
        interval: 1000;
        repeat: true;
        triggeredOnStart: true;

        onTriggered: {
            countShow.text = attrs.counter;
            attrs.counter -= 1;
            if(attrs.counter < 0 )
            {
                countDown.stop();
                countShow.text = "Fire Now!!";
                keyoff.start();
            }
        }
    }

       Button{
        id:startButton
        anchors.top:countShow.bottom
        anchors.topMargin:20
        anchors.horizontalCenter:countShow.horizontalCenter
        width: 200
        height: 150
       // font.pixelSize:30
        text:"Start"
        
         onClicked: {
            //qmlrediscontrol.value=10;
            qmlSignal("uvc_out","1")
            attrs.counter = 1;
            countDown.start();
           
            console.log("---"+ tabPositionGroup.current.text )
            if(tabPositionGroup.current.text==="1s")
            {
               attrs.timer_off=10
            }else if(tabPositionGroup.current.text==="1.5s"){
               attrs.timer_off=15
            }else if(tabPositionGroup.current.text==="2s"){
               attrs.timer_off=20
            }else if(tabPositionGroup.current.text==="5s"){
               attrs.timer_off=50
            }else if(tabPositionGroup.current.text==="10s"){
               attrs.timer_off=100
            }
        }
       }
       

    }
 Timer{
        id:keyoff;
        interval: 100;
        repeat: true;
        triggeredOnStart: true;
        onTriggered: {
            
            attrs.timer_off -= 1;
            if(attrs.timer_off < 0 )
            {
            //    redisInterface1.insertKey("uvc_out","0")
                qmlSignal("uvc_out","0")
                keyoff.stop();
                countShow.text = "Finsh!!";
            }
        }
    }
    Image {
        id: chart
        x: 242
        y: 836
 //       source: "maps/chart01.png"
    }

    Timeline {
        id: timeline
        endFrame: 1000
        enabled: true
        startFrame: 0

        KeyframeGroup {
            target: chart
            property: "y"
            Keyframe {
                value: 836
                frame: 0
            }

            Keyframe {
                easing.bezierCurve: [0.39, 0.575, 0.552, 0.809, 1, 1]
                value: 376
                frame: 1000
            }
        }
    }
}
