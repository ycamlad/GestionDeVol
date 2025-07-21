/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Vol.cpp
 * Author: etudiant
 * 
 * Created on 24 juin 2025, 16 h 42
 */

#include "Vol.h"
#include "validationFormat.h"
#include "ContratException.h"
#include "sstream"

using namespace aerien;
using namespace util;
/**
 * \brief Constructeur avec paramètres
 *        Initialise un objet Vol avec les informations fournies.
 * \param[in] p_numero Le numéro du vol.
 * \param[in] p_compagnie Le nom de la compagnie aérienne.
 * \param[in] p_heure L’heure du vol au format 24h.
 * \param[in] p_ville La ville de destination ou de provenance.
 * \pre Tous les paramètres doivent être valides selon les fonctions de validation fournies.
 * \post Les attributs internes sont initialisés avec les valeurs passées.
 */
Vol::Vol(const std::string &p_numero, const std::string &p_compagnie, const std::string &p_heure,
         const std::string &p_ville): m_numero(p_numero),m_compagnie(p_compagnie),m_heure(p_heure),m_ville(p_ville) {
    PRECONDITION(estNumeroVolValide(p_numero))
    PRECONDITION(estNomValide(p_compagnie))
    PRECONDITION(estFormat24HValide(p_heure))
    PRECONDITION(estNomValide(p_ville))

    POSTCONDITION(m_numero==p_numero)
    POSTCONDITION(m_compagnie==p_compagnie)
    POSTCONDITION(m_heure==p_heure)
    POSTCONDITION(m_ville==p_ville)
    INVARIANTS();
}

/**
 * \brief Retourne le numéro du vol
 * \return Une chaîne représentant le numéro du vol
 */
const std::string &Vol::reqNumero() const {
    return m_numero;
}
/**
 * \brief Retourne le nom de la compagnie aérienne
 * \return Une chaîne représentant la compagnie
 */
const std::string &Vol::reqCompagnie() const {
    return m_compagnie;
}

/**
 * \brief Retourne l'heure du vol
 * \return Une chaîne représentant l'heure
 */
const std::string &Vol::reqHeure() const {
    return m_heure;
}

/**
 * \brief Retourne la ville de destination ou de provenance
 * \return Une chaîne représentant la ville
 */
const std::string &Vol::reqVille() const {
    return m_ville;
}

/**
 * \brief Assigne une nouvelle heure au vol
 * \param[in] p_heure L’heure à assigner au format 24h
 * \pre p_heure doit être au format valide 24h
 * \post L’attribut m_heure est mis à jour
 */
void Vol::asgHeureVol(const std::string& p_heure) {
    PRECONDITION(estFormat24HValide(p_heure))
    m_heure=p_heure;
    POSTCONDITION(m_heure==p_heure)
}

/**
 * \brief Surcharge de l’opérateur d’égalité
 * \param[in] p_vol L’objet Vol avec lequel comparer
 * \return true si les numéros de vol sont identiques, false sinon
 */
bool Vol::operator==(const Vol& p_vol) const {
    return m_numero == p_vol.m_numero;
}

/**
 * \brief Retourne une représentation formatée du vol
 * \return Une chaîne contenant les champs du vol alignés en tableau
 */
std::string Vol::reqVolFormate() const {

    std::string numero ="|"+m_numero+"|";
    std::string compagnie =centrer(m_compagnie,19);
    std::string heure ="|"+m_heure+"|";
    std::string ville =centrer(m_ville,19)+"|";
    std::ostringstream os;
    os<<numero+compagnie+heure+ville;
    return os.str();
}

/**
 * \brief Vérifie l’invariant de la classe Vol
 *        Valide que tous les attributs respectent les formats attendus.
 */
void Vol::verifierInvariant() const {
    INVARIANT(estNumeroVolValide(m_numero))
    INVARIANT(estNomValide(m_compagnie))
    INVARIANT(estFormat24HValide(m_heure))
    INVARIANT(estNomValide(m_ville))
}









