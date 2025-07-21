//
// Created by chris on 6/25/2025.
//
#include "gtest/gtest.h"
#include "ContratException.h"
#include "Arrivee.h"
using namespace aerien;
/**
 * \brief Test du constructeur avec paramètres de la classe Arrivee
 *
 *   Cas valides :
 *     - ConstructeurParametreValide : Création d’un objet Arrivee avec un statut valide.
 *
 *   Cas invalides :
 *     - ConstructeurStatutInvalide : Statut est invalide.
 */
TEST(Arrivee,ConstructeurParametreValide)
{
    Arrivee a("WS0214","WESTJEST","00:34","CALGARY"," Atterri ");

    ASSERT_EQ(" Atterri ",a.reqStatut());
}

TEST(Arrivee,ConstructeurStatutInvalide){
    ASSERT_THROW(Arrivee a("WS0214","WESTJEST","00:34","CALGARY","Atterri"),PreconditionException)
                                <<"Le statut est invalid.";
}

/**
 * \class unArrivee
 * \brief Fixture pour les tests unitaires sur un objet Arrivee
 */
class unArrivee:public ::testing::Test{
public:
    unArrivee():
            t_arrivee("WS0214","WESTJEST","00:34","CALGARY","À l’heure"){}
    Arrivee t_arrivee;
};


/**
 * \brief Test de la méthode reqStatut()
 *        Cas valide : récupération correcte du statut
 */
TEST_F(unArrivee,reqStatut){
    ASSERT_EQ("À l’heure",t_arrivee.reqStatut());
}

/**
 * \brief Test de la méthode asgStatut()
 *   Cas valides :
 *     - asgStatusValide : assignation d’un statut
 *   Cas invalides :
 *     - asgStatusInvalide : mauvaise assignation d'un statut
 */
TEST_F(unArrivee,asgStatusValide){
    t_arrivee.asgStatut(" Retardé ");
    ASSERT_EQ(" Retardé ",t_arrivee.reqStatut());
}

TEST_F(unArrivee,asgStatusInvalide){
    ASSERT_THROW(t_arrivee.asgStatut("Retardé"),PreconditionException);
}


/**
 * \brief Test de la méthode reqVolFormate()
 *        Cas valide : formatage correct avec différents statuts
 */
TEST_F(unArrivee,reqVolFormate){
    ASSERT_EQ("|WS0214|     WESTJEST      |00:34|      CALGARY      |A l'heure |",t_arrivee.reqVolFormate());
    t_arrivee.asgStatut(" Retardé ");
    ASSERT_EQ("|WS0214|     WESTJEST      |00:34|      CALGARY      | Retarde  |",t_arrivee.reqVolFormate());
    t_arrivee.asgStatut(" Atterri ");
    ASSERT_EQ("|WS0214|     WESTJEST      |00:34|      CALGARY      | Atterri  |",t_arrivee.reqVolFormate());
}