add_library(p016 OBJECT p016.cpp)
target_include_directories(p016 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p016 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p016>)
