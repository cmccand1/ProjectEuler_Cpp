add_library(p017 OBJECT p017.cpp)
target_include_directories(p017 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p017 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p017>)
