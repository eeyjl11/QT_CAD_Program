/** @file
* Main file for the cell test class
*/

//--------------------------------------------

// test_cell.cpp

// Copyright Jason Lloyd

// Cpp file containing the test functions for Tetrahedron, Pyramid and Hexahedron

// Required headers: test_cell.h, ostreamfix.h

//--------------------------------------------

#include "test_cell.h"
#include "ostreamfix_tests.h"
using namespace std;

//--------------------------------------------

// Tetrahedron test function

//--------------------------------------------

/**
* Function to test tetrahedron class functions @n 
* This creates a tetrahedron using the alternate constructor @n 
* Then it calls the volume, COG and weight functions @n 
* It then prints the shape ID and vertices to check if the tetrahedron instance is initialised properly @n 
* Then it prints the volume, centre of gravity and weight @n 
* These can be checked to values calculated by hand to ensure they match
*/
void test_tetrahedron() {
    // Create Tetrahedron instance using alternate constructor
    Tetrahedron t1(vector3d(1,2,4), vector3d(4,0,3), vector3d(1,1,7), vector3d(3,2,1));

    // Set t1's ID to 1
    t1.set_id(1);

    // Retrieve the vertices so we can check they are input correct later
    vector3d get_p0 = t1.get_p0();
    vector3d get_p1 = t1.get_p1();
    vector3d get_p2 = t1.get_p2();
    vector3d get_p3 = t1.get_p3();

    // Call volume function
    double vol = t1.getVolume();

    // Call centre of gravity function
    vector3d cog = t1.getCOG();
 
    // Call weight function
    double weight = t1.getWeight(5);

    // Print shape ID
    cout << "Tetrahedron\nID: " << t1.get_id() << endl;

    // Print the vertices of the shape
    cout << "\nP0 is " << get_p0 << "\nP1 is " << get_p1 << "\nP2 is " << get_p2 << "\nP3 is " << get_p3 << endl;

    // Print the volume, centre of gravity and weight
    cout << "\nVolume is " << vol << "\nCentre of gravity is " << cog << "\nWeight is " << weight << endl;
}

//--------------------------------------------

// Pyramid test function

//--------------------------------------------

/**
* Function to test pyramid class functions @n 
* This creates a pyramid using the alternate constructor @n 
* Then it calls the volume, COG and weight functions @n 
* It then prints the shape ID and vertices to check if the pyramid instance is initialised properly @n 
* Then it prints the volume, centre of gravity and weight @n 
* These can be checked to values calculated by hand to ensure they match
*/
void test_pyramid() {
    // Initialise five vector3d containing the vertices
    vector3d p0_set(4,-1,0);
    vector3d p1_set(6,0,3);
    vector3d p2_set(5,6,2);
    vector3d p3_set(2,1,-1);
    vector3d p4_set(3, 4, 7);

    // Create Pyramid instance
    Pyramid p1;

    // Set p1's vertices to the four previous vectors
    p1.set_p0(p0_set);
    p1.set_p1(p1_set);
    p1.set_p2(p2_set);
    p1.set_p3(p3_set);
    p1.set_p4(p4_set);

    // Set p1's ID to 2
    p1.set_id(2);

    // Retrieve the vertices so we can check they are input correct later
    vector3d get_p0 = p1.get_p0();
    vector3d get_p1 = p1.get_p1();
    vector3d get_p2 = p1.get_p2();
    vector3d get_p3 = p1.get_p3();
    vector3d get_p4 = p1.get_p4();

    // Call volume function
    double vol = p1.getVolume();

    // Call centre of gravity function
    vector3d cog = p1.getCOG();

    // Call weight function
    double weight = p1.getWeight(5);

    // Print shape ID
    cout << "\nPyramid\nID: " << p1.get_id() << endl;

    // Print the vertices of the shape
    cout << "\nP0 is " << get_p0 << "\nP1 is " << get_p1 << "\nP2 is " << get_p2 << "\nP3 is " << get_p3 << "\nP4 is " << get_p4 << endl;
    
    // Print the volume, centre of gravity and weight
    cout << "\nVolume is " << vol << "\nCentre of gravity is " << cog << "\nWeight is " << weight << endl;
}

//--------------------------------------------

// Hexahedron test function

//--------------------------------------------

/**
* Function to test hexahedron class functions @n 
* This creates a hexahedron using the alternate constructor @n 
* Then it calls the volume, COG and weight functions @n 
* It then prints the shape ID and vertices to check if the hexahedron instance is initialised properly @n 
* Then it prints the volume, centre of gravity and weight @n 
* These can be checked to values calculated by hand to ensure they match
*/
void test_hexahedron() {
    // Initialise eight vector3d containing the vertices
    vector3d p0_set(1, 1, 1);
    vector3d p1_set(3, 1, 1);
    vector3d p2_set(3, 3, 1);
    vector3d p3_set(1, 3, 1);
    vector3d p4_set(1, 1, 3);
    vector3d p5_set(3, 1, 3);
    vector3d p6_set(3, 3, 3);
    vector3d p7_set(1, 3, 3);

    // Create Hexahedron instance
    Hexahedron h1;

    // Set p1's vertices to the four previous vectors
    h1.set_p0(p0_set);
    h1.set_p1(p1_set);
    h1.set_p2(p2_set);
    h1.set_p3(p3_set);
    h1.set_p4(p4_set);
    h1.set_p5(p5_set);
    h1.set_p6(p6_set);
    h1.set_p7(p7_set);

    // Set h1's ID to 2
    h1.set_id(3);

    // Retrieve the vertices so we can check they are input correct later
    vector3d get_p0 = h1.get_p0();
    vector3d get_p1 = h1.get_p1();
    vector3d get_p2 = h1.get_p2();
    vector3d get_p3 = h1.get_p3();
    vector3d get_p4 = h1.get_p4();
    vector3d get_p5 = h1.get_p5();
    vector3d get_p6 = h1.get_p6();
    vector3d get_p7 = h1.get_p7();

    // Call volume function
    double vol = h1.getVolume();

    // Call centre of gravity function
    vector3d cog = h1.getCOG();

    // Call weight function
    double weight = h1.getWeight(5);

    // Print shape ID
    cout << "\nHexahedron\nID: " << h1.get_id() << endl;

    // Print the vertices of the shape
    cout << "\nP0 is " << get_p0 << "\nP1 is " << get_p1 << "\nP2 is " << get_p2 << "\nP3 is " << get_p3 << "\nP4 is " << get_p4 << "\nP5 is " << get_p5 << "\nP6 is " << get_p6 << "\nP7 is " << get_p7 << endl;
    
    // Print the volume, centre of gravity and weight
    cout << "\nVolume is " << vol << "\nCentre of gravity is " << cog << "\nWeight is " << weight << endl;
}
