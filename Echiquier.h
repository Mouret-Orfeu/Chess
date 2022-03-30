#ifndef ECHIQUIER
#define ECHIQUIER

using namespace std;
#define NBCOL 8

#include <string>
#include <iostream>
#include <vector>
#include <Piece.h>
#include <Coup.h>


class Echiquier
{
    private: 
        Piece *echiquier[8][8];
        
        Piece  *piecesb[8];
        Piece  *piecesn[8];

        Piece *pionsb[8];
        Piece *pionsn[8];

       


    public:
        void alloc_mem_echiquier()
        {
            echiquier= new Piece **[8];
            for(int l=0; l<NBCOL; l++)
            {
                echiquier[l]= new Piece *[8];
                
                for(int c=0; c<NBCOL; c++)
                {
                    echiquier[l][c]= NULL;
                }
            }

            piecesb= new Piece *[8];
            piecesn= new Piece *[8];

            pionsb= new Piece *[8];
            pionsn= new Piece *[8];

        }



        // constructeur
        Echiquier () 
        {

            alloc_mem_echiquier(); // --> alloue un tableau équivalent à un Piece *[8][8]
                                   //     en initialisant les cases à nullptr 
                                   //     et alloue des vecteurs piecesb, piecesn, pionsb

            // Constructeur (Couleur, representaion, coodonnée i, coordonnée j)
            piecesb[0] = new Tour    (blanc," \u2656 ",  0, 0);
            piecesb[1] = new Cheval  (blanc," \u2658 ",  0, 1);
            piecesb[2] = new Fou     (blanc," \u2657 ",  0, 2);
            piecesb[3] = new Reine   (blanc," \u2655 ",  0, 3);
            piecesb[4] = new Roi     (blanc," \u2654 ",  0, 4);
            piecesb[5] = new Fou     (blanc," \u2657 ",  0, 5);
            piecesb[6] = new Cheval  (blanc," \u2658 ",  0, 6);
            piecesb[7] = new Tour    (blanc," \u2656 ",  0, 7); 
            piecesn[0] = new Tour    (noir, " \u265C ",  7, 0);
            piecesn[1] = new Cheval  (noir, " \u265E ",  7, 1);
            piecesn[2] = new Fou     (noir, " \u265D ",  7, 2);
            piecesn[3] = new Reine   (noir, " \u265B ",  7, 3);
            piecesn[4] = new Roi     (noir, " \u265A ",  7, 4);
            piecesn[5] = new Fou     (noir, " \u265D ",  7, 5);
            piecesn[6] = new Cheval  (noir, " \u265E ",  7, 6);
            piecesn[7] = new Tour    (noir, " \u265C ",  7, 7);

            // allocation des pions
            for (unsigned char i(0);i<NBCOL;i++) 
            {
                pionsb[i] =  new Pion(blanc, " \u2659 ", Square(1,i));
                pionsn[i] =  new Pion(noir,  " \u265F ", Square(6,i));
            }

            // Pose des pieces en position initiale
            // pose des pieces blanches
            for (unsigned char i(0);i<NBCOL;i++) 
                // met à jour le tableau echiquier, à la case donnée par 
                // la position courante de la pièce obtenue avec 
                // piecesb[i]->get_pos(),
                // avec le pointeur vers la pièce (piecesb[i])
                pose_piece(piecesb[i],piecesb[i]->get_pos());   

                // puis pose des pièces noires, pions blancs, pions noirs
                // ....
        }

        void pose_piece(Piece &piece, vector<int> coord)
        {
            echiquier[coord[0], coord[1]]= piece;
        }

        void affiche () const {

                string space5 = string(5,' ');
                cout << endl;
                cout << "     a     b     c     d     e     f     g     h    "<< endl;
                cout << "  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐" << endl;
                           
                for (int i(NBCOL-1);i>=1;i--) 
                {
                        cout << i+1 << " "; // numérotation ligne dans affichage
                        for (int j(0);j<NBCOL;j++) {
                                cout << "|" ;
                                if (echiquier[i][j]) { 
                                  cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                                  echiquier[i][j]-> affiche();
                                  cout << "\u0020" << " ";
                                }
                                else 
                                        cout << space5;  // 2 ascii spaces
                        }
                        cout << "|\n  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤";
                        cout << endl
                }
                cout << "|\n  └─────┴─────┴─────┴─────┴─────┴─────┴─────┴────┘"
        }
        
        //modifie l'échiquier conformément au coup valide saisi par le joueur
        void joue_le_coup(string string_coup)
        {
            vector<vector<int>> int_coup= string_to_int_coord(string string_coord);

            //on met l'@ de piece echiquier[int_coup[0][0], int_coup[0][1]] dans echiquier[int_coup[1][0], int_coup[1][1]]
            //on met NULL à l'@ de piece echiquier[int_coup[0][0], int_coup[0][1]]

        }

        //une fois que la partie sera terminée, on free toutes les pièces qui restent (on aura free les pièces disparues dés leur désaparition)
        void free_pieces()
        {
            for(int l=0; l<NBCOL; l++)
            {
                for(int c=0; c<NBCOL; c++)
                {
                    if(echiquier[l][c]!= NULL)
                        free(echiquier.echiquier[l][c]);
                }
            }
        }
}

#endif