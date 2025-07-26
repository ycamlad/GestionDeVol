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
#include "DataBaseException.h"

/**
 * faire une methode statique qui va renvoyer le resultat d'une requete
 * ou encore instancier un objet db manager a la creation de la fenetre principal
 * **/
//FenetrePrincipal::FenetrePrincipal ():m_db(DatabaseManager::instance())
FenetrePrincipal::FenetrePrincipal(DatabaseManager &p_db,const QString& p_id,
                                   const QString& p_role,const QString& p_aero,
                                   QWidget *parent):m_db(p_db),
                                   m_id(p_id),m_role(p_role),m_aeroport(p_aero.toStdString())
{
    widget.setupUi (this);

    Aeroport aeroport(p_aero.toStdString());
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
                if (query.value("Statut").toString() == "1") statut = " Atterri ";
                else if (query.value("Statut").toString() == "2")
                    statut = " Retardé ";
                else statut = "À l’heure";
                if (query.value("TypeVol").toBool()) {
                    aeroport.ajouterVol(Arrivee(query.value("NumVol").toString().toStdString(),
                                                query.value("Compagnie").toString().toStdString(),
                                                query.value("Heure").toString().toStdString(),
                                                query.value("Ville").toString().toStdString(),
                                                statut));
                } else {
                    aeroport.ajouterVol(Depart(query.value("NumVol").toString().toStdString(),
                                               query.value("Compagnie").toString().toStdString(),
                                               query.value("Heure").toString().toStdString(),
                                               query.value("Ville").toString().toStdString(),
                                               query.value("HEmbq").toString().toStdString(),
                                               query.value("PNum").toString().toStdString()));
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
            if (query.value("Statut").toString() == "1")
                statut = " Atterri ";
            else if (query.value("Statut").toString() == "2")
                statut = " Retardé ";
            else
                statut = "À l’heure";
            if (query.value("TypeVol").toBool()) {
                aeroport.ajouterVol(Arrivee(query.value("NumVol").toString().toStdString(),
                                            query.value("Compagnie").toString().toStdString(),
                                            query.value("Heure").toString().toStdString(),
                                            query.value("Ville").toString().toStdString(),
                                            statut));
            } else {
                aeroport.ajouterVol(Depart(query.value("NumVol").toString().toStdString(),
                                           query.value("Compagnie").toString().toStdString(),
                                           query.value("Heure").toString().toStdString(),
                                           query.value("Ville").toString().toStdString(),
                                           query.value("HEmbq").toString().toStdString(),
                                           query.value("PNum").toString().toStdString()));
            }

        }
    }

    m_aeroport=aeroport;


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

    //Depart table
    widget.tableWidgetDepart->setColumnCount(6);
    widget.tableWidgetDepart->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Embarquement", "Porte"});

    //Arrivee table
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
            QSqlQuery query;
            query.prepare("INSERT INTO Vols (NAeroport,UID,NumVol,TypeVol,Compagnie,Heure,Ville,HEmbq,PNum) VALUES(:na,:id,:num,:type,:comp,:heure,:ville,:embq,:porte)");
            query.bindValue(":na",QString::fromStdString(m_aeroport.reqCode()));
            query.bindValue(":id",m_id);
            query.bindValue(":num",QString::fromStdString(interfaceDepart.reqNumero()));
            query.bindValue(":type",0);
            query.bindValue(":comp",QString::fromStdString(interfaceDepart.reqCompagnie()));
            query.bindValue(":heure",QString::fromStdString(interfaceDepart.reqHeure()));
            query.bindValue(":ville",QString::fromStdString(interfaceDepart.reqVille()));
            query.bindValue(":embq",QString::fromStdString(interfaceDepart.reqEmbq()));
            query.bindValue(":porte",QString::fromStdString(interfaceDepart.reqPorte()));

            if (!query.exec()) throw DatabaseException("Insertion invalide:",query.lastError().text());

            m_aeroport.ajouterVol(unDepart);
            rafraichirAffichage();

        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        } catch (DatabaseException &e) {
            QMessageBox::warning(this,"Erreur",e.what());

        }
    }
}

void FenetrePrincipal::slotMenuArrivee(){
    AjouterArrivee interfaceArrivee;
    interfaceArrivee.setWindowIcon(icon());
    try {
        //if (yul.reqAeroportFormate()==interfaceArrivee.reqNumero()) throw VolDejaPresentException(" Le vol "+yul.reqCode()+" est deja present!");
        Arrivee unArrivee(interfaceArrivee.reqNumero(), interfaceArrivee.reqCompagnie(),
                          interfaceArrivee.reqHeure(), interfaceArrivee.reqVille(), interfaceArrivee.reqStatus());
        QSqlQuery query;
        int statut ;

        if(interfaceArrivee.reqStatus()==" Atterri ") statut=1;
        if(interfaceArrivee.reqStatus()==" Retardé ") statut=2;
        if(interfaceArrivee.reqStatus()=="À l’heure") statut=3;

        query.prepare("INSERT INTO Vols (NAeroport,UID,NumVol,TypeVol,Compagnie,Heure,Ville,Statut) VALUES(:na,:id,:num,:type,:comp,:heure,:ville,:Statut)");
        query.bindValue(":na",QString::fromStdString(m_aeroport.reqCode()));
        query.bindValue(":id",m_id);
        query.bindValue(":num",QString::fromStdString(interfaceArrivee.reqNumero()));
        query.bindValue(":type",1);
        query.bindValue(":comp",QString::fromStdString(interfaceArrivee.reqCompagnie()));
        query.bindValue(":heure",QString::fromStdString(interfaceArrivee.reqHeure()));
        query.bindValue(":ville",QString::fromStdString(interfaceArrivee.reqVille()));
        query.bindValue(":Statut",statut);

        if (!query.exec()) throw DatabaseException("Insertion invalide:",query.lastError().text());

        m_aeroport.ajouterVol(unArrivee);
        rafraichirAffichage();

    }catch (VolDejaPresentException &e){
        QMessageBox::warning(this,"Erreur",e.what());
    }catch (DatabaseException &e) {
        QMessageBox::warning(this,"Erreur",e.what());

    }
    if(interfaceArrivee.exec()){
    }
}

void FenetrePrincipal::slotMenuSupprimerVol(){
    SupprimerVol interfaceSupprimer(m_aeroport);
    interfaceSupprimer.setWindowIcon(icon());
    if(interfaceSupprimer.exec()){
        try{
            QSqlQuery query;

            query.prepare("DELETE FROM Vols WHERE NumVol =:num");
            query.bindValue(":num",QString::fromStdString(interfaceSupprimer.reqNumero()));

            if (!query.exec()) throw DatabaseException("Suppression invalide:",query.lastError().text());

            m_aeroport.supprimeVol (interfaceSupprimer.reqNumero());
            rafraichirAffichage();

        }catch(VolAbsentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }catch (DatabaseException &e) {
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



