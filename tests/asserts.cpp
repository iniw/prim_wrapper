#if defined(TESTS_ASSERTS) && !defined(TESTS_BENCHMARK)

#include "prim_wrapper.hpp"

#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>

TEST_CASE("f32 construction", "[f32]") {
    REQUIRE(f32().get() == 0.f);
    REQUIRE(f32(5.f).get() == 5.f);
    REQUIRE(f32(f32(10.f)).get() == 10.f);
}

TEST_CASE("f32 comparison", "[f32]") {
    REQUIRE(f32() == 0.f);
    REQUIRE(f32(5.f) == 5.f);
    REQUIRE(f32(f32(10.f)) == 10.f);

    REQUIRE(f32(1.f) > 0.f);
    REQUIRE(f32(1.f) >= 1.f);

    REQUIRE(f32(1.f) < 2.f);
    REQUIRE(f32(1.f) <= 1.f);

    REQUIRE(f32(1.f) != 0.f);
}

TEST_CASE("f32 operators", "[f32]") {
    f32 test = 5.f;
    REQUIRE(test == 5.f);

    test = test;
    REQUIRE(test == 5.f);

    test = 0.f;

    REQUIRE((test + 5.f) == 5.f);
    REQUIRE((test + test) == 0.f);
    REQUIRE((test += 5.f) == 5.f);
    REQUIRE((test += test) == 10.f);

    REQUIRE((test - 5.f) == 5.f);
    REQUIRE((test - test) == 0.f);
    REQUIRE((test -= 5.f) == 5.f);
    REQUIRE((test -= test) == 0.f);

    test = 1.f;

    REQUIRE((test * 5.f) == 5.f);
    REQUIRE((test * test) == 1.f);
    REQUIRE((test *= 5.f) == 5.f);
    REQUIRE((test *= test) == 25.f);

    REQUIRE((test / 5.f) == 5.f);
    REQUIRE((test / test) == 1.f);
    REQUIRE((test /= 5.f) == 5.f);
    REQUIRE((test /= test) == 1.f);

    REQUIRE(test);

    REQUIRE(-test == -1.f);
    REQUIRE(+test == 1.f);
    REQUIRE(++test == 2.f);
    REQUIRE(test++ == 2.f);
    REQUIRE(test-- == 3.f);
    REQUIRE(--test == 1.f);

    i32 a = 15;
    u64 d = a;
    //u64 b = 5;
    auto c = d / 5;

    test = 0.f;

    REQUIRE(!test);
}

TEST_CASE("f32 construction from string", "[f32]") {
    REQUIRE(f32::from_str("0.f") == 0.f);
    REQUIRE(f32::from_str("5.f") == 5.f);
    REQUIRE(f32::from_str("10.fabc") == 10.f);
    REQUIRE(f32::from_str("abc10.f") == 0.f);
    REQUIRE(f32::from_str("abc") == 0.f);
}

int main() {
    return Catch::Session().run();
}
#endif