
#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>
#include "Vol.h"
#include "ContratException.h"

using namespace aerien;
/**
 * \brief Test du constructeur avec paramètres de la classe Vol
 *
 *   Cas valides :
 *     constructeurParametreValide : Création d'un objet Vol avec des valeurs valides
 *                                  et vérification de tous les attributs.
 *
 *   Cas invalides :
 *     constructeurParametreInvalide :
 *       - heureInvalide : l'heure est supérieure à 24.
 *       - minuteInvalide : la minute est supérieure à 60.
 *       - secondeInvalide : la seconde est supérieure à 60.
 *       - numeroInvalide : le numéro de vol ne respecte pas le format attendu.
 *       - compagnieInvalide : le nom de compagnie n'est pas bon
 *       - villeInvalide : le nom de la ville n'est pas bon.
 */

class tVol:public Vol{
public:
    tVol(const std::string &pNumero, const std::string &pCompagnie, const std::string &pHeure,
         const std::string &pVille);

    virtual ~tVol() ;
    virtual std::unique_ptr<Vol> clone ()const;

};

tVol::tVol(const std::string &pNumero, const std::string &pCompagnie, const std::string &pHeure,
           const std::string &pVille) : Vol(pNumero, pCompagnie, pHeure, pVille) {

}

tVol::~tVol()  = default;

std::unique_ptr<Vol> tVol::clone() const {
    return std::unique_ptr<Vol>();
}


TEST(Vol,ConstructeurParametreValide)
{
     tVol v1("AC1636","AIR CANADA","18:00","ORLONDO");


    ASSERT_EQ("AC1636",v1.reqNumero());
    ASSERT_EQ("AIR CANADA",v1.reqCompagnie());
    ASSERT_EQ("18:00",v1.reqHeure());
    ASSERT_EQ("ORLONDO",v1.reqVille());

  //std::cout << "Mettre vos tests dans ce fichier" << std::endl;
}


/**
 * \brief Test du constructeur Vol avec un numéro invalide
 *        Cas invalide :
 *          constructeurNumeroInvalide : numéro de vol incorrect
 */
TEST(Vol,ConstructeurNumeroInvalide){
    ASSERT_THROW(tVol v1("C163","AIR CANADA","18:00","ORLONDO"),PreconditionException)
                                <<"Le code du vol doit etre egale a 6 et n'avoir que des majuscule";
}


/**
 * \brief Test du constructeur Vol avec un nom de compagnie invalide
 *        Cas invalide :
 *          constructeurCompagnieInvalide : compagnie avec des minuscules ou chiffres
 */
TEST(Vol,ConstructeurCompagnieInvalide){
    ASSERT_THROW(tVol v1("C163","air CANADA","18:00","ORLONDO"),PreconditionException)
                                <<"Le nom de compagnie doit etre en majuscule et ne pas contenir de chiffre";
}

/**
 * \brief Test du constructeur Vol avec une heure invalide
 *        Cas invalide :
 *          constructeurHeureInvalide : heure hors plage 0-24
 */
TEST(Vol,ConstructeurHeureInvalide){
    ASSERT_THROW(tVol v1("C163","AIR CANADA","78:00","ORLONDO"),PreconditionException)
                                <<"L'heure doit etre comrpis entre 0 et 24";
}


/**
 * \brief Test du constructeur Vol avec une ville invalide
 *        Cas invalide :
 *          constructeurVilleInvalide : nom de ville non conforme
 */
TEST(Vol,ConstructeurVilleInvalide){
    ASSERT_THROW(tVol v1("C163","AIR CANADA","18:00","orLONDO"),PreconditionException)
                                <<"Le nom de la ville doit etre en majuscule et ne pas contenir de numero";
}

/**
 * \class UnVol
 * \brief Fixture pour tests sur un Vol valide
 */
class UnVol:public ::testing::Test{
public:
    UnVol():
        t_vol("AC1636","AIR CANADA","18:00","ORLONDO"){
    }

    tVol t_vol;
};

/**
 * \class UnVol2
 * \brief Fixture pour tests sur un deuxième Vol valide différent
 */
class UnVol2:public UnVol{
public:
    UnVol2():
            t_vol2("RJ0271","ROYAL JORDANIAN","07:12","AMMAN"){
    }

    tVol t_vol2;
};


/**
 * \class UnVol3
 * \brief Fixture pour tests sur un troisième Vol identique au premier
 */
class UnVol3:public UnVol{
public:
    UnVol3():
            t_vol3("AC1636","AIR CANADA","18:00","ORLONDO"){
    }

    tVol t_vol3;
};

/**
 * \brief Test de la méthode reqNumero()
 *        Cas valide : numéro correct
 */
TEST_F(UnVol,reqNumero){
    ASSERT_EQ("AC1636",t_vol.reqNumero());
}

/**
 * \brief Test de la méthode reqCompagnie()
 *        Cas valide : nom de compagnie correct
 */
TEST_F(UnVol,reqCompagnie){
    ASSERT_EQ("AIR CANADA",t_vol.reqCompagnie());
}

/**
 * \brief Test de la méthode reqHeure()
 *        Cas valide : heure correcte
 */
TEST_F(UnVol,reqHeure){
    ASSERT_EQ("18:00",t_vol.reqHeure());
}

/**
 * \brief Test de la méthode reqVille()
 *        Cas valide : nom de ville correct
 */
TEST_F(UnVol,reqVille){
    ASSERT_EQ("ORLONDO",t_vol.reqVille());
}

/**
 * \brief Test de la méthode asgHeureVol()
 *        Cas valides :
 *          - asgHeureVolValide : assigner une heure valide.
 *        Cas invalides :
 *          - asgHeureInvalide : assigner une heure invalide déclenche une exception.
 */
TEST_F(UnVol,asgHeureVolValide){
    t_vol.asgHeureVol("19:25");
    ASSERT_EQ("19:25",t_vol.reqHeure());
}

TEST_F(UnVol,asgHeureInvalide){
    ASSERT_THROW(t_vol.asgHeureVol("75:68"),PreconditionException);
}

/**
 * \brief Test de l'opérateur d'égalité (operator==)
 *        Cas valides :
 *          - operateurEgalitervalide : deux vols identiques == vrai
 *          - operateurEgaliterInvalide : deux vols identiques == faux
 */
TEST_F(UnVol3,operateurEgaliterVvalide){
    ASSERT_EQ(t_vol3==t_vol, true);
}

TEST_F(UnVol2,operateurEgaliterInvalide){
    ASSERT_EQ(t_vol2==t_vol, false);
}

/**
 * \brief Test de la méthode reqVolFormate()
 *        Cas valide : formatage correct d'un vol
 */
TEST_F(UnVol,reqVolFormate){
    ASSERT_EQ("|AC1636|    AIR CANADA     |18:00|      ORLONDO      |",t_vol.reqVolFormate());
}