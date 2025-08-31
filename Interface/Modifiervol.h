#ifndef GESTION_DE_VOL_MODIFIERVOL_H
#define GESTION_DE_VOL_MODIFIERVOL_H

#include "QDialog"
#include <Aeroport.h>
#include <ui_ModifierVol.h>

QT_BEGIN_NAMESPACE
namespace Ui { class ModifierVol; }
QT_END_NAMESPACE
using namespace aerien;
class ModifierVol : public QDialog {
Q_OBJECT

public:
    explicit ModifierVol(const Aeroport&p_aero,QWidget *parent = nullptr);

    ~ModifierVol() override;
    std::string reqNumero() const;
    std::string reqCompagnie() const;
    std::string reqHeure()const;
    std::string reqVille() const;
    std::string reqEmbq()const;
    std::string reqPorte()const;
    std::string reqStatut()const;
    const Aeroport& reqAero ()const;
private slots:
    void slotModifierVol();

private:
    Ui::ModifierVol *ui;
    Aeroport m_aero;
    void  refresh();
    void departMode(bool estDpart);

};


#endif //GESTION_DE_VOL_MODIFIERVOL_H
