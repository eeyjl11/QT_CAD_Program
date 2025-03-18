#include "model.h"
#include <sstream>
#include <algorithm>
using namespace std;
/*
vector<string> model::open_file(string file_path)
{
    ifstream model_file;
    model_file.open(file_path);
    vector<string> tmp_file_storage;
    string line;
    if (model_file.is_open())
    {
        while (getline(model_file, line))
        {
            tmp_file_storage.push_back(line);
        }
        model_file.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    return tmp_file_storage;
}
*/


int model::parser(string file_path, vector<material> &materials, vector<vertece3d> &vertecies, vector<Tetrahedron> &tetrahedrons, vector<Hexahedron> &hexahedrons, vector<Pyramid> &pyramids)
{
    ifstream file_to_parse;
    file_to_parse.open(file_path);

    if (!(file_to_parse.is_open()))
    {
        cout << "Unable to open file" << endl;
        file_to_parse.close();
        return 1;
    }
    int error_counter = 0;
    string current_line;
    while (getline(file_to_parse, current_line))
    {
        if (current_line.empty() || current_line[0] == 13)
        {
            continue;
        }
        else
        {
            current_line.erase(remove(current_line.begin(), current_line.end(), 13), current_line.end());
            vector<string> separated_strings = separate_by_space(current_line);
            if (separated_strings[0].length() > 1)
            {
                continue;
            }
            switch (separated_strings[0][0])
            {
            case 'm':
            {
                if (separated_strings.size() != 5)
                {
                    cout << "Error reading line" << endl;
                    cout << current_line << endl;
                    error_counter++;
                    break;
                }
                material tmp_material;
                tmp_material.set_id(stoi(separated_strings[1]));
                tmp_material.set_density(stof(separated_strings[2]));
                color tmp_color;
                tmp_color.set(separated_strings[3]);
                tmp_material.set_color(tmp_color);
                tmp_material.set_name(separated_strings[4]);
                materials.push_back(tmp_material);
                break;
            }
            case 'v':
            {
                if (separated_strings.size() != 5)
                {
                    cout << "Error reading line" << endl;
                    cout << current_line << endl;
                    error_counter++;
                    break;
                }
                vector3d tmp_vector3d;
                tmp_vector3d = vector3d(stod(separated_strings[2]), stod(separated_strings[3]), stod(separated_strings[4]));
                vertece3d tmp_vertece;
                tmp_vertece.set_id(stoi(separated_strings[1]));
                tmp_vertece.set_vector3d(tmp_vector3d);
                vertecies.push_back(tmp_vertece);
                break;
            }
            case 'c':
            {
                if (!(separated_strings.size() <= 12))
                {
                    cout << "Error reading line" << endl;
                    cout << current_line << endl;
                    error_counter++;
                    break;
                }
                switch (separated_strings[2][0])
                {
                case 't':
                {
                    if ((separated_strings.size() != 8))
                    {
                        cout << "Error reading line" << endl;
                        cout << current_line << endl;
                        error_counter++;
                        continue;
                    }
                    Tetrahedron tmp_tetrahedron;
                    tmp_tetrahedron.set_id(stoi(separated_strings[1]));
                    tmp_tetrahedron.set_material_id(stoi(separated_strings[3]));
                    tmp_tetrahedron.set_p0_id(stoi(separated_strings[4]));
                    tmp_tetrahedron.set_p1_id(stoi(separated_strings[5]));
                    tmp_tetrahedron.set_p2_id(stoi(separated_strings[6]));
                    tmp_tetrahedron.set_p3_id(stoi(separated_strings[7]));
                    tetrahedrons.push_back(tmp_tetrahedron);
                    break;
                }
                case 'h':
                {
                    if ((separated_strings.size() != 12))
                    {
                        cout << "Error reading line" << endl;
                        cout << current_line << endl;
                        error_counter++;
                        continue;
                    }
                    Hexahedron tmp_hexahedron;
                    tmp_hexahedron.set_id(stoi(separated_strings[1]));
                    tmp_hexahedron.set_material_id(stoi(separated_strings[3]));
                    tmp_hexahedron.set_p0_id(stoi(separated_strings[4]));
                    tmp_hexahedron.set_p1_id(stoi(separated_strings[5]));
                    tmp_hexahedron.set_p2_id(stoi(separated_strings[6]));
                    tmp_hexahedron.set_p3_id(stoi(separated_strings[7]));
                    tmp_hexahedron.set_p4_id(stoi(separated_strings[8]));
                    tmp_hexahedron.set_p5_id(stoi(separated_strings[9]));
                    tmp_hexahedron.set_p6_id(stoi(separated_strings[10]));
                    tmp_hexahedron.set_p7_id(stoi(separated_strings[11]));
                    hexahedrons.push_back(tmp_hexahedron);
                    break;
                }
                case 'p':
                {
                    if ((separated_strings.size() != 9))
                    {
                        cout << "Error reading line" << endl;
                        cout << current_line << endl;
                        error_counter++;
                        continue;
                    }
                    Pyramid tmp_pyramid;
                    tmp_pyramid.set_id(stoi(separated_strings[1]));
                    tmp_pyramid.set_material_id(stoi(separated_strings[3]));
                    tmp_pyramid.set_p0_id(stoi(separated_strings[4]));
                    tmp_pyramid.set_p1_id(stoi(separated_strings[5]));
                    tmp_pyramid.set_p2_id(stoi(separated_strings[6]));
                    tmp_pyramid.set_p3_id(stoi(separated_strings[7]));
                    tmp_pyramid.set_p4_id(stoi(separated_strings[8]));
                    pyramids.push_back(tmp_pyramid);
                    break;
                }
                default:
                    cout << "Error reading shape" << endl;
                    cout << current_line << endl;
                    error_counter++;
                    break;
                }
                break;
            }
            case '#': //Comment Line
                break;
            default:
                error_counter++;
                break;
            }
        }
    }
    file_to_parse.close();
    return error_counter;
}

int model::deparser(string file_path, vector<material> &materials, vector<vertece3d> &vertecies, vector<Tetrahedron> &tetrahedrons, vector<Hexahedron> &hexahedrons, vector<Pyramid> &pyramids)
{
    ofstream file_to_deparse;
    file_to_deparse.open(file_path);

    if (!(file_to_deparse.is_open()))
    {
        cout << "Unable to open file" << endl;
        file_to_deparse.close();
        return 1;
    }
    string tmp_string;
    for(material material_item : materials)
    {
        tmp_string = string("m") + string(" ") + 
        to_string(material_item.get_id()) + string(" ") +  
        to_string(material_item.get_density()) + string(" ")  + 
        material_item.get_color().get_hex() +  string(" ") +  
        material_item.get_name();
        cout << tmp_string << endl;
        file_to_deparse << tmp_string << endl;
    }
    for(vertece3d vertece_item : vertecies)
    {
        tmp_string = string("v") + string(" ") + 
        to_string(vertece_item.get_id()) + string(" ") + 
        to_string(vertece_item.get_vector3d().getxCoord()) + string(" ") + 
        to_string(vertece_item.get_vector3d().getyCoord())+ string(" ") + 
        to_string(vertece_item.get_vector3d().getzCoord());
        cout << tmp_string << endl;
        file_to_deparse << tmp_string << endl;
    }
    for(Tetrahedron tetrahedron_item : tetrahedrons)
    {
        tmp_string = string("c") + string(" ") +
        to_string(tetrahedron_item.get_id()) + string(" ") +
        string("t") + string(" ") + 
        to_string(tetrahedron_item.get_material_id()) + string(" ") +
        to_string(tetrahedron_item.get_p0_id()) + string(" ") +
        to_string(tetrahedron_item.get_p1_id()) + string(" ") +
        to_string(tetrahedron_item.get_p2_id()) + string(" ") +
        to_string(tetrahedron_item.get_p3_id());
        cout << tmp_string << endl;
        file_to_deparse << tmp_string << endl;
    }
    for(Pyramid pyramid_item : pyramids)
    {
        tmp_string = string("c") + string(" ") + 
        to_string(pyramid_item.get_id()) + string(" ") + 
        string("p") + string(" ") + 
        to_string(pyramid_item.get_material_id()) + string(" ") +
        to_string(pyramid_item.get_p0_id()) + string(" ") +
        to_string(pyramid_item.get_p1_id()) + string(" ") +
        to_string(pyramid_item.get_p2_id()) + string(" ") +
        to_string(pyramid_item.get_p3_id()) + string(" ") +
        to_string(pyramid_item.get_p4_id());
        cout << tmp_string << endl;
        file_to_deparse << tmp_string << endl;
    }
    for(Hexahedron hexahedron_item : hexahedrons)
    {
        tmp_string = string("c") + string(" ") + 
        to_string(hexahedron_item.get_id()) + string(" ") + 
        string("h") + string(" ") + 
        to_string(hexahedron_item.get_material_id()) + string(" ") +
        to_string(hexahedron_item.get_p0_id()) + string(" ") +
        to_string(hexahedron_item.get_p1_id()) + string(" ") +
        to_string(hexahedron_item.get_p2_id()) + string(" ") +
        to_string(hexahedron_item.get_p3_id()) + string(" ") +
        to_string(hexahedron_item.get_p4_id()) + string(" ") +
        to_string(hexahedron_item.get_p5_id()) + string(" ") +
        to_string(hexahedron_item.get_p6_id()) + string(" ") +
        to_string(hexahedron_item.get_p7_id());
        cout << tmp_string << endl;
        file_to_deparse << tmp_string << endl;
    }
    file_to_deparse.close();
    return 0;
}

vector<string> model::separate_by_space(string const input_string)
{
    vector<string> separated_strings;

    stringstream ss(input_string);

    string s;
    while (std::getline(ss, s, ' '))
    {
        separated_strings.push_back(s);
    }
    return separated_strings;
}
