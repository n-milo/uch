#define UCH_ALL_IMPLEMENTATION
#include "array.h"
#include "math/vec3.h"

#include <catch2/catch_all.hpp>

TEST_CASE("Arrays work", "[array]") {
    int *arr = (int *)array_require(nullptr, 5 * sizeof(int));
    REQUIRE(array_len(arr) == 0);
    REQUIRE(array_cap(arr) == 5);

    int six = 6;
    arr = (int *)array_append_data(arr, &six, sizeof six);
    REQUIRE(array_len(arr) == 1);
    REQUIRE(array_cap(arr) == 5);
    REQUIRE(arr[0] == 6);

    for (int i = 0; i < 4; i++) {
        arr = (int *)array_append(arr, &i);
    }
    REQUIRE(array_len(arr) == 5);
    REQUIRE(array_cap(arr) == 5);
    REQUIRE(memcmp(arr, (int[]){6,0,1,2,3}, 5 * sizeof(int)) == 0);

    int seven = 7;
    arr = (int *)array_append(arr, &seven);
    REQUIRE(array_len(arr) == 6);
    REQUIRE(array_cap(arr) > 5);
    REQUIRE(arr[5] == 7);

    arr = (int *)array_require(arr, 100000);
    REQUIRE(array_len(arr) == 6);
    REQUIRE(array_cap_bytes(arr) == 100000 + array_len(arr) * sizeof(int));

    array_print(arr);
    array_free(arr);
}

TEST_CASE("vector tests", "[math]") {
    vec3 a = vec3(0, 3, 4);
    vec3 b = vec3(1, 2, 3);
    REQUIRE(vec3_len(a) == 5);

    vec3 v = vec3_add(a, b);
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 5);
    REQUIRE(v.z == 7);
}