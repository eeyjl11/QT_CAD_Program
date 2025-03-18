#include "test_model.h"
int test_model(char * input_file_path,char * output_file_path)
{
    vector<material> our_materials;
    vector<vertece3d> our_verteces;
    vector<Tetrahedron> our_tetrahedrons;
    vector<Hexahedron> our_hexahedrons;
    vector<Pyramid> our_pyramids;
    string example_file = input_file_path;
    string output_file = output_file_path;
    cout << "Input file: " << example_file << endl;
    //int parser_errors = model::parser(opened_file,our_materials,our_shapes,our_verteces);
    int parser_errors = model::parser(example_file, our_materials, our_verteces, our_tetrahedrons, our_hexahedrons, our_pyramids);
    if (parser_errors > 1)
    {
        cout << "Errors in parser: " << parser_errors << endl;
    }
    cout << "Materials parsed: " << our_materials.size() << endl;
    for (int i = 0; i < our_materials.size(); i++)
    {
        print_material(our_materials[i].get_id(),our_materials);
    }
    cout << "Vertecies parsed: " << our_verteces.size() << endl;
    for (int i = 0; i < our_verteces.size(); i++)
    {
        print_vertecies(our_verteces[i].get_id(),our_verteces);
    }
    cout << "Cells parsed: " << (our_tetrahedrons.size() + our_hexahedrons.size() + our_pyramids.size()) << endl;
    cout << "Tetrahedrons : " << our_tetrahedrons.size() << endl;
    for (int i = 0; i < our_tetrahedrons.size(); i++)
    {
        cout << "ID: " << our_tetrahedrons[i].get_id() << endl;
        cout << "Material Info:" << endl;
        print_material(our_tetrahedrons[i].get_material_id(),our_materials);
        cout << "Vertecies:" << endl;
        print_vertecies(our_tetrahedrons[i].get_p0_id(),our_verteces);
        print_vertecies(our_tetrahedrons[i].get_p1_id(),our_verteces);
        print_vertecies(our_tetrahedrons[i].get_p2_id(),our_verteces);
        print_vertecies(our_tetrahedrons[i].get_p3_id(),our_verteces);
    }
    cout << "Pyramids : " << our_pyramids.size() << endl;
    for (int i = 0; i < our_pyramids.size(); i++)
    {
        cout << "ID: " << our_pyramids[i].get_id() << endl;
        cout << "Material Info:" << endl;
        print_material(our_pyramids[i].get_material_id(),our_materials);
        cout << "Vertecies:" << endl;
        print_vertecies(our_pyramids[i].get_p0_id(),our_verteces);
        print_vertecies(our_pyramids[i].get_p1_id(),our_verteces);
        print_vertecies(our_pyramids[i].get_p2_id(),our_verteces);
        print_vertecies(our_pyramids[i].get_p3_id(),our_verteces);
        print_vertecies(our_pyramids[i].get_p4_id(),our_verteces);
    }
    cout << "Hexahedrons : " << our_hexahedrons.size() << endl;
    for (int i = 0; i < our_hexahedrons.size(); i++)
    {
        cout << "ID: " << our_hexahedrons[i].get_id() << endl;
        cout << "Material Info:" << endl;
        print_material(our_hexahedrons[i].get_material_id(),our_materials);
        cout << "Vertecies:" << endl;
        print_vertecies(our_hexahedrons[i].get_p0_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p1_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p2_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p3_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p4_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p5_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p6_id(),our_verteces);
        print_vertecies(our_hexahedrons[i].get_p7_id(),our_verteces);
    }
    model::deparser(output_file, our_materials, our_verteces, our_tetrahedrons, our_hexahedrons, our_pyramids);
    return 0;
}


void print_material(int input_material_id,vector<material> &input_materials)
{
    cout << "ID: " << input_materials[input_material_id].get_id() << ", "
             << "Name: " << input_materials[input_material_id].get_name() << ", "
             << "Density: " << input_materials[input_material_id].get_density() << ", "
             << "Color: { "
             << "R: " << input_materials[input_material_id].get_color().get_red() << " "
             << "G: " << input_materials[input_material_id].get_color().get_green() << " "
             << "B: " << input_materials[input_material_id].get_color().get_blue() << " }" << endl;
}

void print_vertecies(int input_vertece3d_id,vector<vertece3d> &input_vertece3ds)
{
    cout << "ID: " << input_vertece3ds[input_vertece3d_id].get_id() << ", "
             << "X: " << input_vertece3ds[input_vertece3d_id].get_vector3d().getxCoord() << ", "
             << "Y: " << input_vertece3ds[input_vertece3d_id].get_vector3d().getyCoord() << ", "
             << "Z: " << input_vertece3ds[input_vertece3d_id].get_vector3d().getzCoord() << endl;
}
