#include "../include/Elevator.hpp"
#include <iostream>

lift::elevator::Elevator::Elevator(int id, lift::elevator::State state)
    : m_id(id),
      m_max_floor(10),
      m_current_floor(0),
      m_direction(Direction::NONE),
      m_state(state),
      m_running(true) {}

void lift::elevator::Elevator::run()
{
    // std::cout << "Elevator " << m_id << " is running.\n";

    while (m_running)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this]() { return !m_requests.empty() || !m_running; });

        if (!m_running) break; // Stop if system shutting down

        int target_floor = m_requests.front();
        m_requests.pop();
        lock.unlock();

        moveToFloor(target_floor);
    }

    std::cout << "Elevator " << m_id << " stopped.\n";
}

void lift::elevator::Elevator::addRequest(int floor)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_requests.push(floor);
    m_cv.notify_one();
}

void lift::elevator::Elevator::moveToFloor(int target_floor)
{
    std::cout << "Elevator " << m_id << " moving from floor " 
              << m_current_floor << " to floor " << target_floor << ".\n";

    if (target_floor < m_current_floor) {
        m_state = State::MOVING_DOWN;
        m_direction = Direction::DOWN;
    } else if (target_floor > m_current_floor) {
        m_state = State::MOVING_UP;
        m_direction = Direction::UP;
    } else {
        m_state = State::IDLE;
        m_direction = Direction::NONE;
    }

    std::this_thread::sleep_for(std::chrono::seconds(abs(target_floor - m_current_floor)));

    m_current_floor = target_floor;
    m_state = State::IDLE;
    m_direction = Direction::NONE;

    std::cout << "Elevator " << m_id << " reached floor " << m_current_floor << " and is now IDLE.\n";
}

int lift::elevator::Elevator::getCurrentFloor()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_current_floor;
}

void lift::elevator::Elevator::setRunning(bool state)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_running = state;
    }
    m_cv.notify_all(); // Wake the thread if waiting
}

int lift::elevator::Elevator::getId() const
{
    return m_id;
}

lift::elevator::State lift::elevator::Elevator::getState()
{
    return m_state;
}

