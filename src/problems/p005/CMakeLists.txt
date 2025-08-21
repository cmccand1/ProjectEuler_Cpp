add_library(p005 OBJECT p005.cpp)
target_include_directories(p005 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p005 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p005>)
