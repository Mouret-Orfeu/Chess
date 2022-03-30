#ifndef SQUARE
#define SQUARE

using namespace std;

#include <vector>
#include <string>
#include <iostream>
 #include <stdlib.h>

//Cette classe ne sert qu'à séparer les fonctions présentes, du reste du code.
class Coup
{
    private:
        string string_coup;
    
    public:

        //Retourne une matrice de 2 colonnes. La 1ère colonne représente les coordonnées (en int) du départ du coup, le 2ème, les coordonnées (en int) de la destination du coup
        vector<vector<int>> string_to_int_coord(string string_coup)
        {
            vector<int> vector_de_construction;
            vector<vector<int>> vector_final;

            //Boucle de 2 itérations pour convertir les 2 parties de string_coord en 2 vecteurs
            for(int k=0; k<2; k++)
            {
                //on convertie les 2 premers char de string_coord en int que l'on met dans un vecteur de taille 2 (quand k=0)
                //puis les 2 char suivants (quand k=1)
                vector_de_construction.push_back(string_coup[0+2*k]-'a');
                vector_de_construction.push_back(atoi(&string_coup[1+2*k]));

                vector_final.push_back(vector_de_construction);

                vector_de_construction.clear();         
            }

            return vector_final;
        }

        //retourne les coordonnées (en int) de la case de départ du coup, à partir de la matrice des coordonnées de départ et d'arrivée du coup.  
        vector<int> extract_coord_depart(vector<vector<int>> int_coord_depart_destination)
        {
            vector<int> int_coord_depart;
            int_coord_depart.push_back(int_coord_depart_destination[0][0]);
            int_coord_depart.push_back(int_coord_depart_destination[0][1]);

            return int_coord_depart;
        }

        vector<int> extract_coord_destination(vector<vector<int>> int_coord_depart_destination)
        {
            vector<int> int_coord_destination;
            int_coord_destination.push_back(int_coord_depart_destination[1][0]);
            int_coord_destination.push_back(int_coord_depart_destination[1][1]);

            return int_coord_destination;
        }
}; 

#endif