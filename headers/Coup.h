#ifndef COUP
#define COUP

#include <string>
#include <vector>

using namespace std;



//Cette classe ne sert qu'à séparer certaines fonctions du reste du code.
class Coup
{
    private:
        string string_coup;
    
    public:
        Coup(string string_coup): string_coup(string_coup){};

        string get_string_coup() const;
        
        void set_string_coup(string new_string_coup);

        //Retourne une matrice de 2 colonnes. La 1ère colonne représente les coordonnées (en int) du départ du coup, le 2ème, les coordonnées (en int) de la destination du coup
        vector<vector<int>> string_to_int_coord();
       

        //retourne les coordonnées (en int) de la case de départ du coup, à partir de la matrice des coordonnées de départ et d'arrivée du coup.  
        vector<int> extract_coord_depart(vector<vector<int>> int_coup);
       

        vector<int> extract_coord_destination(vector<vector<int>> int_coup);
       
}; 

#endif