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
FenetrePrincipal::FenetrePrincipal(DatabaseManager &p_db, QWidget *parent):m_db(p_db)
{

    m_db.connect();

    std::string ar = "YUL";
    // int u = 1;
    QSqlQuery query;
//    query.prepare("SELECT NAeroport FROM Utilisateurs WHERE NAeroport =:na");
//    query.bindValue(":na",QString::fromStdString(ar));
//    //query.bindValue(":id",u);
//    query.exec();
//    std::string na =(query.value(0).toString()).toStdString();


    query.prepare("SELECT NumVol, TypeVol, Compagnie, Heure, Ville, HEmbq, PNum, Statut FROM Vols");
    //query.bindValue(":ae",QString::fromStdString(ar));


    query.exec();

    auto model = std::make_unique<QSqlQueryModel>(this);
    model->setQuery(query);


    //Aeroport a (na);
    //a.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C85"));
    //a.ajouterVol(Arrivee("RJ0271","ROYAL JORDANIAN","07:12","AMMAN"," Atterri "));
    widget.setupUi (this);

    widget.tableViewDepart->setModel(model.get());
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
    //widget.tableWidgetDepart->setColumnCount(6);
    //widget.tableWidgetDepart->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Embarquement", "Porte"});

// For Arrivee table
    //widget.tableWidgetArrivee->setColumnCount(5);
    //widget.tableWidgetArrivee->setHorizontalHeaderLabels({"Numéro", "Compagnie", "Heure", "Ville", "Statut"});


    //rafraichirAffichage();
}

FenetrePrincipal::~FenetrePrincipal () { }

void FenetrePrincipal::slotMenuDepart(){
    AjouterDepart interfaceDepart;
    interfaceDepart.setWindowIcon(icon());
    if(interfaceDepart.exec()){
        try {
            Depart unDepart(interfaceDepart.reqNumero(), interfaceDepart.reqCompagnie(), interfaceDepart.reqHeure(),
                            interfaceDepart.reqVille(), interfaceDepart.reqEmbq(), interfaceDepart.reqPorte());
            //yul.ajouterVol(unDepart);
            //rafraichirAffichage();
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
           // yul.ajouterVol(unArrivee);
            //rafraichirAffichage();
        }catch (VolDejaPresentException &e){
            QMessageBox::warning(this,"Erreur",e.what());
        }
    }
}

//void FenetrePrincipal::slotMenuSupprimerVol(){
//    SupprimerVol interfaceSupprimer(yul);
//    interfaceSupprimer.setWindowIcon(icon());
//    if(interfaceSupprimer.exec()){
//        try{
//            //yul.supprimeVol (interfaceSupprimer.reqNumero());
//            //rafraichirAffichage();
//        }catch(VolAbsentException &e){
//            QMessageBox::warning(this,"Erreur",e.what());
//        }
//    }
//}

//void FenetrePrincipal::rafraichirAffichage() {
//    widget.tableWidgetDepart->clearContents();
//    widget.tableWidgetDepart->setRowCount(0);
//    widget.tableWidgetArrivee->clearContents();
//    widget.tableWidgetArrivee->setRowCount(0);
//
//    for (const auto &vol: yul.reqVols()) {
//        if (vol->estDepart()) {
//            int row = widget.tableWidgetDepart->rowCount();
//            widget.tableWidgetDepart->insertRow(row);
//
//            widget.tableWidgetDepart->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(vol->reqNumero())));
//            widget.tableWidgetDepart->setItem(row, 1,
//                                              new QTableWidgetItem(QString::fromStdString(vol->reqCompagnie())));
//            widget.tableWidgetDepart->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(vol->reqHeure())));
//            widget.tableWidgetDepart->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(vol->reqVille())));
//            widget.tableWidgetDepart->setItem(row, 4, new QTableWidgetItem(
//                    QString::fromStdString(dynamic_cast<Depart *>(vol.get())->reqHeureEmbarquement())));
//            widget.tableWidgetDepart->setItem(row, 5, new QTableWidgetItem(
//                    QString::fromStdString(dynamic_cast<Depart *>(vol.get())->reqPorteEmbarquement())));
//        } else {
//            int row = widget.tableWidgetArrivee->rowCount();
//            widget.tableWidgetArrivee->insertRow(row);
//
//            widget.tableWidgetArrivee->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(vol->reqNumero())));
//            widget.tableWidgetArrivee->setItem(row, 1,
//                                               new QTableWidgetItem(QString::fromStdString(vol->reqCompagnie())));
//            widget.tableWidgetArrivee->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(vol->reqHeure())));
//            widget.tableWidgetArrivee->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(vol->reqVille())));
//            widget.tableWidgetArrivee->setItem(row, 4, new QTableWidgetItem(
//                    QString::fromStdString(dynamic_cast<Arrivee *>(vol.get())->reqStatut())));
//        }
//
//    }
//}

QIcon FenetrePrincipal::icon() {
    return QIcon(":/Resources/iconmonstr-airport-10-240.png");
}

void FenetrePrincipal::slotMenuSupprimerVol() {

}


