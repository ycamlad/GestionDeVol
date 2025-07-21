//
// Created by chris on 6/25/2025.
//

#include "gtest/gtest.h"
#include "ContratException.h"
#include "Depart.h"
using namespace aerien;
/**
 * \brief Test du constructeur avec paramètres de la classe Depart
 *
 *   Cas valides :
 *     constructeurParametreValide : Création d'un objet Depart avec des valeurs valides
 *                                  et vérification des attributs porte et heure d'embarquement.
 *
 *   Cas invalides :
 *     constructeurPorteInvalide : la porte d'embarquement ne commence pas par une majuscule
 *                                ou n'est pas suivie de deux chiffres valides (>0).
 *     constructeurHeureInvalide : l'heure d'embarquement n'est pas valide.
 */
TEST(Depart,ConstructeurParametreValide)
{
    Depart d("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86");

    ASSERT_EQ("C86",d.reqPorteEmbarquement());
    ASSERT_EQ("17:15",d.reqHeureEmbarquement());

    //std::cout << "Mettre vos tests dans ce fichier" << std::endl;
}

TEST(Depart,ConstructeurPorteInvalide){
    ASSERT_THROW(Depart d("C163","AIR CANADA","18:00","ORLONDO","c86","17:15"),PreconditionException)
                                <<"La porte d'embarquement est invalide, doit commencer par une lettre majuscule et est suivis de 2 numero plus grand que 0";
}
TEST(Depart,ConstructeurCompagnieInvalide){
    ASSERT_THROW(Depart d("C163","air CANADA","18:00","ORLONDO","C86","18:15"),PreconditionException)
                                <<"L'heure dembarquement est invalide. Elle doit etre entre 0 et 24 et ne peux pas etre plus grande que l'heure de depart ";
}

/**
 * \class unDepart
 * \brief Fixture pour les tests sur un objet Depart valide
 */
class unDepart:public ::testing::Test{
public:
    unDepart():
        t_depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86"){}
        Depart t_depart;
};

/**
 * \brief Test de la méthode reqPorteEmbarquement()
 *        Cas valide : récupération correcte de la porte d'embarquement
 */
TEST_F(unDepart,reqPorte){
    ASSERT_EQ("C86",t_depart.reqPorteEmbarquement());
}

/**
 * \brief Test de la méthode reqHeureEmbarquement()
 *        Cas valide : récupération correcte de l'heure d'embarquement
 */
TEST_F(unDepart,reqHeure) {
    ASSERT_EQ("17:15", t_depart.reqHeureEmbarquement());
}

/**
 * \brief Test de la méthode asgPorteEmbarquement()
 *        Cas valides :
 *          - asgPorteValide : assignation d'une porte valide.
 *        Cas invalides :
 *          - asgPorteValideInvalide : assignation d'une porte invalide (lettre minuscule) déclenche exception.
 */
TEST_F(unDepart,asgPorteValide){
    t_depart.asgPorteEmbarquement("Z89");
    ASSERT_EQ("Z89",t_depart.reqPorteEmbarquement());
}

TEST_F(unDepart,asgPorteValideInvalide){
    ASSERT_THROW(t_depart.asgPorteEmbarquement("z89"), PreconditionException);
}

/**
 * \brief Test de la méthode asgHeureEmbarquement()
 *        Cas valides :
 *          - asgHeureEmbarquementValide : assignation d'une heure valide.
 *        Cas invalides :
 *          - asgHeureEmbarquementInvalide : assignation d'une heure invalide déclenche une exception.
 */
TEST_F(unDepart,asgHeureEmbarquementValide){
    t_depart.asgHeureEmbarquement("17:25");
    ASSERT_EQ("17:25",t_depart.reqHeureEmbarquement());
}



TEST_F(unDepart,asgHeureEmbarquementInvalide){
    ASSERT_THROW(t_depart.asgHeureEmbarquement("18:25"), PreconditionException);
}


/**
 * \brief Test de la méthode reqVolFormate()
 *        Cas valide : formatage correct d'un objet Depart
 */
TEST_F(unDepart,reqVolFormate){
    ASSERT_EQ("|AC1636|    AIR CANADA     |18:00|      ORLONDO      |17:15| C86 |",t_depart.reqVolFormate());
}

