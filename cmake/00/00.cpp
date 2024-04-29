#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

std::integral auto factorial(std::integral auto number) {
    if (number <= 0) return 1;
    else return number * factorial(number -1);
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout<<"Usage: Factorial <integer>"<<endl;
        return 1;
    }
    
    //C stdlib. 
    //int x = atoi(argv[1]);
    //cout << factorial (x) << endl;
    
    string arg = argv[1];
    try {
        size_t pos;
        auto castedInt = std::stoi(arg, &pos);
        if (pos <arg.size()) {
            cerr << "Trailing characters after " << arg << endl;
        }
        if ( castedInt <0 )
            throw std::out_of_range("Negative" );
            
        auto result = factorial(castedInt);
        if (result <0 )
            throw std::out_of_range("Overflow");
        else  
            cout << factorial(castedInt) << endl;
    }
    catch (std::invalid_argument const &ex) {
        cerr << "Invalid number: " << arg << endl;
    }
    catch (std::out_of_range const &ex) {
        cerr << "Number out of range: " << arg << " because "<< ex.what() << endl;
    }
    return 0;
}
