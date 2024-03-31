#include <iostream>
#include <string>
#include <vector>
#include "Vector.hpp"

using namespace std;

int main() {
    double arr[] = {1,2,3,1,2,1,0};
    Vector v(arr, 6);
    v.print();
    cout << sizeof(v) << endl;
    

    return 0;
}
