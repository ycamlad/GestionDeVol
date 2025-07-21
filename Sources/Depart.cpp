//
// Created by chris on 6/25/2025.
//

#include <sstream>
#include "Depart.h"
#include "ContratException.h"
#include "validationFormat.h"

using namespace aerien;
using namespace util;
/**
 * \brief Constructeur avec paramètres
 *        Initialise un vol de départ avec les attributs du vol de base et ceux spécifiques au départ.
 * \param[in] p_numero Le numéro du vol
 * \param[in] p_compagnie Le nom de la compagnie aérienne
 * \param[in] p_heure L’heure prévue du vol
 * \param[in] p_ville La ville de destination
 * \param[in] p_heureEmbarquement L’heure d’embarquement
 * \param[in] p_porteEmbarquement La porte d’embarquement
 * \pre Tous les paramètres doivent être valides, et l’heure d’embarquement doit précéder l’heure du vol
 * \post Les attributs sont initialisés avec les valeurs fournies
 */
Depart::Depart(const std::string &p_numero, const std::string &p_compagnie, const std::string &p_heure,
               const std::string &p_ville, const std::string &p_heureEmbarquement,
               const std::string &p_porteEmbarquement): Vol(p_numero,p_compagnie,p_heure,p_ville),
               m_heureEmbarquement(p_heureEmbarquement),m_porteEmbarquement(p_porteEmbarquement) {

    PRECONDITION(estFormat24HValide(p_heureEmbarquement)&&p_heure>p_heureEmbarquement)
    PRECONDITION(estPorteValide(p_porteEmbarquement))

    POSTCONDITION(m_heureEmbarquement==p_heureEmbarquement)
    POSTCONDITION(m_porteEmbarquement==p_porteEmbarquement)

    INVARIANTS();
}

/**
 * \brief Destructeur
 */
Depart::~Depart() = default;

/**
 * \brief Accesseur pour l’heure d’embarquement
 * \return Une chaîne représentant l’heure d’embarquement
 */
const std::string &Depart::reqHeureEmbarquement() const {
    return m_heureEmbarquement;
}

/**
 * \brief Mutateur pour modifier l’heure d’embarquement
 * \param[in] p_HeureEmbarquement La nouvelle heure d’embarquement
 * \pre L’heure doit être au format 24h et inférieure à l’heure du vol
 * \post m_heureEmbarquement est mise à jour
 */
void Depart::asgHeureEmbarquement(const std::string &p_HeureEmbarquement) {
    PRECONDITION(estFormat24HValide(p_HeureEmbarquement)&&p_HeureEmbarquement<reqHeure())
    m_heureEmbarquement = p_HeureEmbarquement;
    POSTCONDITION(m_heureEmbarquement==p_HeureEmbarquement)

}

/**
 * \brief Accesseur pour la porte d’embarquement
 * \return Une chaîne représentant la porte d’embarquement
 */
const std::string &Depart::reqPorteEmbarquement() const {
    return m_porteEmbarquement;
}

/**
 * \brief Mutateur pour modifier la porte d’embarquement
 * \param[in] p_PorteEmbarquement La nouvelle porte
 * \pre La porte doit être valide selon estPorteValide
 * \post m_porteEmbarquement est mise à jour
 */
void Depart::asgPorteEmbarquement(const std::string &p_PorteEmbarquement) {
    PRECONDITION(estPorteValide(p_PorteEmbarquement))
    m_porteEmbarquement = p_PorteEmbarquement;
    POSTCONDITION(m_porteEmbarquement==p_PorteEmbarquement)
}

/**
 * \brief Clone le vol de départ
 * \return Un pointeur vers une nouvelle instance identique
 */
std::unique_ptr<Vol> Depart::clone() const {
    return std::unique_ptr<Vol>(new Depart(*this));
}

/**
 * \brief Retourne une représentation formatée du vol de départ
 * \return Une chaîne contenant les champs du vol avec heure et porte d’embarquement
 */
std::string Depart::reqVolFormate() const {

    std::string vol = Vol::reqVolFormate();
    std::string heureEmbarquement =m_heureEmbarquement+"|";
    std::string porteEmbarquement = centrer(m_porteEmbarquement,5)+"|";
    std::stringstream os;
    os<<vol+heureEmbarquement+porteEmbarquement;
    return os.str();
}

/**
 * \brief Vérifie l’invariant de la classe Depart
 *        L’heure d’embarquement doit être valide et antérieure à l’heure du vol,
 *        et la porte d’embarquement doit être conforme.
 */
void Depart::verifierInvariant() const {
    INVARIANT(estFormat24HValide(m_heureEmbarquement)&&m_heureEmbarquement<reqHeure())
    INVARIANT(estPorteValide(m_porteEmbarquement))
}


