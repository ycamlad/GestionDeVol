#include "FenetrePrincipal.h"
#include "AjouterDepart.h"
#include "AjouterArrivee.h"
#include "SupprimerVol.h"
#include "VolDejaPresentException.h"
#include "VolAbsentException.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <memory>
#include "QSvgWidget"
#include "QSqlQueryModel"
#include "databasemanager.h"

/**
 * faire une methode statique qui va renvoyer le resultat d'une requete
 * ou encore instancier un objet db manager a la creation de la fenetre principal
 * **/
//FenetrePrincipal::FenetrePrincipal ():m_db(DatabaseManager::instance())
FenetrePrincipal::FenetrePrincipal(DatabaseManager &p_db,const QString& p_id,
                                   const QString& p_role,const QString& p_aero,
                                   QWidget *parent):m_db(p_db),
                                   m_nom(p_id),m_role(p_role),m_aeroport(p_aero.toStdString())
{
    widget.setupUi (this);

    Aeroport aeroport(m_aeroport);
    QSqlQuery query;

    if(m_role=="Admin") {
        query.prepare(
                "SELECT "
                " NAeroport,"
                " TypeVol,"
                " NumVol,"
                " Compagnie,"
                " Heure,"
                " Ville,"
                " HEmbq,"
                " PNum,"
                " Statut"
                " FROM Vols");

        while (!query.exec()){
            QMessageBox::critical(this,"Erreur",query.lastError().text());
            return;
        }
            while (query.next()) {
                std::string statut;
                if (query.value(8).toString() == "1") statut = " Atterri ";
                else if (query.value(8).toString() == "2")
                    statut = " Retardé "; //" Atterri "||p_statut==" Retardé "||p_statut=="À l’heure"
                else statut = "À l’heure";
                if (query.value(1).toBool()) {
                    aeroport.ajouterVol(Arrivee(query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                query.value(4).toString().toStdString(),
                                                query.value(5).toString().toStdString(),
                                                statut));
                } else {
                    aeroport.ajouterVol(Depart(query.value(2).toString().toStdString(),
                                               query.value(3).toString().toStdString(),
                                               query.value(4).toString().toStdString(),
                                               query.value(5).toString().toStdString(),
                                               query.value(6).toString().toStdString(),
                                               query.value(7).toString().toStdString()));
                    }

                }

    }else {
        query.prepare(
                "SELECT "
                " NAeroport,"
                " TypeVol,"
                " NumVol,"
                " Compagnie,"
                " Heure,"
                " Ville,"
                " HEmbq,"
                " PNum,"
                " Statut"
                " FROM Vols WHERE UID=:id ");
        query.bindValue(":id", p_id);

        if (!query.exec()) {
            QMessageBox::critical(this,"Erreur",query.lastError().text());
            return;
        }
        while (query.next()) {
            std::string statut;
            if (query.value(8).toString() == "1")
                statut = " Atterri ";
            else if (query.value(8).toString() == "2")
                statut = " Retardé ";
            else
                statut = "À l’heure";
            if (query.value(1).toBool()) {
                aeroport.ajouterVol(Arrivee(query.value(2).toString().toStdString(),
                                            query.value(3).toString().toStdString(),
                                            query.value(4).toString().toStdString(),
                                            query.value(5).toString().toStdString(),
                                            statut));
            } else {
                aeroport.ajouterVol(Depart(query.value(2).toString().toStdString(),
                                           query.value(3).toString().toStdString(),
                                           query.value(4).toString().toStdString(),
                                           query.value(5).toString().toStdString(),
                                           query.value(6).toString().toStdString(),
                                           query.value(7).toString().toStdString()));
            }

        }
    }


//    for(int i =0;i<model.get()->rowCount();++i){
//        bool vol = model->data(model->index(i,1)).toInt();
//        if(!vol){
//            widget.tableViewDepart->setModel(model.get());
//            widget.tableViewDepart->hideColumn(7);
//        }else{
//            widget.tableViewArrivee->setModel(model.get());
//            widget.tableViewArrivee->hideColumn(5);
//            widget.tableViewArrivee->hideColumn(6);
//        }
//    }
    //widget.tableViewDepart->setModel(model.get());

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
            m_aeroport.ajouterVol(unDepart);
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
            m_aeroport.ajouterVol(unArrivee);
            rafraichirAffichage();
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

void FenetrePrincipal::slotMenuSupprimerVol(){
    SupprimerVol interfaceSupprimer(m_aeroport);
    interfaceSupprimer.setWindowIcon(icon());
    if(interfaceSupprimer.exec()){
        try{
            m_aeroport.supprimeVol (interfaceSupprimer.reqNumero());
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

        for (const auto &vol: m_aeroport.reqVols()) {
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



