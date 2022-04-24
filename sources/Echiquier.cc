#include <string>
#include <iostream>
using namespace std;



#include "Echiquier.h"
#include "Jeu.h"

/******************************************************************************/

void Echiquier::set_coord_pion_blanc_vient_d_etre_jouer(int i, int j)
{
    coord_pion_blanc_vient_d_etre_jouer[0]= i;
    coord_pion_blanc_vient_d_etre_jouer[1]= j;
}

/******************************************************************************/

void Echiquier::set_coord_pion_noir_vient_d_etre_jouer(int i, int j)
{
    coord_pion_noir_vient_d_etre_jouer[0]= i;
    coord_pion_noir_vient_d_etre_jouer[1]= j;
}

/******************************************************************************/

vector<int> Echiquier::get_coord_pion_blanc_vient_d_etre_jouer() const
{
    return coord_pion_blanc_vient_d_etre_jouer;
}

/******************************************************************************/

vector<int> Echiquier::get_coord_pion_noir_vient_d_etre_jouer() const
{
    return coord_pion_noir_vient_d_etre_jouer;
}

/******************************************************************************/

Piece *** Echiquier::get_grille() const
{
    return grille;
}

/******************************************************************************/

void Echiquier::pose_piece(Piece *piece_ptr, vector<int> coord)
{
    grille[coord[0]][coord[1]]= piece_ptr;
}

/******************************************************************************/

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

/******************************************************************************/

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
    piecesn[3] = new Reine   (noir,"\u2655",  0, 3);
    piecesn[4] = new Roi     (noir,"\u2654",  0, 4);
    piecesn[5] = new Fou     (noir,"\u2657",  0, 5);
    piecesn[6] = new Cheval  (noir,"\u2658",  0, 6);
    piecesn[7] = new Tour    (noir,"\u2656",  0, 7); 
    piecesb[0] = new Tour    (blanc,"\u265C",  7, 0);
    piecesb[1] = new Cheval  (blanc,"\u265E",  7, 1);
    piecesb[2] = new Fou     (blanc,"\u265D",  7, 2);
    piecesb[3] = new Reine   (blanc,"\u265B",  7, 3);
    piecesb[4] = new Roi     (blanc,"\u265A",  7, 4);
    piecesb[5] = new Fou     (blanc,"\u265D",  7, 5);
    piecesb[6] = new Cheval  (blanc,"\u265E",  7, 6);
    piecesb[7] = new Tour    (blanc,"\u265C",  7, 7);
    
    // allocation des pions
    for (int i=0; i<NBCOL; i++) 
    {
        pionsn[i] =  new Pion(noir, "\u2659", 1,i);
        pionsb[i] =  new Pion(blanc, "\u265F", 6,i);
    }

    // Pose des pieces en position initiale
    // pose des pieces blanches
  
    for (int i=0; i<NBCOL; i++) 
    {
        pose_piece(piecesb[i],piecesb[i]->get_pos());  
        pose_piece(pionsb[i],pionsb[i]->get_pos());

        pose_piece(piecesn[i],piecesn[i]->get_pos());  
        pose_piece(pionsn[i],pionsn[i]->get_pos());
    }

  

      
  
     
}

/******************************************************************************/

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

/******************************************************************************/

void Echiquier::joue_le_coup(Coup &coup, couleur_t couleur_joueur, bool pour_tester_auto_echec)
{
    //jouer un roque***********************************************************/

    //gerer le roque
    bool roque= gerer_le_roque(coup, couleur_joueur);

    if(roque== true)
        return;
    
        

    //jouer un coup normale****************************************************/

    //accès aux variables utiles***********************************************/

    vector<vector<int>> int_coup= coup.string_to_int_coord();
            
    //on récupère les coordonnées de départ et d'arrivée de la pièce pour plus de clareté
    vector<int> depart= coup.extract_coord_depart(int_coup);
    vector<int> destination= coup.extract_coord_destination(int_coup);

    //met à jour depart et destination du dernier coup dans l'objet coup
    coup.set_depart_destination_coup(depart, destination);

    //on récupère l'adresse de la piece à jouer
    Piece* piece_ptr= grille[depart[0]][depart[1]];

    //on recupère la représentation de la piece à jouer, et sa couleur
    string repr_piece= piece_ptr->get_repre();
    couleur_t couleur= piece_ptr->get_couleur();

    //avant de jouer le coup,
    //on enregistre les coordonnées des pions qui viennent d'être joué 
    coup.set_coord_pion_vient_d_etre_jouer_avant(coord_pion_blanc_vient_d_etre_jouer, coord_pion_noir_vient_d_etre_jouer);

    //actions à réaliser******************************************************

    //gerer la prise en passant (ne déplace pas notre pion, mange juste le pion adverse, et met à jour les coordonnées des derniers pions déplacés)
    gerer_prise_en_passant(repr_piece, depart, destination, coord_pion_noir_vient_d_etre_jouer, coord_pion_blanc_vient_d_etre_jouer, piece_ptr, couleur, coup);

    //on modifie la grille de l'échiquier conformément au coup 
    deplacement_piece(destination, depart, piece_ptr, coup);

    //si je suis pas en train de jouer le coup juste pour tester l'auto echec
    if(pour_tester_auto_echec== false)
        gerer_promotion(coup, piece_ptr);


    //on incrémente le nbr de coup de la piece
    piece_ptr->incr_nbr_de_coup();
}


/******************************************************************************/

bool Echiquier::gerer_le_roque(Coup &coup, couleur_t couleur)
{
    string string_coup= coup.get_string_coup();

    type_de_coup_t type_de_coup= coup.get_type_de_coup();

    if(type_de_coup== petit_roque)
    {
        jouer_le_roque(coup, couleur, petit_roque);
        return true;
    }
    else if(type_de_coup== grand_roque)
    {
        jouer_le_roque(coup, couleur, grand_roque);
        return true;
    }
    else
        return false;
}

/******************************************************************************/

void Echiquier::jouer_le_roque(Coup &coup, couleur_t couleur, type_de_coup_t roque)
{
    string string_coup= coup.get_string_coup();

    Piece *roi_ptr;
    Piece *tour_ptr;
        
    vector<int> depart_roi;
    vector<int> destination_roi;

    vector<int> depart_tour;
    vector<int> destination_tour;
   
    if(couleur== blanc)
    {
        roi_ptr= piecesb[4];
        depart_roi= roi_ptr->get_pos();

        if(roque== petit_roque)
        {
            tour_ptr        = piecesb[7];
            destination_roi = {7,6};
            depart_tour     = {7,7}; 
            destination_tour= {7,5};

        }
        //si roque== grand_roque
        else 
        {
            tour_ptr        = piecesb[0];
            destination_roi = {7,2};
            depart_tour     = {7,0}; 
            destination_tour= {7,3};
        }
    }
    //si couleur== noir
    else
    {
        roi_ptr= piecesn[4];
        depart_roi= roi_ptr->get_pos();
        
        if(roque== petit_roque)
        {
            tour_ptr         = piecesn[7];
            destination_roi  = {0,6};
            depart_tour      = {0,7}; 
            destination_tour = {0,5};
        }
        //si roque== grand_roque
        else 
        {
            tour_ptr        = piecesn[0];
            destination_roi = {0,2};
            depart_tour     = {0,0}; 
            destination_tour= {0,3};
        }  
    }

    deplacement_piece(destination_roi, depart_roi, roi_ptr, coup);
    deplacement_piece(destination_tour, depart_tour, tour_ptr, coup);
}

/******************************************************************************/

void Echiquier::gerer_prise_en_passant(string repr_piece, vector<int> depart, vector<int> destination, vector<int> coord_pion_noir_vient_d_etre_jouer, vector<int> coord_pion_blanc_vient_d_etre_jouer, Piece* piece_ptr, couleur_t couleur, Coup &coup)
{
    //si la piece qu'on vient de jouer est un pion noir
    if(repr_piece.compare("\u2659") ==0) 
    {
        //si le coup joué est une prise en passant
        //i.e si on change de colonne
        if(depart[1]!= destination[1])
        {
            //sans qu'il y ai une piece à manger sur la case destination
            if(grille[destination[0]][destination[1]]== NULL)
            {

                //on enregistre ce qu'on mange dans struct_coup_precedent en dans Coup
                coup.set_piece_prise(grille[destination[0]-1][destination[1]]);

                //on mange le pion en passant
                grille[destination[0]-1][destination[1]]= NULL;
            }
        }

        //on enregistre la nouvelle position du pion joué
        this->set_coord_pion_noir_vient_d_etre_jouer(destination[0], destination[1]);
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
                //on enregistre ce qu'on mange dans struct_coup_precedent
                coup.set_piece_prise(grille[destination[0]+1][destination[1]]);

                //on mange le pion en passant
                grille[destination[0]+1][destination[1]]= NULL;
            }
        }

        this->set_coord_pion_blanc_vient_d_etre_jouer(destination[0], destination[1]);

    } 
    //si la piece qu'on vient de jouer n'est ni un pion blanc, ni un pion noir
    else
    {

        if(couleur== blanc)
        {
            coord_pion_blanc_vient_d_etre_jouer[0]= -1;
            coord_pion_blanc_vient_d_etre_jouer[1]= -1; 
        }
        
        if(couleur== noir)
        {
            coord_pion_noir_vient_d_etre_jouer[0]= -1;
            coord_pion_noir_vient_d_etre_jouer[1]= -1; 
        }

        
    }

    //cout<<"ECHIQUIER fin gerer prise: coord pion blanc :"<<coord_pion_blanc_vient_d_etre_jouer[0]<<","<<coord_pion_blanc_vient_d_etre_jouer[1]<<endl;
    //cout<<"ECHIQUIER fin gerer prise: coord pion noir:"<<coord_pion_noir_vient_d_etre_jouer[0]<<","<<coord_pion_noir_vient_d_etre_jouer[1]<<endl;
}

/******************************************************************************/

void Echiquier::deplacement_piece(vector<int> destination, vector<int> depart, Piece *piece_ptr, Coup &coup)
{

    //Si on va manger une piece, on enregistre cette piece dans 
    if(grille[destination[0]][destination[1]]!= NULL)
    {
        coup.set_piece_prise(grille[destination[0]][destination[1]]);
    }

    

    //on met l'@ de piece jouée dans la case destination 
    grille[destination[0]][destination[1]]= piece_ptr;

    //on met NULL dans la case de départ du coup 
    grille[depart[0]][depart[1]]= NULL;

    //on met à jour la position de la pièce dans ses attributs
    piece_ptr->set_position(destination[0], destination[1]);

}

/******************************************************************************/

void Echiquier::affiche_message_echec(couleur_t couleur_joueur)
{
    if(couleur_joueur== blanc)
    {
        if(test_echec(noir)== true)
        {
            cout<<"\n echec au roi noir"<<endl;
        }
    }
    else if(couleur_joueur== noir)
    {
        if(test_echec(blanc)== true)
        {
            cout<<"\n echec au roi blanc"<<endl;
        }
    }
}

/******************************************************************************/

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

    for(auto Piece_ptr : pieces_promues_blanches)
    {
        free(Piece_ptr);
    }

    for(auto Piece_ptr : pieces_promues_noires)
    {
        free(Piece_ptr);
    }
}

/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

bool Echiquier::test_echec(couleur_t couleur_Roi) const
{
    Piece *roi_ptr;
    Piece **pieces_adverses;
    Piece **pions_adverses;
    
    
    if(couleur_Roi== blanc)
    {
        roi_ptr= piecesb[4];
        
        pieces_adverses= piecesn;
        pions_adverses = pionsn;
        
    }
        
    else 
    {
        roi_ptr= piecesn[4];
        pions_adverses = pionsb;
        pieces_adverses= piecesb;
    }

    vector<int> destination= roi_ptr->get_pos();

    vector<int> depart;

    //On va tester pour chaque piece adverse, si elle peut se déplacer sur la case du roi
    for(int k=0; k<NBCOL; k++)
    {
        depart= pieces_adverses[k]->get_pos();

        if(pieces_adverses[k]->test_mouvement_piece(destination, depart, *this)== true)
            return true;
        

        depart= pions_adverses[k]->get_pos();

        if(pions_adverses[k]->test_mouvement_piece(destination, depart, *this)== true)
            return true;
        
           
    }
    //On va tester pour chaque pièces promues si elles peuvent se déplacer sur la case du roi
    for(auto piece_ptr : pieces_promues_blanches)
    {
        depart= piece_ptr->get_pos();

        if(piece_ptr->test_mouvement_piece(destination, depart, *this)== true)
            return true;
    }
    for(auto piece_ptr : pieces_promues_noires)
    {
        depart= piece_ptr->get_pos();

        if(piece_ptr->test_mouvement_piece(destination, depart, *this)== true)
            return true;
    }

    return false;  
}

void Echiquier::annule_le_coup(Coup &coup, couleur_t couleur)
{
    //on va mettre dans destination la destination du coup à annuler
    //on va mettre dans depart, le depart du coup à annuler

    type_de_coup_t type_de_coup= coup.get_type_de_coup();

    //si le dernier coup est un roque
    if(type_de_coup!= pas_un_roque)
    {
        Piece *roi_ptr;
        Piece *tour_ptr;
        
        vector<int> depart_roi;
        vector<int> destination_roi;

        vector<int> depart_tour;
        vector<int> destination_tour;

        if(type_de_coup== petit_roque)
        {
            if(couleur== blanc)
            {
                roi_ptr= piecesb[4];
                destination_roi= roi_ptr->get_pos();
                
                tour_ptr        = piecesb[7];
                depart_roi      = {7,4};

                depart_tour     = {7,7}; 
                destination_tour= {7,5};

                //on décrémente le nombre de coup du roi et de la tour
                roi_ptr->decr_nbr_de_coup();
                tour_ptr->decr_nbr_de_coup();
            }
            //si (couleur== noir)
            else
            {
                roi_ptr        = piecesn[4];
                destination_roi= roi_ptr->get_pos();
                
                tour_ptr  = piecesn[7];
                depart_roi= {0,4};

                depart_tour     = {0,7}; 
                destination_tour= {0,5};

                //on décrémente de 2 le nbre de coup de pieces bougé parce qu'on a incrémenté de 1 pour jouer le coup et de 1 pour l'annuler
                roi_ptr->decr_nbr_de_coup();
                tour_ptr->decr_nbr_de_coup();

            }
        }
        //si (type_coup_precedent== grand_roque)
        else
        {
            if(couleur== blanc)
            {
                roi_ptr= piecesb[4];
                destination_roi= roi_ptr->get_pos();
                
                tour_ptr  = piecesb[0];
                depart_roi= {7,4};

                depart_tour     = {7,0}; 
                destination_tour= {7,3};


                //on décrémente de 2 le nbre de coup de pieces bougé parce qu'on a incrémenté de 1 pour jouer le coup et de 1 pour l'annuler
                roi_ptr->decr_nbr_de_coup();
                tour_ptr->decr_nbr_de_coup();
            }
            //si (couleur== noir)
            else
            {
                roi_ptr= piecesn[4];
                destination_roi= roi_ptr->get_pos();
                
                tour_ptr  = piecesn[0];
                depart_roi= {0,4};

                depart_tour     = {0,0}; 
                destination_tour= {0,3};

                //on décrémente de 2 le nbre de coup de pieces bougé parce qu'on a incrémenté de 1 pour jouer le coup et de 1 pour l'annuler
                roi_ptr->decr_nbr_de_coup();
                tour_ptr->decr_nbr_de_coup();
            }
        }

        //on fait le deplacement inverse du roque: de la destination au depart
        deplacement_piece(depart_roi, destination_roi, roi_ptr, coup);
        deplacement_piece(depart_tour, destination_tour, tour_ptr, coup);

        
    }
    // si le dernier coup n'est pas un roque
    else
    {
        vector<int> depart= coup.get_depart_coup();
        vector<int> destination= coup.get_destination_coup();

        Piece *piece_ptr= grille[destination[0]][destination[1]];

        //AFFICHAE DEBUG
        //cout<<"on a réussit à prendre la piece"<<endl;

        //on remet l'@ de piece jouée dans la case de départ
        grille[depart[0]][depart[1]]= piece_ptr;

        //on met NULL dans la case de destination du coup 
        grille[destination[0]][destination[1]]= NULL;

        //AFFICHAE DEBUG
        //cout<<"on a réussit à reverse le coup"<<endl;

        //on remet la position de la piece comme avant le coup
        piece_ptr->set_position(depart[0], depart[1]);

        //on décremente le nombre de coup joué par la pièce de 1 (et pas de 2 parce que cette fois on utilise pas la fonction deplcement_piece)
        piece_ptr->decr_nbr_de_coup();

        //AFFICHAE DEBUG
        //cout<<"set_position piece et decr passé"<<endl;

        //on remet les coordonnées des pions qui viennent d'être joué à leur valeur d'avant le coup
        coord_pion_blanc_vient_d_etre_jouer= coup.get_coord_pion_blanc_vient_d_etre_jouer_avant();
        coord_pion_noir_vient_d_etre_jouer = coup.get_coord_pion_noir_vient_d_etre_jouer_avant();

        //AFFICHAE DEBUG
        //cout<<"on a remis les coord_pion_avant"<<endl;
        //coup.set_piece_prise(NULL);

        //si on à mangé une piece durant ce coup, on remet la piece en place
        Piece* piece_prise_ptr= coup.get_piece_prise();

        //AFFCHAGE DEBUG
        //cout<<piece_prise_ptr<<endl;


        if(piece_prise_ptr!= NULL)
        {
            int position_i= (piece_prise_ptr->get_pos())[0];
            int position_j= (piece_prise_ptr->get_pos())[1];

            grille[position_i][position_j]= piece_prise_ptr;
        }

        

        //AFFICHE DEBUG
        //cout<<"fin annule coup"<<endl;
    }

}

/******************************************************************************/

bool Echiquier::test_roque(Coup &coup, couleur_t couleur, type_de_coup_t roque)
{
    //on teste d'abord si le roi de la couleur "couleur n'est pas en echec";
    if(test_echec(couleur)== true)
        return false;


    bool jouable= false;

    Piece *roi_ptr;
    Piece *tour_ptr;

    if(couleur== blanc)
    {
        roi_ptr= grille[7][4];

        if(roque== grand_roque)
        {
            
            tour_ptr= grille[7][0];
            
            if(roi_ptr!= NULL && tour_ptr!=NULL)
            {  
                string repr_roi = roi_ptr->get_repre();
                string repr_tour= tour_ptr->get_repre();

                if(repr_roi=="\u265A" && repr_tour=="\u265C")
                {
                    if(roi_ptr->get_nbr_de_coup()==0 && tour_ptr->get_nbr_de_coup()==0)
                    {
                        jouable= true;
                    }
                }
                
            }
        }
        else if(roque== petit_roque)
        {
            tour_ptr= grille[7][7];

            if(roi_ptr!= NULL && tour_ptr!=NULL)
            {
                string repr_roi = roi_ptr->get_repre();
                string repr_tour= tour_ptr->get_repre();
                
                if(repr_roi=="\u265A" && repr_tour=="\u265C")
                {
                    if(roi_ptr->get_nbr_de_coup()==0 && tour_ptr->get_nbr_de_coup()==0)
                    {  
                        jouable= true;
                    }
                }
            }
        }
        
    }

    else if(couleur== noir)
    {
        roi_ptr= grille[0][4];

        if(roque== grand_roque)
        {
            tour_ptr= grille[0][0];
            if(roi_ptr!= NULL && tour_ptr!=NULL)
            {
                string repr_roi = roi_ptr->get_repre();
                string repr_tour= tour_ptr->get_repre();

                if(repr_roi=="\u2654" && repr_tour== "\u2656")
                {
                    if(roi_ptr->get_nbr_de_coup()==0 && tour_ptr->get_nbr_de_coup()==0)
                    {
                        jouable= true;
                    }
                }
            }
        }
        else if(roque== petit_roque)
        {
            tour_ptr= grille[0][7];
            if(roi_ptr!= NULL && tour_ptr!=NULL)
            {
                string repr_roi = roi_ptr->get_repre();
                string repr_tour= tour_ptr->get_repre();

                if(repr_roi=="\u2654" && repr_tour=="\u2656")
                {
                    if(roi_ptr->get_nbr_de_coup()==0 && tour_ptr->get_nbr_de_coup()==0)
                    {  
                        jouable= true;
                    }
                }
            }
        }
        
    }

    return jouable;  
}

/******************************************************************************/

bool Echiquier::traitement_roque(Coup &coup, couleur_t couleur)
{
    type_de_coup_t roque= coup.get_type_de_coup();

    bool jouable= test_roque(coup, couleur, roque);
  
    if(jouable== true)
        return false;


    else
    {
        string string_coup;

        cout<< "roque impossible à effectuer, veuillez entrer un autre coup\n"<< endl;
        cin>> string_coup;
        coup.set_string_coup(string_coup); 

        return true; 
    }
        
}

/******************************************************************************/

string demander_saisie_pour_promotion()
{
    cout<< "\n En quelle pièce voulez vous transformer votre pion, parmis {Q,R,B,K}? \n";
    string saisie;
    cin>> saisie;

    bool bonne_saisie= false;

    while(bonne_saisie== false)
    {
        switch (saisie[0])
        {
            case 'Q':
                return saisie;
                break;
            case 'R':
                return saisie;
                break;
            case 'B':
                return saisie;
                break;
            case 'N':
                return saisie;
                break;
            default:
                cout<<"erreur, il faut entrer une lettre parmis {Q,R,B,K}"<<endl;
                cin>> saisie;
        }
    }

    return saisie;

}

/******************************************************************************/
void Echiquier::gerer_promotion(Coup &coup, Piece* piece_ptr)
{
    vector<int> depart= coup.get_depart_coup();
    vector<int> destination= coup.get_destination_coup();

    string repr= piece_ptr->get_repre();

    //Si un pion noir va sur la derniere ligne avec le coup
    if(repr== "\u2659" && destination[0]==7)
    {
        string saisie= demander_saisie_pour_promotion();

        switch (saisie[0])
        {
            case 'Q':
            {
                Reine *new_reine_noir= new Reine(noir,"\u2655", destination[0], destination[1]);
                pose_piece(new_reine_noir,new_reine_noir->get_pos());
                pieces_promues_noires.push_back(new_reine_noir);
                break;
            }
            case 'R':
            {
                Tour *new_tour_noir= new Tour(noir,"\u2656", destination[0], destination[1]);
                pose_piece(new_tour_noir,new_tour_noir->get_pos());
                pieces_promues_noires.push_back(new_tour_noir);
                break;
            }
            case 'B':
            {
                Fou *new_fou_noir= new Fou (noir,"\u2657", destination[0], destination[1]);
                pose_piece(new_fou_noir,new_fou_noir->get_pos());
                pieces_promues_noires.push_back(new_fou_noir);
                break;
            }
            case 'N':
            {
                Cheval *new_cheval_noir= new Cheval  (noir,"\u2658", destination[0], destination[1]);
                pose_piece(new_cheval_noir,new_cheval_noir->get_pos());
                pieces_promues_noires.push_back(new_cheval_noir);
                break;
            }
            default:
                ;
                
                
        }
    }
    //Si un pion blanc va sur la 1ère ligne avec le coup
    if(repr== "\u265F" && destination[0]==0)
    {
        string saisie= demander_saisie_pour_promotion();

        switch (saisie[0])
        {
            case 'Q':
            {
                Reine *new_reine_blanche= new Reine(blanc,"\u265B", destination[0], destination[1]);
                pose_piece(new_reine_blanche,new_reine_blanche->get_pos());
                pieces_promues_blanches.push_back(new_reine_blanche);
                break;
            }
            case 'R':
            {
                Tour *new_tour_blanche= new Tour(blanc,"\u265C", destination[0], destination[1]);
                pose_piece(new_tour_blanche,new_tour_blanche->get_pos());
                pieces_promues_blanches.push_back(new_tour_blanche);
                break;
            }
            case 'B':
            {
                Fou *new_fou_blanc= new Fou(blanc,"\u265D", destination[0], destination[1]);
                pose_piece(new_fou_blanc,new_fou_blanc->get_pos());
                pieces_promues_blanches.push_back(new_fou_blanc);
                break;
            }
            case 'N':
            {
                Cheval *new_cheval_blanc=new Cheval  (blanc,"\u265E", destination[0], destination[1]);
                pose_piece(new_cheval_blanc,new_cheval_blanc->get_pos());
                pieces_promues_blanches.push_back(new_cheval_blanc);
                break;
            }
            default:
                ;
        }
    }
    
}

