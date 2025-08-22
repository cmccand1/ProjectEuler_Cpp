# for adding each pNNN subdir
# Dev-friendly: auto-add pNNN dirs; later you can pin to an explicit list if you prefer
file(GLOB PROBLEM_DIRS LIST_DIRECTORIES TRUE "p[0-9][0-9][0-9]")
foreach (dir ${PROBLEM_DIRS})
    if (EXISTS "${dir}/CMakeLists.txt")
        add_subdirectory(${dir})
    endif ()
endforeach ()
