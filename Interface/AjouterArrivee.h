/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/qtFiles/form.h to edit this template
 */

/* 
 * File:   AjouterArrivee.h
 * Author: etudiant
 *
 * Created on 6 juillet 2025, 21 h 48
 */

#ifndef _AJOUTERARRIVEE_H
#define _AJOUTERARRIVEE_H

#include "ui_AjouterArrivee.h"

class AjouterArrivee : public QDialog
{
  Q_OBJECT
public:
  AjouterArrivee ();
  virtual ~AjouterArrivee ();
  std::string reqNumero() const;
  std::string reqCompagnie() const;
  std::string reqHeure()const;
  std::string reqVille() const;
  std::string reqStatus() const;
    private slots:
    void slotAjouterArrivee();
private:
  Ui::AjouterArrivee widget;
};

#endif /* _AJOUTERARRIVEE_H */
