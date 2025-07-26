//
// Created by chris on 7/26/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ModifierVol.h" resolved

#include "Modifiervol.h"
#include "ui_ModifierVol.h"


ModifierVol::ModifierVol(QWidget *parent) :
        QWidget(parent), ui(new Ui::ModifierVol) {
    ui->setupUi(this);
}

ModifierVol::~ModifierVol() {
    delete ui;
}
