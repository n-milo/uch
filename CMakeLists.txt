cmake_minimum_required(VERSION 3.21)
project(uch)

set(CMAKE_CXX_STANDARD 14)

function(DEFINE_VECTOR NAME T N COMPONENTS)
    add_custom_command(
            OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/include/math/${NAME}.h
            COMMAND sed
            -e 's/$$NAME/${NAME}/g'
            -e 's/$$N/${N}/g'
            -e 's/$$COMPONENTS/${COMPONENTS}/g'
            -e 's/$$T/${T}/g'
            ${CMAKE_CURRENT_SOURCE_DIR}/include/math/vec.h
            > ${CMAKE_CURRENT_SOURCE_DIR}/include/math/${NAME}.h
            DEPENDS include/math/vec.h
    )
endfunction()

define_vector(vec2 float 2 x,y)
define_vector(vec3 float 3 x,y,z)
define_vector(vec4 float 4 x,y,z,w)
define_vector(ivec2 int 2 x,y)
define_vector(ivec3 int 3 x,y,z)
define_vector(ivec4 int 4 x,y,z,w)
define_vector(dvec2 double 2 x,y)
define_vector(dvec3 double 3 x,y,z)
define_vector(dvec4 double 4 x,y,z,w)

find_package(Catch2 3 REQUIRED)

add_executable(uch
        main.cpp
        include/xmalloc.h
        include/math/vec.h

        include/math/vec2.h
        include/math/vec3.h
        include/math/vec4.h
        include/math/ivec2.h
        include/math/ivec3.h
        include/math/ivec4.h
        include/math/dvec2.h
        include/math/dvec3.h
        include/math/dvec4.h

        )
target_include_directories(uch PUBLIC include)
target_link_libraries(uch PRIVATE Catch2::Catch2WithMain)
