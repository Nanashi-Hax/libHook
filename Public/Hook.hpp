#pragma once

#include <Hook/Declare.hpp>
#include <Hook/PowerPC.hpp>
#include <Hook/Replace.hpp>
#include <cstddef>
#include <cstdint>
#include <span>

namespace Library::Hook
{
    void KernelMemoryCopy(void * dst, void const * src, size_t size);
    void KernelMemorySet(void * dst, uint8_t byte, size_t size);
    void * ReplaceFunction(void * dst, void const * src);
    void HookFunction(void * dst, void const * src, uint32_t overwriteCount = 0);
    void * MakeFunction(std::span<std::byte> inst);
}