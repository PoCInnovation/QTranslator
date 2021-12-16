#pragma once

#include <exception>
#include <string>
#include <utility>

namespace compiler {
class exception : public std::exception
{
private:
    std::string m_error;
public:
    explicit exception(std::string error) : m_error(std::move(error)) {}
    template<typename ...T>
    explicit exception(T &&...error) : m_error() {((m_error += error), ...);}
    ~exception() override = default;
    [[nodiscard]] inline const char *what() const noexcept override {return m_error.c_str();}
};
}