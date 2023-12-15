#ifndef BACKENDMODEL_H
#define BACKENDMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>

class BackendModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ getCount NOTIFY countChanged)

public:
    explicit BackendModel(QObject *parent = nullptr);

    int getCount() const;

    Q_INVOKABLE void increment();

signals:
    void countChanged();

private:
    int m_count;
    void initializeDatabase();
};

#endif
