#pragma once

namespace concepts {
    template<typename T>
    concept number = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<bool, T>;

    template<typename T>
    concept unsigned_integral = std::is_integral_v<T> && std::is_unsigned_v<T> && !std::is_same_v<bool, T>;
}

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
        constexpr static T bswap_impl(T v, std::index_sequence<N...>) {
            return ((((v >> (N * CHAR_BIT)) & (T)(std::uint8_t)(-1)) << ((sizeof(T) - 1 - N) * CHAR_BIT)) | ...);
        };

    public:

        template<concepts::unsigned_integral T>
        constexpr static T bswap(T v) {
            return bswap_impl(v, std::make_index_sequence<sizeof(T)>{});
        }
    };

protected:

    using numlim = std::numeric_limits<T>;

    T m_val;

public:

    using byte_set = std::array<std::uint8_t, sizeof(T)>;

    friend struct fmt::formatter<PW>;
        
    /* constructors */

    constexpr prim_wrapper() noexcept : m_val{} {}
    constexpr prim_wrapper(CTR v) noexcept : m_val{v} {}

    template<concepts::number U>
    constexpr prim_wrapper(const prim_wrapper<U>& pw) noexcept : m_val{static_cast<T>(pw.get())} {}

    /* operators */

    auto operator <=>(const PW&) const = default;

    constexpr PWR operator=(CTR v) { m_val = v; return *this; }
    constexpr PWR operator=(CPWR pw) { m_val = pw.get(); return *this; }

    constexpr PW operator+(CTR v) { return m_val + v; }
    constexpr PW operator+(CPWR pw) const { return m_val + pw.get(); }
    constexpr PWR operator+=(CTR v) { m_val += v; return *this; }
    constexpr PWR operator+=(CPWR pw) { m_val += pw.get(); return *this; }

    constexpr PW operator-(CTR v) { return m_val - v; }
    constexpr PW operator-(CPWR pw) const { return m_val - pw.get(); }
    constexpr PWR operator-=(CTR v) { m_val -= v; return *this; }
    constexpr PWR operator-=(CPWR pw) { m_val -= pw.get(); return *this; }

    constexpr PW operator*(CTR v) { return m_val * v; }
    constexpr PW operator*(CPWR pw) const { return m_val * pw.get(); }
    constexpr PWR operator*=(CTR v) { m_val *= v; return *this; }
    constexpr PWR operator*=(CPWR pw) { m_val *= pw.get(); return *this; }

    constexpr PW operator/(CTR v) { return m_val / v; }
    constexpr PW operator/(CPWR pw) const { return m_val / pw.get(); }
    constexpr PWR operator/=(CTR v) { m_val /= v; return *this; }
    constexpr PWR operator/=(CPWR pw) { m_val /= pw.get(); return *this; }

    constexpr PW operator%(CTR v) { return m_val % v; }
    constexpr PW operator%(CPWR pw) const { return m_val % pw.get(); }
    constexpr PWR operator%=(CTR v) { m_val %= v; return *this; }
    constexpr PWR operator%=(CPWR pw) { m_val %= pw.get(); return *this; }

    constexpr PW operator&(CTR v) { return m_val & v; }
    constexpr PW operator&(CPWR pw) const { return m_val & pw.get(); }
    constexpr PWR operator&=(CTR v) { m_val &= v; return *this; }
    constexpr PWR operator&=(CPWR pw) { m_val &= pw.get(); return *this; }

    constexpr PW operator|(CTR v) { return m_val | v; }
    constexpr PW operator|(CPWR pw) const { return m_val | pw.get(); }
    constexpr PWR operator|=(CTR v) { m_val |= v; return *this; }
    constexpr PWR operator|=(CPWR pw) { m_val |= pw.get(); return *this; }
    
    constexpr PW operator^(CTR v) { return m_val ^ v; }
    constexpr PW operator^(CPWR pw) const { return m_val ^ pw.get(); }
    constexpr PWR operator^=(CTR v) { m_val ^= v; return *this; }
    constexpr PWR operator^=(CPWR pw) { m_val ^= pw.get(); return *this; }

    constexpr PW operator<<(CTR v) { return m_val << v; }
    constexpr PW operator<<(CPWR pw) const { return m_val << pw.get(); }
    constexpr PWR operator<<=(CTR v) { m_val <<= v; return *this; }
    constexpr PWR operator<<=(CPWR pw) { m_val <<= pw.get(); return *this; }

    constexpr PW operator>>(CTR v) { return m_val >> v; }
    constexpr PW operator>>(CPWR pw) const { return m_val >> pw.get(); }
    constexpr PWR operator>>=(CTR v) { m_val >>= v; return *this; }
    constexpr PWR operator>>=(CPWR pw) { m_val >>= pw.get(); return *this; }

    constexpr PWR operator++() { m_val++; return *this; }
    constexpr PWR operator--() { m_val--; return *this; }
    constexpr PW operator++(int) { return m_val++; }
    constexpr PW operator--(int) { return m_val--; }

    constexpr PW operator+() const { return +m_val; }
    constexpr PW operator-() const { return -m_val; }
    constexpr PW operator~() const { return ~m_val; }
    constexpr bool operator!() const { return !m_val; }

    /* constants */

    constexpr static inline auto MAX = numlim::max();
    constexpr static inline auto MIN = std::numeric_limits<T>::min();
    constexpr static inline auto EPSILON = std::numeric_limits<T>::epsilon();
    constexpr static inline auto RADIX = std::numeric_limits<T>::radix;
    
    constexpr static inline auto BYTES = sizeof(T);
    constexpr static inline auto BITS = sizeof(T) * CHAR_BIT;

    /* getters */

    constexpr T& get() noexcept {
        return m_val;
    }

    constexpr const T& get() const noexcept {
        return m_val;
    }

    /* conversion stuff */
    
    static std::string to_str(CTR v) noexcept {
        return fmt::to_string(v);
    }

    constexpr static byte_set to_bytes(CPWR pw) noexcept {
        byte_set out{};
        
        for (int i = 0; i < BYTES; i++)
            out[i] = (pw.get() >> BITS - (i + 1) * CHAR_BIT) & 0xFF; 

        return out;
    }
        
    std::string str() const noexcept {
        return fmt::to_string(m_val);
    }

    constexpr byte_set bytes() const noexcept {
        byte_set out{};

        for (int i = 0; i < BYTES; i++)
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

    constexpr static PW from_bytes(const byte_set& bytes) noexcept {
        T out = 0;

        for (auto byte: bytes) {
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

    constexpr PW byte_swap() const requires concepts::unsigned_integral<T> {
        return detail::bswap(m_val);
    }

    constexpr PW rotate_left(std::uint32_t v) const requires concepts::unsigned_integral<T> {
        return std::rotl(m_val, v);
    }

    constexpr PW rotate_right(std::uint32_t v) const requires concepts::unsigned_integral<T> {
        return std::rotr(m_val, v);
    }
};

template<concepts::number T>
struct fmt::formatter<prim_wrapper<T>> : fmt::formatter<T> {
    auto format(const prim_wrapper<T>& val, format_context& ctx) {
        return formatter<T>::format(val.m_val, ctx);
    }
};

template<std::floating_point T>
struct float_wrapper : prim_wrapper<T> {
private:
    using FW = float_wrapper<T>;
    using FWR = float_wrapper<T>&;
    using CFWR = const float_wrapper<T>&;

public:

    // inherit all the constructors
    using prim_wrapper<T>::prim_wrapper;

    friend struct fmt::formatter<FW>;

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

template<std::floating_point T>
struct fmt::formatter<float_wrapper<T>> : fmt::formatter<T> {
    auto format(const float_wrapper<T>& val, format_context& ctx) {
        return formatter<T>::format(val.m_val, ctx);
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