//
// Created by chris on 7/27/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AjouterUtilisateur.h" resolved

#include "AjouterUtilisateur.h"
#include "ui_AjouterUtilisateur.h"
#include "QSqlQuery"
#include "QMessageBox"
#include "DataBaseException.h"
#include "databasemanager.h"
#include "vector"
#include "validationFormat.h"

using namespace util;
AjouterUtilisateur::AjouterUtilisateur(const Aeroport&p_aero,QWidget *parent) :
        QDialog(parent), ui(new Ui::AjouterUtilisateur), m_aeroport(p_aero){
    ui->setupUi(this);

    QSqlQuery query;
    std::vector<QString> nomAeroport;
    query.prepare("SELECT * FROM Aeroport");
    if (!query.exec()) throw DatabaseException("Insertion invalide:",query.lastError().text());

    while(query.next()){
        nomAeroport.push_back(query.value("Nom").toString());
    }

    for(auto &e:nomAeroport) {
        ui->comboBoxVols->addItem(e);
    }

    ui->comboBoxRole->addItem("Admin");
    ui->comboBoxRole->addItem("Utilisateur");

}

AjouterUtilisateur::~AjouterUtilisateur() {
    delete ui;
}

void AjouterUtilisateur::slotAjouterUtilisateur() {
    while(reqNomUtilisateur().isEmpty()||reqMotDePasse().isEmpty()){
        if(reqNomUtilisateur().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Nom d'utilisateur vide");
        }
        if(reqMotDePasse().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Mot de passe vide ");
        }
        return;
    }
    accept();
}

QString AjouterUtilisateur::reqNomUtilisateur() {
    return ui->lineEdiNutilisateur->text();
}

QString AjouterUtilisateur::reqMotDePasse() {
    return ui->lineEditMotDepasse->text();
}

QString AjouterUtilisateur::reqAeroport() {
    return ui->comboBoxVols->currentText();
}

QString AjouterUtilisateur::reqRole() {
    return ui->comboBoxRole->currentText();
}

QString AjouterUtilisateur::reqNom() {
    return QString();
}

QString AjouterUtilisateur::reqPrenom() {
    return QString();
}




