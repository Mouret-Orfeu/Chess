#ifndef JEU
#define JEU

using namespace std;
#define NBCOL 7

#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <Coup.h>
#include <Jeu.h>
#include <Piece.h>
#include <Echiquier.h>

class Jeu
{
    private:
        Echiquier echiquier;

    public:
        bool test_hors_plateau(string const & cmd) 
        {
            regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
            return regex_match(cmd,mouvmtpattern);
        }

        //affiche un message d'erreur temps que le coup saisis est hors plateau ou est mal écrit
        //un coup est composé d'un départ et d'une destination
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_saisie(string &string_coup)
        {
            bool modif_string_coup= false;

            int termine=0;
            while(!termine)
            {
                bool correcte= Jeu::test_hors_plateau(string_coup);
                if(correcte= true)
                {
                    termine= 1;
                }
                else
                {
                    modif_string_coup= true;

                    cout<< "Ça ne correspond à aucune position de l'echiquier, veuillez réessayer\n"<< endl;
                    cin>> string_coup;
                    continue;
                }
            
            }
            
            return  modif_string_coup;  
        }
        

        bool test_case_vide(string string_coup)
        {
            //on regarde le char dans la grille, correspondant au départ du coup voulu, et on renvoie false si c'est une case vide, true sinon
        }

        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_depart_coup(string &string_coup) const 
        {
            bool modif_string_coup= false;

            int termine=0;
            while(!termine)
            {
                //on convertie le string_coup en int_coup 
                vector<vector<int>> int_coord_coup= Square::string_to_int_coord(string_coup);

                //on extrait les coordonnées en int de la destination du coup
                vector<int> int_depart= Square::get_depart(int_coord_coup);

                bool jouable= test_case_vide(int_depart);

                if(jouable== true)
                {
                    termine= 1;
                }
                else 
                {
                    modif_string_coup= true;

                    cout<< "Il n'y a pas de pièce à déplacer à la case saisie, veuillez recommencer\n"<< endl;
                    cin>> string_coup;
                    continue;
                }    
            }

            return  modif_string_coup;
        }

        //demande où est ce que le joueur veux jouer, et enregistre les coordonnées saisies, en vérifiant la validité du coup
        virtual string demander_coup() const
        {
            cout<< "où voulez vous jouer?\n";
            string string_coup;
            cin>> string_coup;

            bool modif_coup= true;

            //on va repasser tous les test jusqu'à ce qu'on ai plus besoin de modifier le coup saisie
            while(modif_coup== true)
            {
                modif_coup= traitement_saisie(&string_coup);

                if(modif_coup== true)
                    continue;

                modif_coup= traitement_depart_coup(&string_coup);

                if(modif_coup== true)
                    continue;


                modif_coup= Piece::traitement_destination_coup(&string_coup);

                if(modif_coup== true)
                    continue;
            }
                
            return string_coup;
        }

        // bool saisie_correcte_petitroque(string const & cmd) {
        // regex mouvmtpattern("(O|o|0)-(O|o|0)");
            // return regex_match(cmd,mouvmtpattern);
        // }


};


#endif