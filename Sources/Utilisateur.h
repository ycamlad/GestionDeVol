//
// Created by chris on 7/28/2025.
//

#ifndef GESTION_DE_VOL_UTILISATEUR_H
#define GESTION_DE_VOL_UTILISATEUR_H
#pragma once
#include "string"
#include "QString"
#include <ContratException.h>

/**
    * \brief Struct contenant un constructeur pour la creation d'un utilisateur
 * **/


struct Utilisateur {
    QString nom;
    QString prenom;
    QString nomUtilisateur;
    QString nAero;
    QString role;
    QString pass;
    int statut;

    /**
     * \brief Constructeur du struct utilisateur
     * \param[in] p_nom nom de l'utilisateur
     * \param[in] p_prenom prenom de l'usager
     * \param[in] p_nomUtilisateur nom d'usager de l'utilisateur
     * \param[in] p_nAero nom de l'aéroport associé a l'usager
     * \param[in] p_role role de l'usager
     * \param[in] p_pass mot de pas de l'usager
     * \param[in] p_statut accèss de l'usager
     * \pre p_nom ne doit pas être vide
     * \pre p_prenom ne doit pas être vide
     * \pre p_nomUtilisateur ne doit pas être vide
     * \pre p_nAero ne doit pas être vide
     * \pre p_role ne doit pas être vide
     * \pre p_pass ne doit pas être vide
     * \pre p_statut ne doit pas être vide
     * **/
    Utilisateur(const QString& p_nom,const QString& p_prenom ,const QString& p_nomUtilisateur,const QString& p_nAero,
                const QString& p_role, const QString& p_pass, int p_statut)
            : nom(p_nom), prenom(p_prenom),nomUtilisateur(p_nomUtilisateur),nAero(p_nAero), role(p_role), pass(p_pass), statut(p_statut) {
        PRECONDITION(!p_nom.isEmpty())
        PRECONDITION(!p_prenom.isEmpty())
        PRECONDITION(!p_nomUtilisateur.isEmpty())
        PRECONDITION(!p_nAero.isEmpty())
        PRECONDITION(!p_role.isEmpty())
        PRECONDITION(!p_pass.isEmpty())
        PRECONDITION(p_statut == 0 || p_statut == 1)
    }
};
#endif //GESTION_DE_VOL_UTILISATEUR_H
