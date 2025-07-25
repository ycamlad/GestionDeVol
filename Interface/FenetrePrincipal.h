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

    FenetrePrincipal();

public:
  FenetrePrincipal (DatabaseManager &p_db,const QString& p_id,const QString& p_role ,const QString& p_aero,QWidget *parent = nullptr);
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
    DatabaseManager &m_db;
    QString m_nom;
    QString m_role;
    QString m_aero;
    Aeroport m_aeroport;
    size_t m_size=m_aeroport.reqVols().size();


  void rafraichirAffichage();
  QIcon icon();
};

#endif /* FENETREPRINCIPAL_H */
