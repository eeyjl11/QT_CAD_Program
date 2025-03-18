/** @file 
* Vector definition file
*/

#include "vector3D.h"

//Constructor definitions
/**
 * Default constructor
 */
vector3d :: vector3d()
{

}

/**
 * Vector3d constructor
 * @param x - X coordinate
 * @param y - Y coordinate
 * @param z - Z coordinate
 */
vector3d :: vector3d( double x, double y, double z)
{
    this->xCoord = x;
    this->yCoord = y;
    this->zCoord = z;
}

//Definitions for get functions

/**
 * Gets x coordinate of vector
 * @return xCoord X co-ordinate
 */
double vector3d :: getxCoord()
{
    return this->xCoord;
}

/**
 * Gets y coordinate of vector
 * @return yCoord Y co-ordinate
 */
double vector3d :: getyCoord()
{
    return this->yCoord;
}

/**
 * Gets z coordinate of vector
 * @return zCoord Z co-ordinate
 */
double vector3d :: getzCoord()
{
    return this->zCoord;
}

//Definitions for set functions
/**
 * Sets the x coordinate of vector
 * @param[in] x - New x coordinate
 */
void vector3d :: setxCoord(double x)
{
    this->xCoord = x;
}

/**
 * Sets the y coordinate of vector
 * @param[in] y - New y coordinate
 */
void vector3d :: setyCoord(double y)
{
    this->yCoord = y;
}

/**
 * Sets the z coordinate of vector
 * @param[in] z - New z coordinate
 */
void vector3d :: setzCoord(double z)
{
    this->zCoord = z;
}

//Operator definitions
/**
 * Operator thats adds two vectors together
 * @param[in] v - Vector which appears after the + sign and is added to the vector before the + sign
 * @return result Result of two vectors added together
 */
vector3d vector3d :: operator+(vector3d v)
{
    vector3d result(this->xCoord+v.getxCoord(), //This is for the + operator
                    this->yCoord+v.getyCoord(), //Simply add the x,y,z values
                    this->zCoord+v.getzCoord());//from each vector by the values
                                           //from the other vector
    return result;
}

/**
 * Operator which subtracts one vectors from another
 * @param[in] v - Vector which is subtracted from the other vector
 * @return result Result of one vector subtracted from another
 */
vector3d vector3d :: operator-(vector3d v)
{
    vector3d result(this->xCoord-v.getxCoord(), //This is for the - operator
                    this->yCoord-v.getyCoord(), //The same procedure as the +
                    this->zCoord-v.getzCoord());

    return result;
}

/**
 * Operator which divides one vector from another
 * @param[in] v - Vector which vector before the sign is divided by
 * @return result Result of two vectors divided together
 */
vector3d vector3d :: operator/(vector3d v)
{
    vector3d result(this->xCoord/v.getxCoord(), //This is for the / operator
                    this->yCoord/v.getyCoord(),//The same procedure as the +
                    this->zCoord/v.getzCoord());

    return result;
}

/**
 * Operator which performs dot product on two vectors
 * @param[in] v - Vector which gets dot multiplied by the vector before sign
 * @return result Dot product of two vectors
 */
double vector3d :: operator*(vector3d v)
{
    double result((this->xCoord*v.getxCoord())+ //This is for scalar/dot product
                    (this->yCoord*v.getyCoord())+ //Multiply the x,y,z by their
                    (this->zCoord*v.getzCoord()));//respective values in the other
                                           //vector and add them all together
    return result;
}

//Does a cross product multiplication on the two vectors
/**
 * Operator which performs cross multiplication of two vectors
 * @param[in] v - Vector which is to be cross-multiplied by the first vector
 * @return result Cross product of two vectors
 */
vector3d vector3d :: operator&(vector3d v)
{
    vector3d result(
                    ((this->yCoord*v.getzCoord())-(this->zCoord*v.getyCoord())),
                    ((this->zCoord*v.getxCoord())-(this->xCoord*v.getzCoord())),
                    ((this->xCoord*v.getyCoord())-(this->yCoord*v.getxCoord())));

    return result;
}

//This next part makes it so you can stream a whole vector object in a the format of 'x, y, z'
/**
 * Operator which allows for a vector to be printed with correct formatting
 * @param[in] obj - Vector which is to be printed
 */
std :: ostream &operator<<(std::ostream &stream, vector3d &obj)
{
    return stream << obj.getxCoord() << ", " << obj.getyCoord() << ", " << obj.getzCoord();
}
