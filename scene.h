#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

/**
 * @brief   Forward declaration for scene
 */
typedef struct scene scene_st;

/**
 * @brief   A function pointer for update logic
 */
typedef void (*scene_update_func)(float delta_time);
/**
 * @brief   A function pointer for draw logic
 */
typedef void (*scene_draw_func)();
/**
 * @brief   A function pointer for scene load function
 */
typedef void (*scene_on_load)(scene_st* scene);
/**
 * @brief   A function pointer for scene unload function
 */
typedef void (*scene_on_unload)(scene_st* scene);

/**
 * @brief   This struct is responsible for holding scene specific data.
 *          Such as update/draw functions, load/unload, etc.
 */
struct scene {
    uint16_t            scene_id;

    // Lifecycle Functions
    scene_on_load       on_load_function;
    scene_on_unload     on_unload_function;

    // Update & Draw Functions
    scene_update_func*  update_functions;
    scene_draw_func*    draw_functions;
    uint16_t            update_function_count;
    uint16_t            draw_function_count;
};

/**
 * @brief       Create a new scene_st and assign it a unique ID before returning it as a pointer.
 * @note        Ensure you call scene_destroy on any scene_st* instances created with this function.
 * @return      A scene_st pointer.
 */
scene_st*   scene_create();

/**
 * @brief       Calls a scene_st's on_load function.
 * @note        Use a scene_st's on_load function to load any necessary resources before running it.
 * @return      void.
 */
void        scene_load(scene_st* scene);

/**
 * @brief       Destroys an existing scene_st* instance. Freeing all the allocated memory.
 * @param[in]   scene: The scene_st struct pointer to destroy.
 * @return      void.
 */
void        scene_destroy(scene_st* scene);

/**
 * @brief       Ties the supplied update function to the supplied scene.
 * @note        Use this function to connect logic functions specific to a scene, to that scene.
 * @param[in]   scene: The scene_st struct pointer to add the scene_update_func to.
 * @param[in]   update_func: The scene_update_func to add to the scene_st instance.
 * @return      void.
 */
void        scene_add_update_function(scene_st* scene, scene_update_func update_func);

/**
 * @brief       Ties the supplied draw function to the supplied scene.
 * @note        Use this function to connect drawing functions specific to a scene, to that scene.
 * @param[in]   scene: The scene_st struct pointer to add the scene_draw_func to.
 * @param[in]   draw_func: The scene_draw_func to add to the scene_st instance.
 * @return      void.
 */
void        scene_add_draw_function(scene_st* scene, scene_draw_func draw_func);

/**
 * @brief       Runs the scene, which executes the drawing and update functions.
 * @note        Use this function to execute the current scene.
 * @param[in]   scene: The scene_st struct pointer of the scene to run.
 * @return      void;
 */
void        scene_run(scene_st* scene);

/**
 * @brief       Runs the scene update functions.
 * @note        Use this function to execute update functions of the current scene.
 * @param[in]   scene: The scene_st struct pointer of the scene to run.
 * @return      void;
 */
void        scene_update(scene_st* scene);

/**
 * @brief       Runs the scene draw functions.
 * @note        Use this function to execute draw functions of the current scene.
 * @param[in]   scene: The scene_st struct pointer of the scene to run.
 * @return      void;
 */
void        scene_draw(scene_st* scene);
