#include "databasemanager.h"

// Static instance getter
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

// Constructor
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}

// Destructor
DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

// Same methods as before
bool DatabaseManager::connect(const QString &dbName)
{
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

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL
        )
    )";

    if (!query.exec(createTable)) {
        qDebug() << "Failed to create table:" << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::insertUser(const QString &name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError();
        return false;
    }

    return true;
}

QList<QPair<int, QString>> DatabaseManager::getUsers()
{
    QList<QPair<int, QString>> users;
    QSqlQuery query("SELECT id, name FROM users");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        users.append(qMakePair(id, name));
    }

    return users;
}
