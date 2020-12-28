#ifndef VARIAD_CPP_HVV_FOR_EACH
#define VARIAD_CPP_HVV_FOR_EACH

#include "hvv_arg.hpp"
#include "hvv_cat.hpp"
#include "hvv_defer.hpp"
#include "hvv_inc.hpp"

#define HVV_FOR_EACH_1(F, fixed_args, ...) \
    HVV_CAT_2(HVV_FOR_EACH_1_ITER, HVV_ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)

#define HVV_FOR_EACH_1_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)
#define HVV_FOR_EACH_1_ITER2(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER2_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER2_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER1(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER3(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER3_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER3_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER2(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER4(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER4_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER4_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER3(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER5(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER5_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER5_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER4(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER6(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER6_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER6_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER5(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER7(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER7_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER7_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER6(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER8(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_1_ITER8_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_1_ITER8_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_1_ITER7(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)

#define HVV_FOR_EACH_2(F, fixed_args, ...) \
    HVV_CAT_2(HVV_FOR_EACH_2_ITER, HVV_ARG_LENGTH(__VA_ARGS__))(F, 0, fixed_arg, __VA_ARGS__)

#define HVV_FOR_EACH_2_ITER1(F, idx, fixed_arg, va_arg, ...) F##0(idx, fixed_arg, va_arg)
#define HVV_FOR_EACH_2_ITER2(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER2_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER2_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER1(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER3(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER3_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER3_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER2(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER4(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER4_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER4_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER3(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER5(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER5_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER5_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER4(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER6(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER6_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER6_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER5(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER7(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER7_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER7_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER6(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER8(F, idx, fixed_arg, va_arg, ...) HVV_FOR_EACH_2_ITER8_IMPL(F, idx, fixed_arg, va_arg, __VA_ARGS__)
#define HVV_FOR_EACH_2_ITER8_IMPL(F, idx, fixed_arg, va_arg, ...) \
    F##1(idx, fixed_arg, va_arg) HVV_FOR_EACH_2_ITER7(F, HVV_CAT_1(HVV_INC_, idx), fixed_arg, __VA_ARGS__)

#endif

