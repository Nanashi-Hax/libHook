#pragma once

#include <Hook/Declare.hpp>
#include <Hook/PowerPC.hpp>
#include <Hook/Replace.hpp>
#include <cstddef>
#include <cstdint>

namespace Library::Hook
{
    void KernelMemoryCopy(void * dst, void const * src, size_t size);
    void KernelMemorySet(void * dst, uint8_t byte, size_t size);
    void * ReplaceFunction(void * dst, void const * src);
}