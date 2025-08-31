#ifndef GESTION_DE_VOL_LOGIN_H
#define GESTION_DE_VOL_LOGIN_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget {
Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    int compteur=0;
    bool statut = false;

    ~Login() override;
private slots:
    void slotConfirmer();

private:
    Ui::Login *ui;
};


#endif //GESTION_DE_VOL_LOGIN_H
