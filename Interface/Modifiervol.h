//
// Created by chris on 7/26/2025.
//

#ifndef GESTION_DE_VOL_MODIFIERVOL_H
#define GESTION_DE_VOL_MODIFIERVOL_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ModifierVol; }
QT_END_NAMESPACE

class ModifierVol : public QWidget {
Q_OBJECT

public:
    explicit ModifierVol(QWidget *parent = nullptr);

    ~ModifierVol() override;

private:
    Ui::ModifierVol *ui;
};


#endif //GESTION_DE_VOL_MODIFIERVOL_H
