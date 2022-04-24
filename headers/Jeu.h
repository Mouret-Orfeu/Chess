#ifndef JEU
#define JEU

using namespace std;
#define NBCOL 8


#include "Echiquier.h"

class Jeu
{
    private:
       

    public:
        bool saisie_correcte(string const & cmd) const;

        //affiche un message d'erreur temps que le coup saisis est hors plateau ou est mal écrit
        //un coup est composé d'un départ et d'une destination
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        //Si le bool== false, cela signifie que la syntaxe du coup est valide
        bool traitement_saisie(Coup &coup) const;
       
        
        //Regarde si il y a bien une pièce dans la case de départ du coup
        bool test_case_vide(Coup &coup, Echiquier &echiquier) const;
       

        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        //Si le bool== false, cela signifie qu'il y a bien une pièce au départ du coup
        bool traitement_depart_coup(Coup &coup, Echiquier &echiquier) const;
        
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        //Si le bool== false, cela signifie que la pièce à déplacer est de la bonne couleur
        bool traitement_couleur(Coup &coup, Echiquier &echiquier, couleur_t couleur) const;
        
        //demande où est ce que le joueur veux jouer, et enregistre les coordonnées saisies, en vérifiant la validité du coup
        void demander_coup(Echiquier &echiquier, couleur_t couleur, Coup &coup) const;
       
        //Regarde si le coup joué nous met nous même en echec, si oui, demande un autre coup et renvoie true, renvois juste false si non
        bool traitement_auto_echec(Coup &coup, couleur_t couleur_joueur, Echiquier &echiquier) const;

        bool saisie_correcte_petitroque(string const & cmd) const;

        bool saisie_correcte_grandroque(string const & cmd) const;
        

        


};


#endif