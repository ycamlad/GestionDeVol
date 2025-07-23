#include "databasemanager.h"
#include "ContratException.h"
#include <QSqlRecord>


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
    PRECONDITION(parent!=nullptr)
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
        db.setDatabaseName(dbName);
    }

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError();
        return false;
    }

    qDebug() << "Database connected.";
    return true;
}

/**
 * \brief Requete pour la creation d'un utilisateur dans la table utilisateur
 * \param[in]name Une chaine représentant le nom de l'utilisateur
 * \return Une valeur boolean représentant le success ou non success de l'operation
 * **/
bool DatabaseManager::inserertUtilisateur(const QString &p_nom,
                                 const QString &p_nomAeroport,
                                 const QString &p_role,
                                 const QString &p_motDePass,
                                 bool p_statut)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (Nom,NAeroport,Role,Pass,Statut) VALUES (:nom,:na,:role,:pass,:stat)");
    query.bindValue(":nom", p_nom);
    query.bindValue(":na",p_nomAeroport);
    query.bindValue(":role",p_role);
    query.bindValue(":pass",p_motDePass);
    query.bindValue(":stat",p_statut);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError();
        return false;
    }

    return true;
}
/**
 * \brief Requete pour cree une liste des utilisateurs
 * \return Une liste des utilisateurs dans la base de donnee
 * **/
QList<QPair<int, QString>> DatabaseManager::reqUtilisateurs()
{
    QList<QPair<int, QString>> users;
    QSqlQuery query("SELECT ID, Nom FROM users");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        users.append(qMakePair(id, name));
    }

    return users;
}

QList<QPair<int, QVector<QVector<QString>>>> DatabaseManager::reqVols(const QString& p_role, int p_uid=0)
{
    PRECONDITION(!p_role.isEmpty())
    PRECONDITION(p_uid>=0)

    QList<QPair<int, QVector<QVector<QString>>>> Vols;

    QVector<QVector<QString>> depart;
    QVector<QVector<QString>> arrivee;

    QSqlQuery query;

    // Role-based filtering
    if (p_role == "Admin") {
        query.prepare("SELECT NumVol, TypeVol, Compagnie, Heure, Ville, HEmbq, PNum, Statut FROM Vols");
    } else {
        query.prepare("SELECT NumVol, TypeVol, Compagnie, Heure, Ville, HEmbq, PNum, Statut "
                      "FROM Vols WHERE UID = :uid");
        query.bindValue(":uid", p_uid);
    }

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return Vols;
    }

    while (query.next()) {
        int typeVol = query.value(1).toInt();

        QVector<QString> row;
        for (int i = 0; i < query.record().count(); ++i) {
            QVariant val = query.value(i);
            if (val.isNull() || val.toString().trimmed().isEmpty()) {
                row.clear();
                break;
            }
            row.append(val.toString());
        }

        if (row.isEmpty()) continue;

        if (typeVol == 0)
            depart.append(row);
        else if (typeVol == 1)
            arrivee.append(row);
    }

    if (!depart.isEmpty())
        Vols.append(qMakePair(0, depart));
    if (!arrivee.isEmpty())
        Vols.append(qMakePair(1, arrivee));

    return Vols;
}
