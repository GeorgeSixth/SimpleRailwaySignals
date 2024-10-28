#pragma once

#include "RailwaySignal.hpp"

#include <chrono>

namespace Railway {

class SignalState {
public:
    virtual ~SignalState() = default;
    virtual void update() = 0;
    virtual bool canTransitionTo(RailwaySignal::Aspect aspect) = 0;
};

class RedState : public SignalState {
public:
    void update() override;
    bool canTransitionTo(RailwaySignal::Aspect aspect) override;
};

class YellowState : public SignalState {
public:
    void update() override;
    bool canTransitionTo(RailwaySignal::Aspect aspect) override;
};

class GreenState : public SignalState {
public:
    void update() override;
    bool canTransitionTo(RailwaySignal::Aspect aspect) override;
};

// Classe utilitaire pour gérer les timeouts de sécurité
class SafetyTimer {
public:
    explicit SafetyTimer(std::chrono::milliseconds timeout);
    bool hasExpired() const;
    void reset();

private:
    std::chrono::milliseconds timeout_;
    std::chrono::steady_clock::time_point start_;
};

// Classe utilitaire pour la validation des transitions
class StateValidator {
public:
    static bool validateTransition(RailwaySignal::Aspect from, RailwaySignal::Aspect to);
};

} // namespace Railway
