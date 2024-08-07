/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the project
 **************************************************************************************************/

#include "Application.hpp"
#include <iostream>
#include <stdexcept>

Application application;

int main() {
    try {
        application.run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}