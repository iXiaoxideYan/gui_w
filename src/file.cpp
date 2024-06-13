#include "file.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>


void writeCSV(QFile &file, QString data){
    if(file.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream out(&file);
        out << data;
    }
    file.close();
}

void writeCSV(QFile &file, QStringList data){
    if(file.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream out(&file);
        foreach(QString str, data){
            out << str << "\t";
        }
        out << "\n";
        out.flush();
    }
    file.close();
}

bool saveListToCSV(const QList<QByteArray> &dataList, const QString &filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    for (const QByteArray &value : dataList) {
        out << value;
    }

    file.close();
    return true;
}

bool createDirectory(const QString &dirPath) {
    QDir dir;
    if (dir.exists(dirPath)) {
        return true;
    }
    return dir.mkpath(dirPath);
}

bool checkDir(QString dirPath){
    return createDirectory(dirPath);
}

void saveCSV(QString filePth, QString data){
    checkFile(filePth);
    QFile myFile(filePth);
    writeCSV(myFile, data);
}

bool createFile(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.close();
        return true;
    }
    return false;
}

bool fileExists(const QString &filePath) {
    QFile file(filePath);
    return file.exists();
}

bool checkFile(const QString &filePath) {
    if (fileExists(filePath)) {
        qDebug() << "File exists:" << filePath;
        return true;
    }

    if (createFile(filePath)) {
        qDebug() << "File created successfully:" << filePath;
        return true;
    } else {
        qWarning() << "Failed to create file:" << filePath;
        return false;
    }
}

QVector<double> readFileData(const QString &fileName){
    QVector<double> data;

    // Open the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return data; // Return an empty QVector if the file cannot be opened

    // Read file contents
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        double value = line.toDouble();
        data.push_back(value); // Add the read value to the QVector
    }
    file.close(); // Close the file

    return data;
}

