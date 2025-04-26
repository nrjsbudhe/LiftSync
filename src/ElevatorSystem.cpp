#include "../include/ElevatorSystem.hpp"
#include <iostream>

lift::elevator::ElevatorSystem::ElevatorSystem(int elevators_count)
{
    for (int i = 0; i < elevators_count; ++i)
    {
        m_elevators.emplace_back(std::make_unique<Elevator>(i));
    }

    std::vector<lift::elevator::Elevator*> elevator_ptrs;
    for (auto& elevator : m_elevators)
    {
        elevator_ptrs.push_back(elevator.get());
    }

    m_request_handler.setElevators(elevator_ptrs);
}

void lift::elevator::ElevatorSystem::start()
{
    std::cout << "Starting Elevator System...\n";
    for (auto& elevator : m_elevators)
    {
        m_elevator_threads.emplace_back(&Elevator::run, elevator.get());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for threads to init
}

void lift::elevator::ElevatorSystem::stop()
{
    std::cout << "Stopping Elevator System...\n";

    for (auto& elevator : m_elevators)
    {
        elevator->setRunning(false);
    }

    for (auto& thread : m_elevator_threads)
    {
        if (thread.joinable())
            thread.join();
    }
}

void lift::elevator::ElevatorSystem::requestElevator(int floor)
{
    m_request_handler.addRequest(floor);
}
