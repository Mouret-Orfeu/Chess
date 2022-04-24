#ifndef COUP
#define COUP

#include <string>
#include <vector>

using namespace std;

class Piece;

typedef enum type_de_coup_t
{
    pas_un_roque,
    petit_roque,
    grand_roque
}type_de_coup_t;


//Cette classe ne sert qu'à séparer certaines fonctions du reste du code.
class Coup
{
    private:
        string string_coup;
       
        type_de_coup_t type_de_coup;

        Piece *piece_prise_ptr;
    
        vector<int> depart;
        vector<int> destination;

        //coord des pions qu'on vient de jouer avant le coup joué
        vector<int> coord_pion_blanc_vient_d_etre_jouer_avant;
        vector<int> coord_pion_noir_vient_d_etre_jouer_avant; 

    public:
        Coup(){};

        string get_string_coup() const;

        type_de_coup_t get_type_de_coup();

        vector<int> get_depart_coup();

        vector<int> get_destination_coup();

        vector<int> get_coord_pion_blanc_vient_d_etre_jouer_avant();

        vector<int> get_coord_pion_noir_vient_d_etre_jouer_avant();

        Piece * get_piece_prise();
        
        void set_type_de_coup(type_de_coup_t type_de_coup);

        void set_string_coup(string new_string_coup);

        //on met à jour la piece prise dans la structure dernier coup de l'objet Coup
        void set_piece_prise(Piece* new_piece_prise_ptr);

        //on met à jour le départ et la destination du dernier coup
        void set_depart_destination_coup(vector<int> depart, vector<int> destination);

        //on met à jour les coordonnée des pions qui viennent d'être joués, avant le coup joué
        void set_coord_pion_vient_d_etre_jouer_avant(vector<int> coord_pion_blanc_vient_d_etre_jouer, vector<int> coord_pion_noir_vient_d_etre_jouer);

        //Retourne une matrice de 2 colonnes. La 1ère colonne représente les coordonnées (en int) du départ du coup, le 2ème, les coordonnées (en int) de la destination du coup
        vector<vector<int>> string_to_int_coord(); 

        //retourne les coordonnées (en int) de la case de départ du coup, à partir de la matrice des coordonnées de départ et d'arrivée du coup.  
        vector<int> extract_coord_depart(vector<vector<int>> int_coup);
       
        vector<int> extract_coord_destination(vector<vector<int>> int_coup);
       
}; 

#endif