#ifndef JEU
#define JEU

using namespace std;
#define NBCOL 8


#include "Echiquier.h"

class Jeu
{
    private:
       

    public:
        bool test_hors_plateau(string const & cmd) const;

        //affiche un message d'erreur temps que le coup saisis est hors plateau ou est mal écrit
        //un coup est composé d'un départ et d'une destination
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_saisie(Coup &coup) const;
       
        
        //Regarde si il y a bien une pièce dans la case de départ du coup
        bool test_case_vide(Coup &coup, Echiquier &echiquier) const;
       

        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_depart_coup(Coup &coup, Echiquier &echiquier) const;
        
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_couleur(Coup &coup, Echiquier &echiquier, couleur_t couleur) const;

       
        
        //demande où est ce que le joueur veux jouer, et enregistre les coordonnées saisies, en vérifiant la validité du coup
        Coup demander_coup(Echiquier &echiquier, couleur_t couleur) const;
       


        // bool saisie_correcte_petitroque(string const & cmd) {
        // regex mouvmtpattern("(O|o|0)-(O|o|0)");
            // return regex_match(cmd,mouvmtpattern);
        // }

        


};


#endif