#include <optional>
#include <queue>
#include "commandBlock.h"
#include "commandBlockQueue.h"


size_t CommandBlockQueue::addBlock(const CommandBlock& block) {
    blocks_.push_back(block);
    return blocks_.size() - 1;
}

std::optional<std::reference_wrapper<CommandBlock>> CommandBlockQueue::getBlockAtIndex(std::size_t index) {
    if (index < blocks_.size()) {
        return std::ref(blocks_[index]);
    } else {
        return std::nullopt;
    }
}

std::optional<std::reference_wrapper<const CommandBlock>> CommandBlockQueue::getBlockAtIndex(std::size_t index) const {
    if (index < blocks_.size()) {
        return std::cref(blocks_[index]);
    } else {
        return std::nullopt;
    }
}

void CommandBlockQueue::deleteBlockByIndex(std::size_t index) {
    if (index < blocks_.size()) {
        auto it = blocks_.begin() + index;
        blocks_.erase(it);
    }
}

void CommandBlockQueue::deactivateBlock(std::size_t index) {
    if (index < blocks_.size()) {
        blocks_[index].deactivate();
    }
}

bool CommandBlockQueue::isEmpty() const {
    return blocks_.empty();
}

std::size_t CommandBlockQueue::Size() const {
    return blocks_.size();
}

std::size_t CommandBlockQueue::getActiveBlockCount() const  {
    std::size_t res = 0;

    if (begin() < end()) {
        for (auto it = begin(); it < end(); ++it ) {
            if ((*it).isActive()) {
                ++res;
            }
        }
    }

    return res;
}

std::size_t CommandBlockQueue::getLasBlocktIndex() const {
    return blocks_.size() - 1;
}

CommandBlockQueue::iterator CommandBlockQueue::begin() {
    return blocks_.begin();
}

CommandBlockQueue::iterator CommandBlockQueue::end() {
    return blocks_.end();
}

CommandBlockQueue::const_iterator CommandBlockQueue::begin() const {
    return blocks_.begin();
}

CommandBlockQueue::const_iterator CommandBlockQueue::end() const {
    return blocks_.end();
}

//  std::size_t CommandBlockQueue::getStartOutputIndex() const {
//     return start_output_index_;
//  }