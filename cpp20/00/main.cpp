#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

        //scratch loops
    int n = 40;
    while (n>30) {
        cout << n<< " ";
        n--;
    }

    cout << "SquareRoot \n";

    if (argc != 2) {
        cout << "SquareRoot <integer>. Non-complex numbers only. "<<endl;
        return 1;
    }
    string arg = argv[1];
    try {
        size_t pos;
        auto castedDbl = std::stod(arg, &pos);

        if ( castedDbl <0 )
            throw std::out_of_range("Negative number. Non-complex numbers only.");
        else
            cout << "Square root is " << sqrt(castedDbl) << endl;
    }
    catch (std::invalid_argument const &ex) {
        cerr << "Invalid number: " << arg << endl;
    }
    catch (std::out_of_range const &ex) {
        cerr << "Number out of range: " << arg << " because "<< ex.what() << endl;
    }




    return 0;
}
