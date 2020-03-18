#pragma once

#include <optixu/optixu_math_namespace.h>
#include "Geometries.h"

/**
 * Structures describing different payloads should be defined here.
 */

struct Payload
{
    optix::float3 radiance;

    // TODO: add more variable to payload if you need to
};

struct ShadowPayload
{
    int isVisible;
};