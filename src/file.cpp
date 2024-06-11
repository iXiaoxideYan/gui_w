#include "file.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

/**
 * Writes data to a CSV file.
 *
 * @param file A reference to the QFile object representing the CSV file.
 * @param data The data to be written to the CSV file as a QString.
 * @return true if the write operation succeeds, false otherwise.
 */
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

/**
 * Checks if a directory exists at the specified path. If not, creates it.
 *
 * @param dirPath The path of the directory to check/create.
 * @return true if the directory exists or is successfully created, false otherwise.
 */
bool checkDir(QString dirPath){
    QDir dir(dirPath);

    // Check if the directory exists
    if (dir.exists()) {
        return true; // Directory already exists
    } else {
        // Attempt to create the directory
        if (dir.mkpath(dirPath)) {
            qDebug() << ">> Created directory:" << dirPath;
            return true;
        } else {
            qWarning() << "checkDir: Failed to create directory:" << dirPath;
            return false;
        }
    }
}

bool isCSVExists(QString filePath){
    QFile file(filePath);

    // Get the directory path of the file
    QFileInfo info(filePath);
    QString dirPath = info.absolutePath();

    // Check if the directory exists, create it if not
    if (!checkDir(dirPath)) {
        qWarning() << "isCSVExists: Failed to create directory" << dirPath;
        return false;
    }

    // Check if the file exists
    if (file.exists()) {
        qDebug(">> The file exits");
        return true;
    } else{
        // Attempt to create the file
        file.open(QIODevice::Append);
        file.close();
        qDebug() << ">> The file exists";
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
            qDebug() << ">> Created the file successfully";
            return true;
        } else {
            qWarning() << "isCSVExists: Failed to create the file";
            return false;
        }
    }
}

void saveCSV(QString filePth, QString data){
    isCSVExists(filePth);
    QFile myFile(filePth);
    writeCSV(myFile, data);
}

bool checkFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.exists()) {
        qWarning() << "File does not exist:" << filePath;
        return false;
    }
    return true;
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

