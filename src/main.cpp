#include <iostream>

#include "RailwaySignal.hpp"
#include "RailwayTypes.hpp"
#include "SignalCommand.hpp"
#include "SignalDemo.hpp"

/**
 * @brief Point d'entrée du programme
 * @safety_level SIL4
 * @requirement REQ_MAIN_001
 */
int main() {
    try {
        SignalDemo demo;
        demo.run();

        std::cout << "\nDemonstration completed successfully.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
