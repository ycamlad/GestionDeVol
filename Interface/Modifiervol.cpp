//
// Created by chris on 7/26/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ModifierVol.h" resolved

#include <iostream>
#include <memory>
#include "Modifiervol.h"
#include "ui_ModifierVol.h"
#include "validationFormat.h"
#include "QMessageBox"
#include "Depart.h"
#include "Arrivee.h"
#include "QDebug"


using namespace util;


ModifierVol::ModifierVol(const Aeroport& p_aero,QWidget *parent) :
        QDialog(parent), ui(new Ui::ModifierVol), m_aero(p_aero) {
    ui->setupUi(this);
    for(const auto & it : m_aero.reqVols()){
        ui->comboBoxVols->addItem(QString::fromStdString(it->reqNumero()));
    }
    connect(ui->comboBoxVols, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ModifierVol::refresh);

    ui->comboBoxVols->setCurrentIndex(0);
    refresh();

}

ModifierVol::~ModifierVol() {
    delete ui;
}



void ModifierVol::slotModifierVol() {


    while(!estNomValide(reqCompagnie())||
    !estFormat24HValide(reqHeure())||
    !estNomValide(reqVille())||
    !estFormat24HValide(reqEmbq())||
    !estPorteValide(reqPorte())||
    reqHeure()<reqEmbq()) {
        if (!estNomValide(reqCompagnie())) {
            QMessageBox::warning(this, "Erreur", "Nom de compagnie invalide");
        }
        if (!estFormat24HValide(reqHeure())) {
            QMessageBox::warning(this, "Erreur", "Heure de depart invalide");
        }
        if (!estNomValide(reqVille())) {
            QMessageBox::warning(this, "Erreur", "Nom de ville invalide");
        }
        if (!estFormat24HValide(reqEmbq())) {
            QMessageBox::warning(this, "Erreur", "Heure d'embarquement invalide");
        }
        if (reqHeure()<reqEmbq()) {
            QMessageBox::warning(this, "Erreur", "Heure d'embarquement superieur a heure de depart.");
        }
        if (!estPorteValide(reqPorte())) {
            QMessageBox::warning(this, "Erreur", "Code de porte invalide");
        }
        return;
    }


    Depart depart(ui->comboBoxVols->currentText().toStdString(),reqCompagnie(),reqHeure(),reqVille(),reqEmbq(),reqPorte());
    std::string s = reqCompagnie();
    Arrivee arrivee(ui->comboBoxVols->currentText().toStdString(),reqCompagnie(),reqHeure(),reqVille(),reqStatut());
    for(auto &e:m_aero.reqVols()){
         if(ui->comboBoxVols->currentText().toStdString()==e->reqNumero()){
             if(e->estDepart()) {
                 e = std::make_unique<Depart>(depart);
             }
             else{
                 e = std::make_unique<Arrivee>(arrivee);
             }
         }
    }

    accept();

}

std::string ModifierVol::reqNumero() const {
    return ui->comboBoxVols->currentText().toStdString();
}

std::string ModifierVol::reqVille() const {
    return ui->lineEditVille->text().toStdString();
}

std::string ModifierVol::reqCompagnie() const {
    return ui->lineEditCompagnie->text().toStdString();
}

std::string ModifierVol::reqHeure() const {
    return ui->lineEditHeure->text().toStdString();
}

std::string ModifierVol::reqEmbq() const {
    return ui->lineEditEmbq->text().toStdString();
}

std::string ModifierVol::reqPorte() const {
    return ui->lineEditPorte->text().toStdString();
}

std::string ModifierVol::reqStatut() const {
    return ui->comboBoxStatut->currentText().toStdString();
}


const Aeroport &ModifierVol::reqAero() const {
    return m_aero;
}

void ModifierVol::refresh() {
    QString selectedVol = ui->comboBoxVols->currentText();
    if (selectedVol.isEmpty())
        return;

    for (const auto& e : m_aero.reqVols()) {
        if (e->reqNumero() == selectedVol.toStdString()) {
            // Common fields
            ui->lineEditCompagnie->setText(QString::fromStdString(e->reqCompagnie()));
            ui->lineEditHeure->setText(QString::fromStdString(e->reqHeure()));
            ui->lineEditVille->setText(QString::fromStdString(e->reqVille()));

            if (e->estDepart()) {
                const Depart* d = dynamic_cast<Depart*>(e.get());
                if (d) {
                    ui->lineEditEmbq->setText(QString::fromStdString(d->reqHeureEmbarquement()));
                    ui->lineEditPorte->setText(QString::fromStdString(d->reqPorteEmbarquement()));
                    this->adjustSize();

                }
                departMode(true);
            } else {
                const Arrivee* a = dynamic_cast<Arrivee*>(e.get());
                if (a) {
                    ui->comboBoxStatut->setCurrentText(QString::fromStdString(a->reqStatut()));
                    this->adjustSize();

                }
                departMode(false);
            }
            break;
        }
    }
}

void ModifierVol::departMode(bool isDepart) {
    ui->lineEditEmbq->setVisible(isDepart);
    ui->lineEditPorte->setVisible(isDepart);
    ui->label_5->setVisible(isDepart);   // assuming you have QLabel* for each
    ui->label_6->setVisible(isDepart);

    ui->comboBoxStatut->setVisible(!isDepart);
    ui->label_8->setVisible(!isDepart);
}





