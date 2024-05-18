#include <QCoreApplication>
#include <iostream>
#include <string>
#include <QSurface>
#include <QOpenGLWindow>

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

    int array[] = {3232, 231,55,03, 0x333};
    cout << "array size " << sizeof(array)<<  '\n';
    cout << "int size " << sizeof(int)<<  '\n';
    for (int i = 0; i < 5; ++i){

        cout << i << ' ' << array[i] << ' ' << &array[i] <<  '\n';
    }

//    int myvar;
  //  int * myptr = nullptr;
 //   *myptr = nullptr;
    //cout << myvar << " " << myptr << " " << *myptr <<  '\n';


    int * dynptr = new (nothrow) int [5];
    if (dynptr == nullptr) {
        cout << "Error: nullptr";
    }




//    a.exec();
//    a.exit();
    return 0;
}

