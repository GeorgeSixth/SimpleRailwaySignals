#include "SignalState.hpp"

#include <chrono>
#include <stdexcept>

namespace Railway {

// RedState
void RedState::update() {
    // Vérification de la sécurité pour l'état rouge
    // Dans un système réel, on vérifierait les capteurs, etc.
}

bool RedState::canTransitionTo(RailwaySignal::Aspect aspect) {
    // Depuis rouge, on ne peut aller qu'à jaune
    return aspect == RailwaySignal::Aspect::YELLOW;
}

// YellowState
void YellowState::update() {
    // Vérification des conditions pour l'état jaune
    // Dans un système réel, vérification des temporisations, etc.
}

bool YellowState::canTransitionTo(RailwaySignal::Aspect aspect) {
    // Depuis jaune, on peut aller soit à rouge soit à vert
    return aspect == RailwaySignal::Aspect::RED || 
           aspect == RailwaySignal::Aspect::GREEN;
}

// GreenState
void GreenState::update() {
    // Vérification des conditions pour l'état vert
    // Dans un système réel, vérification des circuits de voie, etc.
}

bool GreenState::canTransitionTo(RailwaySignal::Aspect aspect) {
    // Depuis vert, on ne peut aller qu'à jaune ou rouge (urgence)
    return aspect == RailwaySignal::Aspect::YELLOW || 
           aspect == RailwaySignal::Aspect::RED;
}

// SafetyTimer implementation
SafetyTimer::SafetyTimer(std::chrono::milliseconds timeout)
    : timeout_(timeout)
    , start_(std::chrono::steady_clock::now()) {}

bool SafetyTimer::hasExpired() const {
    auto now = std::chrono::steady_clock::now();
    return (now - start_) > timeout_;
}

void SafetyTimer::reset() {
    start_ = std::chrono::steady_clock::now();
}

// StateValidator implementation
bool StateValidator::validateTransition(
    RailwaySignal::Aspect from, 
    RailwaySignal::Aspect to
) {
    // Matrice de transition
    static const bool transitionMatrix[3][3] = {
        // TO:   RED    YELLOW  GREEN
        /* FROM RED */    
        {       false,  true,   false  },
        /* FROM YELLOW */
        {       true,   false,  true   },
        /* FROM GREEN */
        {       true,   true,   false  }
    };

    int fromIndex = static_cast<int>(from);
    int toIndex = static_cast<int>(to);

    if (fromIndex < 0 || fromIndex > 2 || toIndex < 0 || toIndex > 2) {
        throw std::invalid_argument("Invalid aspect value");
    }

    return transitionMatrix[fromIndex][toIndex];
}

} // namespace Railway
