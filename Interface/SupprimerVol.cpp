/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/qtFiles/form.cc to edit this template
 */

/*
 * File:   SupprimerVol.cpp
 * Author: etudiant
 *
 * Created on 7 juillet 2025, 11 h 51
 */

#include "SupprimerVol.h"
#include "validationFormat.h"
#include "QMessageBox"
using namespace util;

SupprimerVol::SupprimerVol ()
{
  widget.setupUi (this);
}

SupprimerVol::~SupprimerVol () { }

void SupprimerVol::slotSupprimerVol(){
    if(!estNumeroVolValide(reqNumero())){
        QMessageBox::warning(this, "Erreur", "Numero de vol invalide");
        return;
    }
  accept();
}

std::string SupprimerVol::reqNumero() const{
  return widget.lineEditNumero->text().toStdString();
}