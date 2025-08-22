add_library(p021 OBJECT p021.cpp)
target_include_directories(p021 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p021 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p021>)
