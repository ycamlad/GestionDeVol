#ifndef FENETREPRINCIPAL_H
#define FENETREPRINCIPAL_H

#include "ui_FenetrePrincipal.h"
#include "Aeroport.h"
#include "Depart.h"
#include "Arrivee.h"
#include "QStandardItemModel"
#include "QApplication"
#include "databasemanager.h"
using namespace aerien;

class FenetrePrincipal : public QMainWindow
{
  Q_OBJECT
public:
  FenetrePrincipal ();
    //DatabaseManager &db=DatabaseManager::instance();


    virtual ~FenetrePrincipal ();
  private slots:
    void slotMenuDepart();
    void slotMenuArrivee();
    void slotMenuSupprimerVol();
private:
private:
    //QStandardItemModel& modelDepart;
    //QStandardItemModel& modelArrivee;
    Ui::FenetrePrincipal widget;
    DatabaseManager &db;
    //Aeroport yul;


  //void rafraichirAffichage();
  QIcon icon();
};

#endif /* FENETREPRINCIPAL_H */
