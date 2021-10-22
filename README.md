# prim_wrapper
 header-only, fast, compile-time, rust-like wrapper around the primitive numerical c++ data types

# dependencies
 [gcem](https://github.com/kthohr/gcem) - provides math functions at compile-time  
 *optional* [benchmark](https://github.com/google/benchmark) - required only if you want to run the benchmarks  
 *optional* [Catch2](https://github.com/catchorg/Catch2) - required only if you want to run the automated tests


# why?
 the point is to make writing and interfacing with numerical types more preditable and intuitive;  
 you want to know the size of a type? `type::BYTES` or `type::BITS`; invert it's endianess? `foo.byte_swap()`; get it's contents as a string? `foo.str()`; or maybe build a it from a string: `type::from_str()`.

# usage
 include `prim_wrapper.hpp` in your project and use the type aliases:
 - i/u8 -> prim_wrapper\<i/uin8_t>
 - i/u16 -> prim_wrapper\<i/uint16_t>
 - i/u32 -> prim_wrapper\<i/uint32_t>
 - i/u64 -> prim_wrapper\<i/uint64_t>
 - f32 -> float_wrapper\<float>
 - f64 -> float_wrapper\<double>

 note: although implicitly casting from a prim_wrapper object to it's primitive counterpart is not allowed - to avoid ambiguity - implicitly casting between prim_wrapper types is supported.

# features  
    T = primitive, PW = prim_wrapper<T>, PW::byte_set = std::array<uint8_t, PW::BYTES>

 - compile-time static members
    - MIN, MAX: minimum and maximum value
    - EPSILON: epsilon value
    - RADIX: radix value
    - BYTES: the type's size, in bytes
    - BITS: the type's size, in bits
- static functions
    - **std::string to_str(T)**: converts primitive value to a string
    - **PW from_str(std::string)**: builds a PW from a string
    - **PW::byte_set to_bytes(PW)** - *integrals only*: converts the value's byte structure to a PW::byte_set
    - **PW from_bytes(PW::byte_set)** - *integrals only*: builds a PW value from a PW::byte_set
- many more member functions ;)
