#ifndef FENETREPRINCIPAL_H
#define FENETREPRINCIPAL_H

#include "ui_FenetrePrincipal.h"
#include "Aeroport.h"
#include "Depart.h"
#include "Arrivee.h"
#include <Utilisateur.h>
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

    virtual ~FenetrePrincipal ();
  private slots:
    void slotMenuDepart();
    void slotMenuArrivee();
    void slotMenuModifierVol();
    void slotMenuSupprimerVol();
    void slotAdminUtilisateur();
    void slotAdminAeroport();
private:
    Ui::FenetrePrincipal widget{};
    DatabaseManager &m_db;
    QString m_id;
    QString m_role;
    QString m_aero;
    Aeroport m_aeroport;
    size_t m_size=m_aeroport.reqVols().size();
    std::vector<Utilisateur>m_utilisateurs;


  void rafraichirAffichage();
  QIcon icon();
};

#endif /* FENETREPRINCIPAL_H */
