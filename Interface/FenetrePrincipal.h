#ifndef _FENETREPRINCIPAL_H
#define _FENETREPRINCIPAL_H

#include "ui_FenetrePrincipal.h"
#include "Aeroport.h"
#include "Depart.h"
#include "Arrivee.h"
#include "QStandardItemModel"
#include "QApplication"
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
  //void rafraichirAffichage();
  QIcon icon();
};

#endif /* _FENETREPRINCIPAL_H */
