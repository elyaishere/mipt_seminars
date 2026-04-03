#pragma once
#include <stack>
#include <memory>

class Command;

class CommandManager {
public:
    void Do(std::unique_ptr<Command> command);
    void Undo();

private:
    std::stack<std::unique_ptr<Command>> m_history;
};
