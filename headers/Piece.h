#ifndef PIECE
#define PIECE

using namespace std;

#include <string>
#include <iostream>
#include <vector>

#include "Coup.h"

class Echiquier;
typedef enum couleur_t
{
    blanc,
    noir
}couleur_t;

class Piece
{
    protected:

        couleur_t couleur;
        string representation; 
        int position_i;
        int position_j;
    
    public:
        Piece(couleur_t couleur, string repr, int i, int j): couleur(couleur), representation(repr), position_i(i), position_j(j){};
        ~Piece();

        void affiche() const;
       
        string get_repre();

        vector<int> get_pos();

        couleur_t get_couleur();

        void set_position(int pos_i, int pos_j);

       

        //retourne si oui ou non, la piece a la capacité de se déplacer aux coordonnées saisis (le fait que la case destination se trouve bien sur l'echiquier a deja été verifié)
        virtual bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const =0;
     
       
        //affiche un message d'erreur tant que le coup saisi est impossible à effectué par la pièce en question
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_deplacement_piece(Coup &coup, Echiquier &echiquier) const;

        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_collision(Coup &coup, Echiquier &echiquier, couleur_t couleur_joueur) const;
       
        
};

class Pion: public Piece
{
    private:
        int nbr_de_coup;

    public:
        Pion(couleur_t couleur, string repr, int i, int j, int nbr_de_coup= 0): Piece(couleur ,repr, i, j){};
        ~Pion();

        void incr_nbr_de_coup();

        void set_bool_premier_coup();

        void set_vient_d_etre_jouer(bool boul);

       
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        //dans les commentaires, on appailera (x,y) les coordonnées de départ du coup
        bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const ;
        
};


class Tour: public Piece
{
    private:
        
    public:
        Tour(couleur_t couleur, string repr, int i, int j): Piece(couleur ,repr, i, j){};
        ~Tour();

        //retourne si oui ou non, la piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const;
        
};


class Cheval: public Piece
{
    private:
        
    public:
        Cheval(couleur_t couleur, string repr, int i, int j): Piece(couleur ,repr, i, j){};
        ~Cheval();


        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const;
       
};

class Fou: public Piece
{
    private:
        
    public:
        Fou(couleur_t couleur, string repr, int i, int j): Piece(couleur ,repr, i, j){};
        ~Fou();


        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const;
        
};

class Reine: public Piece
{
    private:
        
    public:
        Reine(couleur_t couleur, string repr, int i, int j): Piece(couleur ,repr, i, j){};
        ~Reine();

        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const;       
};

class Roi: public Piece
{
    private:
        
    public:
        Roi(couleur_t couleur, string repr, int i, int j): Piece(couleur ,repr, i, j){};
        ~Roi();


        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> destination, vector<int> depart, Echiquier &echiquier) const;         
};




#endif