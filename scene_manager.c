#include "scene_manager.h"

scene_manager_st* scene_manager_create(scene_st* initial_scene) {
    scene_manager_st* manager = calloc(1, sizeof(scene_manager_st));
    if (manager == NULL) return NULL;
    manager->stack_size = SCENE_MANAGER_PREALLOC_COUNT;
    scene_st** scene_stack = calloc(manager->stack_size, sizeof(scene_st*));
    if (scene_stack == NULL) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m Scene Manager failed to create scene stack!\n");
        return NULL;
    }
    manager->scene_stack = scene_stack;
    scene_stack = NULL;

    manager->active_scene_id = initial_scene->scene_id;
    manager->current_scene_idx = 0;
    manager->scene_stack[0] = initial_scene;

    return manager;
}

scene_st* scene_manager_get_active_scene(scene_manager_st* manager) {
    if (manager == NULL) return NULL;
    return manager->scene_stack[manager->current_scene_idx];
}

// Private function for resizing scene stack, only used internally.
void __scene_manager_resize_stack(scene_manager_st* manager, size_t new_size) {
    if (manager == NULL) return;

    scene_st** resized_stack = realloc(manager->scene_stack, new_size*sizeof(scene_st*));
    if (resized_stack == NULL) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m Scene Manager failed to resize stack!\n");
        return;
    }
    manager->stack_size = new_size;
    manager->scene_stack = resized_stack;
}


void scene_manager_push_scene(scene_manager_st* manager, scene_st* scene) {
    if (manager == NULL || scene == NULL) return;

    if (manager->current_scene_idx == manager->stack_size-1) {
        size_t pre_resize_size = manager->stack_size;
        __scene_manager_resize_stack(manager, manager->stack_size+SCENE_MANAGER_ALLOC_STEP_COUNT); 
        // This occurs when the above resize fails, so return and don't try to write to unallocated memory.
        if (pre_resize_size == manager->stack_size) return;
    }
    manager->current_scene_idx++;
    manager->scene_stack[manager->current_scene_idx] = scene;
    manager->active_scene_id = scene->scene_id;
}

void scene_manager_pop_scene(scene_manager_st* manager) {
    if (manager == NULL) return;
    // If we are the only scene, don't pop and just return.
    if (manager->current_scene_idx == 0) return;
    // Pop the scene
    scene_st* prior_scene = manager->scene_stack[manager->current_scene_idx-1];
    if (prior_scene == NULL) {
        // The prior scene is null somehow, print error and return.
        fprintf(stderr, "\033[31m[ERROR]\033[0m Scene at index %d is NULL, cannot pop backwards!\n", manager->current_scene_idx-1);
        return;
    }
    prior_scene = NULL;
    manager->scene_stack[manager->current_scene_idx] = NULL;
    manager->current_scene_idx--;
    manager->active_scene_id = manager->scene_stack[manager->current_scene_idx]->scene_id;
}

void scene_manager_pop_scenes(scene_manager_st* manager, size_t pop_count) {
    for (size_t idx = 0; idx < pop_count; idx++) {
        scene_manager_pop_scene(manager);
    }
}

void scene_manager_replace_active_scene(scene_manager_st* manager, scene_st* scene) {
    if (manager == NULL || scene == NULL) return;
    manager->scene_stack[manager->current_scene_idx] = scene;
    manager->active_scene_id = scene->scene_id;
}

void scene_manager_destroy(scene_manager_st* manager) {
    if (manager == NULL) return;
    if (manager->scene_stack != NULL) free(manager->scene_stack);
    free(manager);
}
