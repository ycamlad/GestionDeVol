#ifndef VALIDATIONFORMAT_H
#define VALIDATIONFORMAT_H
#include <string>

 namespace util {

     bool estNumeroVolValide(const std::string &p_numeroVol);

     bool estFormat24HValide(const std::string &p_heure);

     bool estPorteValide(const std::string &p_porte);

     bool estNomValide(const std::string &p_nom);

     void traiterFichierVols(std::istream &p_flux);

     bool estCodeValide(const std::string &p_code);

     std::string ajusterLargeur(const std::string &p_champ, int p_largeur = 19);

     std::string centrer(const std::string &str, int max);

#endif /* VALIDATIONFORMAT_H */

}