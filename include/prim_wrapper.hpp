#pragma once

namespace concepts {
    template<typename T>
    concept number = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<bool, T>;

    template<typename T>
    concept unsigned_integral = std::is_integral_v<T> && std::is_unsigned_v<T> && !std::is_same_v<bool, T>;
}

#define FORCEINLINE __forceinline
#define INTEGRAL_ONLY requires std::is_integral_v<T>
#define UNSIGNED_INTEGRAL_ONLY requires concepts::unsigned_integral<T>

template<concepts::number T>
struct prim_wrapper {
private:

    using PW = prim_wrapper<T>;
    using PWR = prim_wrapper<T>&;
    using CPWR = const prim_wrapper<T>&;
    using CTR = const T&;

    struct detail {
    private:

        // credits to: https://stackoverflow.com/a/36937049

        template<concepts::unsigned_integral T, std::size_t... N>
        FORCEINLINE constexpr static T bswap_impl(T v, std::index_sequence<N...>) {
            return ((((v >> (N * CHAR_BIT)) & (T)(std::uint8_t)(-1)) << ((sizeof(T) - 1 - N) * CHAR_BIT)) | ...);
        };

    public:

        template<concepts::unsigned_integral T>
        FORCEINLINE constexpr static T bswap(T v) {
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
    FORCEINLINE constexpr prim_wrapper(const U& v) noexcept : m_val{static_cast<T>(v)} {}

    template<concepts::number U>
    FORCEINLINE constexpr prim_wrapper(const prim_wrapper<U>& pw) noexcept : m_val{static_cast<T>(pw.get())} {}

    /* operators */

    FORCEINLINE constexpr explicit operator bool() const { return m_val; };

    FORCEINLINE constexpr bool operator==(CTR v) const { return m_val == v; }
    FORCEINLINE constexpr bool operator==(CPWR pw) const { return m_val == pw.get(); }
    FORCEINLINE constexpr bool operator!=(CTR v) const { return m_val != v; }
    FORCEINLINE constexpr bool operator!=(CPWR pw) const { return m_val != pw.get(); }
    FORCEINLINE constexpr bool operator>(CTR v) const { return m_val > v; }
    FORCEINLINE constexpr bool operator>(CPWR pw) const { return m_val > pw.get(); }
    FORCEINLINE constexpr bool operator>=(CTR v) const { return m_val >= v; }
    FORCEINLINE constexpr bool operator>=(CPWR pw) const { return m_val >= pw.get(); }
    FORCEINLINE constexpr bool operator<(CTR v) const { return m_val < v; }
    FORCEINLINE constexpr bool operator<(CPWR pw) const { return m_val < pw.get(); }
    FORCEINLINE constexpr bool operator<=(CTR v) const { return m_val <= v; }
    FORCEINLINE constexpr bool operator<=(CPWR pw) const { return m_val <= pw.get(); }

    template<concepts::number U>
    FORCEINLINE constexpr PWR operator=(const U& v) noexcept { m_val = static_cast<T>(v); return *this; }
    template<concepts::number U>
    FORCEINLINE constexpr PWR operator=(const prim_wrapper<U>& pw) noexcept { m_val = static_cast<T>(pw.get()); return *this; }

    FORCEINLINE constexpr PW operator+(CTR v) const { return m_val + v; }
    FORCEINLINE constexpr PW operator+(CPWR pw) const { return m_val + pw.get(); }
    FORCEINLINE constexpr PWR operator+=(CTR v) { m_val += v; return *this; }
    FORCEINLINE constexpr PWR operator+=(CPWR pw) { m_val += pw.get(); return *this; }

    FORCEINLINE constexpr PW operator-(CTR v) const { return m_val - v; }
    FORCEINLINE constexpr PW operator-(CPWR pw) const { return m_val - pw.get(); }
    FORCEINLINE constexpr PWR operator-=(CTR v) { m_val -= v; return *this; }
    FORCEINLINE constexpr PWR operator-=(CPWR pw) { m_val -= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator*(CTR v) const { return m_val * v; }
    FORCEINLINE constexpr PW operator*(CPWR pw) const { return m_val * pw.get(); }
    FORCEINLINE constexpr PWR operator*=(CTR v) { m_val *= v; return *this; }
    FORCEINLINE constexpr PWR operator*=(CPWR pw) { m_val *= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator/(CTR v) const { return m_val / v; }
    FORCEINLINE constexpr PW operator/(CPWR pw) const { return m_val / pw.get(); }
    FORCEINLINE constexpr PWR operator/=(CTR v) { m_val /= v; return *this; }
    FORCEINLINE constexpr PWR operator/=(CPWR pw) { m_val /= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator%(CTR v) const INTEGRAL_ONLY { return m_val % v; }
    FORCEINLINE constexpr PW operator%(CPWR pw) const INTEGRAL_ONLY { return m_val % pw.get(); }
    FORCEINLINE constexpr PWR operator%=(CTR v) INTEGRAL_ONLY { m_val %= v; return *this; }
    FORCEINLINE constexpr PWR operator%=(CPWR pw) INTEGRAL_ONLY { m_val %= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator&(CTR v) const INTEGRAL_ONLY { return m_val & v; }
    FORCEINLINE constexpr PW operator&(CPWR pw) const INTEGRAL_ONLY { return m_val & pw.get(); }
    FORCEINLINE constexpr PWR operator&=(CTR v) INTEGRAL_ONLY { m_val &= v; return *this; }
    FORCEINLINE constexpr PWR operator&=(CPWR pw) INTEGRAL_ONLY { m_val &= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator|(CTR v) const INTEGRAL_ONLY { return m_val | v; }
    FORCEINLINE constexpr PW operator|(CPWR pw) const INTEGRAL_ONLY { return m_val | pw.get(); }
    FORCEINLINE constexpr PWR operator|=(CTR v) INTEGRAL_ONLY { m_val |= v; return *this; }
    FORCEINLINE constexpr PWR operator|=(CPWR pw) INTEGRAL_ONLY { m_val |= pw.get(); return *this; }
    
    FORCEINLINE constexpr PW operator^(CTR v) const INTEGRAL_ONLY { return m_val ^ v; }
    FORCEINLINE constexpr PW operator^(CPWR pw) const INTEGRAL_ONLY { return m_val ^ pw.get(); }
    FORCEINLINE constexpr PWR operator^=(CTR v) INTEGRAL_ONLY { m_val ^= v; return *this; }
    FORCEINLINE constexpr PWR operator^=(CPWR pw) INTEGRAL_ONLY { m_val ^= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator<<(CTR v) const INTEGRAL_ONLY { return m_val << v; }
    FORCEINLINE constexpr PW operator<<(CPWR pw) const INTEGRAL_ONLY { return m_val << pw.get(); }
    FORCEINLINE constexpr PWR operator<<=(CTR v) INTEGRAL_ONLY { m_val <<= v; return *this; }
    FORCEINLINE constexpr PWR operator<<=(CPWR pw) INTEGRAL_ONLY { m_val <<= pw.get(); return *this; }

    FORCEINLINE constexpr PW operator>>(CTR v) const INTEGRAL_ONLY { return m_val >> v; }
    FORCEINLINE constexpr PW operator>>(CPWR pw) const INTEGRAL_ONLY { return m_val >> pw.get(); }
    FORCEINLINE constexpr PWR operator>>=(CTR v) INTEGRAL_ONLY { m_val >>= v; return *this; }
    FORCEINLINE constexpr PWR operator>>=(CPWR pw) INTEGRAL_ONLY { m_val >>= pw.get(); return *this; }

    FORCEINLINE constexpr PWR operator++() { ++m_val; return *this; }
    FORCEINLINE constexpr PWR operator--() { --m_val; return *this; }
    FORCEINLINE constexpr PW operator++(int) { return m_val++; }
    FORCEINLINE constexpr PW operator--(int) { return m_val--; }

    FORCEINLINE constexpr PW operator+() const { return +m_val; }
    FORCEINLINE constexpr PW operator-() const { return -m_val; }
    FORCEINLINE constexpr PW operator~() const INTEGRAL_ONLY { return ~m_val; }
    FORCEINLINE constexpr bool operator!() const { return !m_val; }

    /* constants */

    constexpr static inline auto MAX = numlim::max();
    constexpr static inline auto MIN = std::numeric_limits<T>::min();
    constexpr static inline auto EPSILON = std::numeric_limits<T>::epsilon();
    constexpr static inline auto RADIX = std::numeric_limits<T>::radix;
    
    constexpr static inline auto BYTES = sizeof(T);
    constexpr static inline auto BITS = sizeof(T) * CHAR_BIT;

    /* getters */

    FORCEINLINE constexpr T& get() noexcept {
        return m_val;
    }

    FORCEINLINE constexpr const T& get() const noexcept {
        return m_val;
    }

    /* conversion stuff */

    template<typename T>
    constexpr T to() {
        return static_cast<T>(m_val);
    }
    
    // change to std::to_string if u don't have fmt
    static std::string to_str(CTR v) noexcept {
        return std::to_string(v);
    }

    constexpr static byte_set to_bytes(CPWR pw) noexcept INTEGRAL_ONLY {
        byte_set out{};
        
        for (auto i = 0; i < BYTES; i++)
            out[i] = (pw.get() >> BITS - (i + 1) * CHAR_BIT) & 0xFF; 

        return out;
    }
    
    // change to std::to_string if u don't have fmt
    std::string str() const noexcept {
        return std::to_string(m_val);
    }

    constexpr byte_set bytes() const noexcept INTEGRAL_ONLY {
        byte_set out{};

        for (auto i = 0; i < BYTES; i++)
            out[i] = (m_val >> BITS - (i + 1) * CHAR_BIT) & 0xFF; 

        return out;
    }

    template<typename U>
    static PW from_str(U&& str) noexcept {
        std::stringstream ss(std::forward<U>(str));
        T out;
        ss >> out;
        return out;
    }

    constexpr static PW from_bytes(const byte_set& bytes) noexcept INTEGRAL_ONLY {
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

    constexpr PW min(CPWR pw) const noexcept {
        return gcem::min(m_val, pw.get());
    }

    constexpr PW max(CPWR pw) const noexcept {
        return gcem::max(m_val, pw.get());
    }

    constexpr PW abs() const noexcept {
        return gcem::abs(m_val);
    }

    constexpr PW byte_swap() const UNSIGNED_INTEGRAL_ONLY {
        return detail::bswap(m_val);
    }

    constexpr PW rotate_left(std::uint32_t v) const UNSIGNED_INTEGRAL_ONLY {
        return std::rotl(m_val, v);
    }

    constexpr PW rotate_right(std::uint32_t v) const UNSIGNED_INTEGRAL_ONLY {
        return std::rotr(m_val, v);
    }
};

template<std::floating_point T>
struct float_wrapper : prim_wrapper<T> {
private:

    using FW = float_wrapper<T>;
    using FWR = float_wrapper<T>&;
    using CFWR = const float_wrapper<T>&;
    using CTR = const T&;

public:

    // inherit all the constructors
    using prim_wrapper<T>::prim_wrapper;

    /* constants */

    constexpr static inline auto LOWEST = std::numeric_limits<T>::lowest();
    constexpr static inline auto INF = std::numeric_limits<T>::infinity();
    constexpr static inline auto NEG_INF = -std::numeric_limits<T>::infinity();
    constexpr static inline auto NaN = std::numeric_limits<T>::quiet_NaN();

    struct consts {
        constexpr static inline T E = std::numbers::e_v<T>;
        constexpr static inline T PI = std::numbers::pi_v<T>;
        constexpr static inline T PI_2 = std::numbers::pi_v<T> / 2.l;
        constexpr static inline T PI_4 = std::numbers::pi_v<T> / 4.l;
    };

    /* general */

    constexpr FW mod(CTR v) const noexcept {
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

#undef FORCEINLINE
#undef INTEGRAL_ONLY
#undef UNSIGNED_INTEGRAL_ONLY