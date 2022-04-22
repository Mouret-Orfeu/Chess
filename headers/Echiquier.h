#ifndef ECHIQUIER
#define ECHIQUIER

using namespace std;
#define NBCOL 8

#include <vector>

#include "Piece.h"



class Echiquier
{
    private: 
        //Pour la prise en passant, on va enregistrer les coordonnées des pions noir et blanc qu'on vient de jouer, si on vient d'en jouer
        //si on vient pas d'en jouer on mettra (-1,-1) dans les vecteurs 
        vector<int> coord_pion_blanc_vient_d_etre_jouer;
        vector<int> coord_pion_noir_vient_d_etre_jouer;


        Piece ***grille;
        
        Piece  **piecesb;
        Piece  **piecesn;

        Piece **pionsb;
        Piece **pionsn;

       


    public:
        //Echiquier(vector<int> coord_1, vector<int> coord_2): coord_pion_blanc_vient_d_etre_jouer(coord_1), coord_pion_noir_vient_d_etre_jouer(coord_2){};
        //constructeur
        Echiquier ();
        vector<int> get_coord_pion_blanc_vient_d_etre_jouer();

        vector<int> get_coord_pion_noir_vient_d_etre_jouer();

        void set_coord_pion_blanc_vient_d_etre_jouer(int i, int j);

        void set_coord_pion_noir_vient_d_etre_jouer(int i, int j);


        Piece *** get_grille();
        
        //Pose la piece pointé par piece_ptr aux coordonnées coord. On utilise cette fonction uniquement pour poser les pièces en position initial au début de la partie
        void pose_piece(Piece *piece_ptr, vector<int> coord);
        
        //Alloue la mémoire pour le tableau où on va mettre les pointeurs vers les pièces (ce tableau sera là où on jouera nos coup)
        void alloc_mem_grille();
       
        //affiche l'echiquier
        void affiche () const; 
        
        //modifie l'échiquier conformément au coup valide saisi par le joueur
        //en effet à ce stade on a déjà vérifié qu'on peut jouer le coup
        void joue_le_coup(Coup &coup);
        

        //une fois que la partie sera terminée, on free toutes les pièces qui restent (on aura free les pièces disparues dés leur désaparition)
        void free_pieces();

        //affiche la position de chaque piece en fin de partie selon l'affichage canonique
        void canonical_position() const; 

        //renvoie le code d'une pièce (ex: wK pour le roi blanc) à partir de sa représentation
        string pgn_piece_name(string const name, bool view_pawn, bool view_color) const;
        
        
};

#endif