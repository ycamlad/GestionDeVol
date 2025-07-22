#include "AjouterArrivee.h"
#include "QMessageBox"
#include "validationFormat.h"

using namespace util;

AjouterArrivee::AjouterArrivee ()
{
  widget.setupUi (this);
}

AjouterArrivee::~AjouterArrivee () { }

void AjouterArrivee::slotAjouterArrivee() {
    while(!estNumeroVolValide(reqNumero())||!estNomValide(reqCompagnie())||!estFormat24HValide(reqHeure())||!estNomValide(reqVille())) {
        if (!estNumeroVolValide(reqNumero())) {
            QMessageBox::warning(this, "Erreur", "Numero de vol invalide");
        }
        if (!estNomValide(reqCompagnie())) {
            QMessageBox::warning(this, "Erreur", "Nom de compagnie invalide");
        }
        if (!estFormat24HValide(reqHeure())) {
            QMessageBox::warning(this, "Erreur", "Heure de vol invalide");
        }
        if (!estNomValide(reqVille())) {
            QMessageBox::warning(this, "Erreur", "Nom de ville invalide");
        }
        return;
    }
    accept();

}

std::string AjouterArrivee::reqNumero() const {
    return widget.lineEditCode->text().toStdString();
}

std::string AjouterArrivee::reqCompagnie() const {
    return widget.lineEditCompagnie->text().toStdString();
}

std::string AjouterArrivee::reqHeure() const {
    return widget.lineEditHeure->text().toStdString();
}

std::string AjouterArrivee::reqVille() const {
    return widget.lineEditVille->text().toStdString();
}

std::string AjouterArrivee::reqStatus() const {
    return widget.comboBox->currentText().toStdString();
}
