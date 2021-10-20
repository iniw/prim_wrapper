# prim_wrapper
 lightweight, compile-time and rust-like wrapper around the primitive numerical c++ data types

# dependencies
 [gcem](https://github.com/kthohr/gcem) - mathematical operations at compile-time  
 *optional* [fmt](https://github.com/fmtlib/fmt/) - integrates with fmt's formatter to make logging prim_wrapper types behave the same as their primitive counterpart

# why?
 the point is to make writing and interfacing with numerical types more preditable and intuitive;
 you want to know the size of a type? `type::BYTES` or `type::BITS`; invert it's endianess? `foo.byte_swap()`; get it's contents as a string? `foo.str()`; or maybe build a it from a string: `type::from_str()`.

# features
 ###### compile-time static members
    - MIN, MAX: minimum and maximum value
    - EPSILON: epsilon value
    - RADIX: radix value
    - BYTES: the type's size, in bytes
    - BITS: the type's size, in bits
###### static functions (T = primitive value, PW = prim_wrapper value)
    - **to_str(T)**: converts value of the specified type to a string
    - **from_str(str)**: builds a PW from a string
    - **_integral only_ to_bytes(PW)**: converts the value's byte structure to a PW::byte_set (std::array)
    - **_integral only_ from_bytes(PW::byte_set)**: builds a PW value from a PW::byte_set (std::array)