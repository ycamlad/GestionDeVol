#include "FenetrePrincipal.h"
#include "AjouterDepart.h"
#include "AjouterArrivee.h"
#include "AjouterAeroport.h"
#include "Modifiervol.h"
#include "SupprimerVol.h"
#include "Utilisateur.h"
#include "AjouterUtilisateur.h"
#include "VolDejaPresentException.h"
#include "VolAbsentException.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include "databasemanager.h"
#include "DataBaseException.h"


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
                " NomAeroport,"
                " TypeVol,"
                " NumeroVol,"
                " Compagnie,"
                " Heure,"
                " Ville,"
                " HeureEmbarqument,"
                " NumeroPorte,"
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
                    aeroport.ajouterVol(Arrivee(query.value("NumeroVol").toString().toStdString(),
                                                query.value("Compagnie").toString().toStdString(),
                                                query.value("Heure").toString().toStdString(),
                                                query.value("Ville").toString().toStdString(),
                                                statut));
                } else {
                    aeroport.ajouterVol(Depart(query.value("NumeroVol").toString().toStdString(),
                                               query.value("Compagnie").toString().toStdString(),
                                               query.value("Heure").toString().toStdString(),
                                               query.value("Ville").toString().toStdString(),
                                               query.value("HeureEmbarqument").toString().toStdString(),
                                               query.value("NumeroPorte").toString().toStdString()));
                    }

                }
            query.prepare("SELECT * FROM Utilisateurs");
            while (!query.exec()){
                QMessageBox::critical(this,"Erreur",query.lastError().text());
                return;
            }
            while(query.next()){
                Utilisateur u(query.value("Nom").toString(),query.value("Prenom").toString(),query.value("NomUtilisateur").toString(),query.value("NomAeroport").toString(),query.value("Role").toString(),query.value("Pass").toString(),query.value("Statut").toInt());

                m_utilisateurs.push_back(u);
            }

    }else {
        query.prepare(
                "SELECT "
                " NomAeroport,"
                " TypeVol,"
                " NumeroVol,"
                " Compagnie,"
                " Heure,"
                " Ville,"
                " HeureEmbarqument,"
                " NumeroPorte,"
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
                aeroport.ajouterVol(Arrivee(query.value("NumeroVol").toString().toStdString(),
                                            query.value("Compagnie").toString().toStdString(),
                                            query.value("Heure").toString().toStdString(),
                                            query.value("Ville").toString().toStdString(),
                                            statut));
            } else {
                aeroport.ajouterVol(Depart(query.value("NumeroVol").toString().toStdString(),
                                           query.value("Compagnie").toString().toStdString(),
                                           query.value("Heure").toString().toStdString(),
                                           query.value("Ville").toString().toStdString(),
                                           query.value("HeureEmbarqument").toString().toStdString(),
                                           query.value("NumeroPorte").toString().toStdString()));
            }

        }

        widget.menuAdmin->menuAction()->setVisible(false);
        widget.tabWidgetFenetrePrincipal->removeTab(2);
    }

    m_aeroport=aeroport;


    //Depart table
    widget.tableWidgetDepart->setColumnCount(6);
    widget.tableWidgetDepart->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Embarquement", "Porte"});

    //Arrivee table
    widget.tableWidgetArrivee->setColumnCount(5);
    widget.tableWidgetArrivee->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Statut"});

    widget.tableWidgetUtilisateurs->setColumnCount(7);
    widget.tableWidgetUtilisateurs->setHorizontalHeaderLabels({"Nom d'utilisateur","Nom","Prenom","Aeroport","Role","Pass","Statut"});

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

            QSqlQuery query;
            query.prepare("INSERT INTO Vols (NomAeroport,UID,NumeroVol,TypeVol,Compagnie,Heure,Ville,HeureEmbarqument,NumeroPorte) VALUES(:na,:id,:num,:type,:comp,:heure,:ville,:embq,:porte)");
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
    if(interfaceArrivee.exec()){
        try {
            Arrivee unArrivee(interfaceArrivee.reqNumero(), interfaceArrivee.reqCompagnie(),
                              interfaceArrivee.reqHeure(), interfaceArrivee.reqVille(), interfaceArrivee.reqStatus());

            m_aeroport.ajouterVol(unArrivee);
            rafraichirAffichage();

            QSqlQuery query;
            int statut ;

            if(interfaceArrivee.reqStatus()==" Atterri ") statut=1;
            if(interfaceArrivee.reqStatus()==" Retardé ") statut=2;
            if(interfaceArrivee.reqStatus()=="À l’heure") statut=3;

            query.prepare("INSERT INTO Vols (NomAeroport,UID,NumeroVol,TypeVol,Compagnie,Heure,Ville,Statut) VALUES(:na,:id,:num,:type,:comp,:heure,:ville,:Statut)");
            query.bindValue(":na",QString::fromStdString(m_aeroport.reqCode()));
            query.bindValue(":id",m_id);
            query.bindValue(":num",QString::fromStdString(interfaceArrivee.reqNumero()));
            query.bindValue(":type",1);
            query.bindValue(":comp",QString::fromStdString(interfaceArrivee.reqCompagnie()));
            query.bindValue(":heure",QString::fromStdString(interfaceArrivee.reqHeure()));
            query.bindValue(":ville",QString::fromStdString(interfaceArrivee.reqVille()));
            query.bindValue(":Statut",statut);

            if (!query.exec()) throw DatabaseException("Insertion invalide:",query.lastError().text());



        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }catch (DatabaseException &e) {
            QMessageBox::warning(this,"Erreur",e.what());

        }

    }
}

void FenetrePrincipal::slotMenuModifierVol(){
    ModifierVol interfaceModifier(m_aeroport);
    interfaceModifier.setWindowIcon(icon());

    if(interfaceModifier.exec()){
        QSqlQuery query;
        int statut ;
        int type;

        if(interfaceModifier.reqStatut()==" Atterri ") statut=1;
        if(interfaceModifier.reqStatut()==" Retardé ") statut=2;
        if(interfaceModifier.reqStatut()=="À l’heure") statut=3;
        for(auto &e:m_aeroport.reqVols()){
            if(interfaceModifier.reqNumero()==e->reqNumero()){
                if(e->estDepart()){
                    type=0;
                    query.prepare("UPDATE Vols SET TypeVol = :type, Compagnie = :comp, Heure = :heure,\n"
                                  "               Ville = :ville, HeureEmbarqument = :embq, NumeroPorte = :porte\n"
                                  "WHERE NumeroVol = :num");
                    query.bindValue(":num",QString::fromStdString(interfaceModifier.reqNumero()));
                    query.bindValue(":type",type);
                    query.bindValue(":comp",QString::fromStdString(interfaceModifier.reqCompagnie()));
                    query.bindValue(":heure",QString::fromStdString(interfaceModifier.reqHeure()));
                    query.bindValue(":ville",QString::fromStdString(interfaceModifier.reqVille()));
                    query.bindValue(":embq",QString::fromStdString(interfaceModifier.reqEmbq()));
                    query.bindValue(":porte",QString::fromStdString(interfaceModifier.reqPorte()));
                    if (!query.exec()) throw DatabaseException("Modification invalide:",query.lastError().text());
                }else{
                    type=1;
                    query.prepare("UPDATE Vols SET TypeVol =:type, SET Compagnie=:comp, SET Heure=:heure ,SET Ville=:ville, SET Statut=:statut WHERE NumeroVol=:num ");
                    query.bindValue(":type",type);
                    query.bindValue(":Compagnie",QString::fromStdString(interfaceModifier.reqCompagnie()));
                    query.bindValue(":heure",QString::fromStdString(interfaceModifier.reqHeure()));
                    query.bindValue(":ville",QString::fromStdString(interfaceModifier.reqVille()));

                    query.bindValue(":statut",statut);
                    if (!query.exec()) throw DatabaseException("Modification invalide:",query.lastError().text());
                }
            }
        }

        //m_db.modifierVol()

    }
    m_aeroport=interfaceModifier.reqAero();
    rafraichirAffichage();
}


void FenetrePrincipal::slotMenuSupprimerVol(){
    SupprimerVol interfaceSupprimer(m_aeroport);
    interfaceSupprimer.setWindowIcon(icon());

    if(interfaceSupprimer.exec()){
        try{
            QSqlQuery query;

            query.prepare("DELETE FROM Vols WHERE NumeroVol =:num");
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


void FenetrePrincipal::slotAdminUtilisateur() {
    AjouterUtilisateur interfaceAjouterUtilisateur(m_aeroport,m_utilisateurs);
    interfaceAjouterUtilisateur.setWindowIcon(icon());

    if(interfaceAjouterUtilisateur.exec())
    {
        try{
            m_db.inserertUtilisateur(interfaceAjouterUtilisateur.reqNom(),
                                     interfaceAjouterUtilisateur.reqPrenom(),
                                     interfaceAjouterUtilisateur.reqNomUtilisateur(),
                                     interfaceAjouterUtilisateur.reqAeroport(),
                                     interfaceAjouterUtilisateur.reqRole(),
                                     interfaceAjouterUtilisateur.reqMotDePasse(),0);

            Utilisateur u (interfaceAjouterUtilisateur.reqNom(),
                           interfaceAjouterUtilisateur.reqPrenom(),
                           interfaceAjouterUtilisateur.reqNomUtilisateur(),
                           interfaceAjouterUtilisateur.reqAeroport(),
                           interfaceAjouterUtilisateur.reqRole(),
                           interfaceAjouterUtilisateur.reqMotDePasse(),0);
            m_utilisateurs.push_back(u);
        }catch(DatabaseException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }

    }
    rafraichirAffichage();
}

void FenetrePrincipal::slotAdminAeroport() {
    AjouterAeroport ajouterAeroport;
    ajouterAeroport.setWindowIcon(icon());
    if(ajouterAeroport.exec()){
        try {
            QSqlQuery query;
            query.prepare("INSERT INTO Aeroport (Nom) VALUES(:nom)");
            query.bindValue(":nom", ajouterAeroport.reqAeroport());
            if (!query.exec()) {
                if (!query.exec()) throw DatabaseException("Insertion invalide:", query.lastError().text());
            }
        }catch (DatabaseException &e){
            QMessageBox::warning(this,"Erreur",e.what());

        }
    }
}



void FenetrePrincipal::rafraichirAffichage() {
        widget.tableWidgetDepart->clearContents();
        widget.tableWidgetDepart->setRowCount(0);
        widget.tableWidgetArrivee->clearContents();
        widget.tableWidgetArrivee->setRowCount(0);
        widget.tableWidgetUtilisateurs->clearContents();
        widget.tableWidgetUtilisateurs->setRowCount(0);

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

        QString statut;
        for(const auto &u:m_utilisateurs){
            int row = widget.tableWidgetUtilisateurs->rowCount();
            widget.tableWidgetUtilisateurs->insertRow(row);

            if(u.statut==0) statut = "Normal";
            else statut = "Bloquer";

            widget.tableWidgetUtilisateurs->setItem(row,0,new QTableWidgetItem(u.nomUtilisateur));
            widget.tableWidgetUtilisateurs->setItem(row,1,new QTableWidgetItem(u.nom));
            widget.tableWidgetUtilisateurs->setItem(row,2,new QTableWidgetItem(u.prenom));
            widget.tableWidgetUtilisateurs->setItem(row,3,new QTableWidgetItem(u.nAero));
            widget.tableWidgetUtilisateurs->setItem(row,4,new QTableWidgetItem(u.role));
            widget.tableWidgetUtilisateurs->setItem(row,5,new QTableWidgetItem(u.pass));
            widget.tableWidgetUtilisateurs->setItem(row,6,new QTableWidgetItem(statut));
        }
}




QIcon FenetrePrincipal::icon() {
    return QIcon(":/Resources/iconmonstr-airport-10-240.png");
}





