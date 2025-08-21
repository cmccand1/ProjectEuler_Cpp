add_library(p002 OBJECT p002.cpp)
target_include_directories(p002 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p002 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p002>)
