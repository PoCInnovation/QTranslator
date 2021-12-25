#pragma once

#include <exception>
#include <string>
#include <utility>

namespace transpiler {
/**
 *  This class provides all informations about an error that occured during the transpilation
 */
class exception : public std::exception
{
private:
    size_t m_pos{};
    std::string m_error;
public:
    /**
     *  Build a new transpiler exception
     *  @param pos the position on the line where the error occured
     *  @param error the reason why transpilation failed
     */
    explicit exception(size_t pos, std::string error) : m_pos(pos), m_error(std::move(error)) {}
    /**
     *  Build a new transpiler exception
     *  @param pos the position on the line where the error occured
     *  @param error the reason why transpilation failed as variadic arguments
     */
    template<typename ...T>
    explicit exception(size_t pos, T &&...error) : m_pos(pos), m_error() {((m_error += error), ...);}
    ~exception() override = default;
    /**
     *  @return the reason why transpilation failed
     */
    [[nodiscard]] inline const char *what() const noexcept override {return m_error.c_str();}
    /**
     *  @return the position on the line where the error occured
     */
    [[nodiscard]] inline const size_t &cursor() const noexcept {return m_pos;}
};
}