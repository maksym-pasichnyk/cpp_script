//
// Created by Maksym Pasichnyk on 25.04.2023.
//

module;

#include <variant>
#include <stdexcept>

export module cpp_script:variant;

export template<typename... Ts>
struct Enum : std::variant<Ts...> {
    using variant = std::variant<Ts...>;
    using variant::variant;

    template<typename T>
    constexpr auto is() const -> bool {
        return std::holds_alternative<T>(*this);
    }

    template<typename T>
    constexpr auto get() -> T& {
        return std::get<T>(*this);
    }

    template<typename T>
    constexpr auto get() const -> T const& {
        return std::get<T>(*this);
    }

    template<typename T>
    constexpr auto get_if() -> T* {
        return std::get_if<T>(*this);
    }

    template<typename T>
    constexpr auto get_if() const -> T const* {
        return std::get_if<T>(*this);
    }
};