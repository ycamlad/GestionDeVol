#include "databasemanager.h"
#include "ContratException.h"
#include "DataBaseException.h"
#include <QSqlRecord>
#include "QSqlQueryModel"


// Static instance getter
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

/**
 * \brief Constructeur avec paramètre
 *        Construit un objet DatabaseManager avec un pointeur QObject.
 * \param[in] parent Un pointeur vers celui qui instancie l'objet
 * \pre parent ne doit pas etre NULL
 * **/
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}


/**
 *\brief Destructeur qui ferme la connection de la base de donnee.
 * **/
DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

/**
 * \brief Connection a la base de donner partager en parametre
 * \param[in] dbName Une chaine représentant la base de donnee
 * \pre dbName ne doit pas etre une chaine vide.
 * \return Une valeur boolean représentant le success ou non success de l'operation
 * **/
bool DatabaseManager::connect(const QString &dbName)
{
    PRECONDITION(!dbName.isEmpty())

    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Voldb.db");
    }

    if (!db.open())throw DatabaseException("La connection à la base de donnée est invalide:", "");

    QSqlQuery pragmaQuery;
    pragmaQuery.exec("PRAGMA foreign_keys = ON;");

    qDebug() << "Database connected.";
    return true;
}

/**
 * \brief Requete pour la creation d'un utilisateur dans la table utilisateur
 * \param[in]name Une chaine représentant le nom de l'utilisateur
 * \return Une valeur boolean représentant le success ou non success de l'operation
 * **/
bool DatabaseManager::inserertUtilisateur(
        const QString &p_nom,
        const QString &p_nomAeroport,
        const QString &p_role,
        const QString &p_motDePass,
        bool p_statut)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Utilisateurs (Nom,NAeroport,Role,Pass,Statut) VALUES (:nom,:na,:role,:pass,:stat)");
    query.bindValue(":nom", p_nom);
    query.bindValue(":na",p_nomAeroport);
    query.bindValue(":role",p_role);
    query.bindValue(":pass",p_motDePass);
    query.bindValue(":stat",p_statut);

    if (!query.exec()) throw DatabaseException("Insertion invalide:",query.lastError().text());

    return true;
}

/**
 * \brief Requete pour cree une liste des utilisateurs
 * \return Une liste des utilisateurs dans la base de donnee
 * **/
//QList<QPair<int, QString>> DatabaseManager::reqUtilisateurs()
//{
//    QList<QPair<int, QString>> users;
//    QSqlQuery query("SELECT ID, Nom FROM users");
//
//    if(!query.exec()) throw DatabaseException("Requete invalide:",query.lastError().text());
//
//    while (query.next()) {
//        int id = query.value(0).toInt();
//        QString name = query.value(1).toString();
//        users.append(qMakePair(id, name));
//    }
//
//    return users;
//}



