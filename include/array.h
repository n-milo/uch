#ifndef UCH_ARRAY_H
#define UCH_ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "keywords.h"

#ifdef __cplusplus
extern "C" {
#endif

// Representation of an array in memory.
typedef struct ArrayStructure {
    size_t cap;
    size_t len;
    char data[];
} ArrayStructure;

// Gets the underlying ArrayStructure behind an array pointer (a pointer to ArrayStructure::data)
static inline struct ArrayStructure *array_structure(void *array_pointer) {
    return (struct ArrayStructure *)((char *)array_pointer - offsetof(struct ArrayStructure, data));
}

static inline size_t array_cap_bytes(void *arr) {
    return array_structure(arr)->cap;
}

static inline size_t array_len_bytes(void *arr) {
    return array_structure(arr)->len;
}

static inline void array_clear(void *arr) {
    array_structure(arr)->len = 0;
}

// Creates a new array with an initial capacity of initial_capacity bytes.
nodiscard void *array_create(size_t initial_capacity);

// Creates a new array with an initial capacity of type T with num_Ts capacity.
#define array_new(T, num_Ts) (T*)array_create((num_Ts) * sizeof(T))

// Modifies array such that it can hold n more bytes than its current length.
nodiscard void *array_require(void *array, size_t n);

// Appends the length bytes pointed to by data to the end of array.
nodiscard void *array_append_data(void *array, const void *data, size_t length);

void array_free(void *arr);
void array_print(void *array);

#define array_append(array, var) \
    ((void) sizeof(*(array) = *(var)), /* (typechecking hack) check that *var is assignable to *array */ \
    array_append_data((array), (var), sizeof(*(var))))

#define array_cap(arr) (array_cap_bytes((arr)) / sizeof(*(arr)))
#define array_len(arr) (array_len_bytes((arr)) / sizeof(*(arr)))

#if defined(UCH_ARRAY_IMPLEMENTATION) || defined(UCH_ALL_IMPLEMENTATION)

void *array_create(size_t initial_capacity) {
    struct ArrayStructure *arr = (struct ArrayStructure *) malloc(sizeof(struct ArrayStructure) + initial_capacity);

    if (!arr)
        return NULL;

    arr->cap = initial_capacity;
    arr->len = 0;
    return arr->data;
}

void *array_require(void *arr, size_t num_bytes) {
    if (arr) {
        struct ArrayStructure *s = array_structure(arr);
        if (s->cap - s->len >= num_bytes)
            return arr;

        size_t required = num_bytes - (s->cap - s->len);
        size_t new_cap = s->cap * 2;
        if (new_cap < s->cap + required)
            new_cap = s->cap + required;

        s = (struct ArrayStructure *) realloc(s, sizeof(struct ArrayStructure) + new_cap);
        if (!s)
            return NULL;

        s->cap = new_cap;
        return s->data;
    } else {
        return array_create(num_bytes);
    }
}

void *array_append_data(void *arr, const void *data, size_t length) {
    arr = array_require(arr, length);
    if (!arr)
        return NULL;

    struct ArrayStructure *s = array_structure(arr);
    memcpy(s->data + s->len, data, length);
    s->len += length;
    return s->data;
}

void array_print(void *arr) {
    struct ArrayStructure *s = array_structure(arr);

    printf("%zu %zu [ ", s->cap, s->len);
    for (int i = 0; i < s->len; i++) {
        printf("%02X ", s->data[i]);
    }
    printf("]\n");
}

void array_free(void *arr) {
    if (arr)
        free(array_structure(arr));
}


#endif // UCH_ARRAY_IMPLEMENTATION

#ifdef __cplusplus
} // extern "C"
#endif

#endif //UCH_ARRAY_H
