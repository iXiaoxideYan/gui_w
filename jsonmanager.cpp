#include "jsonmanager.h"
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>

JsonManager::JsonManager(QObject *parent) : QObject(parent) {}

JsonManager::JsonManager(const QString &filePath, QObject *parent)
    : QObject(parent), m_filePath(filePath) {}

bool JsonManager::readJsonFile() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file:" << file.errorString();
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError error;
    m_jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Failed to parse JSON:" << error.errorString();
        return false;
    }

    return true;
}

bool JsonManager::writeJsonFile() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file for writing:" << file.errorString();
        return false;
    }

    QByteArray jsonData = m_jsonDoc.toJson();
    qint64 bytesWritten = file.write(jsonData);
    file.close();

    if (bytesWritten == -1) {
        qDebug() << "Failed to write JSON data to file:" << file.errorString();
        return false;
    }

    return true;
}

QVariant JsonManager::getProperty(const QString &propertyName) const {
    if (m_jsonDoc.isNull() || !m_jsonDoc.isObject()) {
        qDebug() << "JSON document is not valid";
        return QVariant();
    }

    QJsonObject jsonObject = m_jsonDoc.object();
    if (!jsonObject.contains(propertyName)) {
        qDebug() << "Property" << propertyName << "not found in JSON document";
        return QVariant();
    }

    return jsonObject[propertyName].toVariant();
}

void JsonManager::setJsonObject(const QJsonObject &jsonObject) {
    m_jsonDoc = QJsonDocument(jsonObject);
}

QJsonObject JsonManager::jsonObject() const
{
    return m_jsonDoc.object();
}

bool JsonManager::isJsonFileEmpty(QVariantMap config) const
{
    if (config.isEmpty()) {
        qWarning() << "Configuration data is empty in JSON file:" << this->m_filePath;
        return false;
    }
    return true;
}
