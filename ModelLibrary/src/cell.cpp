/** @file
* Main file for the cell class
*/

//--------------------------------------------

// Cell.cpp

// Copyright Jason Lloyd

// Cpp file containing the functions for Cell, Tetrahedron, Pyramid and Hexahedron

// Required headers: cell.h, iostream, ostreamfix.h, math.h

//--------------------------------------------

#include "cell.h"

#include <iostream>

#include <math.h>

//--------------------------------------------

// Cell functions

//--------------------------------------------

// Volume of Cell, returns zero as we only want volume of the three shapes
double Cell :: getVolume() {
	return 0;
}

// Centre of gravity of Cell, returns zero as we only want centre of gravity of the three shapes
vector3d Cell :: getCOG() {
	return vector3d(0,0,0);
}

// Weight of Cell, returns zero as we only want weight of the three shapes
double Cell :: getWeight(double density) {
	return 0;
}

// Get ID of Cell
/**
 * @return id ID of cell
 */
int Cell :: get_id() {
	return this->id;
}

// Set ID of Cell
/**
 * @param[in] id New ID value
 */
void Cell :: set_id(int id) {
	this->id = id;
}

// Get material ID of Cell
/**
 * @return material_id Material ID of cell
 */
int Cell :: get_material_id() {
	return this->material_id;
}

// Set material ID of Cell
/**
 * @param[in] material_id New material ID
 */
void Cell :: set_material_id(int material_id) {
	this->material_id = material_id;
}

// Set colour of Cell
/**
 * @param[in] c New colour for cell
 */
void Cell :: set_colour(color &c) {
	this->col = c;
}

//--------------------------------------------

// Tetrahedron functions

//--------------------------------------------

Tetrahedron :: Tetrahedron() {
	this->p0 = vector3d(0,0,0);
	this->p1 = vector3d(0,0,0);
	this->p2 = vector3d(0,0,0);
	this->p3 = vector3d(0,0,0);
}

/**
 * @param[in] p0,p1,p2,p3 Four points of tetrahedron
 */
Tetrahedron :: Tetrahedron(vector3d p0, vector3d p1, vector3d p2, vector3d p3) {
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

Tetrahedron :: ~Tetrahedron() {}

//--------------------------------------------

/**
 * @return p0 First vertice
 */
vector3d Tetrahedron :: get_p0() {
	return this->p0;
}

/**
 * @return p1 Second Vertice
 */
vector3d Tetrahedron :: get_p1() {
	return this->p1;
}

/**
 * @return p2 Third vertice
 */
vector3d Tetrahedron :: get_p2() {
	return this->p2;
}

/**
 * @return p3 Fourth Vertice
 */
vector3d Tetrahedron :: get_p3() {
	return this->p3;
}

//--------------------------------------------
/**
 * @param[in] p0 New vertice for p0
 */
void Tetrahedron :: set_p0(vector3d &p0) {
	this->p0 = p0;
}

/**
 * @param[in] p1 New vertice for p1
 */
void Tetrahedron :: set_p1(vector3d &p1) {
	this->p1 = p1;
}

/**
 * @param p2 New vertice for p2
 */
void Tetrahedron :: set_p2(vector3d &p2) {
	this->p2 = p2;
}

/**
 * @param[in] p3 New vertice for p3
 */
void Tetrahedron :: set_p3(vector3d &p3) {
	this->p3 = p3;
}

//--------------------------------------------
/**
 * @return p0_id First vertice ID
 */
int Tetrahedron :: get_p0_id() {
	return this->p0_id;
}

/**
 * @return p1_id Second vertice ID
 */
int Tetrahedron :: get_p1_id() {
	return this->p1_id;
}

/**
 * @return p2_id Third vertice ID
 */
int Tetrahedron :: get_p2_id() {
	return this->p2_id;
}

/**
 * @return p3_id Fourth vertice ID
 */
int Tetrahedron :: get_p3_id() {
	return this->p3_id;
}

//--------------------------------------------
/**
 * @param[in] p0_id New ID for vertice p0
 */
void Tetrahedron :: set_p0_id(int p0_id) {
	this->p0_id = p0_id;
}

/**
 * @param[in] p1_id New ID for vertice p1
 */
void Tetrahedron :: set_p1_id(int p1_id) {
	this->p1_id = p1_id;
}

/**
 * @param[in] p2_id New ID for vertice p2
 */
void Tetrahedron :: set_p2_id(int p2_id) {
	this->p2_id = p2_id;
}

/**
 * @param[in] p3_id New ID for vertice p3
 */
void Tetrahedron :: set_p3_id(int p3_id) {
	this->p3_id = p3_id;
}
//--------------------------------------------

/**
 * First needs three vector lengths
 * This is calculated by taking one vector as a common point and subtracting the other three vectors
 * Finds volume by calculating the scalar triple product of those three lengths
 * @return volume Volume of tetrahedron
 */
double Tetrahedron :: getVolume() {
	vector3d A, B, C; // Three vector3d objects containing the vectors to the common point p3

	// Calulating vectors to common point
	A = this->p0 - this->p3;
	B = this->p1 - this->p3;
	C = this->p2 - this->p3;

	// Calculating volume by the scalar triple product
	this->volume = (((A.getxCoord()*B.getyCoord()*C.getzCoord())+(A.getyCoord()*B.getzCoord()*C.getxCoord())+(A.getzCoord()*B.getxCoord()*C.getyCoord()))-((A.getxCoord()*B.getzCoord()*C.getyCoord())+(A.getyCoord()*B.getxCoord()*C.getzCoord())+(A.getzCoord()*B.getyCoord()*C.getxCoord())))/((double)6);
	
	this->volume = sqrt(this->volume*this->volume); // Square rooting the square of volume so it's always positive

	return this->volume; // Return calulated volume
}

/**
 * The centre of gravity is calculated by adding all four vertices together and then dividing by four
 * @return tetrahedronCOG Centre of gravity of tetrahedron
 */
vector3d Tetrahedron :: getCOG() {
// The centre of gravity is calculated by adding all four vertices together and then dividing by four

	vector3d divideByFour(4,4,4); // Vector3d instance to dividy by four with

	vector3d tetrahedronCOG = (this->p0 + this->p1 + this->p2 + this->p3) / divideByFour; // Calculating centre of gravity
	
	return tetrahedronCOG; // Return calculated centre of gravity
}

/**
 * @param[in] density Density of material
 * @return Weight of tetrahedron
 */
double Tetrahedron :: getWeight(double density) {
// Weight is calculated by multiplying the volume and density

	return this->volume * density; // Return calculted density
}

//--------------------------------------------

// Pyramid functions

//--------------------------------------------

Pyramid :: Pyramid() {
	this->p0 = vector3d(0,0,0);
	this->p1 = vector3d(0,0,0);
	this->p2 = vector3d(0,0,0);
	this->p3 = vector3d(0,0,0);
	this->p4 = vector3d(0,0,0);
}

/**
 * @param[in] p0,p1,p2,p3,p4 Vertices of new pyramid
 */
Pyramid :: Pyramid(vector3d p0, vector3d p1, vector3d p2, vector3d p3, vector3d p4) {
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
}

Pyramid :: ~Pyramid() {}

//--------------------------------------------
/**
 * @return p0 First vertice
 */
vector3d Pyramid :: get_p0() {
	return this->p0;
}

/**
 * @return p1 Second vertice
 */
vector3d Pyramid :: get_p1() {
	return this->p1;
}

/**
 * @return p2 Third vertice
 */
vector3d Pyramid :: get_p2() {
	return this->p2;
}

/**
 * @return p3 Fourth vertice
 */
vector3d Pyramid :: get_p3() {
	return this->p3;
}

/**
 * @return p4 Fifth vertice
 */
vector3d Pyramid :: get_p4() {
	return this->p4;
}

//--------------------------------------------
/**
 * @param[in] p0 Vertice to set to
 */
void Pyramid :: set_p0(vector3d &p0) {
	this->p0 = p0;
}

/**
 * @param[in] p1 Vertice to set to
 */
void Pyramid :: set_p1(vector3d &p1) {
	this->p1 = p1;
}

/**
 * @param[in] p2 Vertice to set to
 */
void Pyramid :: set_p2(vector3d &p2) {
	this->p2 = p2;
}

/**
 * @param[in] p3 Vertice to set to
 */
void Pyramid :: set_p3(vector3d &p3) {
	this->p3 = p3;
}

/**
 * @param[in] p4 Vertice to set to
 */
void Pyramid :: set_p4(vector3d &p4) {
	this->p4 = p4;
}

//--------------------------------------------
/**
 * @return p0-id First vertice ID
 */
int Pyramid :: get_p0_id() {
	return this->p0_id;
}

/**
 * @return p1_id Second vertice ID
 */
int Pyramid :: get_p1_id() {
	return this->p1_id;
}

/**
 * @return p2_id Third vertice ID
 */
int Pyramid :: get_p2_id() {
	return this->p2_id;
}

/**
 * @return p3_id Fourth vertice ID
 */
int Pyramid :: get_p3_id() {
	return this->p3_id;
}

/**
 * @return p4_id Fifth vertice ID
 */
int Pyramid :: get_p4_id() {
	return this->p4_id;
}

//--------------------------------------------
/**
 * @param[in] p0_id New ID of vertice
 */
void Pyramid :: set_p0_id(int p0_id) {
	this->p0_id = p0_id;
}

/**
 * @param[in] p1_id New ID of vertice
 */
void Pyramid :: set_p1_id(int p1_id) {
	this->p1_id = p1_id;
}

/**
 * @param[in] p2_id New ID of vertice
 */
void Pyramid :: set_p2_id(int p2_id) {
	this->p2_id = p2_id;
}

/**
 * @param[in] p3_id New ID of vertice
 */
void Pyramid :: set_p3_id(int p3_id) {
	this->p3_id = p3_id;
}

/**
 * @param[in] p4_id New ID of vertice
 */
void Pyramid :: set_p4_id(int p4_id) {
	this->p4_id = p4_id;
}
//--------------------------------------------

/**
 * Splits the pyramid into two tetrahedrons,
 * Calculates volume for each tetrahedron,
 * Adds volumes together to get pyramid volume
 * @return volume Calculated value of the volume
 */
double Pyramid :: getVolume() {
// The volume has been calculated by dividing the Pyramid into two Tetrahedrons
// The volume is then calculated for each tetrahedron then summed for total volume of the Pyramid

	vector3d t1A, t1B, t1C, t2A, t2B, t2C; // Two sets of three vector3d objects containing the vectors to a common point

	// Calulating the vectors to common point for first Tetrahedron
	t1A = this->p0 - this->p4;
	t1B = this->p1 - this->p4;
	t1C = this->p2 - this->p4;

	// Calulating the vectors to common point for second Tetrahedron
	t2A = this->p0 - this->p4;
	t2B = this->p3 - this->p4;
	t2C = this->p2 - this->p4;

	// Calculating the volume of each Tetrahedron by the scalar triple product
	double volume1 = (((t1A.getxCoord()*t1B.getyCoord()*t1C.getzCoord())+(t1A.getyCoord()*t1B.getzCoord()*t1C.getxCoord())+(t1A.getzCoord()*t1B.getxCoord()*t1C.getyCoord()))-((t1A.getxCoord()*t1B.getzCoord()*t1C.getyCoord())+(t1A.getyCoord()*t1B.getxCoord()*t1C.getzCoord())+(t1A.getzCoord()*t1B.getyCoord()*t1C.getxCoord())))/((double)6);
	double volume2 = (((t2A.getxCoord()*t2B.getyCoord()*t2C.getzCoord())+(t2A.getyCoord()*t2B.getzCoord()*t2C.getxCoord())+(t2A.getzCoord()*t2B.getxCoord()*t2C.getyCoord()))-((t2A.getxCoord()*t2B.getzCoord()*t2C.getyCoord())+(t2A.getyCoord()*t2B.getxCoord()*t2C.getzCoord())+(t2A.getzCoord()*t2B.getyCoord()*t2C.getxCoord())))/((double)6);

 	// Square rooting the squares of the volumes so it's always positive
	volume1 = sqrt(volume1*volume1);
	volume2 = sqrt(volume2*volume2);

	this->volume = volume1 + volume2; // Summing individual volumes

	return this->volume; // Return calculated volume
}

/**
 * The centre of gravity is calculated by adding all five vertices together and then dividing by five
 * @return pyramidCOG Calculated centre of gravity
 */
vector3d Pyramid :: getCOG() {
// The centre of gravity is calculated by adding all five vertices together and then dividing by five
	
	vector3d divideByFive(5,5,5); // Vector3d instance to dividy by five with
	
	// Calculating centre of gravity
	vector3d pyramidCOG = (this->p0 + this->p1 + this->p2 + this->p3 + this->p4) / divideByFive;
	
	return pyramidCOG; // Return calculated centre of gravity
}

/**
 * Weight is calculated as mass*volume
 * @param[in] density Density of the material
 * @return Weight of the pyramid
 */
double Pyramid :: getWeight(double density) {
// Weight is calculated by multiplying the volume and density

	return this->volume * density; // Return calculted density
}

//--------------------------------------------

// Hexahedron functions

//--------------------------------------------


Hexahedron :: Hexahedron() {
	this->p0 = vector3d(0,0,0);
	this->p1 = vector3d(0,0,0);
	this->p2 = vector3d(0,0,0);
	this->p3 = vector3d(0,0,0);
	this->p4 = vector3d(0,0,0);
	this->p5 = vector3d(0,0,0);
	this->p6 = vector3d(0,0,0);
	this->p7 = vector3d(0,0,0);
}

/**
 * @param[in] p0,p1,p2,p3,p4,p5,p6,p7 Vertices of the hexahedron
 */
Hexahedron :: Hexahedron(vector3d p0, vector3d p1, vector3d p2, vector3d p3, vector3d p4, vector3d p5, vector3d p6, vector3d p7) {
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->p5 = p5;
	this->p6 = p6;
	this->p7 = p7;
}

Hexahedron :: ~Hexahedron() {}

//--------------------------------------------
/**
 * @return p0 First vertice
 */
vector3d Hexahedron :: get_p0() {
	return this->p0;
}

/**
 * @return p1 Second Vertice
 */
vector3d Hexahedron :: get_p1() {
	return this->p1;
}

/**
 * @return p2 Third Vertice
 */
vector3d Hexahedron :: get_p2() {
	return this->p2;
}

/**
 * @return p3 Fourth vertice
 */
vector3d Hexahedron :: get_p3() {
	return this->p3;
}

/**
 * @return p4 Fifth vertice
 */
vector3d Hexahedron :: get_p4() {
	return this->p4;
}

/**
 * @return p5 Sixth vertice
 */
vector3d Hexahedron :: get_p5() {
	return this->p5;
}

/**
 * @return p6 Seventh vertice
 */
vector3d Hexahedron :: get_p6() {
	return this->p6;
}

/**
 * @return p7 Eigth vertice
 */
vector3d Hexahedron :: get_p7() {
	return this->p7;
}

//--------------------------------------------
/**
 * @param[in] p0 New vertice to set
 */
void Hexahedron :: set_p0(vector3d &p0) {
	this->p0 = p0;
}

/**
 * @param[in] p1 New vertice to set
 */
void Hexahedron :: set_p1(vector3d &p1) {
	this->p1 = p1;
}

/**
 * @param[in] p2 New vertice to set
 */
void Hexahedron :: set_p2(vector3d &p2) {
	this->p2 = p2;
}

/**
 * @param[in] p3 New vertice to set
 */
void Hexahedron :: set_p3(vector3d &p3) {
	this->p3 = p3;
}

/**
 * @param[in] p4 New vertice to set
 */
void Hexahedron :: set_p4(vector3d &p4) {
	this->p4 = p4;
}

/**
 * @param[in] p5 New vertice to set
 */
void Hexahedron :: set_p5(vector3d &p5) {
	this->p5 = p5;
}

/**
 * @param[in] p6 New vertice to set
 */
void Hexahedron :: set_p6(vector3d &p6) {
	this->p6 = p6;
}

/**
 * @param[in] p7 New vertice to set
 */
void Hexahedron :: set_p7(vector3d &p7) {
	this->p7 = p7;
}

//--------------------------------------------
/**
 * @return p0_id First vertice ID
 */
int Hexahedron :: get_p0_id() {
	return this->p0_id;
}

/**
 * @return p1_id Second vertice ID
 */
int Hexahedron :: get_p1_id(){
	return this->p1_id;
}

/**
 * @return p2_id Third vertice ID
 */
int Hexahedron :: get_p2_id() {
	return this->p2_id;
}

/**
 * @return p3_id Fourth vertice ID
 */
int Hexahedron :: get_p3_id() {
	return this->p3_id;
}

/**
 * @return p4_id Fifth vertice ID
 */
int Hexahedron :: get_p4_id() {
	return this->p4_id;
}

/**
 * @return p5_id Sixth vertice ID
 */
int Hexahedron :: get_p5_id() {
	return this->p5_id;
}

/**
 * @return p6_id Seventh vertice ID
 */
int Hexahedron :: get_p6_id() {
	return this->p6_id;
}

/**
 * @return p7_id Eigth vertice ID
 */
int Hexahedron :: get_p7_id() {
	return this->p7_id;
}

//--------------------------------------------
/**
 * @param[in] p0_id New ID to set
 */
void Hexahedron :: set_p0_id(int p0_id) {
	this->p0_id = p0_id;
}

/**
 * @param[in] p1_id New ID to set
 */
void Hexahedron :: set_p1_id(int p1_id) {
	this->p1_id = p1_id;
}

/**
 * @param[in] p2_id New ID to set
 */
void Hexahedron :: set_p2_id(int p2_id) {
	this->p2_id = p2_id;
}

/**
 * @param[in] p3_id New ID to set
 */
void Hexahedron :: set_p3_id(int p3_id) {
	this->p3_id = p3_id;
}

/**
 * @param[in] p4_id New ID to set
 */
void Hexahedron :: set_p4_id(int p4_id) {
	this->p4_id = p4_id;
}

/**
 * @param[in] p5_id New ID to set
 */
void Hexahedron :: set_p5_id(int p5_id) {
	this->p5_id = p5_id;
}

/**
 * @param[in] p6_id New ID to set
 */
void Hexahedron :: set_p6_id(int p6_id) {
	this->p6_id = p6_id;
}

/**
 * @param[in] p7_id New ID to set
 */
void Hexahedron :: set_p7_id(int p7_id) {
	this->p7_id = p7_id;
}
//--------------------------------------------

/**
 * Divides hexahedron into five tetrahedrons,
 * Volume calculated for each tetrahedron,
 * Each volume added together to get volume for hexahedron
 * @return volume Calculated value of hexahedron
 */
double Hexahedron :: getVolume() {
// The volume has been calculated by dividing the Hexahedron into five Tetrahedrons
// The volume is then calculated for each tetrahedron then summed for total volume of the Hexahedron

	// Five sets of three vector3d objects containing the vectors to a common point
	vector3d t1A, t1B, t1C, t2A, t2B, t2C, t3A, t3B, t3C, t4A, t4B, t4C, t5A, t5B, t5C;

	// Calulating the vectors to common point for first Tetrahedron
	t1A = this->p0 - this->p5;
	t1B = this->p1 - this->p5;
	t1C = this->p2 - this->p5;

	// Calulating the vectors to common point for second Tetrahedron
	t2A = this->p2 - this->p7;
	t2B = this->p5 - this->p7;
	t2C = this->p6 - this->p7;

	// Calulating the vectors to common point for third Tetrahedron
	t3A = this->p0 - this->p7;
	t3B = this->p4 - this->p7;
	t3C = this->p5 - this->p7;

	// Calulating the vectors to common point for fourth Tetrahedron
	t4A = this->p0 - this->p7;
	t4B = this->p2 - this->p7;
	t4C = this->p3 - this->p7;

	// Calulating the vectors to common point for fifth Tetrahedron
	t5A = this->p0 - this->p7;
	t5B = this->p2 - this->p7;
	t5C = this->p5 - this->p7;

	// Calculating the volume of each Tetrahedron by the scalar triple product
	double volume1 = (((t1A.getxCoord()*t1B.getyCoord()*t1C.getzCoord())+(t1A.getyCoord()*t1B.getzCoord()*t1C.getxCoord())+(t1A.getzCoord()*t1B.getxCoord()*t1C.getyCoord()))-((t1A.getxCoord()*t1B.getzCoord()*t1C.getyCoord())+(t1A.getyCoord()*t1B.getxCoord()*t1C.getzCoord())+(t1A.getzCoord()*t1B.getyCoord()*t1C.getxCoord())))/((double)6);
	double volume2 = (((t2A.getxCoord()*t2B.getyCoord()*t2C.getzCoord())+(t2A.getyCoord()*t2B.getzCoord()*t2C.getxCoord())+(t2A.getzCoord()*t2B.getxCoord()*t2C.getyCoord()))-((t2A.getxCoord()*t2B.getzCoord()*t2C.getyCoord())+(t2A.getyCoord()*t2B.getxCoord()*t2C.getzCoord())+(t2A.getzCoord()*t2B.getyCoord()*t2C.getxCoord())))/((double)6);
	double volume3 = (((t3A.getxCoord()*t3B.getyCoord()*t3C.getzCoord())+(t3A.getyCoord()*t3B.getzCoord()*t3C.getxCoord())+(t3A.getzCoord()*t3B.getxCoord()*t3C.getyCoord()))-((t3A.getxCoord()*t3B.getzCoord()*t3C.getyCoord())+(t3A.getyCoord()*t3B.getxCoord()*t3C.getzCoord())+(t3A.getzCoord()*t3B.getyCoord()*t3C.getxCoord())))/((double)6);
	double volume4 = (((t4A.getxCoord()*t4B.getyCoord()*t4C.getzCoord())+(t4A.getyCoord()*t4B.getzCoord()*t4C.getxCoord())+(t4A.getzCoord()*t4B.getxCoord()*t4C.getyCoord()))-((t4A.getxCoord()*t4B.getzCoord()*t4C.getyCoord())+(t4A.getyCoord()*t4B.getxCoord()*t4C.getzCoord())+(t4A.getzCoord()*t4B.getyCoord()*t4C.getxCoord())))/((double)6);
	double volume5 = (((t5A.getxCoord()*t5B.getyCoord()*t5C.getzCoord())+(t5A.getyCoord()*t5B.getzCoord()*t5C.getxCoord())+(t5A.getzCoord()*t5B.getxCoord()*t5C.getyCoord()))-((t5A.getxCoord()*t5B.getzCoord()*t5C.getyCoord())+(t5A.getyCoord()*t5B.getxCoord()*t5C.getzCoord())+(t5A.getzCoord()*t5B.getyCoord()*t5C.getxCoord())))/((double)6);
	
	// Square rooting the squares of the volumes so it's always positive
	volume1 = sqrt(volume1*volume1);
	volume2 = sqrt(volume2*volume2);
	volume3 = sqrt(volume3*volume3);
	volume4 = sqrt(volume4*volume4);
	volume5 = sqrt(volume5*volume5);

	this->volume = volume1 + volume2 + volume3 + volume4 +volume5; // Summing individual volumes

	return this->volume; // Return calculated volume
}

/**
 * Calculated by adding all eight vertices together before dividing by eight
 * @return hexahedronCOG Calculated value of centre of gravity of hexahedron
 */
vector3d Hexahedron :: getCOG() {
// The centre of gravity is calculated by adding all eight vertices together and then dividing by eight
	
	vector3d divideByEight(8,8,8); // Vector3d instance to dividy by eight with
	
	// Calculating centre of gravity
	vector3d hexahedronCOG = (this->p0 + this->p1 + this->p2 + this->p3 + this->p4 + this->p5 + this->p6 + this->p7) / divideByEight;
	
	return hexahedronCOG; // Return calculated centre of gravity
}

/**
 * Calculates using mass*volume
 * @param[in] density Density of material used
 * @return Calculated value for the weight of the hexahedron
 */
double Hexahedron :: getWeight(double density) {
// Weight is calculated by multiplying the volume and density
	
	return this->volume * density; // Return calculted density
}

//--------------------------------------------
