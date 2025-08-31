#include "AjouterAeroport.h"
#include "ui_AjouterAeroport.h"
#include "validationFormat.h"
#include "QMessageBox"
using namespace util;

AjouterAeroport::AjouterAeroport(QWidget *parent) :
        QDialog(parent), ui(new Ui::AjouterAeroport) {
    ui->setupUi(this);
}

AjouterAeroport::~AjouterAeroport() {
    delete ui;
}

void AjouterAeroport::slotAjouterAeroport() {
    if(!estCodeValide(reqAeroport().toStdString())){
        QMessageBox::warning(this, "Erreur", "Code de vol invalide");
        return;
    }
    accept();
}

QString AjouterAeroport::reqAeroport() {
    return ui->lineEditCodeAeroport->text();
}
