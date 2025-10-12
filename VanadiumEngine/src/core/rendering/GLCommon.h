#pragma once
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>	

GLenum glCheckError_(const char* file, int line);

#define GL_CHECK(stmt) stmt; glCheckError_(__FILE__, __LINE__);