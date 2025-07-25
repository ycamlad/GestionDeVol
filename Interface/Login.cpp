//
// Created by chris on 7/24/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved

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
    auto *f = new FenetrePrincipal(db);
    //background.load()
    f->setWindowIcon(icon);
    f->setFixedHeight(775);
    f->setFixedWidth(1018);
    f->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(f->backgroundRole(),QBrush(pixmap.scaled(f->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
    f->setPalette(palette);
    f->show();
    this->hide();
}

