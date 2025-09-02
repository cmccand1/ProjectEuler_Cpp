add_library(p025 OBJECT p025.cpp)
target_include_directories(p025 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p025 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p025>)
