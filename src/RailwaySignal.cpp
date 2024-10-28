#include "RailwaySignal.hpp"
#include "SignalState.hpp"

#include <stdexcept>
#include <format>

namespace Railway {

RailwaySignal::RailwaySignal(const std::string& id)
    : id_(id)
    , currentAspect_(Aspect::RED)  // État initial sûr
    , currentCommandIndex_(0) {
    // Initialisation de l'état
    state_ = std::make_unique<RedState>();
}

RailwaySignal::~RailwaySignal() = default;

std::expected<void, std::string> RailwaySignal::setAspect(Aspect aspect) {
    // Vérification de la validité de la transition
    if (!state_->canTransitionTo(aspect)) {
        return std::unexpected(
            std::format("Invalid transition from {} to {} for signal {}", 
                static_cast<int>(currentAspect_), 
                static_cast<int>(aspect), 
                id_)
        );
    }

    // Mise à jour de l'état
    try {
        Aspect oldAspect = currentAspect_;
        currentAspect_ = aspect;

        // Mise à jour de l'état interne
        switch (aspect) {
            case Aspect::RED:
                state_ = std::make_unique<RedState>();
                break;
            case Aspect::YELLOW:
                state_ = std::make_unique<YellowState>();
                break;
            case Aspect::GREEN:
                state_ = std::make_unique<GreenState>();
                break;
        }

        // Vérification post-transition
        state_->update();

        // Notification du changement d'état
        aspectChanged(aspect);

        return {};
    } catch (const std::exception& e) {
        // En cas d'erreur, retour à l'état sûr
        currentAspect_ = Aspect::RED;
        state_ = std::make_unique<RedState>();
        return std::unexpected(
            std::format("Error during aspect change: {}", e.what())
        );
    }
}

Aspect RailwaySignal::getAspect() const {
    return currentAspect_;
}

void RailwaySignal::executeCommand(std::unique_ptr<SignalCommand> command) {
    if (!command) {
        throw std::invalid_argument("Command cannot be null");
    }

    // Supprimer toutes les commandes après l'index courant
    while (commandHistory_.size() > currentCommandIndex_) {
        commandHistory_.pop_back();
    }

    // Exécuter la nouvelle commande
    command->execute();

    // Ajouter au historique
    commandHistory_.push_back(std::move(command));
    currentCommandIndex_++;
}

void RailwaySignal::undoLastCommand() {
    if (currentCommandIndex_ == 0) {
        throw std::runtime_error("No command to undo");
    }

    currentCommandIndex_--;
    commandHistory_[currentCommandIndex_]->undo();
}

void RailwaySignal::redoCommand() {
    if (currentCommandIndex_ >= commandHistory_.size()) {
        throw std::runtime_error("No command to redo");
    }

    commandHistory_[currentCommandIndex_]->execute();
    currentCommandIndex_++;
}

} // namespace Railway
