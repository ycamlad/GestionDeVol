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

QT_BEGIN_NAMESPACE
namespace Ui { class AjouterUtilisateur; }
QT_END_NAMESPACE
using namespace aerien;
class AjouterUtilisateur : public QDialog {
Q_OBJECT

public:
    explicit AjouterUtilisateur(DatabaseManager &p_db,const Aeroport&p_aero,QWidget *parent = nullptr);

    ~AjouterUtilisateur() override;

private slots:
    void slotAjouterUtilisateur();

private:
    Ui::AjouterUtilisateur *ui;
    Aeroport m_aeroport;
    DatabaseManager &m_db;
};


#endif //GESTION_DE_VOL_AJOUTERUTILISATEUR_H
