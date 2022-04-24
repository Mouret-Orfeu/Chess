#include <string>
#include <iostream>
#include <vector>
#include <regex>

#include "Jeu.h"

void Jeu::demander_coup(Echiquier &echiquier, couleur_t couleur_joueur, Coup &coup) const
{

    cout<< "\n où voulez vous jouer? \n";
    string string_coup;
    cin>> string_coup;

    //on set up les valeurs initiales des attributs du coup
    coup.set_string_coup(string_coup);
    coup.set_piece_prise(NULL);

    bool modif_coup= true;

    Piece*** grille= echiquier.get_grille();
    Piece *piece_depart_ptr;

    //on va repasser tous les tests jusqu'à ce qu'on ai plus besoin de modifier le coup saisie
    while(modif_coup== true)
    {
        coup.set_type_de_coup(pas_un_roque);

        //on teste si le joueur veut arreter la partie
        if(coup.get_string_coup().compare("/quit")==0)
            break;

        //on teste si le joueur veut jouer un petit ou un grand roque
        bool bool_petit_roque= saisie_correcte_petitroque((string const)coup.get_string_coup());
        bool bool_grand_roque= saisie_correcte_grandroque((string const)coup.get_string_coup());

        if(bool_petit_roque== true || bool_grand_roque== true)
        {
            if(bool_petit_roque== true)
                coup.set_type_de_coup(petit_roque);
            if(bool_grand_roque== true)
                coup.set_type_de_coup(grand_roque);
            
            modif_coup= echiquier.traitement_roque(coup, couleur_joueur);

            //si le roque respact les conditions du roque (i.e on a pas du modifier le coup)
            //ce qui inclus le test de couleur et de pièce au départ du coup
            if(modif_coup== false)
            {
                //on test si on ne se met pas en echec en roquant
                modif_coup= traitement_auto_echec(coup, couleur_joueur, echiquier);
                
                if(modif_coup== true)
                    continue;
                else
                    break;

            }

            if(modif_coup== true)
                continue;
        }

        //on teste si le coup saisie est bien de la forme LettreChiffreLettreChiffre et que ça correspond bien à une case existante
        modif_coup= traitement_saisie(coup);

        if(modif_coup== true)
            continue;
                

        //on teste si il y a bien une pièce à déplacer aux coordonnées de départ du coup
        modif_coup= traitement_depart_coup(coup, echiquier);

        if(modif_coup== true)
            continue;

        //on teste si la piece est de la couleur du joueur qui doit jouer
        modif_coup= traitement_couleur(coup, echiquier, couleur_joueur);

        if(modif_coup== true)
            continue;


        //on récupère les coordonnées de la pièce qu'il faut bouger
        vector<vector<int>> int_coord_coup= coup.string_to_int_coord();
        vector<int> depart= coup.extract_coord_depart(int_coord_coup);
                
        //on test si la pièce aux cordonnées de départ du coup a la capacité de se déplacer à la destination saisie
        //Ce test prend en compte le fait qu'une pièces ne peuvent pas passer à travers une autre pièce (sauf pur le Cheval) 
        piece_depart_ptr= grille[depart[0]][depart[1]];


        modif_coup= piece_depart_ptr->traitement_deplacement_piece(coup, echiquier);

        if(modif_coup== true)
            continue;

        //on teste si il n'y a pas une pièce de la même couleur sur la case destination
        Piece *piece_destination_ptr= grille[depart[0]][depart[1]];
        
        modif_coup= piece_destination_ptr->traitement_collision(coup, echiquier, couleur_joueur);

        if(modif_coup== true)
            continue;
                
        modif_coup= traitement_auto_echec(coup, couleur_joueur, echiquier);
                
        if(modif_coup== true)
            continue;
    }
                
    return;
}

/******************************************************************************/

/******************************************************************************/

bool Jeu::saisie_correcte(string const & cmd) const
{
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);
}

/******************************************************************************/

bool Jeu::traitement_saisie(Coup &coup) const
{
    string string_coup=coup.get_string_coup();

    bool modif_string_coup= false;
    
    bool correcte= saisie_correcte(string_coup);
  
    if(correcte== false)
    {
        modif_string_coup= true;   
        cout<< "erreur de saisie, veuillez saisir un coup correspondant à un déplacement d'une case à une autre sur echiquier\n"<< endl;
        cin>> string_coup; 
        coup.set_string_coup(string_coup);
    }
            
    
            
    return  modif_string_coup;  
}

/******************************************************************************/

bool Jeu::test_case_vide(Coup &coup, Echiquier &echiquier) const
{
    Piece*** grille= echiquier.get_grille();

    //on convertie le string_coup en int_coup 
    vector<vector<int>> int_coord_coup= coup.string_to_int_coord();

    //on extrait les coordonnées en int de la case de départ du coup
    vector<int> int_depart= coup.extract_coord_depart(int_coord_coup);
            
    //on regarde dans la grille de l'echiquier, aux coordonnées correspondantes au départ du coup voulu, et on renvoie false si c'est une case vide, true sinon
    bool il_y_a_une_piece= true;
    if(grille[int_depart[0]][int_depart[1]]== NULL)
        il_y_a_une_piece= false;
           
    return il_y_a_une_piece;
}

/******************************************************************************/

bool Jeu::traitement_depart_coup(Coup &coup, Echiquier &echiquier) const
{
    bool modif_string_coup= false;

    bool jouable= test_case_vide(coup, echiquier);
  
    if(jouable== false) 
    {
        string string_coup;

        modif_string_coup= true;
        cout<< "Il n'y a pas de pièce à déplacer à la case saisie, veuillez entrer un autre coup\n"<< endl;
        cin>> string_coup;
        coup.set_string_coup(string_coup);
    }    
    
    return  modif_string_coup;
}

/******************************************************************************/

bool Jeu::traitement_couleur(Coup &coup, Echiquier &echiquier, couleur_t couleur) const
{
    vector<vector<int>> int_coup= coup.string_to_int_coord();
    vector<int> depart          = coup.extract_coord_depart(int_coup);
    vector<int> destination     = coup.extract_coord_destination(int_coup);

    Piece ***grille= echiquier.get_grille();

    bool modif_string_coup= false;

    couleur_t couleur_piece= grille[depart[0]][depart[1]]->get_couleur();

    if(couleur_piece != couleur)
    {
        string string_coup;

        modif_string_coup= true;
        cout<< "Cette pièce n'est pas à vous, veuillez essayer de déplacer une pièce de votre couleur\n"<< endl;
        cin>> string_coup;
        coup.set_string_coup(string_coup);
    }    
    

    return  modif_string_coup;
}

/******************************************************************************/


bool Jeu::traitement_auto_echec(Coup &coup, couleur_t couleur_joueur, Echiquier &echiquier) const 
{
    bool modif_string_coup= false;

    //pour tester si on va être en echec après ce coup, on va jouer le coup, tester l'echec, puis annuler le coup joué
    vector<vector<int>> int_coup= coup.string_to_int_coord();
    vector<int> depart          = coup.extract_coord_depart(int_coup);
    vector<int> destination     = coup.extract_coord_depart(int_coup);

    echiquier.joue_le_coup(coup, couleur_joueur, true);

    bool jouable= !(echiquier.test_echec(couleur_joueur));

    echiquier.annule_le_coup(coup, couleur_joueur);
  
    if(jouable== false) 
    {
        string string_coup;

        modif_string_coup= true;
        cout<< "\n vous ne pouvez pas jouer un coup qui vous met en echec, veuillez entrer un autre coup\n"<< endl;
        cin>> string_coup;
        coup.set_string_coup(string_coup);
    }    
    
    return  modif_string_coup;
}

/******************************************************************************/

bool Jeu::saisie_correcte_petitroque(string const & cmd) const
{
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

/******************************************************************************/

bool Jeu::saisie_correcte_grandroque(string const & cmd) const
{
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}
