#ifndef VARIAD_HVV_FOR_EACH
#define VARIAD_HVV_FOR_EACH

#include "hvv_arg.hpp"
#include "hvv_cat.hpp"
#include "hvv_inc.hpp"


// FOR_EACH applies Fn(idx, fixed_arg, va_arg) for eahc va_arg in __VA_ARGS__.
// `idx` is 0 for the first iteration and for each subsequent iteration step
// up by 1.
//
// Fn refers to two macros, F1 and F0. F1 is used for non-final loop
// iterations, and F0 is used for the final loop iteration. This is useful
// for forming expressions, where F1 generates a portion of an expression with
// some operand, and F0 generates the final term without any operand.

#define HVV_FOR_EACH1(F, fixed_arg, ...) \
    HVV_CAT_2(HVV_FOR_EACH1_ITER, HVV_ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)

// ITER8. Invokes F1.
#define HVV_FOR_EACH1_ITER8(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER8_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER8_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER7(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER7. Invokes F1.
#define HVV_FOR_EACH1_ITER7(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER7_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER7_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER6(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER6. Invokes F1.
#define HVV_FOR_EACH1_ITER6(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER6_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER6_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER5(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER5. Invokes F1.
#define HVV_FOR_EACH1_ITER5(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER5_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER5_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER4(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER4. Invokes F1.
#define HVV_FOR_EACH1_ITER4(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER4_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER4_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER3(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER3. Invokes F1.
#define HVV_FOR_EACH1_ITER3(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER3_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER3_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER2(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER2. Invokes F1.
#define HVV_FOR_EACH1_ITER2(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH1_ITER2_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH1_ITER2_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH1_ITER1(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER1. Invokes F0.
#define HVV_FOR_EACH1_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)


// FOR_EACH applies Fn(idx, fixed_arg, va_arg) for eahc va_arg in __VA_ARGS__.
// `idx` is 0 for the first iteration and for each subsequent iteration step
// up by 1.
//
// Fn refers to two macros, F1 and F0. F1 is used for non-final loop
// iterations, and F0 is used for the final loop iteration. This is useful
// for forming expressions, where F1 generates a portion of an expression with
// some operand, and F0 generates the final term without any operand.

#define HVV_FOR_EACH2(F, fixed_arg, ...) \
    HVV_CAT_2(HVV_FOR_EACH2_ITER, HVV_ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)

// ITER8. Invokes F1.
#define HVV_FOR_EACH2_ITER8(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER8_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER8_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER7(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER7. Invokes F1.
#define HVV_FOR_EACH2_ITER7(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER7_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER7_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER6(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER6. Invokes F1.
#define HVV_FOR_EACH2_ITER6(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER6_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER6_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER5(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER5. Invokes F1.
#define HVV_FOR_EACH2_ITER5(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER5_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER5_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER4(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER4. Invokes F1.
#define HVV_FOR_EACH2_ITER4(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER4_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER4_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER3(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER3. Invokes F1.
#define HVV_FOR_EACH2_ITER3(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER3_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER3_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER2(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER2. Invokes F1.
#define HVV_FOR_EACH2_ITER2(F, idx, fixed_arg, va_arg, ...) \
    HVV_FOR_EACH2_ITER2_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH2_ITER2_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH2_ITER1(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
// ITER1. Invokes F0.
#define HVV_FOR_EACH2_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)

#endif
