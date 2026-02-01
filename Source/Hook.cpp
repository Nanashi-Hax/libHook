#include "PowerPC.hpp"
#include "Memory.hpp"
#include <array>
#include <cstdint>

namespace Library::Hook
{
    struct FunctionEntry
    {
        std::array<uint32_t, 4> original;
        std::array<uint32_t, 4> jump;
    };

    void * ReplaceFunction(void * dst, void const * src)
    {
        uint32_t dstAddress = reinterpret_cast<uint32_t>(dst);
        uint32_t srcAddress = reinterpret_cast<uint32_t>(src);

        std::array<uint32_t, 4> original;
        KernelMemoryCopy(original.data(), dst, sizeof(original));

        FunctionEntry entry;
        
        void * codeCave = GetCodecave(sizeof(entry));
        uint32_t jumpTo = dstAddress + sizeof(original);

        entry.original = original;
        entry.jump =
        {
            ASM_LIS(R12, HA_16(jumpTo)),
            ASM_ORI(R12, R12, LO_16(jumpTo)),
            ASM_MTCTR(R12),
            ASM_BCTR
        };
        KernelMemoryCopy(codeCave, &entry, sizeof(entry));

        std::array<uint32_t, 4> hook =
        {
            ASM_LIS(R12, HA_16(srcAddress)),
            ASM_ORI(R12, R12, LO_16(srcAddress)),
            ASM_MTCTR(R12),
            ASM_BCTR
        };
        KernelMemoryCopy(dst, hook.data(), sizeof(hook));

        return codeCave;
    }
}