#ifndef VARIAD_CPP_ARG
#define VARIAD_CPP_ARG

#define ARG_9TH(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define ARG_LENGTH(...) ARG_9TH(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)

#endif
