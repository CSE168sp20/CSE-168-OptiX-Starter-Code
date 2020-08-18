#include "utils.h"

void resultToPNG(std::string outputFilename, int width, int height, 
    const std::vector<unsigned char>& result)
{
    // Attempt to use lodepng to make the png image
    unsigned error = lodepng::encode(outputFilename, result, width, height);
    if (error)
    {
        throw std::runtime_error(lodepng_error_text(error));
    }

    std::cout << outputFilename << " is saved." << std::endl;
}

namespace Viewer
{
    int width, height;
    std::string outputFilename;
    Renderer* renderer;

    void setRenderer(Renderer* renderer)
    {
        Viewer::renderer = renderer;
        width = renderer->getWidth();
        height = renderer->getHeight();
        outputFilename = renderer->getOutputFilename();
    }

    void display()
    {
        renderer->run();

        std::string title = outputFilename;
        int cf = renderer->getCurrentFrame();
        int nf = renderer->getNumFrames();
        title += cf == nf ? " (Finished)" :
            " (" + std::to_string(cf) + "/" + std::to_string(nf) + ")";
        glutSetWindowTitle(title.c_str());

        sutil::displayBufferGL(renderer->getResultBuffer(),
            BUFFER_PIXEL_FORMAT_RGB, true);

        glutSwapBuffers();
    }

    void exit()
    {
        // Output a png image
        resultToPNG(outputFilename, width, height, renderer->getResult());
    }

    void run()
    {
        // Initialize GL state                                                            
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 1, 0, 1, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glViewport(0, 0, width, height);

        glutShowWindow();
        glutReshapeWindow(width, height);

        // register glut callbacks
        glutDisplayFunc(display);
        glutIdleFunc(display);

#ifdef _WIN32
        glutCloseFunc(exit);  // this function is freeglut-only
#else
        atexit(exit);
#endif
        glutMainLoop();
    }
}