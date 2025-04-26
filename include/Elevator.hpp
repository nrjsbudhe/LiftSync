#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>
#include <chrono>

namespace lift {
namespace elevator {

enum class Direction {
    UP,
    DOWN,
    NONE
};

enum class State {
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
};

class Elevator {
private:
    int m_id;
    int m_max_floor;
    int m_current_floor;
    Direction m_direction;
    State m_state;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<int> m_requests;
    bool m_running;

public:
    // ctor
    Elevator(int id, State state = State::IDLE);

    // Add request to the elevator queue
    void addRequest(int floor);

    // Main function to run the elevator thread
    void run();

    // Move to the requested floor
    void moveToFloor(int target_floor);

    // Returns the current floor of a elevator
    int getCurrentFloor();

    // Set state for running
    void setRunning(bool state);

    // Get elevator ID
    int getId() const;

    // Get State
    State getState();

    // dtor
    virtual ~Elevator() = default;
};

} // namespace elevator
} // namespace lift

#endif // ELEVATOR_H