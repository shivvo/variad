#ifndef VARIAD_CPP_CAT
#define VARIAD_CPP_CAT

#define CAT_1(a, b) a##b
#define CAT_2(a, b) CAT_1(a, b)
#define CAT_3(a, b) CAT_2(a, b)
#define CAT_4(a, b) CAT_3(a, b)
#define CAT_5(a, b) CAT_4(a, b)
#define CAT_6(a, b) CAT_5(a, b)
#define CAT_7(a, b) CAT_6(a, b)
#define CAT_8(a, b) CAT_7(a, b)

#endif
