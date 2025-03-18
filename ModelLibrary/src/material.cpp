#include "material.h"

/** @file
* Main file for the material class
*/

/**
 * @brief Sets colour using three separate values for red, green and blue
 * @param red_value - Red value of new colour
 * @param green_value - Green value of new colour
 * @param blue_value - Blue value of new colour
 */
bool color::set(int red_value, int green_value, int blue_value)
{
    if (red_value > 255 || green_value > 255 || blue_value > 255)
    {
        return false;
    }
    this->red = red_value;
    this->green = green_value;
    this->blue = blue_value;
    return true;
}

/**
 * @brief Sets colour using string value
 * @param value - String that correlates to colour value
 */
bool color::set(string value)
{
	unsigned int tmp_val;
	if (value.length() != 6){
	    return false;
	}
	else
	{
		if (value.find_first_not_of("abcdef0123456789") == string::npos )
		{
			this->red = strtol(value.substr(0, 2).c_str(), NULL, 16);
			this->green = strtol(value.substr(2, 2).c_str(), NULL, 16);
			this->blue = strtol(value.substr(4, 2).c_str(), NULL, 16);	
			return true;
		}
		else 
		{
			return false;
		}
	}
}

/**
 * @brief Gets hexadecimal values of red, green and blue values of colour
 */
string color::get_hex()
{
    std::stringstream sstream_red;
    std::stringstream sstream_green;
    std::stringstream sstream_blue;

	string result;
    string red;
    string green;
    string blue;
    sstream_red << std::hex << this->red;
    sstream_green << std::hex << this->green;
    sstream_blue << std::hex << this->blue;

    red = sstream_red.str();
    green = sstream_green.str();
    blue = sstream_blue.str();

    if(red.size() == 1)
    {
        red = "0" + red;
    }
    if(green.size() == 1)
    {
        green = "0" + green;
    }
    if(blue.size() == 1)
    {
        blue = "0" + blue;
    }

    result = red + green + blue;
	return result;
}
