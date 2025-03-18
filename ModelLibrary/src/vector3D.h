#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
#include <stdio.h>

/** @file
* Header file for the vector class
*/

using namespace std;

//-----------------------------------------------
//Class for a 3D vector
//Created by Jack Wade from group 5 on 06/12/21
//-----------------------------------------------

//Class definition
class vector3d
{

//Private variables - cant be accessed directly, need the get/set commands
//to access and change them
private:
    double xCoord;
    double yCoord;
    double zCoord;

//Public functions
public:
    vector3d(); //Default constructor
    vector3d( double x, double y, double z); //Constructor declaration to initialise variables
    //~vector3d(); //Destructor to free memory

    //Get function declarations which return the variable in question
    double getxCoord();
    double getyCoord();
    double getzCoord();

    //Set function declarations which set the variable in questions to a value
    void setxCoord(double x);
    void setyCoord(double y);
    void setzCoord(double z);

    //Operator declarations
    vector3d operator+(vector3d v);
    vector3d operator-(vector3d v);
    vector3d operator/(vector3d v); // Each co-ordinate divided by vector3d
    double operator*(vector3d v); //Scalar product ... dot product

    vector3d operator&(vector3d v);
};
#endif