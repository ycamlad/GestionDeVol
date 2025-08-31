#include "AjouterUtilisateur.h"
#include "ui_AjouterUtilisateur.h"
#include "QSqlQuery"
#include "QMessageBox"
#include "DataBaseException.h"
#include "vector"
#include "validationFormat.h"

using namespace util;
AjouterUtilisateur::AjouterUtilisateur(const Aeroport&p_aero,std::vector<Utilisateur>&p_utililsateur,QWidget *parent) :
        QDialog(parent), ui(new Ui::AjouterUtilisateur), m_aeroport(p_aero),m_utilisateurs(p_utililsateur){
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
    while(reqNomUtilisateur().isEmpty()||reqNom().isEmpty()||reqPrenom().isEmpty()||reqMotDePasse().isEmpty()||!estNomDisponible()){

        if(reqNom().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Nom vide");
        }
        if(reqPrenom().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Prenom vide");
        }
        if(reqNomUtilisateur().isEmpty()){
            QMessageBox::warning(this, "Erreur", "Nom d'utilisateur vide");
        }
        if(!estNomDisponible()){
            QMessageBox::warning(this, "Erreur", "ce nom d'utilisateur existe deja");
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
    return upper[0].toUpper();
}

QString AjouterUtilisateur::reqPrenom() {
    QString upper = ui->lineEdiPrenom->text();
    return upper[0].toUpper();
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

bool AjouterUtilisateur::estNomDisponible(){
    for(auto &e: m_utilisateurs){
        if(e.nomUtilisateur==reqNomUtilisateur()) return false;
    }
    return true;
}

void AjouterUtilisateur::slotGenererNomUtilisateur() {
    QString prenom = ui->lineEdiPrenom->text();
    QString nom = ui->lineEdiNom->text();

    if(!(reqNom().isEmpty()&&reqPrenom().isEmpty())){
        ui->lineEditNomUtilisateur->setText((prenom[0]+nom).toLower());
    }
}







