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
    widget.textBrowserPrincipal->setPlainText (yul.reqAeroportFormate ().c_str());
}

FenetrePrincipal::~FenetrePrincipal () { }

void FenetrePrincipal::slotMenuDepart(){
    AjouterDepart interfaceDepart;
    if(interfaceDepart.exec()){
        try {
            Depart unDepart(interfaceDepart.reqNumero(), interfaceDepart.reqCompagnie(), interfaceDepart.reqHeure(),
                            interfaceDepart.reqVille(), interfaceDepart.reqEmbq(), interfaceDepart.reqPorte());
            yul.ajouterVol(unDepart);
            widget.textBrowserPrincipal->setPlainText(yul.reqAeroportFormate().c_str());
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
            widget.textBrowserPrincipal->setPlainText(yul.reqAeroportFormate().c_str());
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::slotMenuSupprimerVol(){
  SupprimerVol interfaceSupprimer;
  if(interfaceSupprimer.exec()){
      try{
          yul.supprimeVol (interfaceSupprimer.reqNumero().c_str ());
          widget.textBrowserPrincipal->setPlainText(yul.reqAeroportFormate().c_str());
        }catch(VolAbsentException &e){
        QMessageBox::warning(this,"Erreur",e.what());
      }
    }
}