/** @file
* Header file for the material test class
*/

#include "test_material.h"

/**
* Function to test the material class @n 
* Several variables contaiinng the colour, name, density (etc) of the material are specified @n 
* Then uses the material class functions to set a material instance equal to these values
*/
void test_material()
{
    int color_red = 110;
    int color_green = 120;
    int color_blue = 130;
    int material_id = 2281;
    string material_name = "Test";
    float material_density = 23.45;
    material test_material;
    test_material.set_id(material_id);
    color test_color;
    test_color.set(color_red, color_green, color_blue);
    test_print_color(test_color);
    test_material.set_color(test_color);
    test_material.set_name(material_name);
    test_material.set_density(material_density);
    cout << "ID: " << test_material.get_id() << endl
         << "Name: " << test_material.get_name() << endl
         << "Density: " << test_material.get_density() << endl;
    test_print_color(test_material.get_color());
    cout << "Testing invalid color value:" << endl;
    color invalid_color;
    if (invalid_color.set(1000, color_green, color_blue))
    {
        cout << "   Failed" << endl;
    }
    else
    {
        cout << "   Success" << endl;
    }
    color hexcolor;
    hexcolor.set("121212");
    test_print_color(hexcolor);
    cout << "Testing incorrect hex value:" << endl;
    if (hexcolor.set("xxxxxx"))
    {
        cout << "   Failed" << endl;
    }
    else
    {
        cout << "   Success" << endl;
    }
    cout << "Testing incorrect color size:" << endl;
    if (hexcolor.set("0123456"))
    {
        cout << "   Failed" << endl;
    }
    else
    {
        cout << "   Success" << endl;
    }
    
}

/**
* Function to test the colour @n 
* Prints the RGB and hex values of the shape
*/
void test_print_color(color inputColor)
{
    cout
        << "Color Data: " << endl
        << "	Red: " << inputColor.get_red() << endl
        << "	Green: " << inputColor.get_green() << endl
        << "	Blue: " << inputColor.get_blue() << endl
        << "    HEX:" << inputColor.get_hex() << endl;
}
