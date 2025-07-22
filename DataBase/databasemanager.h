//
// Created by chris on 7/22/2025.
//

#ifndef GESTION_DE_VOL_DATABASEMANAGER_H
#define GESTION_DE_VOL_DATABASEMANAGER_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

class DatabaseManager : public QObject
{
Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool connect(const QString &dbName);
    bool createTables();
    bool insertUser(const QString &name);
    QList<QPair<int, QString>> getUsers();

private:
    QSqlDatabase db;
};



#endif //GESTION_DE_VOL_DATABASEMANAGER_H
