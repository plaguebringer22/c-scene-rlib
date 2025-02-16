#include "scene.h"

static uint16_t scene_id_pool = 0;

scene_st* scene_create() {
    scene_st* scene_new = (scene_st*) calloc(1, sizeof(scene_st));
    scene_new->scene_id = scene_id_pool++;
    return scene_new;
}

void scene_load(
    scene_st* scene
) {
    if (scene->on_load_function == NULL) return;
    (*(scene->on_load_function))(scene);
}

void scene_destroy(
    scene_st* scene
) {
    // Unload if loaded
    if (scene->on_unload_function != NULL) (*(scene->on_unload_function))(scene);
    // Check if scene->update_functions & scene->draw_functions need freeing
    if (scene->update_functions != NULL) free(scene->update_functions);
    if (scene->draw_functions != NULL) free(scene->draw_functions);
    // Free the scene
    free(scene);
}

void scene_add_update_function(
    scene_st* scene,
    scene_update_func update_func
) {
    scene->update_function_count++;
    scene_update_func* reallocated_array = realloc(
        scene->update_functions, 
        scene->update_function_count*sizeof(scene_update_func*)
    );
    if (reallocated_array == NULL) return;
    scene->update_functions = reallocated_array;
    scene->update_functions[scene->update_function_count-1] = update_func;
}

void scene_add_draw_function(
    scene_st* scene,
    scene_draw_func draw_func
) {
    scene->draw_function_count++;
    scene_draw_func* reallocated_array = realloc(
        scene->draw_functions, 
        scene->draw_function_count*sizeof(scene_draw_func*)
    );
    if (reallocated_array == NULL) return;
    scene->draw_functions = reallocated_array;
    scene->draw_functions[scene->draw_function_count-1] = draw_func;
}

void scene_run(
    scene_st* scene
) {
    float delta_time = GetFrameTime();
    for (int update_idx = 0; update_idx < scene->update_function_count; update_idx++) {
        (*(scene->update_functions[update_idx]))(delta_time);
    }

    for (int draw_idx = 0; draw_idx < scene->draw_function_count; draw_idx++) {
        (*(scene->draw_functions[draw_idx]))();
    }
}

void scene_update(
    scene_st* scene
) {
    float delta_time = GetFrameTime();
    for (int update_idx = 0; update_idx < scene->update_function_count; update_idx++) {
        (*(scene->update_functions[update_idx]))(delta_time);
    }
}

void scene_draw(
    scene_st* scene
) {
    for (int draw_idx = 0; draw_idx < scene->draw_function_count; draw_idx++) {
        (*(scene->draw_functions[draw_idx]))();
    }
}
