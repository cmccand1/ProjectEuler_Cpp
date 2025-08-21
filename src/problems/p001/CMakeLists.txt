add_library(p001 OBJECT p001.cpp)
target_include_directories(p001 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p001 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p001>)
