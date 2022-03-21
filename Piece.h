#ifndef PIECE
#define PIECE

#include <string>
using namespace std;
#include <iostream>
#include <vector>

typedef enum couleur_t
{
    vide,
    blanc,
    noir
}couleur_t;

class Piece
{
    private:
        string nom;
        int couleur;
    
    public:

        void affiche() const
        {
            cout<<nom<<endl;
        }

        //affiche un message d'erreur temps que le coup saisis est hors plateau
        void traitement_saisie(string *string_position_ptr)
        {
            int termine=0;
            while(!termine)
            {
                bool correcte= Jeu::test_hors_plateau(string_position_ptr);
                if(correcte= true)
                {
                    continue;
                }
                else
                {
                    cout<< "Ça ne correspond à aucune position de l'echiquier, veuillez réessayer\n"<< endl;
                    cin>> *string_position_ptr;
                    continue;
                }
                termine= 1;
            
            }
        }

        //retourne l'ensemble des positions accessibles à une piece
        virtual vector<string> calcul_coups_possibles(string string_position) const=0;

        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        virtual bool test_mouvement_piece(string string_position) const =0;

        //affiche un message d'erreur tant que le coup saisi est impossible à effectué par la pièce en question
        string traitement_coup(string *string_position_ptr) const =0;

        //demande où est ce que le joueur veux jouer, et enregistre les coordonnées saisies
        virtual vector<int> ou_jouer() const =0;

        
       

        
};

class pion: public Piece
{
    private:

    public:
        //retourne l'ensemble des positions accessibles à une piece
        virtual vector<vector<int>> calcul_coups_possibles(string string_position)
        {
            //conversion string string_pos-> int_pos vect<int>
            //if blanc:
                        //ajouter 1 dans le bon sens à la coord y
                        //voir 2 si premier coup
                        //voir diagos si piece à bouffer
                        //voir prise en passant
            //if noir :
                        //ajouter 1 dans le bon sens à la coord y
                        //voir 2 si premier coup
                        //voir diagos si piece à bouffer
                        //voir prise en passant

        }

        //retourne si oui ou non, une piece a la capacité de se déplacer aux coordonnées saisis
        virtual bool test_mouvement_piece(string string_position) const 
        {
            
            
            vector<vector<int>> coups_possibles= calcul_coups_possibles(string_position);

            //for tout les coups_possibles:
            //comparer
        }
        


        virtual vector<int> ou_jouer() const
        {
            cout<< "où voulez vous jouer?\n";
            string string_position;
            cin>> string_position;

            traitement_saisie(string_position);

            traitement_coup()
            
            

                return n;
            }
        }

        virtual string traitement_coup(string *string_position_ptr) const 
        {
            bool jouable= test_mouvement_piece(*string_position_ptr);

            int termine=0;
            while(!termine)
            {
                if(jouable= true)
                {
                    continue;
                }
                else
                {
                    cout<< "Cette pièce n'est pas capable de se déplacer ainsi, veuillez taper une destination valide \n"<< endl;
                    cin>> *string_position_ptr;
                    continue;
                }
                termine= 1;
                
            }
        }

}
#endif