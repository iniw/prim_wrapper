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
 - f32 -> prim_wrapper\<float>
 - f64 -> prim_wrapper\<double>

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

# known issues
 take the following code:  
 ```
 std::int32_t a = 15;
 std::int64_t b = 15;  
 std::uint32_t c = a + b;
 ```
 the order of events is:  
 1. `a` gets constructed with 15
 2. `b` gets constructed via an implicit cast where 15 is promoted to a 64bit integer
 3. `a` gets promoted to a 64bit integer and `a + b` is evaluated as a 64 bit integer
 4. the expression is implicitly casted to a 32bit unsigned and stored in c  

 now take the following code:
```
 i32 a = 15;
 i64 b = 15;  
 u32 c = a + b;
 ```
 the order of events is: 
 1. same as the previous snippet
 2. same as the previous snippet
 3. `b` gets implicitly downgraded to a 32 bit integer and the expression is evaluated as a 32 bit integer
 4. same as the previous snippet

 i'm planning to solve that soon.
