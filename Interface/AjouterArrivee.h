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
