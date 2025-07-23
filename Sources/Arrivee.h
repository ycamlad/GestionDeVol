//
// Created by chris on 6/25/2025.
//

#ifndef TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_ARRIVEE_H
#define TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_ARRIVEE_H
#include "Vol.h"

/**
 * \class Arrivee
 * \brief Classe dérivée de Vol représentant un vol d'arrivée.
 *
 *        Cette classe ajoute un attribut spécifique aux vols d’arrivée
 *
 *        Elle hérite de la classe Vol et redéfinit les méthodes nécessaires.
 *
 * \invariant Le statut doit être une chaîne valide selon estStatutValide().
 */
namespace aerien {

    class Arrivee : public Vol {
    public:
        Arrivee(const std::string &p_numero, const std::string &p_compagnie, const std::string &p_heure,
                const std::string &p_ville, const std::string &p_statut);

        virtual ~Arrivee() = default;

        const std::string &reqStatut() const;

        void asgStatut(const std::string &p_statut);

        virtual std::unique_ptr<Vol> clone() const;

        std::string reqVolFormate() const;

    private:
        std::string m_statut;

        void verifierInvariant() const;

        bool estDepart() const;
    };
}

#endif //TP2HIERARCHIEDECLASSES_CHRISTOPHERDALMACY_ARRIVEE_H
