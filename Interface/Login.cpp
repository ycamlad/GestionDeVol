//
// Created by chris on 7/24/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved

#include <QMessageBox>
#include "Login.h"
#include "ui_Login.h"
#include "FenetrePrincipal.h"
#include "databasemanager.h"
#include "QSqlRecord"


Login::Login(QWidget *parent) :
        QWidget(parent), ui(new Ui::Login) {
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::slotConfirmer() {
    DatabaseManager &db(DatabaseManager::instance());
    db.connect();
    QPixmap pixmap(":/Resources/background.png");
    QIcon icon(":/Resources/iconmonstr-airport-10-240.png");

    QString nom =ui->lineEditNom->text();
    QString pass=ui->lineEditPass->text();

    QSqlQuery query;
    query.prepare("SELECT ID,NomAeroport,Role FROM Utilisateurs WHERE NomUtilisateur=:nom AND Pass=:pass AND Statut=0");
    query.bindValue(":nom",nom);
    query.bindValue(":pass",pass);

    if(!query.exec())  {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête:\n" + query.lastError().text());        return;
    }
    if(query.next()){
    //if(query.first()){
        QString id = query.value("ID").toString();
        QString role = query.value("Role").toString();
        QString aeroport = query.value("NomAeroport").toString();
        for (int i = 0; i < query.record().count(); ++i) {
            qDebug() << "Column" << i << ":" << query.record().fieldName(i);
        }
        auto *f = new FenetrePrincipal(db, id, role, aeroport);
        f->setWindowIcon(icon);
        f->setFixedHeight(775);
        f->setFixedWidth(1018);
        f->setAutoFillBackground(true);

        QPalette palette;
        palette.setBrush(f->backgroundRole(),
                         QBrush(pixmap.scaled(f->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        f->setPalette(palette);
        f->show();
        this->hide();
    }else{
        QMessageBox::warning(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect.");
        return;
    }
}

