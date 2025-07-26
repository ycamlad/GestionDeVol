//
// Created by chris on 7/24/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved

#include <QMessageBox>
#include "Login.h"
#include "ui_Login.h"
#include "FenetrePrincipal.h"
#include "databasemanager.h"


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
    QString id = "";
    QString role="";
    QString naero="";

    QSqlQuery query;
    query.prepare("SELECT ID,Role,NAeroport FROM Utilisateurs WHERE Nom=:nom AND  Pass=:pass AND  Statut=0");
    query.bindValue(":nom",nom);
    query.bindValue(":pass",pass);

    if(!query.exec())  {
        QMessageBox::warning(this,"Erreur","Mots de passe ou/et nom d'utilisateur invalide");
        return;
    }
        if(query.next()) {

            auto *f = new FenetrePrincipal(db,query.value("ID").toString(),
                                           query.value("Role").toString(),
                                           query.value("NAeroport").toString());



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
            QMessageBox::critical(this,"Erreur",query.lastError().text());

        }
//
//    auto *f = new FenetrePrincipal(db,id,role,naero);
//
//
//
//    f->setWindowIcon(icon);
//    f->setFixedHeight(775);
//    f->setFixedWidth(1018);
//    f->setAutoFillBackground(true);
//
//    QPalette palette;
//    palette.setBrush(f->backgroundRole(),
//                     QBrush(pixmap.scaled(f->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
//    f->setPalette(palette);
//
//    f->show();
//
//    this->hide();


}

