using namespace std;

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>


class Coup
{
    private:
        string string_coup;
    
    public:
        Coup(string string_coup): string_coup(string_coup){};
       


        string get_string_coup() const
        {
            return string_coup;
        }

        void set_string_coup(string new_string_coup) 
        {
            string_coup= new_string_coup;
        }


        void affiche()
        {
            cout<< string_coup<< endl;
        }
};

int main(void)
{
    int n= -2;

    int destination_1= 2;
    int destination_2= 2;

    int depart_1     = 4;
    int depart_2     = 4;

    if(destination_1== depart_1+n  && destination_2== depart_2+n)
        printf("AhAA!!\n");
    
    return 0;
}

