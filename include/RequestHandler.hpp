#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <vector>
#include <mutex>
#include <queue>
#include <Elevator.hpp>
#include <climits>

namespace lift {
namespace elevator {

class RequestHandler {
private:
    std::vector<lift::elevator::Elevator*> m_elevators;

public:
    std::mutex m_mutex;
    std::queue<int> m_requests;

    // ctor
    RequestHandler() = default;

    // Add a request
    void addRequest(int floor);

    // Assign elevator to a request
    void assignElevator();

    // Set elevator pointers
    void setElevators(std::vector<lift::elevator::Elevator*>& elevators);
};

} // namespace elevator
} // namespace lift

#endif // REQUESTHANDLER_H
