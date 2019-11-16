import QtQuick 2.0
import QtQuick.Window 2.0
import QMLogger 0.1

Window {
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("QMLog test");
    color: "black";

    QMLogger {
        id: logger;
        logFile: "/tmp/qmlogger.log";
        console: true;
        logLevel: "INFO";
        dateFormat: "yyyy-MM-dd hh:mm:ss";
        logFormat: "${DATETIME} [${LEVEL}] ${COMPONENT}: ${MESSAGE}";
        truncateFile: false;
        onLogError: {
            console.log("Could not log message: ", error);
        }
    }

    Rectangle {
        x: 16;
        y: 16;
        width: 256;
        height: 256;
        color: "red";
        MouseArea {
            anchors.fill: parent;
            onClicked: {
                logger.info("RedRectangle", "I've been clicked");
                logger.warn("RedRectangle", "This is a warn message");
                logger.error("RedRectangle", "this is an error message");
                logger.critical("RedRectangle", "This is a critical error message");

            }
            onReleased: {
                logger.debug("RedRectangle", "I've been released");
            }
        }
    }

    Rectangle {
        x: 128;
        y: 300;
        width: 480;
        height: 128;
        color: "yellow";
        MouseArea {
            anchors.fill: parent;
            onClicked: {
                logger.info("YellowRectangle", "I've been clicked");
            }
        }
    }
}
