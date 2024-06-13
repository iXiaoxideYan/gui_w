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

bool saveListToCSV(const QList<QByteArray> &dataList, const QString &filePath);

/**
 * Checks if a CSV file exists at the specified file path.
 *
 * @param filePath The path of the CSV file to check.
 * @return true if the CSV file exists, false otherwise.
 */
// bool isCSVExists(QString filePath);

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
 * @brief Checks if the file exists at the specified path.
 *
 * @param filePath The path of the file to check.
 * @return true if the file exists, otherwise false.
 */
bool fileExists(const QString &filePath);

/**
 * @brief Creates a file at the specified path.
 *
 * @param filePath The path of the file to create.
 * @return true if the file was created successfully, otherwise false.
 */
bool createFile(const QString &filePath);

/**
 * @brief Creates a directory at the specified path.
 *
 * @param dirPath The path of the directory to create.
 * @return true if the directory was created successfully or already exists, otherwise false.
 */
bool createDirectory(const QString &dirPath);

/**
 * @brief Checks if the file exists and creates it if it doesn't.
 *
 * @param filePath The path of the file to check or create.
 * @return true if the file exists or was created successfully, otherwise false.
 */
bool checkFile(const QString &filePath);

/**
 * @brief Reads numeric data from a text file and stores it in a QVector<double>.
 *
 * @param fileName The path of the file to read.
 * @return A QVector<double> containing the read data. If the file cannot be opened
 * or read, an empty QVector<double> is returned.
 */
QVector<double> readFileData(const QString &fileName);

#endif
