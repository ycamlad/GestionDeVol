/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/qtFiles/form.h to edit this template
 */

/* 
 * File:   FenetrePrincipal.h
 * Author: etudiant
 *
 * Created on 5 juillet 2025, 12 h 09
 */

#ifndef _FENETREPRINCIPAL_H
#define _FENETREPRINCIPAL_H

#include "ui_FenetrePrincipal.h"
#include "Aeroport.h"
#include "Depart.h"
#include "Arrivee.h"
#include "QStandardItemModel"
using namespace aerien;

class FenetrePrincipal : public QMainWindow
{
  Q_OBJECT
public:
  FenetrePrincipal ();
  virtual ~FenetrePrincipal ();
  private slots:
    void slotMenuDepart();
    void slotMenuArrivee();
    void slotMenuSupprimerVol();
private:
private:
    QStandardItemModel* modelDepart;
    QStandardItemModel* modelArrivee;
    Ui::FenetrePrincipal widget;
  Aeroport yul;
  void rafraichirAffichage();
};

#endif /* _FENETREPRINCIPAL_H */
