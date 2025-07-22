#ifndef _AJOUTERDEPART_H
#define _AJOUTERDEPART_H

#include "ui_AjouterDepart.h"

class AjouterDepart : public QDialog
{
  Q_OBJECT
public:
  AjouterDepart ();
  virtual ~AjouterDepart ();
  std::string reqNumero() const;
  std::string reqCompagnie() const;
  std::string reqHeure()const;
  std::string reqVille() const;
  std::string reqEmbq()const;
  std::string reqPorte()const;
  private slots:
    void slotAjoutDepart();
private:
  Ui::AjouterDepart widget;
};

#endif /* _AJOUTERDEPART_H */
