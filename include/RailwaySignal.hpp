#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <exception>
#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "RailwayTypes.hpp"
#include "SignalCommand.hpp"

namespace Railway {

// Forward declarations
class SignalCommand;
class SignalState;

/**
 * @brief Classe principale du signal ferroviaire
 * @safety_level SIL4
 * @requirement REQ_SIGNAL_001
 */
class RailwaySignal {
   public:
    explicit RailwaySignal(const std::string& id);
    ~RailwaySignal();

    /**
     * @brief Change l'aspect du signal
     * @safety_requirement SR_SIGNAL_001
     * @param aspect Nouvel aspect du signal
     * @return std::expected contenant le succès ou l'erreur
     */
    std::expected<void, std::string> setAspect(Aspect aspect);

    /**
     * @brief Obtient l'aspect actuel du signal
     * @safety_requirement SR_SIGNAL_002
     * @return Aspect actuel
     */
    Aspect getAspect() const;

    void executeCommand(std::unique_ptr<SignalCommand> command);
    void undoLastCommand();
    void redoCommand();

    // Signal pour la notification de changement d'état
    boost::signals2::signal<void(Aspect)> aspectChanged;

   private:
    std::string                                 id_;
    Aspect                                      currentAspect_;
    std::vector<std::unique_ptr<SignalCommand>> commandHistory_;
    size_t                                      currentCommandIndex_;
    boost::asio::io_context                     ioContext_;
    std::unique_ptr<SignalState>                state_;
};

}  // namespace Railway
