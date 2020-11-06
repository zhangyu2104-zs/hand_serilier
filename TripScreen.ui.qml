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
import QmlThread 1.0

Item {
    id: tripScreen
    width: Constants.width
    height: Constants.height
    property alias currentFrame: timeline.currentFrame


  Connections{
    target:qmlthread
   onDataChanged:{
            var tempdata = qmlthread.m_data
           // countShow.text = tempdata.toString();
           tempatureleft.text = tempdata["temp"].toFixed(2);
           range_left.text = tempdata["infrared_left"];
           
           console.log("device temp=="+tempdata["temp"]+"--infrared_left=="+tempdata["infrared_left"])
    }
   }
   
   QmlThread{
    id:qmlthread
   }
    GridLayout {
        x: 44
        y: 75
        width: 728
        height: 147
        columnSpacing: 1
        rows: 2
        columns: 2

        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("距离1")
            font.pixelSize: 48
        }

        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("距离2")
            font.pixelSize: 48
        }

        CustomLabel {
            id:range_left
            color: "#ffffff"
            text: (Backend.metricSystem ? "148.8" : "92.5")

            font.bold: true

            font.pixelSize: 48
        }

        CustomLabel {
            color: "#ffffff"
            text: (Backend.metricSystem ? "18.9" : "11.8")

            font.bold: true
            font.pixelSize: 48
        }
    }

    GridLayout {
        x: 36
        y: 228
        width: 728
        height: 147
        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("温度1")
            font.pixelSize: 48
        }

        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("温度2")
            font.pixelSize: 48
        }

        CustomLabel {
            id:tempatureleft
            color: "#ffffff"
            text: (Backend.metricSystem ? "148.8" : "92.5")
            font.pixelSize: 48
            font.bold: true
        }

        CustomLabel {
            color: "#ffffff"
            text: (Backend.metricSystem ? "18.9" : "11.8")
            font.pixelSize: 48
            font.bold: true
        }
        columns: 2
        columnSpacing: 1
        rows: 2
    }

    GridLayout {
        x: 36
        y: 401
        width: 736
        height: 147
        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("电压1")
            font.pixelSize: 48
        }

        CustomLabel {
            color: "#9d9d9d"
            text: qsTr("保留")
            font.pixelSize: 48
        }

        CustomLabel {
            color: "#ffffff"
            text: (Backend.metricSystem ? "148.8" : "92.5")
            font.pixelSize: 48
            font.bold: true
        }

        CustomLabel {
            color: "#ffffff"
            text: (Backend.metricSystem ? "18.9" : "11.8")
            font.pixelSize: 48
            font.bold: true
        }
        columns: 2
        columnSpacing: 1
        rows: 2
    }

    ColumnLayout {
        id: col
        width: 75
        height: 403
        anchors.verticalCenterOffset: -9
        anchors.horizontalCenterOffset: -8
        spacing: 20
        //        anchors.fill: parent
        anchors.centerIn: parent

        Rectangle {
            id: rec_green
            width: 50
            height: 50
            radius: width / 2
            color: "green"
            border.color: Qt.darker(color)
        }
        Rectangle {
            id: rec_yellow
            width: 50
            height: 50
            radius: width / 2
            color: "yellow"
            border.color: Qt.darker(color)
        }
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

    CustomLabel {
        id: customLabel
        x: 590
        y: 165
        color: "#9d9d9d"
        text: qsTr("按钮状态")
        font.pixelSize: 48
    }

    CustomLabel {
        id: customLabel1
        x: 599
        y: 342
        color: "#9d9d9d"
        text: qsTr("UVC状态")
        font.pixelSize: 48
    }
}
