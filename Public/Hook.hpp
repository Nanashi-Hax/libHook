#pragma once

#include <Hook/Declare.hpp>
#include <Hook/PowerPC.hpp>
#include <Hook/Replace.hpp>

namespace Library::Hook
{
    void * ReplaceFunction(void * dst, void const * src);
}