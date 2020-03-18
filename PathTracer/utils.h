#pragma once

// OpenGL related
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glew.h>
#  if defined( _WIN32 )
#    include <GL/freeglut.h>
#  else
#    include <GL/glut.h>
#  endif
#endif

// OptiX
#include <optixu/optixpp_namespace.h>
#include <sutil.h>

// A library for outputing images
#include "lodepng.h"

// Renderer
#include "Renderer.h"

// STL
#include <vector>
#include <string>
#include <iostream>


/**
 * Output a png image of the rendered result.
 */
void resultToPNG(std::string outputFilename, int width, int height, 
    const std::vector<unsigned char>& result);

/**
 * Display the rendering process progressively using OpenGL and GLUT. 
 */
namespace Viewer
{
    extern int width, height;
    extern std::string outputFilename;
    extern Renderer* renderer;

    void setRenderer(Renderer* renderer);

    void display();

    void exit();

    void run();
}