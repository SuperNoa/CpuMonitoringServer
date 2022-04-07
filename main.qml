import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15

Item {
    id: root

    width:  Screen.width  * 0.5
    height: Screen.height * 0.5

    visible: true

    property int theshold: 65
    property bool tempOverTheshold: false

    ChartView {
        id: chartView

        title: "CPU Temperature"

        //anchors.fill: parent
        width:  parent.width  * 0.7
        height: parent.height * 0.7
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        legend.alignment: Qt.AlignTop

        // Series animation is enabled in the chart
        animationOptions: ChartView.SeriesAnimations

        antialiasing: true

        axes: [
            // @disable-check M300
            ValueAxis {
                id: timeAxis;
                min: 0;
                max: 60;
                tickCount: 1;
                titleText: "time";
            },

            // @disable-check M300
            ValueAxis {
                id: tempAxis;
                min: 0;
                max: 150;
                tickCount: 1;
                titleText: "temperature";
            }
        ]

        LineSeries {
            id: lineSeries

            axisX: timeAxis
            axisY: tempAxis

            name: "temperatures"
        }
    }

    Timer {
        id: timer

        interval: 1000
        repeat: true
        triggeredOnStart: true
        running: true

        property int elapsedTime: 0
        property int temperature: 60

        function getRandomIntInclusive(min, max) {
            min = Math.ceil(min);
            max = Math.floor(max);

            //The maximum is inclusive and the minimum is inclusive
            return Math.floor(Math.random() * (max - min + 1) + min);
        }

        onTriggered: {

            print("At second " + elapsedTime + " CPU temperature is " + temperature)

            if( elapsedTime >= 60 ) {

                elapsedTime = 0

                //lineSeries.removeAllSeries()

                lineSeries.createSeries(ChartView.SeriesTypeLine, "temperatures", timeAxis, tempAxis)
            }
            else {

                temperature = getRandomIntInclusive(30, 90)
                elapsedTime++;

                if( temperature > root.theshold ) {

                    root.tempOverTheshold = true
                }
                else {

                    root.tempOverTheshold = false
                }
            }

            lineSeries.append(elapsedTime, temperature);
        }
    }

    Text {
        id: name

        text: {

            qsTr("The CPU temperature is " + timer.temperature) + " °C." +
            qsTr(" It is ") +
            ( (root.tempOverTheshold) ? qsTr("over") : qsTr("under") ) +
            qsTr(" the theshold of ") + root.theshold + " °C."
        }

        color: (root.tempOverTheshold) ? "red" : "green"

        anchors.top: chartView.bottom
        anchors.topMargin: (root.height - chartView.height) * 0.25

        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff"}D{i:1}
}
##^##*/
