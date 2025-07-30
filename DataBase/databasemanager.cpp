#include "databasemanager.h"
#include "ContratException.h"
#include "DataBaseException.h"
#include <QSqlRecord>
#include "QSqlQueryModel"
#include "Depart.h"
#include "Arrivee.h"


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
    qDebug() << "DB file in use:" << db.databaseName();

    return true;
}

void DatabaseManager::ajouterVol(const Vol& vol, const std::string& codeAeroport, int uid) {
    QSqlQuery query;

    query.bindValue(":na", QString::fromStdString(codeAeroport));
    query.bindValue(":id", uid);
    query.bindValue(":num", QString::fromStdString(vol.reqNumero()));
    query.bindValue(":comp", QString::fromStdString(vol.reqCompagnie()));
    query.bindValue(":heure", QString::fromStdString(vol.reqHeure()));
    query.bindValue(":ville", QString::fromStdString(vol.reqVille()));
    query.bindValue(":type", vol.estDepart() ? 0 : 1);

    if (vol.estDepart()) {
        const Depart& d = dynamic_cast<const Depart&>(vol);
        query.prepare(R"(
            INSERT INTO Vols (NomAeroport, UID, NumeroVol, TypeVol, Compagnie, Heure, Ville, HeureEmbarqument, NumeroPorte)
            VALUES(:na, :id, :num, :type, :comp, :heure, :ville, :embq, :porte)
        )");
        query.bindValue(":embq", QString::fromStdString(d.reqHeureEmbarquement()));
        query.bindValue(":porte", QString::fromStdString(d.reqPorteEmbarquement()));
    } else {
        const Arrivee& a = dynamic_cast<const Arrivee&>(vol);
        query.prepare(R"(
            INSERT INTO Vols (NomAeroport, UID, NumeroVol, TypeVol, Compagnie, Heure, Ville, Statut)
            VALUES(:na, :id, :num, :type, :comp, :heure, :ville, :Statut)
        )");

        int statut = 0;
        const std::string& s = a.reqStatut();
        if (s == " Atterri ") statut = 1;
        else if (s == " Retardé ") statut = 2;
        else if (s == "À l’heure") statut = 3;
        query.bindValue(":Statut", statut);
    }

    if (!query.exec()) {
        throw DatabaseException("Insertion invalide:", query.lastError().text());
    }
}


/**
 * \brief Requete pour la creation d'un utilisateur dans la table utilisateur
 * \param[in]name Une chaine représentant le nom de l'utilisateur
 * \return Une valeur boolean représentant le success ou non success de l'operation
 * **/
bool DatabaseManager::inserertUtilisateur(
        const QString &p_nom,
        const QString &p_prenom,
        const QString &p_nomUtilisateur,
        const QString &p_nomAeroport,
        const QString &p_role,
        const QString &p_motDePass,
        int p_statut
        )
{

    QSqlQuery query;
    query.prepare(
            "INSERT INTO Utilisateurs(Nom,Prenom,NomUtilisateur,NomAeroport,Role,Pass,Statut) VALUES(:nom,:pnom,:nomu,:aero,:role,:pass,:statut)");
    query.bindValue(":nom", p_nom);
    query.bindValue(":pnom", p_prenom);
    query.bindValue(":nomu", p_nomUtilisateur);
    query.bindValue(":aero", p_nomAeroport);
    query.bindValue(":role", p_role);
    query.bindValue(":pass", p_motDePass);
    query.bindValue(":statut", p_statut);

    if (!query.exec()) throw DatabaseException("Insertion invalide:", query.lastError().text());

    return true;
}



void DatabaseManager::modifierVol(
        Aeroport& aeroport,
        const std::string& numero,
        const std::string& compagnie,
        const std::string& heure,
        const std::string& ville,
        const std::string& embq,
        const std::string& porte,
        const std::string& statutStr){


    QSqlQuery query;
    int statut = -1;
    int type = -1;

    if (statutStr == " Atterri ") statut = 1;
    else if (statutStr == " Retardé ") statut = 2;
    else if (statutStr == "À l’heure") statut = 3;

    const QString numVol = QString::fromStdString(numero);

    for (auto& vol : aeroport.reqVols()) {
        if (numero == vol->reqNumero()) {

            if (vol->estDepart()) {
                type = 0;
                query.prepare(R"(
                    UPDATE Vols
                    SET TypeVol = :type,
                        Compagnie = :comp,
                        Heure = :heure,
                        Ville = :ville,
                        HeureEmbarqument = :embq,
                        NumeroPorte = :porte
                    WHERE NumeroVol = :num
                )");
                query.bindValue(":type", type);
                query.bindValue(":comp", QString::fromStdString(compagnie));
                query.bindValue(":heure", QString::fromStdString(heure));
                query.bindValue(":ville", QString::fromStdString(ville));
                query.bindValue(":embq", QString::fromStdString(embq));
                query.bindValue(":porte", QString::fromStdString(porte));
                query.bindValue(":num", numVol);
            }
            else {
                type = 1;
                query.prepare(R"(
                    UPDATE Vols
                    SET TypeVol = :type,
                        Compagnie = :comp,
                        Heure = :heure,
                        Ville = :ville,
                        Statut = :statut
                    WHERE NumeroVol = :num
                )");
                query.bindValue(":type", type);
                query.bindValue(":comp", QString::fromStdString(compagnie));
                query.bindValue(":heure", QString::fromStdString(heure));
                query.bindValue(":ville", QString::fromStdString(ville));
                query.bindValue(":statut", statut);
                query.bindValue(":num", numVol);
            }

            if (!query.exec()) {
                throw DatabaseException("Mise à jour invalide :", query.lastError().text());
            }

            break;
        }
    }
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



