#ifndef UCH_$NAME_H
#define UCH_$NAME_H

#include <math.h>

typedef union $NAME {
    struct { $T $COMPONENTS; };
    $T values[$N];
} $NAME;

typedef $NAME $NAME_t;

#define $NAME($COMPONENTS) (($NAME){{ $COMPONENTS }})

static inline $NAME $NAME_from_array(const $T *arr) {
    $NAME ret;
    for (int i = 0; i < $N; i++)
        ret.values[i] = arr[i];
    return ret;
}

static inline bool $NAME_eq($NAME a, $NAME b) {
    for (int i = 0; i < $N; i++)
        if (a.values[i] != b.values[i])
            return false;
    return true;
}

static inline bool $NAME_eq_within($NAME a, $NAME b, double epsilon) {
    for (int i = 0; i < $N; i++)
        if (fabs((double) (a.values[i] - b.values[i])) > epsilon)
            return false;
    return true;
}

static inline $NAME $NAME_zero() {
    return ($NAME) {};
}

static inline $NAME $NAME_add($NAME a, $NAME b) {
    for (int i = 0; i < $N; i++)
        a.values[i] += b.values[i];
    return a;
}

static inline $NAME $NAME_sub($NAME a, $NAME b) {
    for (int i = 0; i < $N; i++)
        a.values[i] -= b.values[i];
    return a;
}

static inline $T $NAME_dot($NAME a, $NAME b) {
    $T ret = 0;
    for (int i = 0; i < $N; i++)
        ret += a.values[i] * b.values[i];
    return ret;
}

static inline $NAME $NAME_scale($NAME a, $T b) {
    for (int i = 0; i < $N; i++)
        a.values[i] *= b;
    return a;
}

static inline $T $NAME_len2($NAME v) {
    return $NAME_dot(v, v);
}

static inline double $NAME_len($NAME v) {
    return sqrt((double) $NAME_len2(v));
}

static inline float $NAME_lenf($NAME v) {
    return sqrtf((float) $NAME_len2(v));
}

static inline $NAME $NAME_normalize($NAME v) {
    double invlen = 1.0 / $NAME_len(v);
    for (int i = 0; i < $N; i++)
        v.values[i] = ($T) ((double)v.values[i] * invlen);
    return v;
}

static inline $NAME $NAME_lerp($NAME a, $NAME b, float t) {
    return $NAME_add($NAME_scale(a, 1 - t), $NAME_scale(b, t));
}

static inline $NAME $NAME_negate($NAME v) {
    for (int i = 0; i < $N; i++)
        v.values[i] = -v.values[i];
    return v;
}

#if $N == 3

static inline $NAME $NAME_cross($NAME a, $NAME b) {
    $NAME res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

#endif

#endif

#endif //UCH_VEC_H
