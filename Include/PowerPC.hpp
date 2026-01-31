#pragma once

#define HI_16(x) (x >> 16) & 0xFFFF
#define HA_16(x) (x + 0x8000) >> 16
#define LO_16(x) x & 0xFFFF

#define ASM_NOP               0x60000000

#define ASM_LI(rD, IMM)       (0x38000000 | ((rD & 0x1F) << 21) | ((IMM) & 0xFFFF))
#define ASM_LIS(rD, IMM)      (0x3C000000 | ((rD & 0x1F) << 21) | ((IMM) & 0xFFFF))

#define ASM_ADDI(rD, rA, IMM) (0x38000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((IMM) & 0xFFFF))
#define ASM_ADDIS(rD, rA, IMM)(0x3C000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((IMM) & 0xFFFF))
#define ASM_ADD(rD, rA, rB)   (0x7C000214 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((rB & 0x1F) << 11))
#define ASM_SUBF(rD, rA, rB)  (0x7C000050 | ((rD & 0x1F) << 21) | ((rB & 0x1F) << 16) | ((rA & 0x1F) << 11))

#define ASM_ORI(rS, rA, IMM)  (0x60000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((IMM) & 0xFFFF))
#define ASM_ANDI(rS, rA, IMM) (0x70000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((IMM) & 0xFFFF))
#define ASM_XORI(rS, rA, IMM) (0x68000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((IMM) & 0xFFFF))
#define ASM_OR(rS, rA, rB)    (0x7C000378 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((rB & 0x1F) << 11))
#define ASM_AND(rS, rA, rB)   (0x7C000038 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((rB & 0x1F) << 11))
#define ASM_XOR(rS, rA, rB)   (0x7C000278 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((rB & 0x1F) << 11))

#define ASM_CMP(rA, rB)       (0x7C000000 | ((rA & 0x1F) << 16) | ((rB & 0x1F) << 11))
#define ASM_CMPWI(rA, IMM)    (0x2C000000 | ((rA & 0x1F) << 16) | ((IMM) & 0xFFFF))

#define ASM_B(offset)         (0x48000000 | ((offset) & 0x03FFFFFC))
#define ASM_BC(bo, bi, offset)(0x40000000 | ((bo & 0x1F) << 21) | ((bi & 0x1F) << 16) | ((offset) & 0xFFFC))
#define ASM_BLR               0x4E800020
#define ASM_BLRL              0x4E800021
#define ASM_BCTR              0x4E800420
#define ASM_BCTRL             0x4E800421

#define ASM_LWZ(rD, d, rA)    (0x80000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))
#define ASM_STW(rS, d, rA)    (0x90000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))

#define ASM_LHZ(rD, d, rA)    (0xA0000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))
#define ASM_STH(rS, d, rA)    (0xB0000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))

#define ASM_LBZ(rD, d, rA)    (0x88000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))
#define ASM_STB(rS, d, rA)    (0x98000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))

#define ASM_LMW(rD, d, rA)    (0xB8000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))
#define ASM_STMW(rS, d, rA)    (0xBC000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))

#define ASM_LWZU(rD, d, rA)    (0x84000000 | ((rD & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))
#define ASM_STWU(rS, d, rA)    (0x94000000 | ((rS & 0x1F) << 21) | ((rA & 0x1F) << 16) | ((d) & 0xFFFF))

#define ASM_MR(rD, rS)        ASM_OR(rD, rS, rS)
#define ASM_MFLR(rS)          (0x7C0802A6 | (rS & 0x1F) << 21)
#define ASM_MTLR(rS)          (0x7C0803A6 | (rS & 0x1F) << 21)
#define ASM_MFCTR(rS)         (0x7C0902A6 | (rS & 0x1F) << 21)
#define ASM_MTCTR(rS)         (0x7C0903A6 | (rS & 0x1F) << 21)

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15
#define R16 16
#define R17 17
#define R18 18
#define R19 19
#define R20 20
#define R21 21
#define R22 22
#define R23 23
#define R24 24
#define R25 25
#define R26 26
#define R27 27
#define R28 28
#define R29 29
#define R30 30
#define R31 31