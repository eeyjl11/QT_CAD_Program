/** @file
* Header file for the cell class
*/

#ifndef CELL_H
#define CELL_H

//--------------------------------------------

// Cell.h

// Copyright Jason Lloyd

// Header containing the cell class and subclasses for Tetrahedron, Pyramid and Hexahedron

// Required headers: material.h, vector3d.h, vector

//--------------------------------------------

#include "material.h"

#include "vector3D.h"

#include <vector>

//--------------------------------------------

// Cell class

//--------------------------------------------

/**
* Parent cell class that contains the vertices, vertice order ID and colour of each shape. Also contains declarations for the volume, centre of gravity and weight functions. 
*/
class Cell {
protected:
	std::vector<vector3d> vertices; /**< Vector of vertices of the shape */
	std::vector<int> verticeOrder; /**< Order of the vertices on the shape */
	int id; /**< Shape ID */
	int material_id; /**< Material ID of the shape */
	double volume; /**< Volume of the shape */
	material cellMaterial; /**< Material class instance containing colour and density */
	color col; /**< Colour of the shape */
public:
	virtual double getVolume(); /**< Volume function */
	virtual vector3d getCOG(); /**< Centre of gravity function */
	virtual double getWeight(double density); /**< Weight function */

	int get_id(); /**< Gets the ID of a cell. */

	void set_id(int id); /**< Sets the ID of a cell. */

	int get_material_id(); /**< Gets the material ID of a cell. */

	void set_material_id(int material_id); /**< Set material ID */

	void set_colour(color &c); /**< Sets the colour of a cell. */
};

//--------------------------------------------

// Tetrahedron class

//--------------------------------------------

/**
* Class containing the points of a Tetrahedron, as well as the functions to calculate volume, centre of gravity and weight. 
*/
class Tetrahedron : public Cell {
private:
	vector3d p0, p1, p2, p3; /**< The four vertices needed for the shape */
	int p0_id, p1_id, p2_id, p3_id; /**< The ID values of the four vertices */
public:
	Tetrahedron(); /**< Default constructor for tetrahedron */
	Tetrahedron(vector3d p0, vector3d p1, vector3d p2, vector3d p3); /**< Alternate constructor of Tetrahedron, containing the arguments of the four vertices */
	~Tetrahedron(); /**< Destructor for tetrahedron */

	// Get values of the vector points
	vector3d get_p0(); /**< Get x, y, z values of vector 0 */
	vector3d get_p1(); /**< Get x, y, z values of vector 1 */
	vector3d get_p2(); /**< Get x, y, z values of vector 2 */
	vector3d get_p3(); /**< Get x, y, z values of vector 3 */

	// Set values of the vector points
	void set_p0(vector3d &p0); /**< Set x, y, z values of vector 0 */
	void set_p1(vector3d &p1); /**< Set x, y, z values of vector 1 */
	void set_p2(vector3d &p2); /**< Set x, y, z values of vector 2 */
	void set_p3(vector3d &p3); /**< Set x, y, z values of vector 3 */

	// Get ID values of the vector points
	int get_p0_id(); /**< Get ID value of vector 0 */
	int get_p1_id(); /**< Get ID value of vector 1 */
	int get_p2_id(); /**< Get ID value of vector 2 */
	int get_p3_id(); /**< Get ID value of vector 3 */
	
	// Set ID values of the vector points
	void set_p0_id(int p0_id); /**< Set ID value of vector 0 */
	void set_p1_id(int p1_id); /**< Set ID value of vector 1 */
	void set_p2_id(int p2_id); /**< Set ID value of vector 2 */
	void set_p3_id(int p3_id); /**< Set ID value of vector 3 */

	/**
	* Member function to calculate volume of Tetrahedron
	*/
	double getVolume(); /**< Get volume of the Tetrahedron */

	/**
	* Member function to find centre of gravity of Tetrahedron
	*/
	vector3d getCOG(); /**< Get the centre of gravity of the Tetrahedron */

	/**
	* Member function to calculate weight of Tetrahedron
	*/
	double getWeight(double density); /**< Get the weight of the Tetrahedron */
};

//--------------------------------------------

// Pyramid class

//--------------------------------------------

/**
* Class containing the points of a Pyramid, as well as the functions to calculate volume, centre of gravity and weight. 
*/
class Pyramid : public Cell {
private:
	vector3d p0, p1, p2, p3, p4; /**< The five vertices needed for the shape */
	int p0_id, p1_id, p2_id, p3_id, p4_id; /**< The ID values of the five vertices */
public:
	Pyramid(); /**< Default constructor of pyramid */
	Pyramid(vector3d p0, vector3d p1, vector3d p2, vector3d p3, vector3d p4); /**< Alternate constructor of Pyramid, containing the arguments of the five vertices */
	~Pyramid(); /**< Pyramid destructor */

	// Get values of the vector points
	vector3d get_p0(); /**< Get x, y, z values of vector 0 */
	vector3d get_p1(); /**< Get x, y, z values of vector 1 */
	vector3d get_p2(); /**< Get x, y, z values of vector 2 */
	vector3d get_p3(); /**< Get x, y, z values of vector 3 */
	vector3d get_p4(); /**< Get x, y, z values of vector 4 */

	// Set values of the vector points
	void set_p0(vector3d &p0); /**< Set x, y, z values of vector 0 */
	void set_p1(vector3d &p1); /**< Set x, y, z values of vector 1 */
	void set_p2(vector3d &p2); /**< Set x, y, z values of vector 2 */
	void set_p3(vector3d &p3); /**< Set x, y, z values of vector 3 */
	void set_p4(vector3d &p4); /**< Set x, y, z values of vector 4 */

	// Get ID values of the vector points
	int get_p0_id(); /**< Get ID value of vector 0 */
	int get_p1_id(); /**< Get ID value of vector 1 */
	int get_p2_id(); /**< Get ID value of vector 2 */
	int get_p3_id(); /**< Get ID value of vector 3 */
	int get_p4_id(); /**< Get ID value of vector 4 */
	
	// Set ID values of the vector points
	void set_p0_id(int p0_id); /**< Set ID value of vector 0 */
	void set_p1_id(int p1_id); /**< Set ID value of vector 1 */
	void set_p2_id(int p2_id); /**< Set ID value of vector 2 */
	void set_p3_id(int p3_id); /**< Set ID value of vector 3 */
	void set_p4_id(int p4_id); /**< Set ID value of vector 4 */

	/**
	* Member function to calculate volume of Pyramid
	*/
	double getVolume(); /**< Get volume of the Pyramid */

	/**
	* Member function to find centre of gravity of Pyramid
	*/
	vector3d getCOG(); /**< Get the centre of gravity of the Pyramid */

	/**
	* Member function to calculate weight of Pyramid
	*/
	double getWeight(double density); /**< Get the weight of the Pyramid */
};

//--------------------------------------------

// Hexahedron class

//--------------------------------------------

/**
* Class containing the points of a Hexahedron, as well as the functions to calculate volume, centre of gravity and weight. 
*/
class Hexahedron : public Cell {
private:
	vector3d p0, p1, p2, p3, p4, p5, p6, p7; /**< The eight vertices needed for the shape */
	int p0_id, p1_id, p2_id, p3_id, p4_id, p5_id, p6_id, p7_id; // The ID values of the eight vertices */
public:
	Hexahedron(); /**< Default constructor for hexahedron */
	Hexahedron(vector3d p0, vector3d p1, vector3d p2, vector3d p3, vector3d p4, vector3d p5, vector3d p6, vector3d p7); /**< Alternate constructor of Hexahedron, containing the arguments of the eight vertices */
	~Hexahedron(); /**< Destructor of hexahedron */

	// Get values of the vector points
	vector3d get_p0(); /**< Get x, y, z values of vector 0 */
	vector3d get_p1(); /**< Get x, y, z values of vector 1 */
	vector3d get_p2(); /**< Get x, y, z values of vector 2 */
	vector3d get_p3(); /**< Get x, y, z values of vector 3 */
	vector3d get_p4(); /**< Get x, y, z values of vector 4 */
	vector3d get_p5(); /**< Get x, y, z values of vector 5 */
	vector3d get_p6(); /**< Get x, y, z values of vector 6 */
	vector3d get_p7(); /**< Get x, y, z values of vector 7 */

	// Set values of the vector points
	void set_p0(vector3d &p0); /**< Set x, y, z values of vector 0 */
	void set_p1(vector3d &p1); /**< Set x, y, z values of vector 1 */
	void set_p2(vector3d &p2); /**< Set x, y, z values of vector 2 */
	void set_p3(vector3d &p3); /**< Set x, y, z values of vector 3 */
	void set_p4(vector3d &p4); /**< Set x, y, z values of vector 4 */
	void set_p5(vector3d &p5); /**< Set x, y, z values of vector 5 */
	void set_p6(vector3d &p6); /**< Set x, y, z values of vector 6 */
	void set_p7(vector3d &p7); /**< Set x, y, z values of vector 7 */

	// Get ID values of the vector points
	int get_p0_id(); /**< Get ID value of vector 0 */
	int get_p1_id(); /**< Get ID value of vector 1 */
	int get_p2_id(); /**< Get ID value of vector 2 */
	int get_p3_id(); /**< Get ID value of vector 3 */
	int get_p4_id(); /**< Get ID value of vector 4 */
	int get_p5_id(); /**< Get ID value of vector 5 */
	int get_p6_id(); /**< Get ID value of vector 6 */
	int get_p7_id(); /**< Get ID value of vector 7 */
	
	// Set ID values of the vector points
	void set_p0_id(int p0_id); /**< Set ID value of vector 0 */
	void set_p1_id(int p1_id); /**< Set ID value of vector 1 */
	void set_p2_id(int p2_id); /**< Set ID value of vector 2 */
	void set_p3_id(int p3_id); /**< Set ID value of vector 3 */
	void set_p4_id(int p4_id); /**< Set ID value of vector 4 */
	void set_p5_id(int p5_id); /**< Set ID value of vector 5 */
	void set_p6_id(int p6_id); /**< Set ID value of vector 6 */
	void set_p7_id(int p7_id); /**< Set ID value of vector 7 */

	/**
	* Member function to calculate volume of Hexahedron
	*/
	double getVolume(); /**< Get volume of the Hexahedron */

	/**
	* Member function to find centre of gravity of Hexahedron
	*/
	vector3d getCOG(); /**< Get the centre of gravity of the Hexahedron */

	/**
	* Member function to calculate weight of Hexahedron
	*/
	double getWeight(double density); /**< Get the weight of the Hexahedron */
};

//--------------------------------------------
#endif
