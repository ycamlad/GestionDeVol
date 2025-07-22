#include "validationFormat.h"

using namespace std;

namespace util {
    bool estNumeroVolValide(const std::string &p_numeroVol) {
        bool numValide = (p_numeroVol.length() == 6);
        numValide &= isupper(p_numeroVol[0]) && isupper(p_numeroVol[1]);
        for (int i = 2; i < 6; i++) {
            numValide &= isdigit(p_numeroVol[i]);
        }
        return numValide;
    }

    bool estFormat24HValide(const std::string &p_heure) {
        bool heureValide = (p_heure.length() == 5 && p_heure[2] == ':');
        heureValide &= isdigit(p_heure[0]) && isdigit(p_heure[1]);
        heureValide &= isdigit(p_heure[3]) && isdigit(p_heure[4]);
        heureValide &= stoi(p_heure.substr(0, 2)) < 24;
        heureValide &= stoi(p_heure.substr(3, 2)) < 60;
        return heureValide;
    }


    bool estPorteValide(const std::string &p_porte) {
        bool porteValide = (p_porte.length() == 3);
        porteValide &= isupper(p_porte[0]) && true;
        porteValide &= isdigit(p_porte[1]);
        porteValide &= isdigit(p_porte[2]);
        porteValide &= !(p_porte[1] == '0' && p_porte[2] == '0');
        return porteValide;
    }

    bool estNomValide(const string &p_nom) {
        size_t longNom = p_nom.length();
        if (longNom < 3 || longNom > 19 || !isupper(p_nom[0]))
            return false;

        for (int i = 1; i < p_nom.length(); i++) {
            if (!isalpha(p_nom[i])) {
                if (p_nom[i] == '-' || p_nom[i] == ' ') {
                    if (i == p_nom.length() - 1 || p_nom[i + 1] == '-' || p_nom[i + 1] == ' ' || !isupper(p_nom[i + 1]))
                        return false;
                    i++;
                } else
                    return false;
            } else if (islower(p_nom[i]))
                return false;
        }
        return true;
    }

    bool estCodeValide(const std::string &p_code) {
        if (p_code.size() != 3 || p_code.empty()) {
            return false;
        }

        for (char i: p_code) {
            if (!isalpha(i) || islower(i))
                return false;
        }
        return true;
    }


/**
 * \brief Ajuste la largeur du champs en ajoutant des espaces des 2 cotés
 * \param[in] string le champ à ajuster
 * \param[in] int la largeur du champ souhaitée
 * \return string ajusté
 */
//    string ajusterLargeur(const string &p_champ, int p_largeur) {
//        string champAjuste = p_champ;
//        bool ajoutEspaceAGauche = false;
//        while (champAjuste.size() < (u_int) p_largeur) {
//            if (ajoutEspaceAGauche)
//                champAjuste = " " + champAjuste;
//            else
//                champAjuste = champAjuste + " ";
//
//            ajoutEspaceAGauche = !ajoutEspaceAGauche;
//        }
//        return champAjuste;
//    }

    std::string centrer(const std::string &str, int max) {
        std::string ss;
        size_t padding = (max - str.size()) / 2;
        size_t largeurTotal = (padding * 2) + str.size();

        for (int i = 0; i < padding; ++i) ss.append(" ");
        ss.append(str);
        for (int i = 0; i < padding; ++i) ss.append(" ");
        if (largeurTotal != max) {
            size_t ajustement = max - largeurTotal;
            for (int i = 0; i < ajustement; ++i) ss.append(" ");
        }
        return ss;
    }

}