#include "Memory.hpp"
#include <cstdint>
#include <cstring>
#include <vector>
#include <coreinit/memorymap.h>
#include <kernel/kernel.h>
#include <coreinit/cache.h>

namespace Library::Hook
{
    unsigned int ReadUInt32(unsigned int address)
    {
        if(OSIsAddressValid(address))
        {
            return *(unsigned int*)address;
        }
        return 0;
    }

    void KernelMemoryCopy(void * dst, void const * src, size_t size)
    {
        uint32_t dstStartAddress = reinterpret_cast<uint32_t>(dst);
        uint32_t dstEndAddress = reinterpret_cast<uint32_t>(dst) + size;
        uint32_t srcStartAddress = reinterpret_cast<uint32_t>(src);
        uint32_t srcEndAddress = reinterpret_cast<uint32_t>(src) + size;
        if(OSIsAddressValid(dstStartAddress) && OSIsAddressValid(dstEndAddress) && OSIsAddressValid(srcStartAddress) && OSIsAddressValid(srcEndAddress))
        {
            uint32_t destPhysicalAddress = OSEffectiveToPhysical(dstStartAddress);
            uint32_t srcPhysicalAddress = OSEffectiveToPhysical(srcStartAddress);
        
            KernelCopyData(destPhysicalAddress, srcPhysicalAddress, size);
            DCFlushRange(dst, size);
            ICInvalidateRange(dst, size);
        }
    }

    void KernelMemorySet(void * dst, uint8_t byte, size_t size)
    {
        std::vector<std::byte> buffer(size);
        std::memset(buffer.data(), byte, size);
        KernelMemoryCopy(dst, buffer.data(), size);
    }

    void * GetCodecave(size_t size)
    {
        static uint32_t currentAddress = 0x10000000;
        currentAddress -= size;
        KernelMemorySet(reinterpret_cast<void*>(currentAddress), 0, size);
        return reinterpret_cast<void *>(currentAddress);
    }
}