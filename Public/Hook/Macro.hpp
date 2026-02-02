#define CONSTRUCTOR(addr, ClassName, ...) \
    inline static void (*ClassName##_Constructor)(ClassName *__VA_OPT__(, __VA_ARGS__)) = \
        reinterpret_cast<void(*)(ClassName *__VA_OPT__(, __VA_ARGS__))>(addr); \
    ClassName(__VA_ARGS__);

#define METHOD(addr, ret, name, ClassName, ...) \
    inline static ret (*name##_Function)(ClassName *__VA_OPT__(, __VA_ARGS__)) = \
        reinterpret_cast<ret(*)(ClassName *__VA_OPT__(, __VA_ARGS__))>(addr); \
    ret name(__VA_ARGS__);

#define STATIC_METHOD(addr, ret, name, ...) \
    inline static ret (*name##_Function)(__VA_ARGS__) = \
        reinterpret_cast<ret(*)(__VA_ARGS__)>(addr); \
    static ret name(__VA_ARGS__);

#define METHOD_FORMAT(addr, ret, name, ClassName, ...) \
    inline static ret (*v_##name##_Function)(ClassName *, const char*, va_list __VA_OPT__(, __VA_ARGS__)) = \
        reinterpret_cast<ret(*)(ClassName *, const char*, va_list __VA_OPT__(, __VA_ARGS__))>(addr); \
    ret name(const char* format, ...);

#define POINTER(addr, type, name) inline static type *const &name = *reinterpret_cast<type *const *>(addr);