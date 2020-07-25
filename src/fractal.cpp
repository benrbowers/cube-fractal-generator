#include <fractal.h>
#include <Label.hpp>
#include <ResourceLoader.hpp>

using namespace godot;

void Fractal::_register_methods() {
    register_method("_ready", &Fractal::_ready);

    register_method("_fractal_button_pressed", &Fractal::_fractal_button_pressed);

    register_method("_fractalize", &Fractal::_fractalize);
}

Fractal::Fractal() {
}

Fractal::~Fractal() {
    //Clean up
}

void Fractal::_init() {
    //Initialize variables
}

void Fractal::_ready() {
    get_parent()->connect("fractalize", this, "_fractal_button_pressed"); // Listen for "fractalize" signal from the Main node
    
    ResourceLoader *loader = ResourceLoader::get_singleton();

    dirt = loader->load("res://Assets/dirt.png");
    stone = loader->load("res://Assets/stone.png");
    netherrack = loader->load("res://Assets/netherrack.png");
    blackstone = loader->load("res://Assets/blackstone.png");
    cobblestone = loader->load("res://Assets/cobblestone.png");

    current_material = stone;

    base_cube = CSGBox::_new(); // Instantiate the base cube for the fractal
}

void Fractal::_fractalize(CSGBox *base_cube, int ratio, int iterations) {
    if (iterations == 1) {
        return;
    }

    int main_side_length = base_cube->get_scale()[0];
    int sub_side_length = main_side_length / ratio;
    int offset = (main_side_length + sub_side_length);
    Vector3 new_scale = Vector3(sub_side_length, sub_side_length, sub_side_length);

    //Top cube
    CSGBox* cube = CSGBox::_new();
    cube->set_scale(new_scale);
    Vector3 origin = cube->get_transform().get_origin();

    std::string std_origin_string = std::to_string(origin[1]);
    godot::String gd_origin_string = godot::String(std_origin_string.c_str());
    Godot::print("Origin1: " + gd_origin_string);
    origin[1] = origin[1] + offset;
    std_origin_string = std::to_string(origin[1]);
    gd_origin_string = godot::String(std_origin_string.c_str());
    Godot::print("Origin2: " + gd_origin_string);

    cube->get_transform().set_origin(origin);
    SpatialMaterial* material = SpatialMaterial::_new();
    material->set_texture(0, current_material);
    material->set_uv1_scale(new_scale);
    cube->set_material(material);
    add_child(cube);
    _fractalize(cube, ratio, iterations - 1);
}

void Fractal::_fractal_button_pressed(int ratio, int iterations) {
    std::string std_ratio_string = std::to_string(ratio);
    godot::String gd_ratio_string = godot::String(std_ratio_string.c_str());
    Godot::print(gd_ratio_string);

    std::string std_iterations_string = std::to_string(iterations);
    godot::String gd_iterations_string = godot::String(std_iterations_string.c_str());
    Godot::print(gd_iterations_string);

    //Prepare the base cube
    int base_size = pow(ratio, iterations);
    Vector3 base_scale = Vector3(base_size, base_size, base_size);
    SpatialMaterial* material = SpatialMaterial::_new();
    material->set_texture(0, current_material);
    material->set_uv1_scale(base_scale);
    base_cube->set_material(material);
    base_cube->set_scale(base_scale);

    add_child(base_cube);

    _fractalize(base_cube, ratio, iterations);
}
