//
// Created by chris on 7/27/2025.
//

#ifndef GESTION_DE_VOL_AJOUTERUTILISATEUR_H
#define GESTION_DE_VOL_AJOUTERUTILISATEUR_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class AjouterUtilisateur; }
QT_END_NAMESPACE

class AjouterUtilisateur : public QDialog {
Q_OBJECT

public:
    explicit AjouterUtilisateur(QWidget *parent = nullptr);

    ~AjouterUtilisateur() override;

private:
    Ui::AjouterUtilisateur *ui;
};


#endif //GESTION_DE_VOL_AJOUTERUTILISATEUR_H
