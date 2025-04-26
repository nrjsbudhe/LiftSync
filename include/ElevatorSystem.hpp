#ifndef ELEVATORSYSTEM_H
#define ELEVATORSYSTEM_H

#include <vector>
#include <thread>
#include "Elevator.hpp"
#include "RequestHandler.hpp"

namespace lift {
namespace elevator {

class ElevatorSystem {
private:
    std::vector<std::unique_ptr<Elevator>> m_elevators;
    lift::elevator::RequestHandler m_request_handler;

public:
    std::vector<std::thread> m_elevator_threads;

    // ctor
    ElevatorSystem(int elevators_count);

    // Start the system
    void start();

    // Stop the system
    void stop();

    // Request Elevator
    void requestElevator(int floor);
};

} // namespace elevator
} // namespace lift

#endif // ELEVATORSYSTEM_H
