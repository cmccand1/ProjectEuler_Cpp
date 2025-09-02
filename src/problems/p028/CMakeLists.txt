add_library(p028 OBJECT p028.cpp)
target_include_directories(p028 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p028 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p028>)
