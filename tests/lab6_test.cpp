#include "lab6.h"
#include <gtest/gtest.h>
#include <memory>
#include <sstream>

TEST(NPCTest, Creation) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>("Grizzly", 5, 5);
    std::shared_ptr<NPC> bittern = std::make_shared<Bittern>("Bitty", 10, 10);
    std::shared_ptr<NPC> desman = std::make_shared<Desman>("Desy", 15, 15);

    EXPECT_EQ(bear->getType(), "B");
    EXPECT_EQ(bear->getName(), "Grizzly");
    EXPECT_EQ(bear->getX(), 5);
    EXPECT_EQ(bear->getY(), 5);

    EXPECT_EQ(bittern->getType(), "I");
    EXPECT_EQ(desman->getType(), "D");
}

TEST(NPCTest, CanFight) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>("Grizzly", 5, 5);
    std::shared_ptr<NPC> desman = std::make_shared<Desman>("Desy", 15, 15);
    std::shared_ptr<NPC> bittern = std::make_shared<Bittern>("Bitty", 10, 10);

    // Bear дерется со всеми, кроме таких же bear
    EXPECT_TRUE(bear->canFight(*desman));
    EXPECT_FALSE(bear->canFight(*bittern));

    // Desman дерется только с Bear
    EXPECT_TRUE(desman->canFight(*bear));
    EXPECT_FALSE(desman->canFight(*bittern));

    // Bittern не дерется ни с кем
    EXPECT_FALSE(bittern->canFight(*bear));
    EXPECT_FALSE(bittern->canFight(*desman));
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    editor.addNPC(std::make_shared<Bear>("Grizzly", 5, 5));
    editor.addNPC(std::make_shared<Bittern>("Bitty", 10, 10));
    editor.addNPC(std::make_shared<Desman>("Desy", 15, 15));

    editor.saveToFile("test_npcs.txt");

    DungeonEditor newEditor;
    newEditor.loadFromFile("test_npcs.txt");

    testing::internal::CaptureStdout();
    newEditor.printAll();
    std::string result = testing::internal::GetCapturedStdout();

    // Проверяем, что все NPC загрузились корректно
    EXPECT_NE(result.find("B Grizzly (5, 5)"), std::string::npos);
    EXPECT_NE(result.find("I Bitty (10, 10)"), std::string::npos);
    EXPECT_NE(result.find("D Desy (15, 15)"), std::string::npos);
}

TEST(ObserverTest, Notify) {
    DungeonEditor editor;

    std::shared_ptr<Observer> consoleObserver = std::make_shared<ConsoleObserver>();
    std::shared_ptr<Observer> fileObserver = std::make_shared<FileObserver>("test_events.log");

    editor.addObserver(consoleObserver);
    editor.addObserver(fileObserver);

    // Проверяем, что уведомления не выбрасывают исключений
    EXPECT_NO_THROW(editor.notifyObservers("Test event"));
}