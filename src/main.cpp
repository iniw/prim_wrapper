#include "prim_wrapper.hpp"

// should probably write some real test cases huh
int main()
{
    constexpr u32 from_bytes = u32::from_bytes({0x32, 0x33, 0x12, 0x32});
    static_assert(from_bytes == 0x32331232);

    constexpr u32::byte_set bytes = from_bytes.bytes();
    static_assert(bytes == u32::byte_set{0x32, 0x33, 0x12, 0x32});

    constexpr f32 inf = f32::INF;
    static_assert(inf.is_inf());

    constexpr f32 nan = f32::NaN;
    static_assert(nan.is_nan());

    constexpr u32 opr_test = from_bytes * 5;
    static_assert(opr_test == from_bytes.get() * 5);

    constexpr u32 test = u32::from_bytes({0x17, 0x27, 0x37, 0x47});
    constexpr u32 test2 = test.byte_swap();

    u32 test64 = 15;
    u32 test32_1 = 15 * 2;
    u32 test32_3 = test32_1 * 2;
    test32_1 *= 2;
    u32 test32_2 = test64 + test32_1;


    u32 pre_rotate = 0x10101010;
    u32 rotate = pre_rotate.rotate_left(1);

    fmt::print("0x{:x}\n", pre_rotate);
    fmt::print("0x{:x}\n", rotate);

    return 0;
}   