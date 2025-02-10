#include <iostream>
#include <string>
#include "../cmdLogger/commandManager.h"
#include "commandReader.h"


CommandReader::CommandReader(size_t block_size) : block_size_(block_size), currentBlockIndex_(0), commandManager_(), level_(0) {
    if (block_size_ == 0) {
        throw std::invalid_argument("Размер блока команд должен быть больше 0");
    }
}

void CommandReader::execute() {
    while (true) {
        for (size_t i = 0; i < block_size_; ++i) {
            if (!readCommand(false, i % block_size_ == 0)) {
                break;
            }
        }
        
        commandManager_.logCommandQueue();
    }
}

bool CommandReader::readCommand(bool isDynamic, bool startIteration) {
    std::string line;

    if (!std::getline(std::cin, line) || line.empty()) {
        commandManager_.logPreviosStaticBlock(currentBlockIndex_);
        return false;
    }

    if (line == "{" || line == "}" || startIteration) {
        currentBlockIndex_ = commandManager_.getNewBlockIndex();
    }

    if (line == "}") {
        --level_;

        if (level_ == 0) {
            commandManager_.logCommandQueue();
        }

        return false;
    }

    if (line == "{") {
        ++level_;

        commandManager_.logPreviosStaticBlock(currentBlockIndex_);

        while (readCommand(true, startIteration)) {
            startIteration = false;
        }
    } else {
        commandManager_.addCommandToBlock(currentBlockIndex_, line, isDynamic);
    } 


    return true;
}
