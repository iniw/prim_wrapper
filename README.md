# prim_wrapper
 lightweight, compile-time and rust-like wrapper around the primitive numerical c++ data types

# dependencies
 [gcem](https://github.com/kthohr/gcem) - provides math functions at compile-time  
 *optional* [benchmark](https://github.com/google/benchmark) - required only if you want to run the benchmarks
 *optional* [Catch2](https://github.com/catchorg/Catch2) - required only if you want to run the automated tests


# why?
 the point is to make writing and interfacing with numerical types more preditable and intuitive;
 you want to know the size of a type? `type::BYTES or `type::BITS`; invert it's endianess? `foo.byte_swap()`; get it's contents as a string? `foo.str()`; or maybe build a it from a string: `type::from_str()`.

# usage
 include `prim_wrapper.hpp` in your project and use the type aliases:
 - i/u8 -> std::i/uin8_t
 - i/u16 -> std::i/uint16_t
 - i/u32 -> std::i/uint32_t
 - i/u64 -> std::i/uint64_t
 - f32 -> float
 - f64 -> double

 note that although implicitly casting from a prim_wrapper object to it's primitive counterpart is not allowed - to avoid ambiguity - implicitly casting between prim_wrapper types is supported.

# features
 - compile-time static members
    - MIN, MAX: minimum and maximum value
    - EPSILON: epsilon value
    - RADIX: radix value
    - BYTES: the type's size, in bytes
    - BITS: the type's size, in bits
- static functions (T = primitive value, PW = prim_wrapper value)
    - **std::string to_str(T)**: converts primitive value to a string
    - **PW from_str(std::string)**: builds a PW from a string
    - **PW::byte_set to_bytes(PW)** - *integrals only*: converts the value's byte structure to a PW::byte_set (std::array)
    - **PW from_bytes(PW::byte_set)** - *integrals only*: builds a PW value from a PW::byte_set (std::array) 