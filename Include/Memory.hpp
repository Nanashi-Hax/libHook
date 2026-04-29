#pragma once

#include <cstddef>
#include <cstdint>

namespace Library::Hook
{
    void * GetCodecaveFar(size_t size); // ジャンプ先の距離がb命令の範囲内になることは保証されない
    void * GetCodecaveNear(size_t size); // ジャンプ先の距離がb命令の範囲内になることが保証される
}