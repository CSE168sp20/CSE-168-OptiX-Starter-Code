#include <optix.h>
#include <optix_device.h>
#include "Geometries.h"

using namespace optix;

rtBuffer<Sphere> spheres; // a buffer of all spheres

rtDeclareVariable(Ray, ray, rtCurrentRay, );

// Attributes to be passed to material programs 
rtDeclareVariable(Attributes, attrib, attribute attrib, );

RT_PROGRAM void intersect(int primIndex)
{
    // Find the intersection of the current ray and sphere
    Sphere sphere = spheres[primIndex];
    float t;

    // TODO: implement sphere intersection test here

    // Report intersection (material programs will handle the rest)
    if (rtPotentialIntersection(t))
    {
        // Pass attributes

        // TODO: assign attribute variables here

        rtReportIntersection(0);
    }
}

RT_PROGRAM void bound(int primIndex, float result[6])
{
    Sphere sphere = spheres[primIndex];

    // TODO: implement sphere bouding box
    result[0] = -1000.f;
    result[1] = -1000.f;
    result[2] = -1000.f;
    result[3] = 1000.f;
    result[4] = 1000.f;
    result[5] = 1000.f;
}