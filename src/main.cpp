#include "../include/backend.hpp"
#include <iostream>
#include <string>

// https://stackoverflow.com/questions/62004186/undefined-reference-using-external-library-with-cmake-and-conan

auto main(int argc, char** argv) -> int {
    /*
    if (argc < 2) {
        std::cout << "provide window size n\n";
        return 1;
    }*/
    (void)argv;
    (void)argc;

    auto server = backend::handler("http://localhost", "8080", "json");

    server.run();
    return 0;
}
