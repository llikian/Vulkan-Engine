/***************************************************************************************************
 * @file  Timer.hpp
 * @brief Declaration of the Timer class
 **************************************************************************************************/

#pragma once

#include <chrono>

/**
 * @class Timer
 * @brief A minimul timer class that allows to measure elapsed time.
 */
class Timer {
public:
    /**
     * @brief Default Constructor. Creates a timer starting now.
     */
    Timer();

    /**
     * @brief The total amount of time elapsed while the timer was unpaused.
     * @return Elapsed time in seconds, with a precision of 3 decimals.
     */
    float elapsed_time() const;

    /**
     * @return Whether the timer is currently paused.
     */
    bool is_paused() const;

    /**
     * @brief Pauses the timer.
     */
    void pause();

    /**
     * @brief Unpauses the timer.
     */
    void unpause();

    /**
     * @brief Resets the timer. Does not change the pause status, so if the timer is not paused, it
     * will start immediately.
     */
    void reset();

private:
    /**
     * @return The time elapsed between start_time and now.
     */
    float get_elapsed_time_from_start() const;

    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

    TimePoint start_time;     ///< The time at which the timer was started or unpaused.
    float total_elapsed_time; ///< The total amount of time the timer was unpaused before start_time.
    bool b_is_paused;         ///< Whether the timer is currently paused.
};
