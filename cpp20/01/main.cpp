#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

    //scratch loops

    cout << "While \n";
    int n = 40;
    while (n>30) {
        cout << n<< " ";
        n--;
    }
    cout << endl;

    for (int i = 0; i < 20; i++) {
        cout << " for " << i << endl;
    }

    cout << "Range for loop  \n";
    for (int i : {1, 2, 3, 4}) {
        cout << i << " ";
    }
    cout << endl;
    string name = "HELLO WORLD";
    for (auto c : name){
        cout << c << " ";
    }
        cout << endl;

    cout << "Switch Case"<<endl;
    int x = 3;
    switch (x) {
        case 1:
            cout << " case " << x;
            break;
        case 2:
            cout << " case " << x;
            break;
        default:
            cout << " default " << x;
    }
        cout << endl;

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
