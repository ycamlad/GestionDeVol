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
AjouterUtilisateur::AjouterUtilisateur(DatabaseManager &p_db,const Aeroport&p_aero,QWidget *parent) :
        QDialog(parent), ui(new Ui::AjouterUtilisateur), m_aeroport(p_aero), m_db(p_db) {
    ui->setupUi(this);

    m_db.connect();
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
    //while(!estNomValide(ui->lineEdiNutilisateur->text().toStdString())){
        if(!estNomValide(ui->lineEdiNutilisateur->text().toStdString())){
            QMessageBox::warning(this, "Erreur", "Nom d'utilisateur invalide");
            return;
        }
    //}
}





