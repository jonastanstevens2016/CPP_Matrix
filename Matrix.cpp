#include <iostream>
#include"Matrix.h"
using namespace std;
int main(){


    Matrix a(3,4);  // single block of memory 3 * 4 set all to 0.0

    a(1,1) = 1.5;
    a(2,1) = 3.2;
    /**
     0.0  0.0  0.0  0.0
     0.0  1.5  0.0  0.0
     3.2  0.0  0.0  0.0
 */

    cout << a(1,2) << '\n';

    cout << a;

    Matrix b(3,4,1.5); // set all values to 1.5
    Matrix c = a + b;
    Matrix d(4,3,2.5);
    Matrix e = b * d; // matrix  mult.
    return 0;
}
