#include <gtest/gtest.h>
#include <type_traits>
#include "stackTask1.h" // Подключаем реализацию из задания 1
#include "stackTask2.h" // Подключаем реализацию из задания 2

// Тестовый некопируемый, но перемещаемый тип
class MoveOnly {
public:
    int value;

    explicit MoveOnly(int v) : value(v) {}

    // Удаляем конструктор копирования
    MoveOnly(const MoveOnly&) = delete;

    // Удаляем оператор присваивания копированием
    MoveOnly& operator=(const MoveOnly&) = delete;

    // Конструктор перемещения
    MoveOnly(MoveOnly&& other) noexcept : value(other.value) {
        other.value = 0;
    }

    // Оператор присваивания перемещением
    MoveOnly& operator=(MoveOnly&& other) noexcept {
        if (this != &other) {
            value = other.value;
            other.value = 0;
        }
        return *this;
    }
};

// Тесты для задания 1
TEST(StackTask1Test, BasicFunctionality) {
    Stack<int> stack;

    // Проверка пустого стека
    EXPECT_TRUE(stack.empty());

    // Добавление элементов
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // Проверка верхнего элемента
    EXPECT_EQ(stack.head(), 3);

    // Удаление элемента
    stack.pop();
    EXPECT_EQ(stack.head(), 2);

    // Очистка стека
    stack.pop();
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(StackTask1Test, MoveSemantics) {
    // Проверка, что класс является перемещаемым
    EXPECT_TRUE(std::is_move_constructible_v<Stack<int>>);
    EXPECT_TRUE(std::is_move_assignable_v<Stack<int>>);

    // Проверка, что класс не является копируемым
    EXPECT_FALSE(std::is_copy_constructible_v<Stack<int>>);
    EXPECT_FALSE(std::is_copy_assignable_v<Stack<int>>);

    // Проверка перемещения
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    Stack<int> stack2 = std::move(stack1); // Перемещение
    EXPECT_EQ(stack2.head(), 2);
    EXPECT_TRUE(stack1.empty()); // stack1 должен быть пуст после перемещения
}

// Тесты для задания 2
TEST(StackTask2Test, BasicFunctionality) {
    LinkedStack<MoveOnly> stack;

    // Проверка пустого стека
    EXPECT_TRUE(stack.empty());

    // Добавление элементов с помощью push_emplace
    stack.push_emplace(1);
    stack.push_emplace(2);
    stack.push_emplace(3);

    // Проверка верхнего элемента
    EXPECT_EQ(stack.head().value, 3);

    // Удаление элемента
    MoveOnly popped = stack.pop();
    EXPECT_EQ(popped.value, 3);
    EXPECT_EQ(stack.head().value, 2);

    // Очистка стека
    stack.pop();
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(StackTask2Test, MoveSemantics) {
    // Проверка, что класс является перемещаемым
    EXPECT_TRUE(std::is_move_constructible_v<LinkedStack<MoveOnly>>);
    EXPECT_TRUE(std::is_move_assignable_v<LinkedStack<MoveOnly>>);

    // Проверка, что класс не является копируемым
    EXPECT_FALSE(std::is_copy_constructible_v<LinkedStack<MoveOnly>>);
    EXPECT_FALSE(std::is_copy_assignable_v<LinkedStack<MoveOnly>>);

    // Проверка перемещения
    LinkedStack<MoveOnly> stack1;
    stack1.push_emplace(1);
    stack1.push_emplace(2);

    LinkedStack<MoveOnly> stack2 = std::move(stack1); // Перемещение
    EXPECT_EQ(stack2.head().value, 2);
    EXPECT_TRUE(stack1.empty()); // stack1 должен быть пуст после перемещения
}

TEST(StackTask2Test, PushEmplace) {
    LinkedStack<MoveOnly> stack;

    // Добавление элемента с помощью push_emplace
    stack.push_emplace(42);
    EXPECT_EQ(stack.head().value, 42);

    // Добавление другого элемента
    stack.push_emplace(100);
    EXPECT_EQ(stack.head().value, 100);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
