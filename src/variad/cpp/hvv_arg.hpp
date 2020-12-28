#ifndef VARIAD_CPP_HVV_ARG
#define VARIAD_CPP_HVV_ARG

#define HVV_ARG_9(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define HVV_ARG_LENGTH(...) HVV_ARG_9(__VA__ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)

#endif

