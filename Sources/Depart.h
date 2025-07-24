//
// Created by chris on 6/25/2025.
//

#ifndef TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_DEPART_H
#define TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_DEPART_H
#include "Vol.h"
/**
 * \class Depart
 * \brief Classe dérivée de Vol représentant un vol de départ.
 *
 *        Cette classe ajoute des informations spécifiques aux vols de départ :
 *        l'heure d'embarquement et la porte d'embarquement.
 *
 *        Elle hérite de la classe Vol et redéfinit certaines méthodes virtuelles.
 *
 * \invariant La validité peut être vérifiée avec les fonctions suivantes : bool estFormat24HValide (p_heureEmbarquement), bool estPorteValide (p_porteEmbarquement).
 */
namespace aerien {
    class Depart : public Vol {
    public:
        Depart(const std::string &p_numero, const std::string &p_compagnie, const std::string &p_heure,
               const std::string &p_ville, const std::string &p_heureEmbarquement,
               const std::string &p_porteEmbarquement);

        ~Depart() override =default;

        const std::string &reqPorteEmbarquement() const;

        void asgHeureEmbarquement(const std::string &mHeureEmbarquement);

        const std::string &reqHeureEmbarquement() const;

        void asgPorteEmbarquement(const std::string &mPorteEmbarquement);

        virtual std::unique_ptr<Vol> clone() const;

        virtual std::string reqVolFormate() const;

    private:
        std::string m_porteEmbarquement;
        std::string m_heureEmbarquement;

        void verifierInvariant() const;

        bool estDepart() const;
    };
}


#endif //TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_DEPART_H
