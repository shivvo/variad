#ifndef VARIAD_HVV_ARG
#define VARIAD_HVV_ARG

#define HVV_ARG_9TH(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N

#define HVV_ARG_LENGTH(...) HVV_ARG_9TH(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)

#define HVV_ARG_2ND_IMPL(a, b, ...) b
#define HVV_ARG_2ND(...) ARG_2ND_IMPL(__VA_ARGS__)

#define HVV_ARG_CAT_1(a, b) a##b
#define HVV_ARG_CAT_2(a, b) HVV_ARG_CAT_1(a, b)

#define HVV_ARG_LENGTH_PROBE_1 _, 1
#define HVV_ARG_IS_SINGLE(...) \
    HVV_ARG_2ND(HVV_ARG_CAT_2(HVV_ARG_LENGTH_PROBE_, HVV_ARG_LENGTH(__VA_ARGS__)), 0)

#define HVV_ARG_IDENTITY(...) __VA_ARGS__
#define HVV_ARG_IS_SINGULAR(a) HVV_ARG_IS_SINGLE(HVV_ARG_IDENTITY a)

#endif
