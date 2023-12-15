#include "backendmodel.h"

BackendModel::BackendModel(QObject *parent)
    : QObject(parent), m_count(0) {
    initializeDatabase();

    QSqlQuery query;
    if (query.exec("SELECT count FROM CountTable WHERE id = 1") && query.next()) {
        m_count = query.value(0).toInt();
    } else {
        qDebug() << "Error loading count from database:" << query.lastError();
    }
}

int BackendModel::getCount() const {
    return m_count;
}

void BackendModel::increment()
{
    m_count++;
    emit countChanged();

    QSqlQuery query;
    query.prepare("UPDATE CountTable SET count = :count WHERE id = 1");
    query.bindValue(":count", m_count);
    if (!query.exec()) {
        qDebug() << "Error updating count in database:" << query.lastError();
    }
}

void BackendModel::initializeDatabase()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString folderPath = documentsPath + "/ButtonIncrement";
    QDir dir(folderPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString databasePath = dir.filePath("countDatabase.db");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        qDebug() << "Error: Connection with database failed";
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS CountTable (id INTEGER PRIMARY KEY, count INTEGER)")) {
        qDebug() << "Failed to create table:" << query.lastError();
    }

    if (!query.exec("SELECT count FROM CountTable WHERE id = 1")) {
        qDebug() << "Failed to query table:" << query.lastError();
    }
    if (!query.next()) {
        if (!query.exec("INSERT INTO CountTable (id, count) VALUES (1, 0)")) {
            qDebug() << "Failed to insert initial value:" << query.lastError();
        }
    }
}

