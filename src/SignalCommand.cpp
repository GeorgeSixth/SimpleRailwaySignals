#include "SignalCommand.hpp"
#include "RailwaySignal.hpp"

namespace Railway {

ChangeAspectCommand::ChangeAspectCommand(RailwaySignal& signal, Aspect aspect)
    : signal_(signal), newAspect_(aspect), previousAspect_(signal.getAspect()) 
{}

void ChangeAspectCommand::execute() {
    previousAspect_ = signal_.getAspect();
    auto result = signal_.setAspect(newAspect_);
    if (!result) {
        throw std::runtime_error(result.error());
    }
}

void ChangeAspectCommand::undo() {
    auto result = signal_.setAspect(previousAspect_);
    if (!result) {
        throw std::runtime_error(result.error());
    }
}

} // namespace Railway
