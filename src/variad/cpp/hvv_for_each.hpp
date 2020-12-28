#ifndef VARIAD_HVV_FOR_EACH
#define VARIAD_HVV_FOR_EACH

#define HVV_FOR_EACH_I0(F, fixed_args, var_args) F ## 0 (fixed_args, var_args)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I2(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I1(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I3(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I2(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)
#define HVV_FOR_EACH_I1(F, fixed_args, var_args, ...) F ## 1 (fixed_args, var_args) HVV_FOR_EACH_I0(F, fixed_args, __VA_ARGS__)

#endif
