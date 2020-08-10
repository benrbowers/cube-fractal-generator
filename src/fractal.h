#ifndef FRACTAL_H
#define FRACTAL_H

#include <Godot.hpp>
#include <CSGBox.hpp>
#include <SpatialMaterial.hpp>
#include <Texture.hpp>

namespace godot {
    class Fractal : public Spatial {
        GODOT_CLASS(Fractal, Spatial)

        private:
            Ref<Texture> dirt;
            Ref<Texture> stone;
            Ref<Texture> blackstone;
            Ref<Texture> cobblestone;
            Ref<Texture> netherrack;
            Ref<Texture> current_material;
            enum direction {UP, DOWN, FRONT, BACK, LEFT, RIGHT, NONE};

        public:
            static void _register_methods();

            Fractal();
            ~Fractal();

            void _init();
            void _ready();

            void _fractal_button_pressed(int ratio, int iterations);
            void _fractalize(CSGBox* base_cube, int ratio, int iterations, int build_direction);
    };
}

#endif