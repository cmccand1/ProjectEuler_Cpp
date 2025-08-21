add_library(p010 OBJECT p010.cpp)
target_include_directories(p010 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p010 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p010>)
