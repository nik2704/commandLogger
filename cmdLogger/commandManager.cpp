#include <cassert>
#include <iostream>
#include <string>
#include "commandBlock.h"
#include "commandBlockQueue.h"
#include "commandManager.h"


size_t CommandManager::getNewBlockIndex() {
    return commandQueue_.Size();
}

void CommandManager::deactivateBlock(size_t blockIndex) {
    commandQueue_.deactivateBlock(blockIndex);
}

void CommandManager::logPreviosStaticBlock(size_t blockIndex) {
    if (blockIndex > 0) {
        size_t staticBlockIndex = blockIndex - 1;
        auto block_opt = commandQueue_.getBlockAtIndex(staticBlockIndex);

        if (block_opt.has_value()) {
            auto& block = block_opt->get();
            if (!block.isDynamic() && block.isActive()) {
                std::cout << "bulk: " << block << std::endl;
                block.deactivate();
            }
        }
    }
}

IndexInfo CommandManager::addCommandToBlock(size_t blockIndex, const std::string& command_text, bool isDynamic) {

    Command command(command_text);
    IndexInfo result{blockIndex, 0};

    if (blockIndex < (commandQueue_.Size() - 1)) {
        blockIndex = commandQueue_.Size();
    }

    if (blockIndex == commandQueue_.Size()) {

        CommandBlock commandBlock(isDynamic);

        result.commandIndex = commandBlock.AddCommand(command);
        result.blockIndex = commandQueue_.addBlock(commandBlock);

        return result;
    }

    auto block_opt = commandQueue_.getBlockAtIndex(blockIndex);
    
    assert(block_opt.has_value());

    result.commandIndex = block_opt.value().get().AddCommand(command);
    return result;
}

void CommandManager::logCommandQueue() {
    if (commandQueue_.getActiveBlockCount() > 0) {
        bool start = true;
        std::cout << "bulk: ";

        for (auto it = commandQueue_.begin(); it != commandQueue_.end(); ++it) {
            if (it->isActive()) {
                if (!start) {
                    std::cout << ", ";
                }

                std::cout << (*it);
                it->deactivate();
                start = false;
            }
        }

        std::cout << std::endl;
    }
}

bool CommandManager::isBlockEmpty(size_t blockIndex) const {
    const auto block_opt = commandQueue_.getBlockAtIndex(blockIndex);

    assert(block_opt.has_value());

    return block_opt.value().get().isEmpty();
}
