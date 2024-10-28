#pragma once

#include "RailwayTypes.hpp"
#include <memory>
#include <stdexcept>

namespace Railway {

// Forward declarations
class RailwaySignal;

class SignalCommand {
public:
    virtual ~SignalCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class ChangeAspectCommand : public SignalCommand {
public:
    ChangeAspectCommand(RailwaySignal& signal, Aspect aspect);
    void execute() override;
    void undo() override;

private:
    RailwaySignal& signal_;
    Aspect newAspect_;
    Aspect previousAspect_;
};

} // namespace Railway
