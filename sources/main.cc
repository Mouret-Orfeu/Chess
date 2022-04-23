#include <iostream>
using namespace std;
#include "Jeu.h"




/*****************************************************************************/
int main() 
{

    Echiquier echiquier;   //initialise l'echiquier

    //AFFICHAGE DEBUG
    vector<int> get_coord_pion_blanc_vient_d_etre_jouer();
    vector<int> get_coord_pion_noir_vient_d_etre_jouer();

    Jeu jeu;             //initialise le jeu 
    
    couleur_t couleur_du_joueur= blanc;
    int it=0;
    
    bool stop(false);
    echiquier.affiche();
    
    do
    {
        Coup coup= jeu.demander_coup(echiquier, couleur_du_joueur);

        //AFFICHAGE DEBUG 
        string string_coup= coup.get_string_coup();
        cout<<"ce qui sort de demander_coup: "<<string_coup<<endl;

        if (string_coup!= "/quit") 
        {
            echiquier.joue_le_coup(coup, couleur_du_joueur, echiquier);
            echiquier.affiche();

            it++;
            if(it%2== 0)
                couleur_du_joueur= blanc;
            else
                couleur_du_joueur= noir;

        }
        else stop=true;
    } while (!stop);
}


