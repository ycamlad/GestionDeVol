//
// Created by chris on 6/25/2025.
//

#ifndef TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_AEROPORT_H
#define TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_AEROPORT_H

#include <memory>
#include "string"
#include "vector"
#include "Vol.h"

/**
 * \class Aeroport
 * \brief Classe représentant un aéroport contenant une liste de vols.
 *
 *        Cette classe permet d’ajouter des vols à un aéroport, de cloner un aéroport,
 *        et de générer un affichage formaté de tous les vols enregistrés.
 *
 *        L’objet Aeroport contient un code unique et un vecteur de vols gérés via des pointeurs intelligents.
 *
 * \invariant La validité peut être vérifiée avec la fonction suivante : bool estCodeValide (p_code).
 */
 namespace aerien {

     class Aeroport {
     public:
         Aeroport(const std::string &p_code);

         Aeroport(const Aeroport &p_aeroport);

         ~Aeroport() = default;

         Aeroport &operator=(const Aeroport &p_aeroport);

         const std::string &reqCode() const;

         void ajouterVol(const Vol &p_vol);

         void supprimeVol(const std::string& p_numero);

         std::string reqAeroportFormate();

     private:
         std::string m_code;
         std::vector<std::unique_ptr<Vol>> m_vVols;

         void verifierInvariant() const;
     };

 }
#endif //TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_AEROPORT_H
