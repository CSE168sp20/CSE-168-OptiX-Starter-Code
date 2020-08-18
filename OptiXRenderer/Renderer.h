#pragma once

// Optix related 
#include <optixu/optixpp_namespace.h>
#include <sutil.h>

// STL
#include <string>
#include <cstring>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <memory>

// Structs to be used for passing info from host to device
#include "Geometries.h"
#include "Light.h"

// Struct representing the scene
#include "Scene.h"

/**
 * Renderer can take a scene, construct the graph for Optix to traverse
 * and render the image described by the scene.
 */
class Renderer
{
    optix::Context context; // an OptiX conext that encapsulates all OptiX resources
    optix::Buffer resultBuffer; // a buffer that stores the rendered image
    std::unordered_map<std::string, optix::Program> programs; // a map that maps a name to a program
    std::shared_ptr<Scene> scene; // the scene to render
    int numFrames; // number of frames to render (>= 1)
    int currentFrame; // the current frame in [1, numFrames], 0 if rendering hasn't started

    // Some info about the output image
    std::string outputFilename;
    unsigned int width, height;

    /**
     * A helper function for readability. One should initialize all the Optix
     * programs here.
     */
    void initPrograms();

    /**
     * A helper function to create a program from a .cu file.
     */
    optix::Program createProgram(const std::string& filename, const std::string& programName);

    /**
     * A helper function to create a buffer and fill it with data.
     */
    template <class T>
    optix::Buffer createBuffer(std::vector<T> data);
public:
    /**
     * The constructor.
     */
    Renderer(std::shared_ptr<Scene> scene);

    /**
     * Build the OptiX Graph according to scene.
     */
    void buildScene();

    /**
     * Run the renderer with the constructed graph. The resultBuffer should
     * contain the rendered image as the function terminates. If progressive
     * is true, it will only render one frame; else, it will render all frames.
     */
    void run(bool progressive = true);

    /**
     * Get the rendered result as a 1D array of bytes.
     */
    std::vector<unsigned char> getResult();

    // Some getters
    std::string getOutputFilename() { return outputFilename; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getNumFrames() { return numFrames; }
    int getCurrentFrame() { return currentFrame; }
    optix::Buffer& getResultBuffer() { return resultBuffer; }
};