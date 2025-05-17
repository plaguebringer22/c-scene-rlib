#include "example_scene_alt.h"

scene_st* example_alt_scene = NULL;

void example_alt_scene_on_load(scene_st* scene) {
    // Insert scene initialisation here such as loading assets, allocating memory, etc.
}

void example_alt_scene_on_unload(scene_st* scene) {
    // Dispose and free any resources here.
}

void example_alt_scene_on_update(float delta_time) {
    // Insert on update code here, such as keypress checking, conditional checking, collision, etc.
    if (IsKeyPressed(KEY_SPACE)) {
        scene_manager_pop_scene(manager);
    }
}

void example_alt_scene_on_draw() {
    // Insert drawing code here
    ClearBackground(WHITE);
    DrawText("Example Alternative Scene is loaded and running!", 16, 16, 18, BLACK);
}

scene_st* get_example_alt_scene() {
    if (example_alt_scene != NULL) return example_alt_scene;

    example_alt_scene = scene_create();
    example_alt_scene->on_load_function = example_alt_scene_on_load;
    example_alt_scene->on_unload_function = example_alt_scene_on_unload;
    // Can add multiple update functions
    scene_add_update_function(example_alt_scene, example_alt_scene_on_update);
    // Can add multiple draw functions
    scene_add_draw_function(example_alt_scene, example_alt_scene_on_draw);

    return example_alt_scene;
}
