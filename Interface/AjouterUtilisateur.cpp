//
// Created by chris on 7/27/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AjouterUtilisateur.h" resolved

#include "AjouterUtilisateur.h"
#include "ui_AjouterUtilisateur.h"
#include "QSqlQuery"
#include "QMessageBox"
#include "DataBaseException.h"
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
    while(reqNomUtilisateur().isEmpty()||reqNom().isEmpty()||reqPrenom().isEmpty()||reqMotDePasse().isEmpty()){

        if(reqNom().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Nom vide");
        }
        if(reqPrenom().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Prenom vide");
        }
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

QString AjouterUtilisateur::reqNom() {
    QString upper =ui->lineEdiNom->text();
    upper[0].toUpper();
    return upper;
}

QString AjouterUtilisateur::reqPrenom() {
    QString upper = ui->lineEdiPrenom->text();
    upper[0].toUpper();
    return upper;
}

QString AjouterUtilisateur::reqNomUtilisateur() {
    return ui->lineEditNomUtilisateur->text();

}

QString AjouterUtilisateur::reqAeroport() {
    return ui->comboBoxVols->currentText();
}

QString AjouterUtilisateur::reqRole() {
    return ui->comboBoxRole->currentText();
}

QString AjouterUtilisateur::reqMotDePasse() {
    return ui->lineEditMotDepasse->text();
}

void AjouterUtilisateur::slotGenererNomUtilisateur() {
    QString prenom = ui->lineEdiPrenom->text();
    QString nom = ui->lineEdiNom->text();

    if(!(reqNom().isEmpty()&&reqPrenom().isEmpty())){
        ui->lineEditNomUtilisateur->setText((nom[0]+prenom).toLower());
    }
    return;
}







