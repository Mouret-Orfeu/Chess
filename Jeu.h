#ifndef JEU
#define JEU

#include <string>
using namespace std;
#include <iostream>
#include <vector>
#include <regex>

class Jeu
{
    private:

    public:
        bool test_hors_plateau(string const & cmd) 
        {
            regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
            return regex_match(cmd,mouvmtpattern);
        }

        // bool saisie_correcte_petitroque(string const & cmd) {
        // regex mouvmtpattern("(O|o|0)-(O|o|0)");
            // return regex_match(cmd,mouvmtpattern);
        // }


};


#endif