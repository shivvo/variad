#ifndef VARIAD_CPP_HVV_CAT
#define VARIAD_CPP_HVV_CAT

#define HVV_CAT_1(a, b) a##b
#define HVV_CAT_2(a, b) HVV_CAT_1(a, b)
#define HVV_CAT_3(a, b) HVV_CAT_2(a, b)
#define HVV_CAT_4(a, b) HVV_CAT_3(a, b)
#define HVV_CAT_5(a, b) HVV_CAT_4(a, b)
#define HVV_CAT_6(a, b) HVV_CAT_5(a, b)
#define HVV_CAT_7(a, b) HVV_CAT_6(a, b)
#define HVV_CAT_8(a, b) HVV_CAT_7(a, b)

#endif

