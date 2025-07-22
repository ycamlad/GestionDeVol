/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/qtFiles/form.h to edit this template
 */

/* 
 * File:   SupprimerVol.h
 * Author: etudiant
 *
 * Created on 7 juillet 2025, 11 h 51
 */

#ifndef _SUPPRIMERVOL_H
#define _SUPPRIMERVOL_H

#include "ui_SupprimerVol.h"
#include <Aeroport.h>

using namespace aerien;

class SupprimerVol : public QDialog
{
  Q_OBJECT
public:
    explicit SupprimerVol(aerien::Aeroport& aeroport, QWidget* parent = nullptr);  virtual ~SupprimerVol ();
  std::string reqNumero() const;
  private slots:
    void slotSupprimerVol();
private:
    aerien::Aeroport& m_aeroport;
  Ui::SupprimerVol widget;
};

#endif /* _SUPPRIMERVOL_H */
