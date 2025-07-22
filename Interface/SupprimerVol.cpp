#include "SupprimerVol.h"
#include "validationFormat.h"
#include "QMessageBox"
using namespace util;

SupprimerVol::SupprimerVol(aerien::Aeroport& aeroport, QWidget* parent)
        : QDialog(parent), m_aeroport(aeroport)
{
  widget.setupUi (this);
    for(auto it =m_aeroport.reqVols().begin();it!=m_aeroport.reqVols().end();++it){
        widget.comboBox->addItem(QString::fromStdString((*it)->reqNumero()));
    }

}

SupprimerVol::~SupprimerVol () { }

void SupprimerVol::slotSupprimerVol(){
    if(!estNumeroVolValide(reqNumero())){
        QMessageBox::warning(this, "Erreur", "Numero de vol invalide");
        return;
    }
  accept();
}

std::string SupprimerVol::reqNumero() const{
  return widget.comboBox->currentText().toStdString();
}