#include "../include/ElevatorSystem.hpp"

int main() 
{
    lift::elevator::ElevatorSystem elevator_system(2); // 1 elevator

    elevator_system.start();

    elevator_system.requestElevator(15);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for operations

    elevator_system.requestElevator(30);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for operations

    elevator_system.requestElevator(10);

    std::this_thread::sleep_for(std::chrono::seconds(15)); // Wait for operations

    elevator_system.requestElevator(23);

    std::this_thread::sleep_for(std::chrono::seconds(120)); // Wait for operations
    elevator_system.stop();
    return 0;
}
