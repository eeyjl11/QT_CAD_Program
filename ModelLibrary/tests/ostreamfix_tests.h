#ifndef OSTREAM_H
#define OSTREAM_H
#include <iostream>
#include "../src/vector3D.h"

/** @file
* Header file for ostreamfix
*/

using namespace std;

/**
* Ostreamfix operator. @n 
* This allows the printing of vector3d to terminal.
*/
ostream &operator<<(ostream &stream, vector3d &obj);
#endif
