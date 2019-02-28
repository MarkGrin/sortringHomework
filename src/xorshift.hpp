#pragma once

#include <cstdint>

namespace xorshift {

uint32_t generate(uint32_t& state, uint32_t range);

} // xorshift
