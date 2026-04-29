#include "Hook/PowerPC.hpp"
#include "Memory.hpp"
#include "Hook.hpp"
#include <array>
#include <cstdint>

namespace Library::Hook
{
    struct FunctionEntry
    {
        std::array<uint32_t, 4> original;
        std::array<uint32_t, 4> jump;
    };

    void * MakeFunction(std::span<std::byte> inst)
    {
        size_t size = inst.size();
        void * func = GetCodecaveFar(size);
        KernelMemoryCopy(func, inst.data(), size);
        return func;
    }

    void * ReplaceFunction(void * dst, void const * src)
    {
        uint32_t dstAddress = reinterpret_cast<uint32_t>(dst);
        uint32_t srcAddress = reinterpret_cast<uint32_t>(src);

        std::array<uint32_t, 4> original;
        KernelMemoryCopy(original.data(), dst, sizeof(original));

        FunctionEntry entry;
        
        void * codeCave = GetCodecaveFar(sizeof(entry));
        uint32_t jumpTo = dstAddress + sizeof(original);

        entry.original = original;
        entry.jump =
        {
            ASM_LIS(R12, HI_16(jumpTo)),
            ASM_ORI(R12, R12, LO_16(jumpTo)),
            ASM_MTCTR(R12),
            ASM_BCTR
        };
        KernelMemoryCopy(codeCave, &entry, sizeof(entry));

        std::array<uint32_t, 4> hook =
        {
            ASM_LIS(R12, HI_16(srcAddress)),
            ASM_ORI(R12, R12, LO_16(srcAddress)),
            ASM_MTCTR(R12),
            ASM_BCTR
        };
        KernelMemoryCopy(dst, hook.data(), sizeof(hook));

        return codeCave;
    }

    void HookFunction(void * dst, void const * src, uint32_t overwriteCount)
    {
        uint32_t dstAddress = reinterpret_cast<uint32_t>(dst);
        uint32_t srcAddress = reinterpret_cast<uint32_t>(src);

        for(uint32_t i = 0; i < overwriteCount; i++)
        {
            uint32_t write = ASM_NOP;
            KernelMemoryCopy(reinterpret_cast<uint8_t*>(dst) + i * 4, &write, sizeof(write));
        }
        
        uint32_t original;
        KernelMemoryCopy(&original, dst, sizeof(original));

        // Far -> Original
        uint32_t returnAddress = dstAddress + 4;
        if (overwriteCount > 0)
        {
            returnAddress = dstAddress + overwriteCount * 4;
        }
        std::array<uint32_t, 19> hook =
        {
            original,
            ASM_STWU(R1, -0x88, R1),
            ASM_STW(R0, 0x84, R1),
            ASM_MFLR(R0),
            ASM_STW(R0, 0x80, R1),
            ASM_STMW(R3, 0xC, R1),
            
            ASM_LIS(R12, HI_16(srcAddress)),
            ASM_ORI(R12, R12, LO_16(srcAddress)),
            ASM_MTCTR(R12),
            ASM_BCTRL,

            ASM_LIS(R12, HI_16(returnAddress)),
            ASM_ORI(R12, R12, LO_16(returnAddress)),
            ASM_MTCTR(R12),

            ASM_LMW(R3, 0xC, R1),
            ASM_LWZ(R0, 0x80, R1),
            ASM_MTLR(R0),
            ASM_LWZ(R0, 0x84, R1),
            ASM_ADDI(R1, R1, 0x88),

            ASM_BCTR,
        };
        void * codeCaveFar = GetCodecaveFar(sizeof(hook));
        KernelMemoryCopy(codeCaveFar, hook.data(), sizeof(hook));

        // Near -> Far
        uint32_t farAddress = reinterpret_cast<uint32_t>(codeCaveFar);
        std::array<uint32_t, 4> returnHook =
        {
            ASM_LIS(R12, HI_16(farAddress)),
            ASM_ORI(R12, R12, LO_16(farAddress)),
            ASM_MTCTR(R12),
            ASM_BCTR
        };
        void * codeCaveNear = GetCodecaveNear(sizeof(returnHook));
        KernelMemoryCopy(codeCaveNear, returnHook.data(), sizeof(returnHook));

        // Original -> Near
        uint32_t jumpToNear = reinterpret_cast<uint32_t>(codeCaveNear);
        uint32_t patch = ASM_B(jumpToNear - dstAddress);
        KernelMemoryCopy(dst, &patch, sizeof(patch));
    }
}