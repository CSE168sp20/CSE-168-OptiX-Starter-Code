file(GLOB CPP_FILES "*.cpp")
file(GLOB H_FILES "*.h")
file(GLOB CU_FILES "*.cu") 

include_directories(${GLUT_INCLUDE_DIR})

# See top level CMakeLists.txt file for documentation of OPTIX_add_sample_executable.
OPTIX_add_sample_executable(PathTracer
  ${CPP_FILES}
  ${H_FILES}
  ${CU_FILES} 
)