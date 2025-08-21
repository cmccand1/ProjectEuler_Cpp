add_library(p007 OBJECT p007.cpp)
target_include_directories(p007 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p007 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p007>)
