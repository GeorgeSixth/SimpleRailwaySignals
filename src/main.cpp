#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "RailwaySignal.hpp"
#include "RailwayTypes.hpp"
#include "SignalCommand.hpp"

using namespace Railway;
using namespace std::chrono_literals;

/**
 * @brief Programme principal de démonstration
 * @safety_level SIL4
 * @requirement REQ_DEMO_001
 */
class SignalDemo {
   public:
    SignalDemo() : signal_("SIGNAL_DEMO_001") {
        // Configuration du handler pour les changements d'aspect
        signal_.aspectChanged.connect([](Aspect aspect) {
            std::cout << "Signal aspect changed to: "
                      << aspectToString(aspect) << std::endl;
        });
    }

    void run() {
        std::cout << "Starting Railway Signal Demo\n";
        std::cout << "Initial aspect: " << aspectToString(signal_.getAspect()) << "\n";

        // Démonstration des commandes et de leur réversibilité
        try {
            std::cout << "\nDémonstration des commandes et de leur réversibilité:\n";

            // Transition vers jaune
            std::cout << "\nChanging to YELLOW...\n";
            auto yellowCmd = std::make_unique<ChangeAspectCommand>(
                signal_, Aspect::YELLOW);
            signal_.executeCommand(std::move(yellowCmd));
            std::this_thread::sleep_for(2s);

            // Transition vers vert
            std::cout << "\nChanging to GREEN...\n";
            auto greenCmd = std::make_unique<ChangeAspectCommand>(
                signal_, Aspect::GREEN);
            signal_.executeCommand(std::move(greenCmd));
            std::this_thread::sleep_for(2s);

            // Démonstration de l'annulation
            std::cout << "\nUndoing last command (should return to YELLOW)...\n";
            signal_.undoLastCommand();
            std::this_thread::sleep_for(2s);

            // Démonstration de la réexécution
            std::cout << "\nRedoing command (should return to GREEN)...\n";
            signal_.redoCommand();
            std::this_thread::sleep_for(2s);

            // Retour à rouge pour la sécurité
            std::cout << "\nReturning to RED (safety state)...\n";
            auto redCmd = std::make_unique<ChangeAspectCommand>(
                signal_, Aspect::RED);
            signal_.executeCommand(std::move(redCmd));

        } catch (const std::exception& e) {
            std::cerr << "Error during demo: " << e.what() << std::endl;
            // En cas d'erreur, on s'assure de revenir à l'état sûr (rouge)
            signal_.setAspect(Aspect::RED);
        }
    }

   private:
    static std::string aspectToString(Aspect aspect) {
        switch (aspect) {
            using enum Railway::Aspect;

            case RED:
                return "RED";
            case YELLOW:
                return "YELLOW";
            case Aspect::GREEN:
                return "GREEN";
            default:
                return "UNKNOWN";
        }
    }

    RailwaySignal signal_;
};

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
