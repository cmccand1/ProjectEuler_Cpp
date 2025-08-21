add_library(p003 OBJECT p003.cpp)
target_include_directories(p003 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(p003 PRIVATE euler_common)

# contribute to the global list of problem objects
set_property(GLOBAL APPEND PROPERTY PROBLEM_OBJECTS $<TARGET_OBJECTS:p003>)
