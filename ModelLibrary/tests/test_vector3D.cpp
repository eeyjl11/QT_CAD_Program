/** @file
* Main file for the vector3d test class
*/

#include "test_vector3D.h"
#include "ostreamfix_tests.h"

/**
* Function to test the vector3d class @n 
* Initially creates two vector3d variables @n 
* It then tests the various operators by using the two previously defined variables and printes them
*/
int test_vector3d()
{
    //Creating and defining two instances of the vector3d object
    vector3d v1(2,3,4);
    vector3d v2(5,6,7);

    //Creating two more vector objects which are defined by adding and subtracting the first two instances
    vector3d v1Addv2 = v1+v2;
    vector3d v1Subtractv2 = v1-v2;

    //Creating a double variable which stores the value of the scalar product of the two instances
    double v1Scalarv2 = v1*v2;

    //Creating a vector3d object with the result of a vector multiplication of the two instances
    vector3d v1Vectorv2 = v1&v2;

    //Outputting the various instances
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1+v2 = " << v1Addv2 << endl;
    cout << "v1-v2 = " << v1Subtractv2 << endl;
    cout << "v1*(scalar)v2 = " << v1Scalarv2 << endl;
    cout << "v1*(vector)v2 = " << v1Vectorv2 << endl;

    return 0;
}

