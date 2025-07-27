//
// Created by chris on 7/27/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AjouterUtilisateur.h" resolved

#include "AjouterUtilisateur.h"
#include "ui_AjouterUtilisateur.h"


AjouterUtilisateur::AjouterUtilisateur(QWidget *parent) :
        QDialog(parent), ui(new Ui::AjouterUtilisateur) {
    ui->setupUi(this);
}

AjouterUtilisateur::~AjouterUtilisateur() {
    delete ui;
}
