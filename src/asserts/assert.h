#pragma once

#include "../utils/utils.h"

#ifdef ASSERTS_ON
#define kernel_assert(arg, msg)                                                                      \
if (!(arg)) {                                                                                        \
  kernel_panic("kernel panic!\nmessage: %s\nin file: %s\nin line: %d\n", (msg), __FILE__, __LINE__); \
}
#else
#define kernel_assert(arg, msg)
#endif
