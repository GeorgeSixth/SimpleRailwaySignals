#pragma once

#include "RailwaySignal.hpp"

namespace Railway {

/**
 * @brief Interface de base pour les commandes de signal
 * @safety_level SIL4
 * @requirement REQ_CMD_001
 */
class SignalCommand {
   public:
    virtual ~SignalCommand() = default;

    /**
     * @brief Exécute la commande
     * @safety_requirement SR_CMD_001
     */
    virtual void execute() = 0;

    /**
     * @brief Annule la commande
     * @safety_requirement SR_CMD_002
     */
    virtual void undo() = 0;
};

/**
 * @brief Commande pour changer l'aspect d'un signal
 * @safety_level SIL4
 * @requirement REQ_CMD_002
 */
class ChangeAspectCommand : public SignalCommand {
   public:
    ChangeAspectCommand(RailwaySignal& signal, RailwaySignal::Aspect newAspect)
        : signal_(signal), newAspect_(newAspect), previousAspect_(signal.getAspect()) {}

    void execute() override {
        previousAspect_ = signal_.getAspect();
        auto result = signal_.setAspect(newAspect_);
        if (!result) {
            throw std::runtime_error(result.error());
        }
    }

    void undo() override {
        auto result = signal_.setAspect(previousAspect_);
        if (!result) {
            throw std::runtime_error(result.error());
        }
    }

   private:
    RailwaySignal&        signal_;
    RailwaySignal::Aspect newAspect_;
    RailwaySignal::Aspect previousAspect_;
};

}  // namespace Railway
