#include <QMessageBox>
#include "Login.h"
#include "ui_Login.h"
#include "FenetrePrincipal.h"
#include "databasemanager.h"
#include "QSqlRecord"


Login::Login(QWidget *parent) :
        QWidget(parent), ui(new Ui::Login) {
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::slotConfirmer() {
    DatabaseManager &db(DatabaseManager::instance());
    db.connect();
    const QPixmap pixmap(":/Resources/background.png");
    const QIcon icon(":/Resources/iconmonstr-airport-10-240.png");

    const QString nom =ui->lineEditNom->text();
    const QString pass=ui->lineEditPass->text();



    QSqlQuery query;
    query.prepare("SELECT ID,NomAeroport,Role,Statut FROM Utilisateurs WHERE NomUtilisateur=:nom AND Pass=:pass");
    query.bindValue(":nom",nom);
    query.bindValue(":pass",pass);

    if(!query.exec())  {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête:\n" + query.lastError().text());        return;
    }
    if(query.next()){
        const QString id = query.value("ID").toString();
        const QString role = query.value("Role").toString();
        const QString aeroport = query.value("NomAeroport").toString();
        statut= query.value("Statut").toBool();

        if (!statut) {
            for (int i = 0; i < query.record().count(); ++i) {
                qDebug() << "Column" << i << ":" << query.record().fieldName(i);
            }
            auto *f = new FenetrePrincipal(db, id, role, aeroport);
            f->setWindowIcon(icon);
            f->setFixedHeight(775);
            f->setFixedWidth(1018);
            f->setAutoFillBackground(true);

            QPalette palette;
            palette.setBrush(f->backgroundRole(),
                             QBrush(pixmap.scaled(f->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
            f->setPalette(palette);
            f->show();
            this->hide();
        }else {
            QMessageBox::warning(this, "Erreur", "Votre compte est suspendu.");
        }
    }else{

        if (!statut) {
            compteur++;
            if (compteur==3) {
                QMessageBox::warning(this, "Erreur", "Votre compte vient d'etre suspendu.");
                query.prepare("UPDATE Utilisateurs SET Statut=1 WHERE NomUtilisateur=:nom");
                query.bindValue(":nom",nom);

                if(!query.exec()) {
                    QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête:\n" + query.lastError().text());
                }
            }else {
                QMessageBox::warning(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect.");
            }
        }else {
            QMessageBox::warning(this, "Erreur", "Votre compte est suspendu.");
        }
    }
}

