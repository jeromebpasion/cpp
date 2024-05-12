#include <QCoreApplication>
#include <iostream>
#include <string>
using namespace std;

template <class XYZ>
XYZ sum (XYZ a, XYZ b){
    XYZ sum;
    sum = a + b;
    return sum;
}

string concatenate (const string &first,const string &second){
    return first+second;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //for testing C++ features

    cout << "Test" << endl;

    string hello="Hello ";
    string world="World";
    cout << concatenate (hello,world);


    int aInt = sum<int>(5,6);
    float aFloat= sum<float>(5.1, 5.9);
    cout << "Sum int: " << aInt << " float; " <<aFloat <<endl;








//    a.exec();
//    a.exit();
    return 0;
}

