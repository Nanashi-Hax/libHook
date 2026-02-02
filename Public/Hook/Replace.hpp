#pragma once

#define DEFINE_FUNCTION(ret, name, ...) \
    ret (*trampoline_##name)(__VA_ARGS__); \
    ret hook_##name(__VA_ARGS__)

#define REPLACE_FUNCTION(originalFunction, hookFunction, trampolineFunction) \
trampolineFunction = reinterpret_cast<decltype(trampolineFunction)>(Library::Hook::ReplaceFunction(reinterpret_cast<void*>(originalFunction), reinterpret_cast<void const *>(hookFunction)));