#include <iostream>
#include "qtranslator.hpp"
#include "format.hpp"
#include "exception.hpp"

int main(int ac, char **av)
{
    try {
        qtranslator app(ac, av);
        return EXIT_SUCCESS;
    } catch (const compiler::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception &e) {
        std::cerr << format::red << "exception occured: " << format::reset << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << format::red << "unknown exception occured" << format::reset << std::endl;
        return EXIT_FAILURE;
    }
}