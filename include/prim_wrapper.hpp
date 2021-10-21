#pragma once

#include "arithmetic_traits.hpp"

/* concepts */

namespace concepts {
    template<typename T>
    concept number = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<bool, T>;

    template<typename T>
    concept unsigned_integral = std::is_integral_v<T> && std::is_unsigned_v<T> && !std::is_same_v<bool, T>;

    template<typename U, typename T>
    concept is_promotable = is_promotion<U, T>::value;
}

/* general macros */

#ifdef _MSC_VER
#define PW_FORCEINLINE __forceinline
#else
#define PW_FORCEINLINE __attribute__((always_inline)) inline
#endif

/* concept macros */

#define PW_INTEGRAL_ONLY std::is_integral_v<T>
#define PW_UNSIGNED_INTEGRAL_ONLY concepts::unsigned_integral<T>
#define PW_PROMOTABLE_ONLY concepts::is_promotable<U, T>

/* operator macros */

#define PW_ADD_CONSTRAINT_OPERATOR(op, constraints) \
PW_FORCEINLINE constexpr PW<T> operator op (CTR<T> v) const noexcept requires constraints { return m_val + v; } \
PW_FORCEINLINE constexpr PW<T> operator op (CPWR<T> pw) const noexcept requires constraints { return m_val + pw.get(); } \
PW_FORCEINLINE constexpr PWR<T> operator op=(CTR<T> v) noexcept requires constraints { m_val op= v; return *this; } \
PW_FORCEINLINE constexpr PWR<T> operator op=(CPWR<T> pw) noexcept requires constraints { m_val op= pw.get(); return *this; } \
template<concepts::number U> requires PW_PROMOTABLE_ONLY && constraints\
PW_FORCEINLINE constexpr friend PW<T> operator op (CPWR<U> pwl, CPWR<T> pwr) noexcept { return pwl.get() op pwr.get(); }; \
template<concepts::number U> requires constraints \
PW_FORCEINLINE constexpr friend PW<T> operator op (CTR<U> v, CPWR<T> pw) noexcept { return v op pw.get(); }; \
template<concepts::number U> requires PW_PROMOTABLE_ONLY && constraints \
PW_FORCEINLINE constexpr friend PW<T> operator op= (CPWR<U> pwl, CPWR<T> pwr) noexcept { return pwl.get() op= pwr.get(); }; \
template<concepts::number U> requires constraints \
PW_FORCEINLINE constexpr friend PW<T> operator op= (CTR<U> v, CPWR<T> pw) noexcept { return v op= pw.get(); }; \

#define PW_ADD_INTEGRAL_ONLY_OPERATOR(op) PW_ADD_CONSTRAINT_OPERATOR(op, PW_INTEGRAL_ONLY)

#define PW_ADD_GENERAL_OPERATOR(op) PW_ADD_CONSTRAINT_OPERATOR(op, true)

#define PW_ADD_COMP_OPERATOR(op) \
PW_FORCEINLINE constexpr bool operator op (CTR<T> v) const noexcept { return m_val op v; } \
PW_FORCEINLINE constexpr bool operator op (CPWR<T> pw) const noexcept { return m_val op pw.get(); } \

/* implementation */

template<concepts::number T>
struct prim_wrapper {
private:

    template<concepts::number U>
    using PW = prim_wrapper<U>;

    template<concepts::number U>
    using PWR = prim_wrapper<U>&;

    template<concepts::number U>
    using CPWR = const prim_wrapper<U>&;

    template<concepts::number U>
    using CTR = const U&;

    struct detail {
    private:

        // credits to: https://stackoverflow.com/a/36937049
        template<concepts::unsigned_integral T, std::size_t... N>
        PW_FORCEINLINE constexpr static T bswap_impl(T v, std::index_sequence<N...>) {
            return ((((v >> (N * CHAR_BIT)) & (T)(std::uint8_t)(-1)) << ((sizeof(T) - 1 - N) * CHAR_BIT)) | ...);
        };

    public:

        template<concepts::unsigned_integral T>
        PW_FORCEINLINE constexpr static T bswap(T v) {
            return bswap_impl(v, std::make_index_sequence<sizeof(T)>{});
        }
    };

protected:

    using numlim = std::numeric_limits<T>;

    T m_val;

public:

    using byte_set = std::array<std::uint8_t, sizeof(T)>;
        
    /* constructors */

    constexpr prim_wrapper() noexcept : m_val{} {}

    template<concepts::number U>
    PW_FORCEINLINE constexpr prim_wrapper(CTR<U> v) noexcept : m_val{static_cast<T>(v)} {}

    template<concepts::number U>
    PW_FORCEINLINE constexpr prim_wrapper(CPWR<U> pw) noexcept : m_val{static_cast<T>(pw.get())} {}

    /* assignment */
    
    template<concepts::number U>
    PW_FORCEINLINE constexpr PWR<T> operator=(CTR<U> v) noexcept { m_val = static_cast<T>(v); return *this; }
    template<concepts::number U>
    PW_FORCEINLINE constexpr PWR<T> operator=(CPWR<U> pw) noexcept { m_val = static_cast<T>(pw.get()); return *this; }

    /* conversions */
            
    PW_FORCEINLINE constexpr explicit operator bool() const { return m_val; };

    /* general operators */

    PW_ADD_GENERAL_OPERATOR(+);

    PW_ADD_GENERAL_OPERATOR(-);

    PW_ADD_GENERAL_OPERATOR(*);

    PW_ADD_GENERAL_OPERATOR(/);

    /* integral only operators */

    PW_ADD_INTEGRAL_ONLY_OPERATOR(%)

    PW_ADD_INTEGRAL_ONLY_OPERATOR(&)

    PW_ADD_INTEGRAL_ONLY_OPERATOR(|)

    PW_ADD_INTEGRAL_ONLY_OPERATOR(^)

    PW_ADD_INTEGRAL_ONLY_OPERATOR(<<)

    PW_ADD_INTEGRAL_ONLY_OPERATOR(>>)

    /* comparison operators */

    PW_ADD_COMP_OPERATOR(==)

    PW_ADD_COMP_OPERATOR(!=)

    PW_ADD_COMP_OPERATOR(>)

    PW_ADD_COMP_OPERATOR(>=)

    PW_ADD_COMP_OPERATOR(<)

    PW_ADD_COMP_OPERATOR(<=)

    /* other operators */

    PW_FORCEINLINE constexpr PWR<T> operator++() { ++m_val; return *this; }
    PW_FORCEINLINE constexpr PWR<T> operator--() { --m_val; return *this; }
    PW_FORCEINLINE constexpr PW<T> operator++(int) { return m_val++; }
    PW_FORCEINLINE constexpr PW<T> operator--(int) { return m_val--; }

    PW_FORCEINLINE constexpr PW<T> operator+() const { return +m_val; }
    PW_FORCEINLINE constexpr PW<T> operator-() const { return -m_val; }
    PW_FORCEINLINE constexpr PW<T> operator~() const requires PW_INTEGRAL_ONLY { return ~m_val; }
    PW_FORCEINLINE constexpr bool operator!() const { return !m_val; }

    /* constants */

    constexpr static inline auto MAX = numlim::max();
    constexpr static inline auto MIN = std::numeric_limits<T>::min();
    constexpr static inline auto EPSILON = std::numeric_limits<T>::epsilon();
    constexpr static inline auto RADIX = std::numeric_limits<T>::radix;
    
    constexpr static inline auto BYTES = sizeof(T);
    constexpr static inline auto BITS = sizeof(T) * CHAR_BIT;

    /* getters */

    PW_FORCEINLINE constexpr T& get() noexcept {
        return m_val;
    }

    PW_FORCEINLINE constexpr const T& get() const noexcept {
        return m_val;
    }

    /* conversion */

    template<typename T>
    constexpr T to() {
        return static_cast<T>(m_val);
    }
    
    static std::string to_str(CTR<T> v) noexcept {
        return std::to_string(v);
    }

    constexpr static byte_set to_bytes(CPWR<T> pw) noexcept requires PW_INTEGRAL_ONLY {
        byte_set out{};
        
        for (auto i = 0; i < BYTES; i++)
            out[i] = (pw.get() >> BITS - (i + 1) * CHAR_BIT) & 0xFF; 

        return out;
    }

    std::string str() const noexcept {
        return to_str(m_val);
    }

    constexpr byte_set bytes() const noexcept requires PW_INTEGRAL_ONLY {
        return to_bytes(*this);
    }

    template<typename U>
    static PW<T> from_str(U&& str) noexcept {
        std::stringstream ss(std::forward<U>(str));
        T out;
        ss >> out;
        return out;
    }

    constexpr static PW<T> from_bytes(const byte_set& bytes) noexcept requires PW_INTEGRAL_ONLY {
        T out = 0;

        for (const auto& byte: bytes) {
            out <<= CHAR_BIT;
            out |= byte;
        }

        return out;
    }

    /* general */
    
    constexpr bool is_null() const noexcept {
        return !m_val;
    }

    constexpr PW<T> min(CPWR<T> pw) const noexcept {
        return gcem::min(m_val, pw.get());
    }

    constexpr PW<T> max(CPWR<T> pw) const noexcept {
        return gcem::max(m_val, pw.get());
    }

    constexpr PW<T> abs() const noexcept {
        return gcem::abs(m_val);
    }

    constexpr PW<T> byte_swap() const requires PW_UNSIGNED_INTEGRAL_ONLY {
        return detail::bswap(m_val);
    }

    constexpr PW<T> rotate_left(std::uint32_t v) const requires PW_UNSIGNED_INTEGRAL_ONLY {
        return std::rotl(m_val, v);
    }

    constexpr PW<T> rotate_right(std::uint32_t v) const requires PW_UNSIGNED_INTEGRAL_ONLY {
        return std::rotr(m_val, v);
    }
};

template<std::floating_point T>
struct float_wrapper : prim_wrapper<T> {
private:

    using FW = float_wrapper<T>;
    using FWR = float_wrapper<T>&;
    using CFWR = const float_wrapper<T>&;

    template<concepts::number U>
    using CTR = const U&;

public:

    // inherit all the constructors
    using prim_wrapper<T>::prim_wrapper;

    /* constants */

    constexpr static inline auto LOWEST = std::numeric_limits<T>::lowest();
    constexpr static inline auto INF = std::numeric_limits<T>::infinity();
    constexpr static inline auto NEG_INF = -std::numeric_limits<T>::infinity();
    constexpr static inline auto NaN = std::numeric_limits<T>::quiet_NaN();

    /* mathematical constants */

    struct consts {
        constexpr static inline T E = std::numbers::e_v<T>;
        constexpr static inline T PI = std::numbers::pi_v<T>;
        constexpr static inline T PI_2 = std::numbers::pi_v<T> / 2.l;
        constexpr static inline T PI_4 = std::numbers::pi_v<T> / 4.l;
    };

    /* general */

    constexpr FW mod(CTR<T> v) const noexcept {
        return gcem::fmod(this->m_val, v);
    }

    constexpr FW ceil() const noexcept {
        return gcem::ceil(this->m_val);
    }

    constexpr FW floor() const noexcept {
        return gcem::floor(this->m_val);
    }

    constexpr FW trunc() const noexcept {
        return gcem::trunc(this->m_val);
    }

    constexpr FW round() const noexcept {
        return gcem::round(this->m_val);
    }

    constexpr bool is_nan() const noexcept {
        return gcem::internal::is_nan(this->m_val);
    }

    constexpr bool is_inf() const noexcept {
        return gcem::internal::is_inf(this->m_val);
    }
};

/* signed integers */

using i8 = prim_wrapper<std::int8_t>;
using i16 = prim_wrapper<std::int16_t>;
using i32 = prim_wrapper<std::int32_t>;
using i64 = prim_wrapper<std::int64_t>;

/* unsigned integers */

using u8 = prim_wrapper<std::uint8_t>;
using u16 = prim_wrapper<std::uint16_t>;
using u32 = prim_wrapper<std::uint32_t>;
using u64 = prim_wrapper<std::uint64_t>;

/* floats */

using f32 = float_wrapper<float>;
using f64 = float_wrapper<double>;

/* goobye macros :( */

#undef PW_FORCEINLINE

#undef PW_INTEGRAL_ONLY
#undef PW_UNSIGNED_INTEGRAL_ONLY
#undef PW_PROMOTABLE_ONLY

#undef PW_ADD_CONSTRAINT_OPERATOR
#undef PW_ADD_INTEGRAL_ONLY_OPERATOR
#undef PW_ADD_GENERAL_OPERATOR
#undef PW_ADD_COMP_OPERATOR