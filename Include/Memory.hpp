#pragma once

#include <cstddef>
#include <cstdint>

namespace Library::Hook
{
    void KernelMemoryCopy(void * dst, void const * src, size_t size);
    void KernelMemorySet(void * dst, uint8_t byte, size_t size);
    void * GetCodecave(size_t size);
}