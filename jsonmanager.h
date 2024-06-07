#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QVariant>

class JsonManager : public QObject
{
    Q_OBJECT

public:
    explicit JsonManager(QObject *parent = nullptr);
    JsonManager(const QString &filePath, QObject *parent = nullptr);

    bool readJsonFile();
    bool writeJsonFile();
    QVariant getProperty(const QString &propertyName) const;

    void setJsonObject(const QJsonObject &jsonObject);

    QJsonObject jsonObject() const;

    bool isJsonFileEmpty(QVariantMap config) const;

private:
    QString m_filePath;
    QJsonDocument m_jsonDoc;
};

#endif // JSONMANAGER_H
