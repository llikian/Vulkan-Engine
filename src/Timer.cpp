/***************************************************************************************************
 * @file  Timer.cpp
 * @brief Implementation of the Timer class
 **************************************************************************************************/

#include "Timer.hpp"

Timer::Timer()
    : start_time(std::chrono::system_clock::now()),
      total_elapsed_time(0.0f),
      b_is_paused(false) { }

float Timer::elapsed_time() const {
    if(b_is_paused) {
        return total_elapsed_time;
    } else {
        return total_elapsed_time + get_elapsed_time_from_start();
    }
}

bool Timer::is_paused() const { return b_is_paused; }

void Timer::pause() {
    b_is_paused = true;
    total_elapsed_time += get_elapsed_time_from_start();
}

void Timer::unpause() {
    b_is_paused = false;
    start_time = std::chrono::system_clock::now();
}

void Timer::reset() {
    total_elapsed_time = 0.0f;
    start_time = std::chrono::system_clock::now();
}

float Timer::get_elapsed_time_from_start() const {
    std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start_time;
    duration = std::chrono::round<std::chrono::milliseconds>(duration);
    return duration.count();
}
