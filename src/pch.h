/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cmath>
#include <cstring>

/*****
 * STL
 *****/
#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/*****
 * Platform-specific
 *****/
// TODO: Maybe include platform check?
#include <windows.h>

/*******
 * External libraries
 *******/
#ifndef GLEW_STATIC
#  define GLEW_STATIC
#endif /* GLEW_STATIC */
#include <gl/glew.h>

/*******
 * Stable code
 *******/
// #include "def.h"
#include "util/memhooks.h"
