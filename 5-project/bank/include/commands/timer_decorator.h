#pragma once
#include "command.h"
#include <memory>
#include <chrono>

class TimerDecorator : public Command {
public:
    explicit TimerDecorator(std::unique_ptr<Command> cmd);
    void Do() override {
        auto start = std::chrono::system_clock::now();
        m_command->Do();
        // std::cout << "elased " << std::chrono::system_clock::now() - start;
    }
    void Undo() override;

private:
    std::unique_ptr<Command> m_command;
};
