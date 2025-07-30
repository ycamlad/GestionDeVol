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
#include <Aeroport.h>

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
    void ajouterVol(const Vol& vol, const std::string& codeAeroport, int uid);
    bool inserertUtilisateur(
            const QString &p_nom,
            const QString &p_prenom,
            const QString &p_nomUtilisateur,
            const QString &p_nomAeroport,
            const QString &p_role,
            const QString &p_motDePass,
            int p_statut=0
    );

    void modifierVol(
            Aeroport& aeroport,
            const std::string& numero,
            const std::string& compagnie,
            const std::string& heure,
            const std::string& ville,
            const std::string& embq,
            const std::string& porte,
            const std::string& statutStr);

private:
    explicit DatabaseManager(QObject *parent = nullptr);

        ~DatabaseManager();

    QSqlDatabase db;
};



#endif //GESTION_DE_VOL_DATABASEMANAGER_H
