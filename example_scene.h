#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <raylib.h>

#include "scene_manager.h"
#include "scene.h"
#include "example_scene_alt.h"

extern scene_manager_st* manager;

scene_st* get_example_scene();

