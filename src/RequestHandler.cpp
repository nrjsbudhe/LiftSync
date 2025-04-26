#include "../include/RequestHandler.hpp"
#include <iostream>
#include <cmath>

void lift::elevator::RequestHandler::addRequest(int floor)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_requests.push(floor);
    assignElevator();
}

void lift::elevator::RequestHandler::assignElevator()
{
    if (m_requests.empty())
    {
        return;
    }

    int floor = m_requests.front();
    m_requests.pop();

    Elevator* best_elevator = nullptr;
    int min_distance = INT_MAX;

    for (auto elevator : m_elevators)
    {
        // Prefer idle elevators
        if (elevator->getState() == State::IDLE)
        {
            int distance = std::abs(floor - elevator->getCurrentFloor());
            if (distance < min_distance)
            {
                min_distance = distance;
                best_elevator = elevator;
            }
        }
    }

    // If no idle elevator found, pick any closest elevator
    if (!best_elevator)
    {
        for (auto elevator : m_elevators)
        {
            int distance = std::abs(floor - elevator->getCurrentFloor());
            if (distance < min_distance)
            {
                min_distance = distance;
                best_elevator = elevator;
            }
        }
    }

    if (best_elevator)
    {
        std::cout << "Sending request to Elevator " << best_elevator->getId()
                  << " to move to floor " << floor << ".\n";
        best_elevator->addRequest(floor);
    }
}


void lift::elevator::RequestHandler::setElevators(std::vector<lift::elevator::Elevator*>& elevators)
{
    m_elevators = elevators;
}
