
#include <iostream>
#include <stdlib.h>

#include "Coup.h"

string Coup::get_string_coup() const
{
    return string_coup;
}

void Coup::set_string_coup(string new_string_coup) 
{
    string_coup= new_string_coup;
}


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

vector<int> Coup::extract_coord_depart(vector<vector<int>> int_coup)
{
    vector<int> int_coord_depart;
    int_coord_depart.push_back(int_coup[0][0]);
    int_coord_depart.push_back(int_coup[0][1]);

    return int_coord_depart;
}

vector<int> Coup::extract_coord_destination(vector<vector<int>> int_coup)
{
    vector<int> int_coord_destination;
    int_coord_destination.push_back(int_coup[1][0]);
    int_coord_destination.push_back(int_coup[1][1]);

    return int_coord_destination;
}