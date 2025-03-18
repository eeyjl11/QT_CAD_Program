#include "test_material.h"
#include "test_model.h"
#include "test_vector3D.h"
#include "test_cell.h"

/** @file
* Main file for the test program
*/

using namespace std;

/** @file
* Main function to call tests @n 
* Runs the material test program @n 
* Runs the model test program @n 
* Runs the vector3d test program @n 
* Runs the tetrahedron test function @n 
* Runs the pyramid test function @n 
* Runs the hexahedron test function
*/
int main(int argc,char *argv[]){
	if (argc != 3)
	{
		cout << "Invalid args supplied" << endl;
		exit(1);
	}
	cout << endl << "Running Material Test" << endl;
	test_material();
	cout << endl << "Running Model Test" << endl;
	test_model(argv[1],argv[2]);
	cout << endl << "Running Vector3D Test" << endl;
	test_vector3d();
	cout << endl << "Running Cell Test" << endl;
	test_tetrahedron();
	test_pyramid();
	test_hexahedron();
}
