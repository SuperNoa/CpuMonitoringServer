import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15

Item {
    width:  Screen.width  * 0.5
    height: Screen.height * 0.5

    visible: true

    ChartView {
        id: chartView

        title: "CPU Temperature"

        anchors.fill: parent

        legend.alignment: Qt.AlignTop

        // Series animation is enabled in the chart
        animationOptions: ChartView.SeriesAnimations

        antialiasing: true

        axes: [
            AbstractAxis  { visible: true; color: "gray"; titleText: "X"; orientation: Qt.Horizontal  },
            AbstractAxis  { visible: true; color: "gray"; titleText: "Y"; orientation: Qt.Vertical  }
        ]

//        createSeries(ChartView.SeriesTypeLine, speedsXml.get(currentIndex).driver);

//        axisY().min = 0;
//        axisY().max = 250;
//        axisY().tickCount = 6;
//        axisY().titleText = "speed (kph)";
//        axisX().titleText = "speed trap";
//        axisX().labelFormat = "%.0f";
    }

}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff"}D{i:1}
}
##^##*/
