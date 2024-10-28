#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include "RailwaySignal.hpp"
#include "RailwayTypes.hpp"
#include "SignalCommand.hpp"

/**
 * @brief Programme principal de démonstration
 * @safety_level SIL4
 * @requirement REQ_DEMO_001
 */
class SignalDemo {
   public:
    SignalDemo();
    ~SignalDemo() = default;

    void run();

   private:
    static std::string aspectToString(Railway::Aspect aspect) {
        switch (aspect) {
            using enum Railway::Aspect;

            case RED:
                return "RED";
            case YELLOW:
                return "YELLOW";
            case GREEN:
                return "GREEN";
            default:
                return "UNKNOWN";
        }
    }

    Railway::RailwaySignal signal_{"SIGNAL_DEMO_001"};
};
