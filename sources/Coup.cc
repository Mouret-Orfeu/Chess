
#include <iostream>
#include <stdlib.h>

#include "Coup.h"
#include "Piece.h"


/******************************************************************************/

string Coup::get_string_coup() const
{
    return string_coup;
}

/******************************************************************************/

type_de_coup_t Coup::get_type_de_coup()
{
    return type_de_coup;
}

/******************************************************************************/

vector<int> Coup::get_depart_coup()
{
    return depart;
}

/******************************************************************************/

vector<int> Coup::get_destination_coup()
{
    return destination;
}

/******************************************************************************/

vector<int> Coup::get_coord_pion_blanc_vient_d_etre_jouer_avant()
{
    return coord_pion_blanc_vient_d_etre_jouer_avant;
}

/******************************************************************************/

vector<int> Coup::get_coord_pion_noir_vient_d_etre_jouer_avant()
{
    return coord_pion_noir_vient_d_etre_jouer_avant;
}

/******************************************************************************/

Piece * Coup::get_piece_prise()
{
    return piece_prise_ptr;
}

/******************************************************************************/

void Coup::set_type_de_coup(type_de_coup_t type_de_coup_set)
{
    type_de_coup= type_de_coup_set;
}

/******************************************************************************/

void Coup::set_string_coup(string new_string_coup) 
{
    string_coup= new_string_coup;
}

/******************************************************************************/

void Coup::set_piece_prise(Piece* new_piece_prise_ptr)
{
    piece_prise_ptr= new_piece_prise_ptr;
}

/******************************************************************************/

void Coup::set_depart_destination_coup(vector<int> new_depart, vector<int> new_destination)
{
    depart     = new_depart;
    destination= new_destination;

}

/******************************************************************************/

void Coup::set_coord_pion_vient_d_etre_jouer_avant(vector<int> coord_1, vector<int> coord_2)
{
    coord_pion_blanc_vient_d_etre_jouer_avant= coord_1;
    coord_pion_noir_vient_d_etre_jouer_avant = coord_2;
}


/******************************************************************************/


vector<vector<int>> Coup::string_to_int_coord()
{
    vector<int> vector_de_construction;
    vector<vector<int>> vector_final;

    //Boucle de 2 itérations pour convertir les 2 parties de string_coord en 2 vecteurs
    for(int k=0; k<2; k++)
    {
        //on convertie les 2 premers char de string_coord en int que l'on met dans un vecteur de taille 2 (quand k=0)
        //puis les 2 char suivants (quand k=1)
        vector_de_construction.push_back(atoi(&string_coup[1+2*k])-1);
        vector_de_construction.push_back(string_coup[0+2*k]-'a');
                
        vector_final.push_back(vector_de_construction);

        vector_de_construction.clear();         
    }

    return vector_final;
}

/******************************************************************************/

vector<int> Coup::extract_coord_depart(vector<vector<int>> int_coup)
{
    vector<int> int_coord_depart;
    int_coord_depart.push_back(int_coup[0][0]);
    int_coord_depart.push_back(int_coup[0][1]);

    return int_coord_depart;
}

/******************************************************************************/

vector<int> Coup::extract_coord_destination(vector<vector<int>> int_coup)
{
    vector<int> int_coord_destination;
    int_coord_destination.push_back(int_coup[1][0]);
    int_coord_destination.push_back(int_coup[1][1]);

    return int_coord_destination;
}