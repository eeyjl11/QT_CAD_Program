#ifndef MATERIAL_H
#define MATERIAL_H
#include <iostream>
#include <sstream>

/** @file
* Header file for the material class
*/

using namespace std;
class color {
    private:
        unsigned short int red;
        unsigned short int green;
        unsigned short int blue;
    public:
        color(){};
        color(int _red, int _green, int _blue)
        {
            red = _red;
            green = _green;
            blue = _blue;
        }
        ~color(){}
        bool set(int red_value, int green_value, int blue_value);
	    bool set(string value);
        string get_hex();
        int get_red()
        {
            return red;
        }
        int get_green()
        {
            return green;
        }
        int get_blue()
        {
            return blue;
        }
};

class material {
private:
	int id;
	string name;
	color material_color;
	float density;
public:
    material(){}
    material(int _id, string _name, color _material_color, float _density)
    {
        id = _id;
        name = _name;
        material_color = _material_color;
        density = _density;
    }
    ~material(){}
    void set_id(int set_value)
    {
        this->id = set_value;
    }
    void set_name(string set_value)
    {
        this->name = set_value;
    }
    void set_color(color set_value)
    {
        this->material_color = set_value;
    }
    void set_density(float set_value)
    {
        this->density = set_value;
    }

    int get_id()
    {
        return id;
    }
    string get_name()
    {
        return name;
    }
    color get_color()
    {
        return material_color;
    }
    float get_density()
    {
        return density;
    }
};
#endif
