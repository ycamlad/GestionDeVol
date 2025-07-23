//
// Created by chris on 6/25/2025.
//

#include <iostream>
#include "Aeroport.h"
#include "ContratException.h"
#include "validationFormat.h"
#include "Depart.h"
#include "Arrivee.h"
#include "VolAbsentException.h"
#include "VolDejaPresentException.h"

using namespace aerien;
using namespace util;
/**
 * \brief Constructeur avec paramètre
 *        Construit un objet Aeroport avec un code d'aéroport valide.
 * \param[in] p_code Une chaîne représentant le code de l'aéroport
 * \pre p_code doit être un code valide selon estCodeValide()
 * \post m_code est initialisé avec p_code
 */
Aeroport::Aeroport(const std::string &p_code):m_code(p_code) {
    PRECONDITION(estCodeValide(p_code))
    POSTCONDITION(m_code==p_code)
    INVARIANTS();
}

/**
 * \brief Constructeur par copie
 *        Construit un nouvel objet Aeroport à partir d'un autre.
 * \param[in] p_aeroport L'objet Aeroport à copier
 * \post m_code est copié de p_aeroport et les vols sont clonés
 */
Aeroport::Aeroport(const Aeroport &p_aeroport):m_code(p_aeroport.m_code){
    for(const auto &vol:p_aeroport.m_vVols){
        m_vVols.push_back(std::unique_ptr<Vol>(vol->clone()));
    }
    INVARIANTS();
}

/**
 * \brief Surcharge de l'opérateur d'affectation
 *        Permet d'affecter un objet Aeroport à un autre.
 * \param[in] p_aeroport L'objet Aeroport à copier
 * \return Une référence vers l'objet courant après affectation
 */
Aeroport& Aeroport::operator=(const Aeroport &p_aeroport) {
    if(this==&p_aeroport){
        return *this;
    }
    m_code=p_aeroport.m_code;
    POSTCONDITION(m_code==p_aeroport.m_code)

    m_vVols.clear();
    for(const auto &vol:p_aeroport.m_vVols){
        m_vVols.push_back(std::unique_ptr<Vol>(vol->clone()));
    }

    POSTCONDITION(m_vVols==p_aeroport.m_vVols)
    return *this;
}

/**
 * \brief Retourne le code de l'aéroport
 * \return Une chaîne représentant le code de l'aéroport
 */
const std::string &Aeroport::reqCode() const {
    return m_code;
}

/**
 * \brief Ajoute un vol à la liste des vols de l'aéroport
 * \param[in] p_vol Une référence vers un objet Vol à ajouter
 * \post Le vecteur m_vVols contient un vol de plus
 */
void Aeroport::ajouterVol(const Vol &p_vol) {
    for(auto &e:m_vVols){
        if(e->reqNumero()==p_vol.reqNumero()) throw VolDejaPresentException(" Le vol "+e->reqNumero()+" est deja present!");
    }
    size_t avant = m_vVols.size();
    m_vVols.push_back(std::unique_ptr<Vol>(p_vol.clone()));
    POSTCONDITION(m_vVols.size()==avant+1)
    INVARIANTS();
}

/**
 * \brief Supprime un vol dans la liste des vols de l'aéroport
 * \param[in] p_numero Une référence vers un numero de Vol à supprimer
 * \pre le p_numero ne doit pas être vide et la largeur du vecteur de vol doit excéder zero
 * \post Le vecteur m_vVols contient un vol de moins
 */
void Aeroport::supprimeVol(const std::string &p_numero) {
    size_t avant = m_vVols.size();
    PRECONDITION(!p_numero.empty())
    PRECONDITION(avant!=0)

    for (auto it = m_vVols.begin(); it != m_vVols.end(); ++it) {
        if ((*it)->reqNumero() == p_numero) {
            m_vVols.erase(it);
            return;
        }
    }

    throw VolAbsentException("Le vol " + p_numero + " n'existe pas!");
    POSTCONDITION(m_vVols.size()==avant-1)
    INVARIANTS();
}

/**
 * \brief Modifie un vol dans la liste des vols de l'aéroport
 * \param[in] p_numero Une référence vers un numero de Vol pour l'identifiacation du vol
 * \param[in] p_heure Une référence vers une heure de Vol à modifier
 * \param[in] p_hembq Une référence vers une heure d'embrquement Vol à modifier
 * \param[in] p_porte Une référence vers un code de porte de Vol à modifier
 * \param[in] p_statut Une référence vers un statut de Vol à modifier
 * \pre Le parametre p_numero ne peut pas etre vide
 * \pre Le membre vector m_vVols ne peut pas etre vide
 * **/
void Aeroport::modifierVol(const std::string &p_numero,const std::string& p_heure="" ,const std::string& p_hembq="",const std::string& p_porte="",const std::string& p_statut=""){
    PRECONDITION(!p_numero.empty())
    PRECONDITION(!m_vVols.empty())

    for (auto & m_vVol : m_vVols) {
        if (m_vVol->reqNumero() == p_numero) {
            if(m_vVol->reqVolFormate().size()==66){
                auto depart =dynamic_cast<Depart *>(m_vVol.get());

                if(!p_heure.empty()) depart->asgHeureVol(p_heure);
                if(!p_hembq.empty()) depart->asgHeureEmbarquement(p_hembq);
                if(!p_porte.empty()) depart->asgPorteEmbarquement(p_porte);
            }else{
                auto arrivee = dynamic_cast<Arrivee *>(m_vVol.get());
                if(!p_heure.empty()) arrivee->asgHeureVol(p_heure);
                if(!p_statut.empty()) arrivee->asgStatut(p_statut);
            }
            return;
        }
    }
    throw VolAbsentException("Le vol " + p_numero + " n'existe pas!");
}

/**
 * \brief Vérifie l'invariant de la classe Aeroport
 *        L'invariant assure que le code de l'aéroport est valide.
 */
void Aeroport::verifierInvariant() const {
    INVARIANT(estCodeValide(m_code))
}

const std::vector<std::unique_ptr<Vol>>& Aeroport::reqVols() const {
    return m_vVols;
}


/**
 * \brief Retourne une chaine formatée représentant l'aéroport et ses vols
 *        Génère un tableau des départs et des arrivées à partir des vols enregistrés.
 * \return Une chaîne formatée contenant les informations des vols
 */
std::string Aeroport::reqAeroportFormate() {
    std::string formater="Aéroport ";
    std::vector<std::unique_ptr<Vol>> depart;
    std::vector<std::unique_ptr<Vol>> arrivee;

    for(auto &e : m_vVols){
        if(e->reqVolFormate().size()==66) depart.push_back(e->clone());
        else arrivee.push_back(e->clone());
    }
    formater.append(m_code+"\n");
    formater.append("Tableau des départs");
    for(int y=0;y<11;++y) {
        if(y==0||y==2||y==4) {

            formater.append("\n");
            for (int i = 0; i < 66; ++i) {
                formater.append("-");
            }
            formater.append("\n");
        }
        if(y==1){
            formater.append("| VOL  |     COMPAGNIE     |HEURE|        VILLE      |EMBRQ|PORTE|");
        }

        if(y==3){
            int j =0;
            for(auto &e:depart){
                formater.append(e->reqVolFormate());
                if(j!=depart.size()-1) {
                    formater.append("\n");
                }
                ++j;
            }
        }


        if(y==5){
            formater.append("Tableau des arrivées");
        }

        if(y==7){
            formater.append("| VOL  |     COMPAGNIE     |HEURE|       VILLE       |  STATUT  |");
        }

        if(y==9){
            int j =0;
            for(auto &e:arrivee){
                formater.append(e->reqVolFormate());
                if(j!=arrivee.size()-1) {
                    formater.append("\n");
                }
                ++j;
            }
        }

        if(y==6||y==8||y==10) {
            formater.append("\n");
            for (int x = 0; x < 65; ++x) {
                formater.append("-");
            }
            if(y!=10)formater.append("\n");
        }
    }

    return formater;
}


