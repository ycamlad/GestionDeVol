/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/qtFiles/form.cc to edit this template
 */

/*
 * File:   FenetrePrincipal.cpp
 * Author: etudiant
 *
 * Created on 5 juillet 2025, 12 h 09
 */

#include "FenetrePrincipal.h"
#include "AjouterDepart.h"
#include "AjouterArrivee.h"
#include "SupprimerVol.h"
#include "VolDejaPresentException.h"
#include "VolAbsentException.h"
#include <QMessageBox>

FenetrePrincipal::FenetrePrincipal ():yul("YUL")
{
    yul.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C85"));
    yul.ajouterVol(Arrivee("RJ0271","ROYAL JORDANIAN","07:12","AMMAN"," Atterri "));
    widget.setupUi (this);

    modelDepart = new QStandardItemModel(this);
    modelDepart->setColumnCount(6);
    modelDepart->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Embarquement", "Porte"});
    widget.tableViewDepart->setModel(modelDepart);

    modelArrivee = new QStandardItemModel(this);
    modelArrivee->setColumnCount(5);
    modelArrivee->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Statut"});
    widget.tableViewArrivee->setModel(modelArrivee);

    rafraichirAffichage();
}

FenetrePrincipal::~FenetrePrincipal () { }

void FenetrePrincipal::slotMenuDepart(){
    AjouterDepart interfaceDepart;
    if(interfaceDepart.exec()){
        try {
            Depart unDepart(interfaceDepart.reqNumero(), interfaceDepart.reqCompagnie(), interfaceDepart.reqHeure(),
                            interfaceDepart.reqVille(), interfaceDepart.reqEmbq(), interfaceDepart.reqPorte());
            yul.ajouterVol(unDepart);
            rafraichirAffichage();
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::slotMenuArrivee(){
    AjouterArrivee interfaceArrivee;
    if(interfaceArrivee.exec()){
        try {
            //if (yul.reqAeroportFormate()==interfaceArrivee.reqNumero()) throw VolDejaPresentException(" Le vol "+yul.reqCode()+" est deja present!");
            Arrivee unArrivee(interfaceArrivee.reqNumero(), interfaceArrivee.reqCompagnie(),
                              interfaceArrivee.reqHeure(), interfaceArrivee.reqVille(), interfaceArrivee.reqStatus());
            yul.ajouterVol(unArrivee);
            rafraichirAffichage();
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::slotMenuSupprimerVol(){
    SupprimerVol interfaceSupprimer(yul);
    if(interfaceSupprimer.exec()){
        try{
            yul.supprimeVol (interfaceSupprimer.reqNumero().c_str ());
            rafraichirAffichage();
        }catch(VolAbsentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::rafraichirAffichage() {
    modelDepart->removeRows(0, modelDepart->rowCount());
    modelArrivee->removeRows(0, modelArrivee->rowCount());

    for (const auto& vol : yul.reqVols()) {
        if (vol->reqVolFormate().size() == 66) {  // Depart
            const Depart* dep = dynamic_cast<const Depart*>(vol.get());
            if (dep) {
                int row = modelDepart->rowCount();
                modelDepart->setItem(row, 0, new QStandardItem(QString::fromStdString(dep->reqNumero())));
                modelDepart->setItem(row, 1, new QStandardItem(QString::fromStdString(dep->reqCompagnie())));
                modelDepart->setItem(row, 2, new QStandardItem(QString::fromStdString(dep->reqHeure())));
                modelDepart->setItem(row, 3, new QStandardItem(QString::fromStdString(dep->reqVille())));
                modelDepart->setItem(row, 4, new QStandardItem(QString::fromStdString(dep->reqHeureEmbarquement())));
                modelDepart->setItem(row, 5, new QStandardItem(QString::fromStdString(dep->reqPorteEmbarquement())));
            }
        } else {
            const Arrivee* arr = dynamic_cast<const Arrivee*>(vol.get());
            if (arr) {
                int row = modelArrivee->rowCount();
                modelArrivee->setItem(row, 0, new QStandardItem(QString::fromStdString(arr->reqNumero())));
                modelArrivee->setItem(row, 1, new QStandardItem(QString::fromStdString(arr->reqCompagnie())));
                modelArrivee->setItem(row, 2, new QStandardItem(QString::fromStdString(arr->reqHeure())));
                modelArrivee->setItem(row, 3, new QStandardItem(QString::fromStdString(arr->reqVille())));
                modelArrivee->setItem(row, 4, new QStandardItem(QString::fromStdString(arr->reqStatut())));
            }
        }
    }
}
