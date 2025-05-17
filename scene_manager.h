#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#include "scene.h"

#define SCENE_MANAGER_PREALLOC_COUNT (size_t) 10
#define SCENE_MANAGER_ALLOC_STEP_COUNT (size_t) 5

/**
 * @brief   Forward declaration for scene manager
 */
typedef struct scene_manager scene_manager_st;

/**
 * @brief   This struct is responsible for holding scenes and handling
 *          scene navigation.
 */
struct scene_manager {
    // The id of the active(current) scene
    uint16_t        active_scene_id;
    // Index for the current scene
    uint16_t        current_scene_idx;
    // Length for the scene_stack
    size_t          stack_size;

    // Arrays
    scene_st**      scene_stack; 

};

/**
 * @brief   Create a new scene_manager_st and initialise it's scene_stack.
 * @note    The scene_manager will allocate more memory for scenes as needed.
 * @return  A scene_manager_st pointer.
 */
scene_manager_st*   scene_manager_create(scene_st* initial_scene);

/**
 * @brief   Get the currently active scene.
 * @note    Use this in palce of referencing the current scene.
 * @return  A scene_st pointer. 
 */
scene_st*           scene_manager_get_active_scene(scene_manager_st* manager);

/**
 * @brief   Push a new scene onto the scene stack.
 * @note    This will allow for navigating back to the prior scene,
 *          as pushing it onto the stack preserves the previous scene(s).
 * @return  void.
 */
void                scene_manager_push_scene(scene_manager_st* manager, scene_st* scene);

/**
 * @brief   Go back from the current scene, "popping" it off the scene stack.
 * @note    This is essentially a backwards navigation, however it removes the
 *          current scene from the stack in the process.
 * @return  void.
 */
void                scene_manager_pop_scene(scene_manager_st* manager);

/**
 * @brief   Wrapper for calling `pop_scene` multiple times.
 * @return  void.
 */
void                scene_manager_pop_scenes(scene_manager_st* manager, size_t pop_count);

/**
 * @brief   Replace the current scene with a different scene.
 * @note    This is destructive, it replaces the active scene instead
 *          of simply moving past it in the stack. This removes the
 *          ability to pop back to the replaced active scene.
 * @return  void.
 */
void                scene_manager_replace_active_scene(scene_manager_st* manager, scene_st* scene);

/**
 * @brief       Destroys an existing scene_manager_st* instance. Freeing all the allocated memory.
 * @param[in]   manager: The scene_manager_st struct pointer to destroy.
 * @return      void.
 */
void                scene_manager_destroy(scene_manager_st* manager);
