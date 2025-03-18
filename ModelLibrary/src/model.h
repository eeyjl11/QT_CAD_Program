#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <fstream>
#include <vector>
#include "material.h"
#include "vector3D.h"
#include "cell.h"

/** @file
* Header file for model related functions
*/

using namespace std;

/**
* Vertice class
*/
class vertece3d {
    private:
        int id; /**< ID of vertice */
        vector3d data_vector3d; /**< Vector3d containing vector co-ordinates */
    public:

	/**
	* Set ID of vertice
	* @param[in] input ID of vertice
	*/
        void set_id(int input)
        {
            this->id = input;
        };

	/**
	* Get ID of vertice
	* @return id ID of vertice
	*/
        int get_id()
        {
            return id;
        };

	/**
	* Set vector
	* @param[in] input Vector3d whose value you want
	*/
        void set_vector3d(vector3d input)
        {
            this->data_vector3d = input;
        };

	/**
	* Get vector
	* @return data_vector3d Return current vector
	*/
        vector3d get_vector3d()
        {
            return data_vector3d;
        };
};

/**
* Model class
*/
class model {
    public:
        //static vector<string> open_file(string file_path);
        //static int parser(vector<string> &file_to_parse, vector<material> &materials, vector<vertece3d> &vertecies, vector<Tetrahedron> &tetrahedrons, vector<Hexahedron> &hexahedrons, vector<Pyramid> &pyramids);
        static int parser(string file_path, vector<material> &materials, vector<vertece3d> &vertecies, vector<Tetrahedron> &tetrahedrons, vector<Hexahedron> &hexahedrons, vector<Pyramid> &pyramids); /**< Parser */
        static int deparser(string file_path, vector<material> &materials, vector<vertece3d> &vertecies, vector<Tetrahedron> &tetrahedrons, vector<Hexahedron> &hexahedrons, vector<Pyramid> &pyramids); /**< De-parser */
        static vector<string> separate_by_space(string input_string); /**< Checks for spaces */
};
#endif