//
// Created by chris on 6/25/2025.
//
#include "gtest/gtest.h"
#include "ContratException.h"
#include "Aeroport.h"
#include "Depart.h"
#include "VolDejaPresentException.h"
#include "VolAbsentException.h"

using namespace aerien;

/**
 * \brief Test du constructeur avec paramètres de la classe Aeroport
 *
 *   Cas valide :
 *     - ConstructeurParametreValide : Création d'un objet Aeroport avec un code valide.
 *
 *   Cas invalide :
 *     - ConstructeurParametreInvalide :  Code invalide .
 */
TEST(Aeroport,ConstructeurParametreValide)
{
    Aeroport a("YUL");

    ASSERT_EQ("YUL",a.reqCode());
}

TEST(Aeroport,ConstructeurParametreInvalide)
{
    ASSERT_THROW(Aeroport a("yUL"),PreconditionException);
}

/**
 * \brief Test du constructeur par copie de la classe Aeroport
 *        Cas valide : copie correcte d’un objet existant
 */
TEST(Aeroport,ConstructeurParametreParCopy)
{
    Aeroport a1("YUL");
    Aeroport a2=a1;
    ASSERT_EQ("YUL",a2.reqCode());
}


/**
 * \class unAeroport
 * \brief Fixture de test pour un objet Aeroport
 */
class unAeroport:public ::testing::Test{
public:
    unAeroport():
    t_aeroport("YUL"){}
    Aeroport t_aeroport;
};

/**
 * \brief Test de l'opérateur d'assignation pour la classe Aeroport
 *        Cas valide : assignation correcte d’un autre objet Aeroport
 */
TEST_F(unAeroport,asgAeroport){
    Aeroport a("BUL");
    t_aeroport=a;
    ASSERT_EQ(a.reqCode(),t_aeroport.reqCode());
}

/**
 * \brief Test de l’accesseur reqCode()
 *        Cas valide : récupération correcte du code de l’aéroport
 */
TEST_F(unAeroport,reqCode){
    ASSERT_EQ("YUL",t_aeroport.reqCode());
}

/**
 * \brief Test de la methode ajouterVol()
 *        Cas Invalide : lancement de VolDejaPresentException
 */
TEST_F(unAeroport,AjouterVolDejaPresent){
    t_aeroport.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86"));
    ASSERT_THROW(t_aeroport.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86")),VolDejaPresentException);
}


/**
 * \brief Test de la methode supprimerVol()
 *        Cas Invalide : lancement de VolAbsentException
 */
TEST_F(unAeroport,SupprimerVolAbsent){
    t_aeroport.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86"));
    ASSERT_THROW(t_aeroport.supprimeVol("JS1458"),VolAbsentException);
}

