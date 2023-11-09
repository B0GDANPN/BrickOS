#pragma once

#include "../utils/utils.h"

#define kernel_assert(arg, msg)                                                                      \
if (!(arg)) {                                                                                        \
  kernel_panic("kernel panic!\nmessage: %s\nin file: %s\nin line: %d\n", (msg), __FILE__, __LINE__); \
}
