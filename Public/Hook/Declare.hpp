#pragma once

#define CONSTRUCTOR(addr, ClassName, ...) \
    inline static void (*original_##name)(ClassName *__VA_OPT__(, __VA_ARGS__)) = \
        reinterpret_cast<void(*)(ClassName *__VA_OPT__(, __VA_ARGS__))>(addr); \
    ClassName(__VA_ARGS__);

#define METHOD(addr, ret, name, ClassName, ...) \
    inline static ret (*original_##name)(ClassName *__VA_OPT__(, __VA_ARGS__)) = \
        reinterpret_cast<ret(*)(ClassName *__VA_OPT__(, __VA_ARGS__))>(addr); \
    ret name(__VA_ARGS__);

#define STATIC_METHOD(addr, ret, name, ...) \
    inline static ret (*original_##name)(__VA_ARGS__) = \
        reinterpret_cast<ret(*)(__VA_ARGS__)>(addr); \
    static ret name(__VA_ARGS__);

#define METHOD_FORMAT(addr, ret, name, ClassName, ...) \
    inline static ret (*original_##name)(ClassName *, const char*, va_list __VA_OPT__(, __VA_ARGS__)) = \
        reinterpret_cast<ret(*)(ClassName *, const char*, va_list __VA_OPT__(, __VA_ARGS__))>(addr); \
    ret name(const char* format, ...);

#define POINTER(addr, type, name) inline static type *const &name = *reinterpret_cast<type *const *>(addr);