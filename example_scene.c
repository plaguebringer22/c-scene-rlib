#include "example_scene.h"

scene_st* example_scene = NULL;

void example_scene_on_load(scene_st* scene) {
    // Insert scene initialisation here such as loading assets, allocating memory, etc.
}

void example_scene_on_unload(scene_st* scene) {
    // Dispose and free any resources here.
}

void example_scene_on_update(float delta_time) {
    // Insert on update code here, such as keypress checking, conditional checking, collision, etc.
    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
        int display = GetCurrentMonitor();
        if (IsWindowFullscreen()) {
            ToggleFullscreen();
            SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        } else {
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
            ToggleFullscreen();
        }
    } 
}

void example_scene_on_draw() {
    // Insert drawing code here
    ClearBackground(BLACK);
    DrawText("Example Scene is loaded and running!", 16, 16, 18, RAYWHITE);
}

scene_st* get_example_scene() {
    if (example_scene != NULL) return example_scene;

    example_scene = scene_create();
    example_scene->on_load_function = example_scene_on_load;
    example_scene->on_unload_function = example_scene_on_unload;
    // Can add multiple update functions
    scene_add_update_function(example_scene, example_scene_on_update);
    // Can add multiple draw functions
    scene_add_draw_function(example_scene, example_scene_on_draw);

    return example_scene;
}
