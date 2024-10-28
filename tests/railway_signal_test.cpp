// Fichier: tests/railway_signal_test.cpp
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

/**
 * @brief Test de changement d'aspect
 * @safety_requirement SR_TEST_001
 */
TEST_F(RailwaySignalTest, AspectChange) {
    // Arrange
    auto initialAspect = signal->getAspect();
    ASSERT_EQ(initialAspect, RailwaySignal::Aspect::RED);

    // Act
    auto result = signal->setAspect(RailwaySignal::Aspect::GREEN);

    // Assert
    ASSERT_TRUE(result);
    ASSERT_EQ(signal->getAspect(), RailwaySignal::Aspect::GREEN);
}

/**
 * @brief Test de commande et d'annulation
 * @safety_requirement SR_TEST_002
 */
TEST_F(RailwaySignalTest, CommandUndoRedo) {
    // Arrange
    auto command = std::make_unique<ChangeAspectCommand>(*signal, RailwaySignal::Aspect::GREEN);

    // Act
    signal->executeCommand(std::move(command));
    ASSERT_EQ(signal->getAspect(), RailwaySignal::Aspect::GREEN);

    // Undo
    signal->undoLastCommand();
    ASSERT_EQ(signal->getAspect(), RailwaySignal::Aspect::RED);

    // Redo
    signal->redoCommand();
    ASSERT_EQ(signal->getAspect(), RailwaySignal::Aspect::GREEN);
}

} // namespace Railway::Test
