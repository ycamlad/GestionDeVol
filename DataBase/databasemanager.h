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
#include "Vol.h"

using namespace aerien;
class DatabaseManager : public QObject
{
Q_OBJECT

public:
    static DatabaseManager& instance();

    // Delete copy/move constructors and assignment operators
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    DatabaseManager(DatabaseManager&&) = delete;
    DatabaseManager& operator=(DatabaseManager&&) = delete;

    bool connect(const QString &dbName="Voldb");
    bool inserertUtilisateur(const QString &p_nom,const QString &p_nomAeroport,const QString &p_role,const QString &p_motDePass,bool p_statut);
//    QList<QPair<int, QString>> reqUtilisateurs();
//    QList<QPair<int, QVector<QVector<QString>>>>reqVols(const QString& p_role,int p_uid=0);


private:
    explicit DatabaseManager(QObject *parent = nullptr);

        ~DatabaseManager();

    QSqlDatabase db;
};



#endif //GESTION_DE_VOL_DATABASEMANAGER_H
