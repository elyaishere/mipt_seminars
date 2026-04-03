#pragma once

class Command {
public:
    virtual ~Command() = default;
    virtual void Do() = 0;
    virtual void Undo() = 0;
};
