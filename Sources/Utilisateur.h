//
// Created by chris on 7/28/2025.
//

#ifndef GESTION_DE_VOL_UTILISATEUR_H
#define GESTION_DE_VOL_UTILISATEUR_H
#pragma once
#include "string"
#include "QString"
#include <ContratException.h>


struct Utilisateur {
    QString nom;
    QString prenom;
    QString nomUtilisateur;
    QString nAero;
    QString role;
    QString pass;
    int statut;

    Utilisateur(const QString& p_nom,const QString& p_prenom ,const QString& p_nomUtilisateur,const QString& p_nAero,
                const QString& p_role, const QString& p_pass, int p_statut)
            : nom(p_nom), prenom(p_prenom),nomUtilisateur(p_nomUtilisateur),nAero(p_nAero), role(p_role), pass(p_pass), statut(p_statut) {
        PRECONDITION(!p_nom.isEmpty());
        PRECONDITION(!p_prenom.isEmpty());
        PRECONDITION(!p_nomUtilisateur.isEmpty());
        PRECONDITION(!p_nAero.isEmpty());
        PRECONDITION(!p_role.isEmpty());
        PRECONDITION(!p_pass.isEmpty());
        PRECONDITION(p_statut == 0 || p_statut == 1)
    }
};
#endif //GESTION_DE_VOL_UTILISATEUR_H
