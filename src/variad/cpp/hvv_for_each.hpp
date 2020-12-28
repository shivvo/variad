#ifndef VARIAD_CPP_HVV_FOR_EACH
#define VARIAD_CPP_HVV_FOR_EACH

#include "hvv_arg.hpp"
#include "hvv_cat.hpp"
#include "hvv_inc.hpp"

// FOR_EACH applies Fn(idx, fixed_arg, va_arg) for each va_arg in __VA_ARGS__.
// idx is 0 for the first iteration and for each subsequent iteration increases
// by 1.

// Fn refers to two macros. F is the prefix of two macros, F_1 and F_0. F_1 is
// used for non-final for loop iterations and F_0 is used by the final
// iteration.
#define HVV_FOR_EACH_1(F, fixed_args, ...) \
    HVV_CAT_2(HVV_FOR_EACH_1_ITER, HVV_ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)

// ITER8. Invokes F_1
#define HVV_FOR_EACH_1_ITER8(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER8_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER8_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER7(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER7. Invokes F_1
#define HVV_FOR_EACH_1_ITER7(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER7_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER7_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER6(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER6. Invokes F_1
#define HVV_FOR_EACH_1_ITER6(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER6_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER6_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER5(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER5. Invokes F_1
#define HVV_FOR_EACH_1_ITER5(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER5_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER5_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER4(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER4. Invokes F_1
#define HVV_FOR_EACH_1_ITER4(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER4_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER4_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER3(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER3. Invokes F_1
#define HVV_FOR_EACH_1_ITER3(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER3_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER3_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER2(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER2. Invokes F_1
#define HVV_FOR_EACH_1_ITER2(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_1_ITER2_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER2_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER1(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER1. Invokes F_0.
#define HVV_FOR_EACH_1_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)

// FOR_EACH applies Fn(idx, fixed_arg, va_arg) for each va_arg in __VA_ARGS__.
// idx is 0 for the first iteration and for each subsequent iteration increases
// by 1.

// Fn refers to two macros. F is the prefix of two macros, F_1 and F_0. F_1 is
// used for non-final for loop iterations and F_0 is used by the final
// iteration.
#define HVV_FOR_EACH_2(F, fixed_args, ...) \
    HVV_CAT_2(HVV_FOR_EACH_2_ITER, HVV_ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)

// ITER8. Invokes F_1
#define HVV_FOR_EACH_2_ITER8(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER8_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER8_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER7(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER7. Invokes F_1
#define HVV_FOR_EACH_2_ITER7(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER7_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER7_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER6(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER6. Invokes F_1
#define HVV_FOR_EACH_2_ITER6(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER6_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER6_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER5(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER5. Invokes F_1
#define HVV_FOR_EACH_2_ITER5(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER5_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER5_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER4(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER4. Invokes F_1
#define HVV_FOR_EACH_2_ITER4(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER4_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER4_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER3(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER3. Invokes F_1
#define HVV_FOR_EACH_2_ITER3(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER3_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER3_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER2(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER2. Invokes F_1
#define HVV_FOR_EACH_2_ITER2(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH_2_ITER2_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER2_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER1(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER1. Invokes F_0.
#define HVV_FOR_EACH_2_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)

#endif

