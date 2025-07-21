#include <iostream>
using namespace std;
#include "Aeroport.h"
#include "Depart.h"
#include "Arrivee.h"
#include <clocale>
#include "validationFormat.h"


using namespace aerien;
using namespace util;
void fonctionPrincipal();
int main ()
{
    std::setlocale(LC_ALL, ".UTF8");

   Aeroport art = Aeroport("YUL");
   art.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86"));
   //art.ajouterVol(Depart("AC1636","AIR CANADA","18:00","ORLONDO","17:15","C86"));
    art.ajouterVol(Arrivee("RJ0271","ROYAL JORDANIAN","07:12","AMMAN"," Retardé "));
   //art.supprimeVol("AC1589");
    cout<<art.reqAeroportFormate ();
  return 0;
}

void functionPrincipal(){
    std::cout<<"Console de saisi des vols."<<std::endl;
    std::cout<<"Entrez nom de  l'aeroport:";
    std::string aeroport;
    std::cin>>aeroport;
    while(!estCodeValide(aeroport)){
        std::cout<<"Entrez nom un d'aeroport valide:";
        std::cin>>aeroport;
    }
    Aeroport art (aeroport);
    std::cout<<"Aeroport "<<art.reqCode()<<std::endl;
    std::cout<<"Console de Depart"<<std::endl;
    std::vector<std::unique_ptr<Vol>>vVol;
    std::string vol;
    std::string compagnie;
    char buffer[256];
    std::string heure;
    std::string ville;

    std::string embarquement;
    std::string porte;
    std::cout<<"Entrez un code de vol:";
    std::cin>>vol;
    while(!estNumeroVolValide(vol)){
        std::cout<<"Entrez un code de vol valide:";
        std::cin>>vol;
    }

    std::cin.ignore();
    std::cout<<"Entrez nom de la compagnie:";
    std::cin.getline(buffer,256);
    compagnie=buffer;

    while(!estNomValide(compagnie)){
        std::cout<<"Entrez  un nom de compagnie valide:";
        std::cin.getline(buffer,256);
        compagnie=buffer;
    }

    std::cout<<"Entrez l'heure de depart:";
    std::cin>>heure;
    while(!estFormat24HValide(heure)){
        std::cout<<"Entrez une heure de depart valide:";
        std::cin>>heure;
    }
    std::cin.ignore();
    std::cout<<"Entrez la ville de depart:";
    std::cin.getline(buffer,256);
    ville=buffer;
    while(!estNomValide(ville)){
        std::cout<<"Entrez la ville de depart:";
        std::cin.getline(buffer,256);
        ville=buffer;
    }
    std::cout<<"Entrez heure d'embarquement:";
    std::cin>>embarquement;
    while(!estFormat24HValide(embarquement)){
        std::cout<<"Entrez heure d'embarquement:";
        std::cin>>embarquement;
    }
    std::cin.ignore();

    while(!estPorteValide(porte)){
        std::cout<<"Entrez la porte d'embarquement:";
        std::cin>>porte;
    }
    auto depart =Depart(vol,compagnie,heure,ville,embarquement,porte);
    std::cout<<"saisi du depart terminer."<<std::endl;
    std::cout<<"\n\n";
    vVol.push_back(depart.clone());


    vol="";
    compagnie="";
    heure="";
    ville="";
    std::string statut;

    std::cout<<"Console d'arriver"<<std::endl;
    std::cout<<"Entrez un code de vol:";
    std::cin>>vol;
    while(!estNumeroVolValide(vol)){
        std::cout<<"Entrez un code de vol valide:";
        std::cin>>vol;
    }

    std::cin.ignore();
    std::cout<<"Entrez nom de la compagnie:";
    std::cin.getline(buffer,256);
    compagnie=buffer;

    while(!estNomValide(compagnie)){
        std::cout<<"Entrez  un nom de compagnie valide:";
        std::cin.getline(buffer,256);
        compagnie=buffer;
    }

    std::cout<<"Entrez l'heure d'arriver:";
    std::cin>>heure;
    while(!estFormat24HValide(heure)){
        std::cout<<"Entrez une heure de d'arriver valide:";
        std::cin>>heure;
    }
    std::cin.ignore();
    std::cout<<"Entrez la ville de d'arriver:";
    std::cin.getline(buffer,256);
    ville=buffer;
    while(!estNomValide(ville)){
        std::cout<<"Entrez une ville d'arriver valide:";
        std::cin.getline(buffer,256);
        ville=buffer;
    }
    std::cout<<"Entrez status:";
    std::cin.getline(buffer,256);
    statut=buffer;
    while(!(statut==" Atterri "||statut==" Retardé "||statut=="À l’heure")){
        std::cout<<"Entrez un status valide:";
        std::cin.getline(buffer,256);
        statut=buffer;
    }
    auto arriver = Arrivee(vol,compagnie,heure,ville,statut);
    std::cout<<"saisi d'arriver terminer."<<std::endl;
    vVol.push_back(arriver.clone());

    for(auto &e:vVol){
        art.ajouterVol(*e);
    }

    std::cout<<"\n\n";
    cout<<art.reqAeroportFormate();
}