add_library(p004 OBJECT p004.cpp)
target_include_directories(p004 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p004 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p004>)
