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

    QSqlQuery query;
    query.prepare("SELECT ID,Role,NAeroport FROM Utilisateurs WHERE Nom=:nom AND WHERE Pass=:pass AND Statut=0");
    query.bindValue(":nom",nom);
    query.bindValue(":pass",pass);

    if(query.exec()){
        auto *f = new FenetrePrincipal(db,
                                       query.value(0).toString(),
                                       query.value(1).toString(),
                                       query.value(2).toString());
        f->setWindowIcon(icon);
        f->setFixedHeight(775);
        f->setFixedWidth(1018);
        f->setAutoFillBackground(true);

        QPalette palette;
        palette.setBrush(f->backgroundRole(),QBrush(pixmap.scaled(f->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        f->setPalette(palette);

        f->show();

        this->hide();
    }else{
        QMessageBox::warning(this,"Erreur","Mot de passe ou/et nom d'utilisateur invalide");
    }




}

