#include <iostream>
#include <string>
#include "../cmdLogger/commandManager.h"
#include "commandReader.h"


CommandReader::CommandReader(size_t block_size) : block_size_(block_size), currentBlockIndex_(0), step_(0), commandManager_() {
    if (block_size_ == 0) {
        throw std::invalid_argument("Размер блока команд должен быть больше 0");
    }
}

void CommandReader::execute() {
    for (size_t i = 0; i < block_size_; ++i) {
        readCommand(false);
    }
    commandManager_.logCommandQueue();
}

bool CommandReader::readCommand(bool isDynamic) {
    std::string line;

    if (!std::getline(std::cin, line)) {
        commandManager_.deactivateDynamicBlock(currentBlockIndex_);
        return false;
    }

    if (line == "}") {
        currentBlockIndex_ = commandManager_.getNewBlockIndex();
        return false;
    }

    if (line == "{") {
        currentBlockIndex_ = commandManager_.getNewBlockIndex();
        commandManager_.logPreviosStaticBlock(currentBlockIndex_);
        while (readCommand(true)) {}
    } else {
        commandManager_.addCommandToBlock(currentBlockIndex_, line, isDynamic);
        ++step_;
    }

    return true;
}
