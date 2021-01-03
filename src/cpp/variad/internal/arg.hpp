#ifndef VARIAD_CPP_ARG
#define VARIAD_CPP_ARG

#define ARG_9TH(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N

#define ARG_LENGTH(...) ARG_9TH(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)

#define ARG_2ND_IMPL(a, b, ...) b
#define ARG_2ND(...) ARG_2ND_IMPL(__VA_ARGS__)

#define ARG_CAT_1(a, b) a##b
#define ARG_CAT_2(a, b) ARG_CAT_1(a, b)

#define ARG_LENGTH_PROBE_1 _, 1
#define ARG_IS_SINGLE(...) \
    ARG_2ND(ARG_CAT_2(ARG_LENGTH_PROBE_, ARG_LENGTH(__VA_ARGS__)), 0)

#define ARG_IDENTITY(...) __VA_ARGS__
#define ARG_IS_SINGULAR(a) ARG_IS_SINGLE(ARG_IDENTITY a)

#endif
