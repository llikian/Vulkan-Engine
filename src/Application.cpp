/***************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 **************************************************************************************************/

#include "Application.hpp"

#include "core/EventHandler.hpp"
#include "core/Window.hpp"
#include "maths/trigonometry.hpp"

Application::Application() : camera(vec3(), degrees_to_radians(90.0f), 0.1f, 1000.0f) {
    EventHandler::set_active_camera(&camera);
}

void Application::run() {
    while(!Window::should_close()) {
        EventHandler::poll_and_handle_events();

        Window::swap_buffers();
    }
}
