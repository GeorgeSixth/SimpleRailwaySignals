#pragma once

#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include <expected>
#include <memory>
#include <string>
#include <vector>

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
    enum class Aspect {
        RED,    ///< Signal fermé
        GREEN,  ///< Signal ouvert
        YELLOW  ///< Signal à vitesse limitée
    };

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

    /**
     * @brief Exécute une commande sur le signal
     * @safety_requirement SR_SIGNAL_003
     * @param command Commande à exécuter
     */
    void executeCommand(std::unique_ptr<SignalCommand> command);

    /**
     * @brief Annule la dernière commande
     * @safety_requirement SR_SIGNAL_004
     */
    void undoLastCommand();

    /**
     * @brief Réexécute la dernière commande annulée
     * @safety_requirement SR_SIGNAL_005
     */
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
