#include "file.h"
#include "mainwindow.h"
#include "serialportreader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filePath = "conf.json"; // Default JSON file path

    // If a JSON file path is provided in the command-line arguments, use that path
    if (argc > 1) {
        filePath = QString(argv[1]);
    }

    if (!fileExists(filePath)) {
        return -1; // Exit the program with an error code
    }

    SerialPortReader serialPortReader;
    if (serialPortReader.readConfigFromFile(filePath)) {
        if (serialPortReader.openSerialPort()) {
            qDebug() << "Serial port opened successfully!";
        } else {
            qWarning() << "Failed to open serial port!";
        }
    } else {
        qWarning() << "Failed to read configuration from JSON file!";
    }

    MainWindow w;
    w.setConfigFilePath(filePath);
    w.setSerialPortReader(&serialPortReader);
    w.show();
    return a.exec();
}
