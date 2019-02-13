
#pragma once

#include "targetver.h"

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN             

// Windows Header Files:
#include <windows.h>
#include <windowsx.h>

#include <map>

// OpenGL headers files
#include <GL\GL.h>
#include <GL\GLU.h>

// OpenGL link files
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "glu32.lib")

//User classes
#include "DrawingObject.h"
#include "KinematicScheme.h"
#include "Scene.h"

//// C RunTime Header Files
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>

// TODO: reference additional headers your program requires here
