file(GLOB CPP_FILES "*.cpp")
file(GLOB H_FILES "*.h")
file(GLOB CU_FILES "*.cu") 

# See top level CMakeLists.txt file for documentation of OPTIX_add_sample_executable.
OPTIX_add_sample_executable(PathTracer
  ${CPP_FILES}
  ${H_FILES}
  ${CU_FILES} 
)

if (WIN32) 
  file(COPY Scenes DESTINATION ${CMAKE_BINARY_DIR}/PathTracer)
else() 
  file(COPY Scenes DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif() 