//
// Created by chris on 7/27/2025.
//

#ifndef GESTION_DE_VOL_AJOUTERUTILISATEUR_H
#define GESTION_DE_VOL_AJOUTERUTILISATEUR_H

#include <QDialog>
#include "Aeroport.h"
#include "DataBaseException.h"
#include "databasemanager.h"
#include "QString"
#include "Utilisateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AjouterUtilisateur; }
QT_END_NAMESPACE
using namespace aerien;
class AjouterUtilisateur : public QDialog {
Q_OBJECT

public:
    explicit AjouterUtilisateur(const Aeroport&p_aero,std::vector<Utilisateur>& p_utilisateur,QWidget *parent = nullptr);

    ~AjouterUtilisateur() override;
    QString reqNom();
    QString reqPrenom();
    QString reqNomUtilisateur();
    QString reqMotDePasse();
    QString reqRole();
    QString reqAeroport();

private slots:
    void slotAjouterUtilisateur();
    void slotGenererNomUtilisateur();

private:
    Ui::AjouterUtilisateur *ui;
    Aeroport m_aeroport;
    std::vector<Utilisateur>m_utilisateurs;
    bool estNomDisponible();


};


#endif //GESTION_DE_VOL_AJOUTERUTILISATEUR_H
