#include "SignalDemo.hpp"

using namespace std::chrono_literals;

SignalDemo::SignalDemo() {
    // Configuration du handler pour les changements d'aspect
    signal_.aspectChanged.connect([](Railway::Aspect aspect) {
        std::cout << "Signal aspect changed to: " << aspectToString(aspect) << std::endl;
    });
}

void SignalDemo::run() {
    std::cout << "Starting Railway Signal Demo\nInitial aspect: " << aspectToString(signal_.getAspect()) << "\n";

    // Démonstration des commandes et de leur réversibilité
    try {
        std::cout << "\nDémonstration des commandes et de leur réversibilité:\n";

        // Transition vers jaune
        std::cout << "\nChanging to YELLOW...\n";
        auto yellowCmd = std::make_unique<Railway::ChangeAspectCommand>(signal_, Railway::Aspect::YELLOW);
        signal_.executeCommand(std::move(yellowCmd));
        std::this_thread::sleep_for(2s);

        // Transition vers vert
        std::cout << "\nChanging to GREEN...\n";
        auto greenCmd = std::make_unique<Railway::ChangeAspectCommand>(signal_, Railway::Aspect::GREEN);
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
        auto redCmd = std::make_unique<Railway::ChangeAspectCommand>(signal_, Railway::Aspect::RED);
        signal_.executeCommand(std::move(redCmd));

    } catch (const std::exception& e) {
        std::cerr << "Error during demo: " << e.what() << std::endl;
        // En cas d'erreur, on s'assure de revenir à l'état sûr (rouge)
        signal_.setAspect(Railway::Aspect::RED);
    }
}
