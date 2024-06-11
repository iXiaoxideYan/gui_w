#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <qstring.h>


/**
 * Writes data to a CSV file.
 *
 * @param file A reference to the QFile object representing the CSV file.
 * @param data The data to be written to the CSV file as a QString.
 */
void writeCSV(QFile &file, QString data);

/**
 * Writes data to a CSV file.
 *
 * @param file A reference to the QFile object representing the CSV file.
 * @param data The data to be written to the CSV file as a QStringList.
 */
void writeCSV(QFile &file, QStringList data);

/**
 * Checks if a CSV file exists at the specified file path.
 *
 * @param filePath The path of the CSV file to check.
 * @return true if the CSV file exists, false otherwise.
 */
bool isCSVExists(QString filePath);

/**
 * Checks if a directory exists at the specified path.
 *
 * @param dirPath The path of the directory to check.
 * @return true if the directory exists or is successfully created,
 * false otherwise.
 */
bool checkDir(QString dirPath);

/**
 * Saves data to a CSV file.
 *
 * @param filePath The file path where the CSV file will be saved.
 * @param data The data to be saved to the CSV file.
 */
void saveCSV(QString filePth, QString data);

/**
 * Checks if the file exists.
 *
 * @param filePath The path to thefile.
 * @return True if the file exists, false otherwise.
 */
bool checkFile(const QString &filePath);

/**
 * Reads data from a file and returns it as a QVector<double>.
 *
 * @param fileName The name of the file to read data from.
 * @return A QVector<double> containing the read data.
 */
QVector<double> readFileData(const QString &fileName);

#endif
