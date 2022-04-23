#include <string>
using namespace std;
#include <iostream>
#include <vector>

#include "Piece.h"
#include "Echiquier.h"

/************************************************************************************************************/
//Piece

void Piece::affiche() const
{
    cout<<representation;
}

string Piece::get_repre()
{
    return representation;
}

vector<int> Piece::get_pos()
{
    vector<int> coord;
    coord.push_back(position_i);
    coord.push_back(position_j);

    return coord;
}

couleur_t Piece::get_couleur()
{
    return couleur;
}


void Piece::set_position(int pos_i, int pos_j)
{
    position_i= pos_i;
    position_j= pos_j;
}

bool Piece::traitement_collision(Coup &coup, Echiquier &echiquier, couleur_t couleur_joueur) const
{
    vector<vector<int>> int_coup= coup.string_to_int_coord();
    vector<int> destination     = coup.extract_coord_destination(int_coup);

    //AFFICHAGE DEBUG 
    int pos_i_dest= destination[0];
    int pos_j_dest= destination[1];
    printf("coord case destination coup: %d , %d\n", pos_i_dest, pos_j_dest);

    Piece ***grille= echiquier.get_grille();

    bool modif_string_coup= false;

    Piece * piece_destination_ptr= grille[destination[0]][destination[1]];

    //Si il n'y a pas de piece à la destination, on renvoie false (pour dire qu'on a pas besoin de modifier le coup pour qu'il respecte les collisions avec les autres pieces de sa couleur)
    if(piece_destination_ptr== NULL)
        return modif_string_coup;

    //Si il y a une piece sur la case destination
    else
    {
        couleur_t couleur_piece_dest= piece_destination_ptr->get_couleur();
        //Si la piece sur la case destination est de la même couleur que le joueur en train de jouer
        if(couleur_piece_dest== couleur_joueur)
        {
            string string_coup;

            modif_string_coup= true;
            cout<< "Il y a une pièce de votre couleur là où vous voulez jouer, veuillez entrer un autre coup\n"<< endl;
            cin>> string_coup;
            coup.set_string_coup(string_coup);
        }
    }    
    

    return  modif_string_coup;
}



bool Piece::traitement_deplacement_piece(Coup &coup, Echiquier &echiquier) const 
{
    //cette variable sert à savor si le joueur a dû saisir un nouveau coup car celui tapé n'était pas valide
    bool modif_string_coup= false;

    
    
    string string_coup= coup.get_string_coup();
    //on convertie le string_coup en int_coup (exemple a1b1 devient [[0,0],[1,0]])
    vector<vector<int>> int_coord_coup= coup.string_to_int_coord();
    //on extrait les coordonnées en int de la destination du coup
    vector<int> destination= coup.extract_coord_destination(int_coord_coup);
    vector<int> depart     = coup.extract_coord_depart(int_coord_coup);
    
    int jouable= test_mouvement_piece(destination, depart, echiquier);
    
    if(jouable== false)
    {
        modif_string_coup= true;
        cout<< "Cette pièce n'est pas capable de se déplacer ainsi, veuillez entrer un autre coup\n"<< endl;
        cin>> string_coup;
        coup.set_string_coup(string_coup);
        
        //AFFICHAGE DEBUG 
        string string_coup_affiche= coup.get_string_coup();
        cout<<"new coup: "<<string_coup_affiche<<endl;
    }     

    return modif_string_coup;
}



/****************************************************************************************************************/
//Pion 

//int Pion::getnb..

void Pion::incr_nbr_de_coup()
{
    nbr_de_coup++;
}


//on notera (i,j) la position de départ de la piece à déplacer 

bool Pion::test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const
{
    //AFFICHAGE DEBUG
    //cout<<representation<<endl;
    
    Piece*** grille= echiquier.get_grille();

    vector<int> coord_pion_vient_d_etre_jouer_blanc= echiquier.get_coord_pion_blanc_vient_d_etre_jouer();
    vector<int> coord_pion_vient_d_etre_jouer_noir= echiquier.get_coord_pion_noir_vient_d_etre_jouer();


    //pointeur vers la piece sur la case destination du pion
    Piece* piece_ptr= grille[destination[0]][destination[1]];

  
    //les blancs commenceront toujours en haut du plateau, les noir en bas
    if (couleur== blanc)
    { 
        //tester si destination== (i-1, j) (i.e si le pion est a avancé d'une case vers le bas en restant sur la meme colonne)
        //Et si il y a pas de pièce sur cette case
        if(destination[0]== depart[0]-1 && destination[1]== depart[1] && piece_ptr== NULL)
            return true;
        //voir si destination==(i-2, j) si premier coup
        else if(nbr_de_coup== 0 && destination[0]== depart[0]-2 && destination[1]== depart[1] && piece_ptr== NULL)
        {  
            //pointeur de piece dans la case devant le pion
            Piece* piece_devant_ptr= grille[depart[0]-1][depart[1]];
            if(piece_devant_ptr== NULL)
                return true;
        }
        //voir si destination==(i-1,j-1), si le pion peut manger à gauche
        else if(piece_ptr!= NULL && destination[0]== depart[0]-1 && destination[1]== depart[1]-1)
            return true;
        //voir si destinnation==(i-1,j+1), si le pion peut manger à droite
        else if(piece_ptr!= NULL && destination[0]== depart[0]-1 && destination[1]== depart[1]+1)
            return true;
        
        //voir pour la prise en passant à gauche
        //si il y a un pion noir qui vient d'être joué à gauche de la piece de départ du coup
        else if(coord_pion_vient_d_etre_jouer_noir[0]== depart[0] && coord_pion_vient_d_etre_jouer_noir[1]== depart[1]-1)
        {
            //si la destination est juste deriere le pion adverse
            if(destination[0]== depart[0]-1 && destination[1]== depart[1]-1)
            { 
                Piece * pion_adverse= grille[coord_pion_vient_d_etre_jouer_noir[0]][coord_pion_vient_d_etre_jouer_noir[1]];
                //si le pion adverse ne s'est deplacé qu'une fois
                if(((Pion*)pion_adverse)->nbr_de_coup==1)
                    //si on est sur la bonne ligne
                    if(depart[0]== 3)
                        return true;
            }
        }

        //voir pour la prise en passant à droite
        //si il y a un pion noir qui vient d'être joué à droite de la piece de départ du coup
        else if(coord_pion_vient_d_etre_jouer_noir[0]== depart[0] && coord_pion_vient_d_etre_jouer_noir[1]== depart[1]+1)
        {
            //si la destination est juste deriere le pion adverse
            if(destination[0]== depart[0]-1 && destination[1]== depart[1]+1)
            {    
                Piece * pion_adverse= grille[coord_pion_vient_d_etre_jouer_noir[0]][coord_pion_vient_d_etre_jouer_noir[1]];
                //si le pion adverse ne s'est deplacé qu'une fois
                if(((Pion*)pion_adverse)->nbr_de_coup==1)
                    //si on est sur la bonne ligne
                    if(depart[0]== 3)
                        return true;
            }
        }
            
    }
                
    if (couleur== noir)
    {
        //tester si destination== (i+1, j)
        if(destination[0]== depart[0]+1 && destination[1]== depart[1] && piece_ptr== NULL)
            return true;
        //voir (i+2, j) si premier coup
        else if(nbr_de_coup== 0 && destination[0]== depart[0]+2 && destination[1]== depart[1] && piece_ptr== NULL)
        {
            //pointeur de piece dans la case devant le pion
            Piece* piece_devant_ptr= grille[depart[0]+1][depart[1]];
            if(piece_devant_ptr== NULL)
                return true;
        }
        //voir si destination==(i+1,j-1), si le pion peut manger à gauche
        else if(piece_ptr!= NULL && destination[0]== depart[0]+1 && destination[1]== depart[1]-1)
            return true;
        //voir si destinnation==(i+1,j+1), si le pion peut manger à droite
        else if(piece_ptr!= NULL && destination[0]== depart[0]+1 && destination[1]== depart[1]+1)
            return true;
        
        //voir pour la prise en passant à gauche
        //si il y a un pion blanc qui vient d'être joué à gauche de la piece de départ du coup
        else if(coord_pion_vient_d_etre_jouer_blanc[0]== depart[0] && coord_pion_vient_d_etre_jouer_blanc[1]== depart[1]-1)
        {
            //AFFICHAGE DEBUG 
            printf("COORD PION VIENT D'ETRE JOUÉ OK \n");

            //si la destination est juste deriere le pion adverse
            if(destination[0]== depart[0]+1 && destination[1]== depart[1]-1)
            { 
                //AFFICHAGE DEBUG 
                printf("DESTINATION OK \n");

                Piece * pion_adverse= grille[coord_pion_vient_d_etre_jouer_blanc[0]][coord_pion_vient_d_etre_jouer_blanc[1]];
                //si le pion adverse ne s'est deplacé qu'une fois
                if(((Pion*)pion_adverse)->nbr_de_coup==1)
                {
                    //AFFICHAGE DEBUG 
                    printf("NOMBRE DE COUP PION OK\n");

                    //si on est sur la bonne ligne
                    if(depart[0]== 4)
                        return true;
                }
            }
        }

        //voir pour la prise en passant à droite
        //si il y a un pion blanc qui vient d'être joué à droite de la piece de départ du coup
        else if(coord_pion_vient_d_etre_jouer_blanc[0]== depart[0] && coord_pion_vient_d_etre_jouer_blanc[1]== depart[1]+1)
        {
            //si la destination est juste deriere le pion adverse
            if(destination[0]== depart[0]+1 && destination[1]== depart[1]+1)
            {    
                Piece * pion_adverse= grille[coord_pion_vient_d_etre_jouer_blanc[0]][coord_pion_vient_d_etre_jouer_blanc[1]];
                //si le pion adverse ne s'est deplacé qu'une fois
                if(((Pion*)pion_adverse)->nbr_de_coup==1)
                {    
                    //si on est sur la bonne ligne
                    if(depart[0]== 4)
                        return true;
                }
            }
        }
    }

    //Si on est rentré dans aucun des cas au dessus, c'est que le mouvement n'est pas valide et on renvoie false
    return false;
}

/****************************************************************************************************************/
//Tour

bool Tour::test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const
{
    //AFFICHAGE DEBUG
    //cout<<representation<<endl;

    Piece*** grille= echiquier.get_grille();
            
    //voir si destination est du type (i, j+ou-n)
    if(destination[0]== depart[0] && destination[1]!= depart[1])
    {  
        //test de collision 
        int it= depart[1];
        int dest= destination[1];

        //si la tour va à droit
        if((depart[1]-destination[1])<0)
        {
            it++;

            while(it!= dest)
            {
                if(grille[depart[0]][it]!= NULL)
                    return false;

                it++;
            }
            return true;
        }

        //si la tour va à gauche
        if((depart[1]-destination[1])>0)
        {
            it--;

            while(it!= dest)
            {
                if(grille[depart[0]][it]!= NULL)
                    return false;

                it--;
            }
            return true;
        }
    }

    //voir si destination est du type (i+ou-n, j) 
    if(destination[1]== depart[1] && destination[0]!= depart[0])
    {   
        //test de collision 
        int it= depart[0];
        int dest= destination[0];

        //si la tour va vers le bas
        if((depart[0]-destination[0])>0)
        {
            it--;

            while(it!= dest)
            {
                if(grille[it][depart[1]]!= NULL)
                    return false;
                
                it--;
            }
            return true;
        }

        //si la tour va vers le haut
        if((depart[0]-destination[0])<0)
        {
            it++;

            while(it!= dest)
            {
                if(grille[it][depart[1]]!= NULL)
                    return false;
                
                it++;
            }
            return true;
        }
    }

    //Si on est rentré dans aucun des cas au dessus, c'est que le mouvement n'est pas valide et on renvoie false
    return false;
}   

/****************************************************************************************************************/
//Cheval

bool Cheval::test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const
{
    (void)echiquier;

    //AFFICHAGE DEBUG
    //cout<<representation<<endl;
    
    //Piece*** grille= echiquier.get_grille();

    //voir si destination est du type (i+ou-1, j+ou-2) 
    if((destination[0]== depart[0]+1 || destination[0]== depart[0]-1) && (destination[1]== depart[1]+2 || destination[1]== depart[1]-2))
        return true;

    //voir si destination est du type (i+ou-2, j+ou-1)
    else if((destination[0]== depart[0]+2 || destination[0]== depart[0]-2) && (destination[1]== depart[1]+1 || destination[1]== depart[1]-1))
        return true;


    //Si on est rentré dans aucun des cas au dessus, c'est que le mouvement n'est pas valide et on renvoie false
    return false;
           

}   

/****************************************************************************************************************/
//Fou

bool Fou::test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const
{
    Piece*** grille= echiquier.get_grille();

    //n est le nombre de marche d'escalier dont s'est déplacé le fou (se déplacer d'une case en diagonale représentant une marche d'escalier)
    int n= destination[0]-depart[0];
            
    //voir si destination est du type (i+n, j-n) ou (i-n, j+n) 
    if(destination[0]== depart[0]+n && destination[1]== depart[1]-n && n!=0)
    {   
        //tests collisions
        int it_i= depart[0];
        int it_j=depart[1];
        int dest= destination[0];

        //si le Fou va en bas à droite
        if(n<0)
        {
            //AFFICHAGE DEBUG
            printf("on rentre dans le if vers le bas droite fou\n");
            
            it_i--;
            it_j++;

            while(it_i!= dest)
            {
                if(grille[it_i][it_j]!= NULL)
                    return false;

                it_i--;
                it_j++;
            }
            return true;
        }

        //si le Fou va à en haut à gauche
        if(n>0)
        {
            //AFFICHAGE DEBUG
            printf("on rentre dans le if vers le haut gauche fou\n");

            it_i++;
            it_j--;

            while(it_i!= dest)
            {
                
                if(grille[it_i][it_j]!= NULL)
                {    
                    //AFFICHAGE DEBUG
                    printf("on rentre dans le if collision adverse vers le haut gauche fou\n");
                    return false;
                }
                it_i++;
                it_j--;

            }
            return true;
        }
    } 

    //voir si destination est du type (i+n, j+n) ou (i-n, j-n) 
    if(destination[0]== depart[0]+n && destination[1]== depart[1]+n && n!=0)
    {  
        //tests collisions
        int it_i= depart[0];
        int it_j=depart[1];
        int dest= destination[0];

        //si le Fou va en haut à droite
        if(n>0)
        {
            //AFFICHAGE DEBUG
            printf("on rentre dans le if vers le haut droite fou\n");

            it_i++;
            it_j++;

            while(it_i!= dest)
            {
                if(grille[it_i][it_j]!= NULL)
                    return false;
                
                it_i++;
                it_j++;
            }
            return true;
        }

        //si le Fou va à en bas à gauche
        if(n<0)
        {
            //AFFICHAGE DEBUG
            printf("on rentre dans le if vers le bas gauche fou\n");

            it_i--;
            it_j--;

            while(it_i!= dest)
            {
                if(grille[it_i][it_j]!= NULL)
                    return false;
                
                it_i--;
                it_j--;
            }
            return true;
        }  
        
    }        
            

    //Si on est rentré dans aucun des cas au dessus, c'est que le mouvement n'est pas valide et on renvoie false
    return false;
           

} 


/****************************************************************************************************************/
//Reine

bool Reine::test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const
{
    //AFFICHAGE DEBUG
    //cout<<representation<<endl;
    
    Piece*** grille= echiquier.get_grille();
            
            
    //voir si destination est du type de celui d'une Tour (c'est le même code que la Tour)
            
    //voir si destination est du type (i, j+ou-n)
    if(destination[0]== depart[0] && destination[1]!= depart[1])
    {  
        //test de collision 
        int it= depart[1];
        int dest= destination[1];

        //si la tour va à droit
        if((depart[1]-destination[1])<0)
        {
            it++;

            while(it!= dest)
            {
                if(grille[depart[0]][it]!= NULL)
                    return false;

                it++;
            }
            return true;
        }

        //si la tour va à gauche
        if((depart[1]-destination[1])>0)
        {
            it--;

            while(it!= dest)
            {
                if(grille[depart[0]][it]!= NULL)
                    return false;

                it--;
            }
            return true;
        }
    }

    //voir si destination est du type (i+ou-n, j) 
    if(destination[1]== depart[1] && destination[0]!= depart[0])
    {   
        //test de collision 
        int it= depart[0];
        int dest= destination[0];

        //si la tour va vers le bas
        if((depart[0]-destination[0])>0)
        {
            it--;

            while(it!= dest)
            {
                if(grille[it][depart[1]]!= NULL)
                    return false;
                
                it--;
            }
            return true;
        }

        //si la tour va vers le haut
        if((depart[0]-destination[0])<0)
        {
            it++;

            while(it!= dest)
            {
                if(grille[it][depart[1]]!= NULL)
                    return false;
                
                it++;
            }
            return true;
        }
    }
   

    //voir si destination est du type de celui d'un Fou

    //n est le nombre de marche d'escalier dont s'est déplacé le fou (se déplacer d'une case en diagonale représentant une marche d'escalier)
    int n= destination[0]-depart[0];
            
    //voir si destination est du type (i+n, j-n) ou (i-n, j+n) 
    if(destination[0]== depart[0]+n && destination[1]== depart[1]-n && n!=0)
    {   
        //tests collisions
        int it_i= depart[0];
        int it_j=depart[1];
        int dest= destination[0];

        //si le Fou va en bas à droite
        if(n<0)
        {
            it_i--;
            it_j++;

            while(it_i!= dest)
            {
                if(grille[it_i][it_j]!= NULL)
                    return false;

                it_i--;
                it_j++;
            }
            return true;
        }

        //si le Fou va à en haut à gauche
        if(n>0)
        {
            it_i++;
            it_j--;

            while(it_i!= dest)
            {
                
                if(grille[it_i][it_j]!= NULL)
                    return false;

                it_i++;
                it_j--;

            }
            return true;
        }
    } 

    //voir si destination est du type (i+n, j+n) ou (i-n, j-n) 
    if(destination[0]== depart[0]+n && destination[1]== depart[1]+n && n!=0)
    {  
        //tests collisions
        int it_i= depart[0];
        int it_j=depart[1];
        int dest= destination[0];

        //si le Fou va en haut à droite
        if(n>0)
        {
            it_i++;
            it_j++;

            while(it_i!= dest)
            {
                if(grille[it_i][it_j]!= NULL)
                    return false;
                
                it_i++;
                it_j++;
            }
            return true;
        }

        //si le Fou va à en bas à gauche
        if(n<0)
        {
            it_i--;
            it_j--;

            while(it_i!= dest)
            {
                if(grille[it_i][it_j]!= NULL)
                    return false;
                
                it_i--;
                it_j--;
            }
            return true;
        }  
        
    }        

    //Si on est rentré dans aucun des cas au dessus, c'est que le mouvement n'est pas valide et on renvoie false
    return false;

}    


/****************************************************************************************************************/
//Roi

bool Roi::test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const
{
    //AFFICHAGE DEBUG
    cout<<representation<<endl;
    
    //Piece*** grille= echiquier.get_grille();
            
    //voir si destination est du type de celui d'une Tour, avec des déplacements d'une seule case

    //voir si destination est du type (i, j+ou-1) 
    if(destination[0]== depart[0] && (destination[1]== depart[1]+1 || destination[1]== depart[1]-1))
        return true;

    //voir si destination est du type (i+ou-1, j) 
    if(destination[1]== depart[1] && (destination[0]== depart[0]+1 || destination[0]== depart[0]-1))
        return true;
            


    //ou du type de celui d'un Fou, mais d'une seule case  
    int n= destination[0]-depart[0];

    if(n== 1 || n== -1)
    {
        //voir si destination est du type (i+1, j+1) ou (i-1, j-1) 
        if(destination[0]== depart[0]+n && destination[1]== depart[1]+n)
            return true;

        //voir si destination est du type (i+1, j-1) ou (i-1, j+1)
        if(destination[0]== depart[0]+n && destination[1]== depart[1]-n)
            return true;
    }


    //Si on est rentré dans aucun des cas au dessus, c'est que le mouvement n'est pas valide et on renvoie false
    return false;

}         
