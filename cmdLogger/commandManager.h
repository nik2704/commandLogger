#pragma once
#include <cassert>
#include <iostream>
#include <string>
#include "commandBlock.h"
#include "commandBlockQueue.h"


/**
 * @brief Структура IndexInfo хранит информацию об индексе блока и команды.
 */
struct IndexInfo {
    size_t blockIndex;
    size_t commandIndex;
};

/**
 * @brief Класс CommandManager управляет блоками команд в очереди.
 */
class CommandManager {
public:
    /**
     * @brief Получить новый индекс для блока.
     * 
     * @return size_t Индекс нового блока.
     */
    size_t getNewBlockIndex();

    /**
     * @brief Деактивировать блок команд.
     * 
     * @param blockIndex Индекс блока для деактивации.
     */
    void deactivateBlock(size_t blockIndex);

    /**
     * @brief Логировать предыдущий статический блок.
     * 
     * @param blockIndex Индекс текущего блока.
     */
    void logPreviosStaticBlock(size_t blockIndex);

    /**
     * @brief Добавить команду в блок.
     * 
     * @param blockIndex Индекс блока.
     * @param command_text Текст команды.
     * @param isDynamic Флаг динамической команды.
     * @return IndexInfo Структура с индексами блока и команды.
     */    
    IndexInfo addCommandToBlock(size_t blockIndex, const std::string& command_text, bool isDynamic);

    /**
     * @brief Логировать очередь команд.
     */
    void logCommandQueue();

    /**
     * @brief Проверить, пуст ли блок команд.
     * 
     * @param blockIndex Индекс блока для проверки.
     * @return bool Возвращает true, если блок пуст, иначе false.
     */
    bool isBlockEmpty(size_t blockIndex) const;

private:
    CommandBlockQueue commandQueue_; /**< Очередь блоков команд. */
};
