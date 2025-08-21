add_library(p020 OBJECT p020.cpp)
target_include_directories(p020 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p020 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p020>)
