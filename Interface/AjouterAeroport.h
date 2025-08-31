#ifndef GESTION_DE_VOL_AJOUTERAEROPORT_H
#define GESTION_DE_VOL_AJOUTERAEROPORT_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class AjouterAeroport; }
QT_END_NAMESPACE

class AjouterAeroport : public QDialog {
Q_OBJECT

public:
    explicit AjouterAeroport(QWidget *parent = nullptr);
    QString reqAeroport();

    ~AjouterAeroport() override;
private slots:
    void slotAjouterAeroport();

private:
    Ui::AjouterAeroport *ui;

};


#endif //GESTION_DE_VOL_AJOUTERAEROPORT_H
