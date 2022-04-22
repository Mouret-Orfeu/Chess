#include <string>
#include <iostream>



#include "Echiquier.h"



void Echiquier::set_coord_pion_blanc_vient_d_etre_jouer(int i, int j)
{
    coord_pion_blanc_vient_d_etre_jouer[0]= i;
    coord_pion_blanc_vient_d_etre_jouer[1]= j;
}

void Echiquier::set_coord_pion_noir_vient_d_etre_jouer(int i, int j)
{
    coord_pion_noir_vient_d_etre_jouer[0]= i;
    coord_pion_noir_vient_d_etre_jouer[1]= j;
}

vector<int> Echiquier::get_coord_pion_blanc_vient_d_etre_jouer()
{
    return coord_pion_blanc_vient_d_etre_jouer;
}

vector<int> Echiquier::get_coord_pion_noir_vient_d_etre_jouer()
{
    return coord_pion_noir_vient_d_etre_jouer;
}

Piece *** Echiquier::get_grille()
{
    return grille;
}

void Echiquier::pose_piece(Piece *piece_ptr, vector<int> coord)
{
    grille[coord[0]][coord[1]]= piece_ptr;
}

void Echiquier::alloc_mem_grille()
{
    grille= new Piece **[8];
    for(int l=0; l<NBCOL; l++)
    {
        grille[l]= new Piece *[8];
                
        for(int c=0; c<NBCOL; c++)
        {
            grille[l][c]= NULL;
        }
    }

    piecesb= new Piece *[8];
    piecesn= new Piece *[8];

    pionsb= new Piece *[8];
    pionsn= new Piece *[8];

}

Echiquier::Echiquier () 
{


    coord_pion_blanc_vient_d_etre_jouer= {-1,-1};
    coord_pion_noir_vient_d_etre_jouer= {-1,-1};


    alloc_mem_grille(); // --> alloue un tableau équivalent à un Piece *[8][8]
                           //     en initialisant les cases à nullptr 
                           //     et alloue des vecteurs piecesb, piecesn, pionsb

    // Constructeur (Couleur, representaion, coodonnée i, coordonnée j)
    piecesn[0] = new Tour    (noir,"\u2656",  0, 0);
    piecesn[1] = new Cheval  (noir,"\u2658",  0, 1);
    piecesn[2] = new Fou     (noir,"\u2657",  0, 2);
    piecesn[3] = new Reine   (noir,"\u2655",  3, 3);
    piecesn[4] = new Roi     (noir,"\u2654",  0, 4);
    piecesn[5] = new Fou     (noir,"\u2657",  0, 5);
    piecesn[6] = new Cheval  (noir,"\u2658",  0, 6);
    piecesn[7] = new Tour    (noir,"\u2656",  0, 7); 
    piecesb[0] = new Tour    (blanc,"\u265C",  7, 0);
    piecesb[1] = new Cheval  (blanc,"\u265E",  7, 1);
    piecesb[2] = new Fou     (blanc,"\u265D",  7, 2);
    piecesb[3] = new Reine   (blanc,"\u265B",  7, 3);
    piecesb[4] = new Roi     (blanc,"\u265A",  2, 2);
    piecesb[5] = new Fou     (blanc,"\u265D",  7, 5);
    piecesb[6] = new Cheval  (blanc,"\u265E",  7, 6);
    piecesb[7] = new Tour    (blanc,"\u265C",  7, 7);

    // allocation des pions
    for (int i=0; i<NBCOL; i++) 
    {
        pionsb[i] =  new Pion(noir, "\u2659", 1,i);
        pionsn[i] =  new Pion(blanc, "\u265F", 6,i);
    }

    // Pose des pieces en position initiale
    // pose des pieces blanches
    pose_piece(piecesn[3],piecesn[3]->get_pos());
    pose_piece(piecesb[4],piecesb[4]->get_pos());
    
    /*for (int i=0; i<NBCOL; i++) 
    {
        // met à jour le tableau grille, à la case donnée par 
        // la position courante de la pièce obtenue avec 
        // piecesb[i]->get_pos(),
        // avec le pointeur vers la pièce (piecesb[i]) //mal dit
        pose_piece(piecesb[i],piecesb[i]->get_pos());  
        pose_piece(pionsb[i],pionsb[i]->get_pos());

        pose_piece(piecesn[i],piecesn[i]->get_pos());  
        pose_piece(pionsn[i],pionsn[i]->get_pos());

        //AFFICHAGE DEBUG
        //vector<int> pos_1= pionsb[i]->get_pos();
        //int pos_i_1= pos_1[0];
        //int pos_j_1= pos_1[1];
        //printf("pos pion blanc %d: %d , %d\n", i, pos_i_1, pos_j_1);

        //vector<int> pos_2= piecesb[i]->get_pos();
        //int pos_i_2= pos_2[0];
        //int pos_j_2= pos_2[1];
        //printf("pos pieces blanc %d: %d , %d\n", i, pos_i_2, pos_j_2);

        //vector<int> pos_3= pionsn[i]->get_pos();
        //int pos_i_3= pos_3[0];
        //int pos_j_3= pos_3[1];
        //printf("pos pion noir %d: %d , %d\n", i, pos_i_3, pos_j_3);

        //vector<int> pos_4= piecesn[i]->get_pos();
        //int pos_i_4= pos_4[0];
        //int pos_j_4= pos_4[1];
        //printf("pos pieces noir %d: %d , %d\n", i, pos_i_4, pos_j_4);


    }*/
     
}

void Echiquier::affiche () const 
{

    string space5 = string(5,' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    "<< endl;
    cout << "  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐" << endl;
                       
    for (int i(NBCOL-1); i>=0 ;i--) 
    {
        cout << i+1 << " "; // numérotation ligne dans affichage
        for (int j(0);j<NBCOL;j++) 
        {
                cout << "|" ;
                if (grille[i][j]) 
                { 
                  cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                  grille[i][j]-> affiche();
                  cout << "\u0020" << " ";
                }
                else 
                        cout << space5;  // 2 ascii spaces
        }
        if(i!=0)
        {
            cout << "|\n  ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤";
            cout << endl;
        }
        else if(i== 0)
        {
            cout << "|\n  └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘";
        }
    }
   
}




void Echiquier::joue_le_coup(Coup &coup)
{
    vector<vector<int>> int_coup= coup.string_to_int_coord();
            
    //on récupère les coordonnées de départ et d'arrivée de la pièce pour plus de clareté
    vector<int> depart= coup.extract_coord_depart(int_coup);
    vector<int> destination= coup.extract_coord_destination(int_coup);

    //on récupère l'adresse de la piece à bouger
    Piece* piece_ptr= grille[depart[0]][depart[1]];




    string repr_piece= piece_ptr->get_repre();
    couleur_t couleur= piece_ptr->get_couleur();

    cout<<"AVANT: coord pion blanc vient de jouer : "<<coord_pion_blanc_vient_d_etre_jouer[0]<<" , "<<coord_pion_blanc_vient_d_etre_jouer[1]<<endl;
    cout<<"AVANT: coord pion noir vient de jouer : "<<coord_pion_noir_vient_d_etre_jouer[0]<<" , "<<coord_pion_noir_vient_d_etre_jouer[1]<<endl;


    //si la piece qu'on vient de jouer est un pion noir
    if(repr_piece.compare("\u2659") ==0) 
    {
        //si le coup joué est une prise en passant
        //i.e si on changé de colonne
        if(depart[1]!= destination[1])
        {
            //sans qu'il y ai une piece à manger sur la case destination
            if(grille[destination[0]][destination[1]]== NULL)
            {
                //on mange le pion en passant
                grille[destination[0]-1][destination[1]]= NULL;
            }
        }

       
        //on enregistre la nouvelle position du pion joué
        coord_pion_noir_vient_d_etre_jouer[0]= destination[0];
        coord_pion_noir_vient_d_etre_jouer[1]= destination[1];  
        ((Pion*)piece_ptr)->incr_nbr_de_coup();
    } 
    //si la piece qu'on vient de jouer est un pion blanc
    else if(repr_piece.compare("\u265F") ==0)
    { 
        //si le coup joué est une prise en passant
        //i.e si on changé de colonne
        if(depart[1]!= destination[1])
        {
            //sans qu'il y ai une piece à manger sur la case destination
            if(grille[destination[0]][destination[1]]== NULL)
            {
                //on mange le pion en passant
                grille[destination[0]+1][destination[1]]= NULL;
            }
        }

        coord_pion_blanc_vient_d_etre_jouer[0]= destination[0];
        coord_pion_blanc_vient_d_etre_jouer[1]= destination[1];  
        ((Pion*)piece_ptr)->incr_nbr_de_coup();
    } 
    //si la piece qu'on vient de jouer n'est ni un pion blanc, ni un pion noir
    else
    {
        //AFFICHAGE DEBUG
        printf("ON DEPLACE UNE PIECE NON PION");

        if(couleur== blanc)
        {
            //AFFICHAGE DEBUG
            printf(" BLANCHE\n");

            coord_pion_blanc_vient_d_etre_jouer[0]= -1;
            coord_pion_blanc_vient_d_etre_jouer[1]= -1; 
        }
        
        if(couleur== noir)
        {
            //AFFICHAGE DEBUG
            printf(" NOIRE\n");

            coord_pion_noir_vient_d_etre_jouer[0]= -1;
            coord_pion_noir_vient_d_etre_jouer[1]= -1; 
        }
    }

    //on modifie la grille de l'échiquier conformément au coup 

    //on met l'@ de piece jouée dans la case destination 
    grille[destination[0]][destination[1]]= piece_ptr;
    //on met NULL dans la case de départ du coup 
    grille[depart[0]][depart[1]]= NULL;

    //on met à jour la position de la pièce dans ses attributs
    piece_ptr->set_position(destination[0], destination[1]);
    
}

void Echiquier::free_pieces()
{
    for(int l=0; l<NBCOL; l++)
    {
        for(int c=0; c<NBCOL; c++)
        {
            if(grille[l][c]!= NULL)
                free(grille[l][c]);
        }
    }
}


string Echiquier::pgn_piece_name(string name, bool view_pawn, bool view_color) const 
{

    string psymb;
    if      (name=="\u2656") psymb="R";  // Rook W
    else if (name=="\u2658") psymb="N";  // Knight W
    else if (name=="\u2657") psymb="B";  // Bishop W
    else if (name=="\u2655") psymb="Q";  // Queen W
    else if (name=="\u2654") psymb="K";  // King W
    else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
    if (psymb.size()>0) // one of the white piece has been found
    {                       
            if (view_color)
                  return "w"+psymb;
            else
                  return psymb;
    } 
    if      (name=="\u265C") psymb= "R";  // Rook B
    else if (name=="\u265E") psymb= "N";  // Knight B
    else if (name=="\u265D") psymb= "B"; // Bishop B
    else if (name=="\u265B")  psymb= "Q"; // Queen B
    else if (name=="\u265A")  psymb= "K"; // King B
    else if (name.rfind("\u265F",0)==0 && view_pawn) psymb= "P"; // Pawn B
    if (psymb.size()>0) // one of the black piece has been found
    { 
            if (view_color)
                  return "b"+psymb;
            else
                  return psymb;
    } 
    else return "";
}

void Echiquier::canonical_position() const 
{
    string output;
    Piece* piece_ptr;
    for (int row=0; row< NBCOL; row++)
    {
        for (int col=0; col< NBCOL; col++) 
        {
            piece_ptr= grille[row][col]; 
            if (piece_ptr!=NULL)
            {
                string piece_repr= piece_ptr->get_repre();
                //true -> with P for pawns, true -> w/b for colors.
                output += pgn_piece_name(piece_repr,true,true);
            }

            output += ",";
        }
    }
    cout<<output<<endl;
}