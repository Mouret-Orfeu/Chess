#include <string>
#include <iostream>
#include <vector>
#include <regex>

#include "Jeu.h"





bool Jeu::test_hors_plateau(string const & cmd) const
{
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);
}


bool Jeu::traitement_saisie(Coup &coup) const
{
    string string_coup=coup.get_string_coup();

    bool modif_string_coup= false;
    
    bool correcte= test_hors_plateau(string_coup);
  
    if(correcte== false)
    {
        modif_string_coup= true;   
        cout<< "erreur de saisie, veuillez saisir un coup correspondant à un déplacement d'une case à une autre sur echiquier\n"<< endl;
        cin>> string_coup; 
        coup.set_string_coup(string_coup);
    }
            
    
            
    return  modif_string_coup;  
}




bool Jeu::test_case_vide(Coup &coup, Echiquier &echiquier) const
{
    Piece*** grille= echiquier.get_grille();

    //AFFICHAGE DEBUG
    string string_coup_actuel= coup.get_string_coup();
    cout<<"coup actuel: "<<string_coup_actuel<<endl;

    //on convertie le string_coup en int_coup 
    vector<vector<int>> int_coord_coup= coup.string_to_int_coord();

    //on extrait les coordonnées en int de la case de départ du coup
    vector<int> int_depart= coup.extract_coord_depart(int_coord_coup);

    //AFFICHAGE DEBUG
    int pos_i_test= int_depart[0];
    int pos_j_test= int_depart[1];
    printf("coord case depart coup: %d , %d\n", pos_i_test, pos_j_test);
            
    //on regarde dans la grille de l'echiquier, aux coordonnées correspondantes au départ du coup voulu, et on renvoie false si c'est une case vide, true sinon
    bool il_y_a_une_piece= true;
    if(grille[int_depart[0]][int_depart[1]]== NULL)
        il_y_a_une_piece= false;
           
    return il_y_a_une_piece;
}


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

bool Jeu::traitement_couleur(Coup &coup, Echiquier &echiquier, couleur_t couleur) const
{
    vector<vector<int>> int_coup= coup.string_to_int_coord();
    vector<int> depart          = coup.extract_coord_depart(int_coup);
    vector<int> destination     = coup.extract_coord_destination(int_coup);

    Piece ***grille= echiquier.get_grille();

    bool modif_string_coup= false;

    couleur_t couleur_piece= grille[depart[0]][depart[1]]->get_couleur();

    if(couleur_piece== blanc)
        printf("jouer la piece blanche\n");
    if(couleur_piece== noir)
        printf("jouer la piece noire\n");

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



Coup Jeu::demander_coup(Echiquier &echiquier, couleur_t couleur_joueur) const
{
    cout<< "\n où voulez vous jouer? \n";
    string string_coup;
    cin>> string_coup;

    Coup coup(string_coup);

    bool modif_coup= true;

    Piece*** grille= echiquier.get_grille();
    Piece *piece_depart_ptr;

    //AFFICHAGE DEBUG 
    int compt=-1;

    //on va repasser tous les tests jusqu'à ce qu'on ai plus besoin de modifier le coup saisie
    while(modif_coup== true)
    {
        //AFFICHAGE DEBUG 
        compt++;
        string string_coup_while= coup.get_string_coup();
        cout<<"while boucle "<<compt<<" : "<<string_coup_while<<endl;

        //on teste si le joueur veut arreter la partie
        if(string_coup.compare("/quit")==0)
            break;

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


        modif_coup=traitement_auto_echec(coup, couleur_joueur, echiquier);
                
        if(modif_coup== true)
            continue;
    }
                
    return coup;
}

bool traitement_auto_echec(Coup &coup, couleur_t couleur_joueur, Echiquier &echiquier)
{
    bool modif_string_coup= false;

    bool jouable= echiquier.test_echec(couleur_joueur, echiquier);
  
    if(jouable== false) 
    {
        string string_coup;

        modif_string_coup= true;
        cout<< "vous ne pouvez pas jouer un coup qui vous met en echec, veuillez entrer un autre coup\n"<< endl;
        cin>> string_coup;
        coup.set_string_coup(string_coup);
    }    
    
    return  modif_string_coup;
}