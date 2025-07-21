//
// Created by chris on 6/25/2025.
//

#include <sstream>
#include "Arrivee.h"
#include "ContratException.h"
#include "validationFormat.h"

using namespace aerien;
using namespace util;

/**
 * \brief Constructeur avec paramètres
 *        Initialise un vol d'arrivée avec les informations fournies.
 * \param[in] p_numero Le numéro du vol
 * \param[in] p_compagnie Le nom de la compagnie aérienne
 * \param[in] p_heure L’heure du vol
 * \param[in] p_ville La ville de provenance
 * \param[in] p_statut Le statut du vol
 * \pre p_statut doit correspondre à un des trois statuts reconnus
 * \post m_statut est initialisé avec p_statut
 */
Arrivee::Arrivee(const std::string &p_numero, const std::string &p_compagnie, const std::string &p_heure,
                 const std::string &p_ville,const std::string &p_statut) : Vol(p_numero, p_compagnie, p_heure, p_ville),m_statut(p_statut) {
    PRECONDITION((p_statut==" Atterri "||p_statut==" Retardé "||p_statut=="À l’heure"))
    POSTCONDITION(m_statut==p_statut)
    INVARIANTS();

}

/**
 * \brief Accesseur pour le statut du vol
 * \return Une chaîne représentant le statut actuel du vol
 */
const std::string &Arrivee::reqStatut()const {
    return m_statut;
}

/**
 * \brief Mutateur pour modifier le statut du vol
 * \param[in] p_statut Le nouveau statut (doit être l’un des statuts reconnus)
 * \pre Le statut doit être non vide et faire partie des statuts valides
 * \post m_statut est mis à jour avec p_statut
 */
void Arrivee::asgStatut(const std::string &p_statut) {
    PRECONDITION(!p_statut.empty()&&(p_statut==" Atterri "||p_statut==" Retardé "||p_statut=="À l’heure"))
    m_statut=p_statut;
    POSTCONDITION(m_statut==p_statut)
}


/**
 * \brief Clone le vol d’arrivée
 * \return Un pointeur vers une copie polymorphique du vol courant
 */
std::unique_ptr<Vol> Arrivee::clone() const {
    //return std::unique_ptr<Vol>(new Arrivee(*this));
    return std::make_unique<Arrivee>(*this);
}

/**
 * \brief Retourne une représentation formatée du vol d’arrivée
 * \return Une chaîne formatée contenant les champs du vol et le statut
 */
std::string Arrivee::reqVolFormate() const {

    std::string vol = Vol::reqVolFormate();
    std::string statut;

    if(m_statut==" Atterri ") statut=m_statut+" |";
    if(m_statut==" Retardé ") statut=" Retarde  |";
    if(m_statut=="À l’heure") statut="A l'heure |";

    std::stringstream os;
    os<<vol+statut;
    return os.str();
}

/**
 * \brief Vérifie l’invariant de la classe Arrivee
 *        Le statut doit être valide parmi les trois statuts reconnus.
 */
void Arrivee::verifierInvariant() const {
    INVARIANT(!m_statut.empty()&&(m_statut==" Atterri "||m_statut==" Retardé "||m_statut=="À l’heure"))
}



