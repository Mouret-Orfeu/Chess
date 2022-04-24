#include <iostream>
using namespace std;
#include "Jeu.h"




/*****************************************************************************/
int main() 
{

    Echiquier echiquier;                               //initialise l'echiquier
    Jeu jeu;                                           //initialise le jeu 
                                               
    //on créer 1 seul objet coup pour toute la partie
    //on le modifie à chaque fois qu'il le faut.
    Coup coup;             //initialisation de l'objet coup
    
    couleur_t couleur_joueur= blanc;
    int it=0;
    
    bool stop(false);
    echiquier.affiche();
    
    do
    {
        jeu.demander_coup(echiquier, couleur_joueur, coup);

        if ((coup.get_string_coup())!= "/quit") 
        {
            //AFFICHAGE DEBUG
            vector<int> depart= coup.get_depart_coup();
            Piece* piece_ptr= (echiquier.get_grille())[depart[0]][depart[1]];
            cout<<"piece_ptr MAIN :"<<piece_ptr<<endl;

            echiquier.joue_le_coup(coup, couleur_joueur, false);

            echiquier.affiche();

            echiquier.affiche_message_echec(couleur_joueur);

            it++;
            if(it%2== 0)
                couleur_joueur= blanc;
            else
                couleur_joueur= noir;

        }
        else stop=true;
    } while (!stop);
}


