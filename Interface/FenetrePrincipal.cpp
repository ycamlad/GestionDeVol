#include "FenetrePrincipal.h"
#include "AjouterDepart.h"
#include "AjouterArrivee.h"
#include "SupprimerVol.h"
#include "VolDejaPresentException.h"
#include "VolAbsentException.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include "QSvgWidget"

FenetrePrincipal::FenetrePrincipal ():yul("YUL")
{
    yul.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C85"));
    yul.ajouterVol(Arrivee("RJ0271","ROYAL JORDANIAN","07:12","AMMAN"," Atterri "));
    widget.setupUi (this);

    // For Depart table
    widget.tableWidgetDepart->setColumnCount(6);
    widget.tableWidgetDepart->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Embarquement", "Porte"});

// For Arrivee table
    widget.tableWidgetArrivee->setColumnCount(5);
    widget.tableWidgetArrivee->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Statut"});


    rafraichirAffichage();
}

FenetrePrincipal::~FenetrePrincipal () { }

void FenetrePrincipal::slotMenuDepart(){
    AjouterDepart interfaceDepart;
    interfaceDepart.setWindowIcon(icon());
    if(interfaceDepart.exec()){
        try {
            Depart unDepart(interfaceDepart.reqNumero(), interfaceDepart.reqCompagnie(), interfaceDepart.reqHeure(),
                            interfaceDepart.reqVille(), interfaceDepart.reqEmbq(), interfaceDepart.reqPorte());
            yul.ajouterVol(unDepart);
            rafraichirAffichage();
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::slotMenuArrivee(){
    AjouterArrivee interfaceArrivee;
    interfaceArrivee.setWindowIcon(icon());
    if(interfaceArrivee.exec()){
        try {
            //if (yul.reqAeroportFormate()==interfaceArrivee.reqNumero()) throw VolDejaPresentException(" Le vol "+yul.reqCode()+" est deja present!");
            Arrivee unArrivee(interfaceArrivee.reqNumero(), interfaceArrivee.reqCompagnie(),
                              interfaceArrivee.reqHeure(), interfaceArrivee.reqVille(), interfaceArrivee.reqStatus());
            yul.ajouterVol(unArrivee);
            rafraichirAffichage();
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::slotMenuSupprimerVol(){
    SupprimerVol interfaceSupprimer(yul);
    interfaceSupprimer.setWindowIcon(icon());
    if(interfaceSupprimer.exec()){
        try{
            yul.supprimeVol (interfaceSupprimer.reqNumero().c_str ());
            rafraichirAffichage();
        }catch(VolAbsentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::rafraichirAffichage() {
    widget.tableWidgetDepart->clearContents();
    widget.tableWidgetDepart->setRowCount(0);
    widget.tableWidgetArrivee->clearContents();
    widget.tableWidgetArrivee->setRowCount(0);

    for (const auto &vol: yul.reqVols()) {
        if (vol->estDepart()) {
            int row = widget.tableWidgetDepart->rowCount();
            widget.tableWidgetDepart->insertRow(row);

            widget.tableWidgetDepart->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(vol->reqNumero())));
            widget.tableWidgetDepart->setItem(row, 1,
                                              new QTableWidgetItem(QString::fromStdString(vol->reqCompagnie())));
            widget.tableWidgetDepart->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(vol->reqHeure())));
            widget.tableWidgetDepart->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(vol->reqVille())));
            widget.tableWidgetDepart->setItem(row, 4, new QTableWidgetItem(
                    QString::fromStdString(dynamic_cast<Depart *>(vol.get())->reqHeureEmbarquement())));
            widget.tableWidgetDepart->setItem(row, 5, new QTableWidgetItem(
                    QString::fromStdString(dynamic_cast<Depart *>(vol.get())->reqPorteEmbarquement())));
        } else {
            int row = widget.tableWidgetArrivee->rowCount();
            widget.tableWidgetArrivee->insertRow(row);

            widget.tableWidgetArrivee->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(vol->reqNumero())));
            widget.tableWidgetArrivee->setItem(row, 1,
                                               new QTableWidgetItem(QString::fromStdString(vol->reqCompagnie())));
            widget.tableWidgetArrivee->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(vol->reqHeure())));
            widget.tableWidgetArrivee->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(vol->reqVille())));
            widget.tableWidgetArrivee->setItem(row, 4, new QTableWidgetItem(
                    QString::fromStdString(dynamic_cast<Arrivee *>(vol.get())->reqStatut())));
        }

    }
}

QIcon FenetrePrincipal::icon() {
    return QIcon(":/Resources/iconmonstr-airport-10-240.png");
}
