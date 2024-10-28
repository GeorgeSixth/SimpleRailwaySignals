#include <gtest/gtest.h>
#include "RailwaySignal.hpp"
#include "SignalCommand.hpp"

namespace Railway::Test {

class RailwaySignalTest : public ::testing::Test {
protected:
    void SetUp() override {
        signal = std::make_unique<RailwaySignal>("TEST_SIGNAL_001");
    }

    void TearDown() override {
        signal.reset();
    }

    std::unique_ptr<RailwaySignal> signal;
};

TEST_F(RailwaySignalTest, AspectChange) {
    // Arrange
    auto initialAspect = signal->getAspect();
    ASSERT_EQ(initialAspect, Aspect::RED);

    // Act
    auto result = signal->setAspect(Aspect::YELLOW);

    // Assert
    ASSERT_TRUE(result);
    ASSERT_EQ(signal->getAspect(), Aspect::YELLOW);
}

TEST_F(RailwaySignalTest, CommandUndoRedo) {
    // Arrange
    auto command = std::make_unique<ChangeAspectCommand>(*signal, Aspect::YELLOW);

    // Act & Assert
    ASSERT_EQ(signal->getAspect(), Aspect::RED);
    
    // Execute
    signal->executeCommand(std::move(command));
    ASSERT_EQ(signal->getAspect(), Aspect::YELLOW);

    // Undo
    signal->undoLastCommand();
    ASSERT_EQ(signal->getAspect(), Aspect::RED);

    // Redo
    signal->redoCommand();
    ASSERT_EQ(signal->getAspect(), Aspect::YELLOW);
}

TEST_F(RailwaySignalTest, InvalidTransition) {
    // Arrange & Act
    auto result = signal->setAspect(Aspect::GREEN);

    // Assert
    ASSERT_FALSE(result);
    ASSERT_EQ(signal->getAspect(), Aspect::RED);
}

} // namespace Railway::Test
