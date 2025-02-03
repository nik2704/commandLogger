#pragma once
#include <optional>
#include <queue>


/**
 * @brief Класс CommandBlockQueue представляет очередь блоков команд.
 * 
 */
class CommandBlockQueue {
public:
    using iterator = std::deque<CommandBlock>::iterator; /**< Тип итератора для блока команд. */
    using const_iterator = std::deque<CommandBlock>::const_iterator; /**< Тип константного итератора для блока команд. */

    /**
     * @brief Оператор присваивания удален.
     * 
     */
    CommandBlockQueue& operator=(const CommandBlockQueue&) = delete;

    /**
     * @brief Добавить блок команд в очередь.
     * 
     * @param block Блок команд для добавления.
     * @return size_t Индекс добавленного блока.
     */
    size_t addBlock(const CommandBlock& block);

    /**
     * @brief Получить блок команд по индексу.
     * 
     * @param index Индекс блока команд.
     * @return std::optional<std::reference_wrapper<CommandBlock>> Опциональная ссылка на блок команд.
     */
    std::optional<std::reference_wrapper<CommandBlock>> getBlockAtIndex(std::size_t index);

    /**
     * @brief Получить блок команд по индексу (константный).
     * 
     * @param index Индекс блока команд.
     * @return std::optional<std::reference_wrapper<const CommandBlock>> Константная опциональная ссылка.
     */
    std::optional<std::reference_wrapper<const CommandBlock>> getBlockAtIndex(std::size_t index) const;

    /**
     * @brief Удалить блок команд по индексу.
     * 
     * @param index Индекс блока команд для удаления.
     */
    void deleteBlockByIndex(std::size_t index);

    /**
     * @brief Деактивировать динамический блок команд по индексу.
     * 
     * @param index Индекс блока команд для деактивации.
     */
    void deactivateBlock(std::size_t index);

    /**
     * @brief Проверить, пуста ли очередь блоков.
     * 
     * @return bool Возвращает true, если очередь пуста, иначе false.
     */
    bool isEmpty() const;

    /**
     * @brief Получить количество блоков в очереди.
     * 
     * @return std::size_t Количество блоков в очереди.
     */
    std::size_t Size() const;

    /**
     * @brief Получить количество активных блоков в очереди.
     * 
     * @return std::size_t Количество активных блоков в очереди.
     */
    std::size_t getActiveBlockCount() const;
    /**
     * @brief Получить индекс последнего блока в очереди.
     * 
     * @return std::size_t Индекс последнего блока.
     */
    std::size_t getLasBlocktIndex() const;

    /**
     * @brief Получить итератор на начало очереди блоков.
     * 
     * @return iterator Итератор на начало очереди блоков.
     */
    iterator begin();

    /**
     * @brief Получить итератор на конец очереди блоков.
     * 
     * @return iterator Итератор на конец очереди блоков.
     */
    iterator end();

    /**
     * @brief Получить константный итератор на начало очереди блоков.
     * 
     * @return const_iterator Константный итератор на начало очереди блоков.
     */
    const_iterator begin() const;

    /**
     * @brief Получить константный итератор на конец очереди блоков.
     * 
     * @return const_iterator Константный итератор на конец очереди блоков.
     */
    const_iterator end() const;

    // std::size_t getStartOutputIndex() const;
    /**
     * @brief Перегрузка оператора вывода для очереди блоков.
     * 
     * @param os Поток вывода.
     * @param queue Объект очереди блоков команд.
     * @return std::ostream& Поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const CommandBlockQueue& queue) {
        bool start = true;

        for (auto it = queue.begin(); it < queue.end(); ++it) {
            if (!start) {
                os << ", ";
            } else {
                start = false;
            }

            os << (*it);
        }

        os << std::endl;
        
        return os;
    }

private:
    std::deque<CommandBlock> blocks_; /**< Очередь блоков команд. */
    // mutable std::size_t start_output_index_ = 0; /**< Индекс последнего выведенного блока. */
};
