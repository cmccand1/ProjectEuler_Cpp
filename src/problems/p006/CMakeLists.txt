add_library(p006 OBJECT p006.cpp)
target_include_directories(p006 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p006 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p006>)
