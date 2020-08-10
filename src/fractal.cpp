#include <fractal.h>
#include <Label.hpp>
#include <ResourceLoader.hpp>
#include <OS.hpp>

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
}

void Fractal::_fractalize(CSGBox *base_cube, int ratio, int iterations, int build_direction) {

    if (iterations == 1) { // Base case
        return;
    }

    int main_side_length = base_cube->get_scale().x;
    int sub_side_length = main_side_length / ratio;
    int offset = (main_side_length + sub_side_length);
    Vector3 new_scale = Vector3(sub_side_length, sub_side_length, sub_side_length);

    if (build_direction != direction::DOWN) {
        //Top cube
        CSGBox* cube = CSGBox::_new(); // Instantiate a CSGBox
        cube->set_scale(new_scale); // Set the size
        // Set position:
        Vector3 origin = base_cube->get_transform().get_origin();
        origin.y = origin.y + offset;
        Transform transform = cube->get_transform();
        transform.set_origin(origin);
        cube->set_transform(transform);
        // Set texture:
        SpatialMaterial* material = SpatialMaterial::_new();
        material->set_texture(0, current_material);
        material->set_uv1_scale(new_scale);
        cube->set_material(material);
        // Add to scene:
        add_child(cube);
        _fractalize(cube, ratio, iterations - 1, direction::UP);
    }

    if (build_direction != direction::UP) {
        //Bottom cube
        CSGBox* cube = CSGBox::_new(); // Instantiate a CSGBox
        cube->set_scale(new_scale); // Set the size
        // Set position:
        Vector3 origin = base_cube->get_transform().get_origin();
        origin.y = origin.y - offset;
        Transform transform = cube->get_transform();
        transform.set_origin(origin);
        cube->set_transform(transform);
        // Set texture:
        SpatialMaterial* material = SpatialMaterial::_new();
        material->set_texture(0, current_material);
        material->set_uv1_scale(new_scale);
        cube->set_material(material);
        // Add to scene:
        add_child(cube);
        _fractalize(cube, ratio, iterations - 1, direction::DOWN);
    }

    if (build_direction != direction::RIGHT) {
        //Left cube
        CSGBox* cube = CSGBox::_new(); // Instantiate a CSGBox
        cube->set_scale(new_scale); // Set the size
        // Set position:
        Vector3 origin = base_cube->get_transform().get_origin();
        origin.x = origin.x - offset;
        Transform transform = cube->get_transform();
        transform.set_origin(origin);
        cube->set_transform(transform);
        // Set texture:
        SpatialMaterial* material = SpatialMaterial::_new();
        material->set_texture(0, current_material);
        material->set_uv1_scale(new_scale);
        cube->set_material(material);
        // Add to scene:
        add_child(cube);
        _fractalize(cube, ratio, iterations - 1, direction::LEFT);
    }

    if (build_direction != direction::LEFT) {
        //Right cube
        CSGBox* cube = CSGBox::_new(); // Instantiate a CSGBox
        cube->set_scale(new_scale); // Set the size
        // Set position:
        Vector3 origin = base_cube->get_transform().get_origin();
        origin.x = origin.x + offset;
        Transform transform = cube->get_transform();
        transform.set_origin(origin);
        cube->set_transform(transform);
        // Set texture:
        SpatialMaterial* material = SpatialMaterial::_new();
        material->set_texture(0, current_material);
        material->set_uv1_scale(new_scale);
        cube->set_material(material);
        // Add to scene:
        add_child(cube);
        _fractalize(cube, ratio, iterations - 1, direction::RIGHT);
    }

    if (build_direction != direction::FRONT) {
        //Back cube
        CSGBox* cube = CSGBox::_new(); // Instantiate a CSGBox
        cube->set_scale(new_scale); // Set the size
        // Set position:
        Vector3 origin = base_cube->get_transform().get_origin();
        origin.z = origin.z - offset;
        Transform transform = cube->get_transform();
        transform.set_origin(origin);
        cube->set_transform(transform);
        // Set texture:
        SpatialMaterial* material = SpatialMaterial::_new();
        material->set_texture(0, current_material);
        material->set_uv1_scale(new_scale);
        cube->set_material(material);
        // Add to scene:
        add_child(cube);
        _fractalize(cube, ratio, iterations - 1, direction::BACK);
    }

    if (build_direction != direction::BACK) {
        //Front cube
        CSGBox* cube = CSGBox::_new(); // Instantiate a CSGBox
        cube->set_scale(new_scale); // Set the size
        // Set position:
        Vector3 origin = base_cube->get_transform().get_origin();
        origin.z = origin.z + offset;
        Transform transform = cube->get_transform();
        transform.set_origin(origin);
        cube->set_transform(transform);
        // Set texture:
        SpatialMaterial* material = SpatialMaterial::_new();
        material->set_texture(0, current_material);
        material->set_uv1_scale(new_scale);
        cube->set_material(material);
        // Add to scene:
        add_child(cube);
        _fractalize(cube, ratio, iterations - 1, direction::FRONT);
    }
}

void Fractal::_fractal_button_pressed(int ratio, int iterations) {
    //std::string std_ratio_string = std::to_string(ratio);
    //godot::String gd_ratio_string = godot::String(std_ratio_string.c_str());
    //Godot::print(gd_ratio_string);

    //std::string std_iterations_string = std::to_string(iterations);
    //godot::String gd_iterations_string = godot::String(std_iterations_string.c_str());
    //Godot::print(gd_iterations_string);

    Array children = get_children();

    for (int i = 0; i < children.size(); i++) {
        Object::cast_to<CSGBox>(children[i])->queue_free();
    }

    //Prepare the base cube
    int base_size = pow(ratio, iterations); // Enlarge base cube so smallest will end up as 2x2
    Vector3 base_scale = Vector3(base_size, base_size, base_size);
    SpatialMaterial* material = SpatialMaterial::_new();
    material->set_texture(0, current_material);
    material->set_uv1_scale(base_scale);
    CSGBox *base_cube = CSGBox::_new();
    base_cube->set_material(material);
    base_cube->set_scale(base_scale);

    add_child(base_cube);

    OS* os = OS::get_singleton();

    int time_before = os->get_ticks_usec();
    _fractalize(base_cube, ratio, iterations, direction::NONE);
    int time_took = os->get_ticks_usec() - time_before;

    std::string std_time_string = std::to_string(time_took);
    godot::String gd_time_string = godot::String(std_time_string.c_str());
    Godot::print("Fractalizing took: " + gd_time_string + " usec");
}
