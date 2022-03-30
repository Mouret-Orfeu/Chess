#ifndef PIECE
#define PIECE

#include <string>
using namespace std;
#include <iostream>
#include <vector>

typedef enum couleur_t
{
    blanc,
    noir
}couleur_t;

class Piece
{
    private:

        couleur_t couleur;
        string representation; 
        int position_i;
        int position_j;
    
    public:
        Piece(couleur_t couleur, string repr, int i, int j): couleur(couleur), representation(repr), position_i(i), position_j(j){};
        ~Piece();

        void affiche() const
        {
            cout<<representation<<endl;
        }

        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        virtual bool test_mouvement_piece(vector<int> int_destination) const =0;
     
       

        //affiche un message d'erreur tant que le coup saisi est impossible à effectué par la pièce en question
        //le bool renvoyé est égal à true si il a fallu modifier string_coup pour terminer le traitement
        bool traitement_destination_coup(string &string_coup) const 
        {
            //cette variable sert à savor si le joueur a dû saisir un nouveau coup car celui tapé n'était pas valide
            bool modif_string_coup= false;

            int termine=0;
            while(!termine)
            {
                //on convertie le string_coup en int_coup 
                vector<vector<int>> int_coord_coup= Square::string_to_int_coord(string_coup);

                //on extrait les coordonnées en int de la destination du coup
                vector<int> int_destination= Square::get_destination(int_coord_coup);

                int jouable= test_mouvement_piece(int_destination);

                if(jouable== true)
                {
                    termine= 1;
                }
                else 
                {
                    modif_string_coup= true;

                    cout<< "Cette pièce n'est pas capable de se déplacer ainsi, veuillez taper une destination valide\n"<< endl;
                    cin>> string_coup;
                } 
                  
            }

            return modif_string_coup;
        }
        
};

class Pion: public Piece
{
    private:

    public:

        Pion(couleur_t couleur, string repr, int i, int j): Piece(couleur ,repr, i, j){};
        ~Pion();
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> int_destination) const override
        {
            //grille= get_grille();

            //les blancs commenceront toujours en bas du plateau, les noir en haut
            if (couleur== noir)
            {
                
                //tester si int_destination== (x, y-1)
                //voir (x, y-2) si premier coup
                //voir (x-1,y-1) et/ou (x+1,y-1) si le pion peut bouffer des pieces
                //voir prise en passant

                //return true si oui, false si non
            }
                        
            if (couleur== blanc)
            {
                //tester si int_destination== (x, y+1)
                //voir (x, y+2) si premier coup
                //voir (x+1,y+1) et/ou (x-1,y+1) si le pion peut bouffer des pieces
                //voir prise en passant

                //return true si oui, false si non
            }
        }
};


class Tour: public Piece
{
    private:
        
    public:
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> int_destination) const override
        {
            //grille= get_grille();

            //conversion string string_pos-> int_pos vect<int>
            
            //voir si int_destination est du type (x, y+ou-n) tq -1<y+ou-n<9 et (x+ou-n, y) tq -1<x+ou-n<9

            //return true si c'est le cas, false si non
        }     
};


class Cheval: public Piece
{
    private:
        
    public:
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> int_destination) const override
        {
            //grille= get_grille();

            
         
            //voir si int_destination est du type (x+ou-1, y+ou-2) tq -1>x+ou-1>9 et -1>y+ou-2>9 et (x+ou-2, y+ou-1) tq -1>x+ou-2>9 et -1>y+ou-1>9 

            //return true si oui, false si non
           

        }     
};

class Fou: public Piece
{
    private:
        
    public:
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> int_destination) const override
        {
            //grille= get_grille();
            
            bool coup_jouable= true;
            
            //voir si int_destination est du type (x+n, y+n), (x-n, y-n), (x+n, y-n), (x-n, y+n) tq les expresion des coord sont entre 0 et 8 inclus
                coup_jouable= false;
            

            //return true si oui, false si non
           

        }     
};

class Reine: public Piece
{
    private:
        
    public:
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> int_destination) const override
        {
            //grille= get_grille();
            
            
            //voir si int_destination est du type (x+n, y+n), (x-n, y-n), (x+n, y-n), (x-n, y+n) tq les expresion des coord sont entre 0 et 8 inclus
            //ou du type (x, y+ou-n) tq -1<y+ou-n<9 et (x+ou-n, y) tq -1<x+ou-n<9
                        
            //rtn true si oui, false si non

        }    
};

class Roi: public Piece
{
    private:
        
    public:
        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        bool test_mouvement_piece(vector<int> int_destination) const override
        {
            //grille= get_grille();
            
            
            //voir si int_destination est du type (x+1, y+1), (x-1, y-1), (x+1, y-1), (x-1, y+1) tq les expresion des coord sont entre 0 et 8 inclus
            //ou du type (x, y+ou-1) tq -1<y+ou-1<9 et (x+ou-1, y) tq -1<x+ou-1<9

            //rtn true si oui, false si non

        }         
};




#endif