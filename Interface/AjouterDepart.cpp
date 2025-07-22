#include "AjouterDepart.h"
#include "QMessageBox"
#include "validationFormat.h"
using namespace util;

AjouterDepart::AjouterDepart ()
{
  widget.setupUi (this);
}

AjouterDepart::~AjouterDepart () { }

void AjouterDepart::slotAjoutDepart(){
    while(!estNumeroVolValide(reqNumero())||!estNomValide(reqCompagnie())||!estFormat24HValide(reqHeure())||!estNomValide(reqVille())||!estFormat24HValide(reqEmbq())||!estPorteValide(reqPorte())||reqHeure()<reqEmbq()) {
        if (!estNumeroVolValide(reqNumero())) {
            QMessageBox::warning(this, "Erreur", "Numero de vol invalide");
        }
        if (!estNomValide(reqCompagnie())) {
            QMessageBox::warning(this, "Erreur", "Nom de compagnie invalide");
        }
        if (!estFormat24HValide(reqHeure())) {
            QMessageBox::warning(this, "Erreur", "Heure de depart invalide");
        }
        if (!estNomValide(reqVille())) {
            QMessageBox::warning(this, "Erreur", "Nom de ville invalide");
        }
        if (!estFormat24HValide(reqEmbq())) {
            QMessageBox::warning(this, "Erreur", "Heure d'embarquement invalide");
        }
        if (reqHeure()<reqEmbq()) {
            QMessageBox::warning(this, "Erreur", "Heure d'embarquement superieur a heure de depart.");
        }
        if (!estPorteValide(reqPorte())) {
            QMessageBox::warning(this, "Erreur", "Code de porte invalide");
        }
        return;
    }
  accept();
}

std::string AjouterDepart::reqNumero() const {
    return widget.lineEditCode->text().toStdString();
}

std::string AjouterDepart::reqCompagnie() const {
    return widget.lineEditCompagnie->text().toStdString();
}

std::string AjouterDepart::reqHeure() const {
    return widget.lineEditHeure->text().toStdString();
}

std::string AjouterDepart::reqVille() const {
    return widget.lineEditVille->text().toStdString();
}

std::string AjouterDepart::reqEmbq() const {
    return widget.lineEditEmbq->text().toStdString();
}

std::string AjouterDepart::reqPorte() const {
    return widget.lineEditPorte->text().toStdString();
}

