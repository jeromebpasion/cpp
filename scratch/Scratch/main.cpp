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

template <class T>
T larger (T a, T b){
    return (a > b ? a : b);
}

template <class AnyType>
AnyType smaller (AnyType a, AnyType b) {
    return (a < b ? a : b);
}

string concatenate (const string &first,const string &second){
    return first+second;
}

//c++11 initializer list
int sum(const std::initializer_list<int>& list) {
    int total=0;
    for (auto& e : list) {
        total += e;
    }
    return total;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //for testing C++ features

    cout << "Test" << endl;

    string hello="Hello ";
    string world="World";
    cout << concatenate (hello,world);

    //c++ templates
    int aInt = sum<int>(5,6);
    float aFloat= sum<float>(5.1, 5.9);
    cout << "Sum int: " << aInt << " float; " <<aFloat <<endl;

    auto templateIntLarger = larger<int>(1111,2222);
    auto templateDoubleLarger = larger<double>(11.11,22.22);
    decltype(auto) templateIntSmaller = smaller<int>(1111,2222);
    decltype(auto) templateDoubleSmaller = smaller<double>(11.11,22.22);

    //c++17 nullptr
    int myvar = 999;
    int * myptr = nullptr;
    myptr = nullptr;
     cout << myvar << " myptr " << &myptr << " " << myptr <<  endl;

    int array[] = {3232, 231,55,03, 0x333};
    cout << "array size " << sizeof(array)<<  '\n';
    cout << "int size " << sizeof(int)<<  '\n';
    for (int i = 0; i < 5; ++i){

        cout << i << " " << array[i] << " " << &array[i] <<  '\n';
    }

    int * dynptr = new (nothrow) int [5];
    if (dynptr == nullptr) {
        cout << "Error: nullptr";
    }

    //c++17 auto
    auto aa = 3.14;
    auto ab = 123;
    auto& ac = ab;
    auto ad = { 12,45,787 };
    auto&& ae = 456;
    auto&& af = ab;
    auto ag = new auto(123);
    const auto ah = 789;
    auto ai = 1011, aj = 1012, ak = 1013;
    auto al = 1014; //can't l, m=true, n=21.00
    auto am = true;
    auto an = 21.00;
    auto ao = 0xDE;
    decltype(auto) ap = &af;
    decltype(auto) aq = af;


    //c++11 initializer list
    auto list = {232,325,362};
    std::cout<< " initializer list " << sum(list);
    std::cout<< " initializer list " << sum({10,10,10});
    std::cout<< " initializer list " << sum({});

    //type aliases
 //   template <typename T>
    using Vector = std::vector<int>;
    Vector v = {223,23};
    std::cout << "type alias using " << v.at(0) << std::endl;


    // ++ * precedence
    int arr[] = {10,20};
    int *p = arr;
    ++*p; //++(*p)
    std::cout << arr[0] << " " << arr[1] << " " << *p << std::endl;

    int arr2[] = {30, 40};
    int *p2 = arr2;
    *p2++; //*(p2++)
    std::cout << arr2[0] << " " << arr2[1] << " " << *p2 << std::endl;

    int arr3[] = {50, 60};
    int *p3 = arr3;
    *++p3;
    std::cout << arr3[0] << " " << arr3[1] << " " << *p3 << std::endl;

    //c++ decltype
    int declvar;
    int&& declfunction();
    auto decla = declvar;
    decltype(auto) declb = declvar;
    auto declc = (declvar);
    decltype(auto) decld = (declvar);
    //auto decle = declfunction();
    //decltype(auto) declf = f();
    auto declg = {1,2,3};
    //decltype(auto) declh = {4,5};
    auto *decli = &declvar;
    //decltype(auto)*declj = &declvar;

    const int declk = 999, &decll = declk;
    auto declm = declk;
    auto decln = decll;
    decltype(auto) declo= declk;
    decltype(auto) declp= decll;











    //    a.exec();
    //    a.exit();
    return 0;
}

