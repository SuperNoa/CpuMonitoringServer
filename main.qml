import QtQuick
import QtQuick.Window
import QtCharts
import QtQuick.Controls

Item {
    id: root

    width:  Screen.width  * 0.5
    height: Screen.height * 0.5

    visible: true

    property int maxSamplesToShow: 100
    property bool tempOverTheshold: false

    Connections {
        target: _temperatureModel

        property int samples: 0

        function onCpuTemperatureChanged(newCpuTemperatureChanged) {

            console.info("Cpu load " + newCpuTemperatureChanged + "%")

            var lineSeries = chartView.series( "cpuLoadSeries" );

            // If not exist create the first series
            if (!lineSeries) {

                lineSeries = chartView.createSeries(ChartView.SeriesTypeLine, "cpuLoadSeries");

                    // samples
                    chartView.axisX().min = 0;
                    chartView.axisX().max = 100;
                    chartView.axisX().tickCount = 5;
                    chartView.axisX().titleText = "Samples";

                    // cpu load percentage
                    chartView.axisY().min = 0;
                    chartView.axisY().max = 100;
                    chartView.axisY().tickCount = 5;
                    chartView.axisY().titleText = "CPU load %";
            }
            else {

                if( samples >= root.maxSamplesToShow ) {

                    // cpu load percentage
                    chartView.axisX().min = chartView.axisX().min + 1;
                    chartView.axisX().max = chartView.axisX().max + 1;
                }
            }

            samples++;

            lineSeries.append(samples, newCpuTemperatureChanged);


            if( newCpuTemperatureChanged > thesholdSlider.value ) {

                root.tempOverTheshold = true
            }
            else {
                root.tempOverTheshold = false
            }


//            if( samples >= root.maxSamplesToShow ) {

//                //samples = 0

//                //chartView.removeSeries("receivedSamples")
//                //samplesAxis.max = samples
//                //root.maxSamplesToShow = samples

//                print("samples " + samples)

//                lineSeries.axisX().min = 0;
//                lineSeries.axisX().max = samples;
//            }
//            else {

//                samples++;

//                if( newCpuTemperatureChanged > thesholdSlider.value ) {

//                    root.tempOverTheshold = true
//                }
//                else {

//                    root.tempOverTheshold = false
//                }
//            }

//            lineSeries.append(samples, newCpuTemperatureChanged);
        }
    }

    ChartView {
        id: chartView

        title: "CPU Load"

//        onSeriesRemoved: {

//            createSeries(ChartView.SeriesTypeLine, "receivedSamples", samplesAxis, cpuLoadAxis)
//        }

        width:  parent.width  * 0.7
        height: parent.height * 0.7

        anchors.top: root.top
        anchors.horizontalCenter: parent.horizontalCenter

        legend.alignment: Qt.AlignTop

        // Series animation is enabled in the chart
        animationOptions: ChartView.SeriesAnimations

        antialiasing: true

//        axes: [
//            // @disable-check M300
//            ValueAxis {
//                id: samplesAxis;

//                min: 0;
//                max: root.maxSamplesToShow;
//                tickCount: 1;
//                titleText: "Samples";
//            },

//            // @disable-check M300
//            ValueAxis {
//                id: cpuLoadAxis;

//                min: 0;
//                max: 100;
//                tickCount: 1;
//                titleText: "CPU load %";
//            }
//        ]

//        LineSeries {
//            id: lineSeries

//            axisX: samplesAxis
//            axisY: cpuLoadAxis

//            name: "receivedSamples"
//        }
    }

    Timer {
        id: timer

        interval: 1000
        repeat: true
        triggeredOnStart: true
        running: false

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
        id: allarmText

        text: {

            ( (root.tempOverTheshold) ? qsTr("ALLERT!!! ") : qsTr("") ) +
            qsTr("The CPU load is " + _temperatureModel.cpuTemperature) + "%." +
            qsTr(" It is ") +
            ( (root.tempOverTheshold) ? qsTr("over") : qsTr("under") ) +
            qsTr(" the theshold of ") + thesholdSlider.value + "%."
        }

        color: (root.tempOverTheshold) ? "red" : "green"

        anchors.top: chartView.bottom
        anchors.topMargin: (root.height - chartView.height) * 0.25

        anchors.horizontalCenter: parent.horizontalCenter
    }

    Slider {
        id: thesholdSlider

        anchors.top: allarmText.bottom
        anchors.topMargin: (root.height - chartView.height) * 0.25
        anchors.horizontalCenter: parent.horizontalCenter

        value: 65
        stepSize: 5

        onValueChanged: {

        }

        from: 0
        to: 100
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff"}
}
##^##*/
