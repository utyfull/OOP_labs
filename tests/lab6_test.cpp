#include "lab6.h"
#include <gtest/gtest.h>

TEST(NPCTest, Creation) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>("Grizzly", 5, 5);
    std::shared_ptr<NPC> bittern = std::make_shared<Bittern>("Bittern", 10, 10);
    std::shared_ptr<NPC> desman = std::make_shared<Desman>("Desman", 15, 15);

    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(bear->getName(), "Grizzly");
    EXPECT_EQ(bear->getX(), 5);
    EXPECT_EQ(bear->getY(), 5);

    EXPECT_EQ(bittern->getType(), "Bittern");
    EXPECT_EQ(desman->getType(), "Desman");
}

TEST(NPCTest, CanFight) {
    std::shared_ptr<NPC> bear = std::make_shared<Bear>("Grizzly", 5, 5);
    std::shared_ptr<NPC> desman = std::make_shared<Desman>("Desman", 15, 15);
    std::shared_ptr<NPC> bittern = std::make_shared<Bittern>("Bittern", 10, 10);

    EXPECT_TRUE(bear->canFight(*desman));
    EXPECT_FALSE(bear->canFight(*bittern));
    EXPECT_TRUE(desman->canFight(*bear));
    EXPECT_FALSE(bittern->canFight(*bear));
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    editor.addNPC(std::make_shared<Bear>("Grizzly", 5, 5));
    editor.addNPC(std::make_shared<Bittern>("Bittern", 10, 10));
    editor.addNPC(std::make_shared<Desman>("Desman", 15, 15));

    editor.saveToFile("test_npcs.txt");

    DungeonEditor newEditor;
    newEditor.loadFromFile("test_npcs.txt");

    std::ostringstream oss;
    newEditor.printAll();
    std::string result = oss.str();

    EXPECT_NE(result.find("Bear Grizzly (5, 5)"), std::string::npos);
    EXPECT_NE(result.find("Bittern Bittern (10, 10)"), std::string::npos);
    EXPECT_NE(result.find("Desman Desman (15, 15)"), std::string::npos);
}

TEST(DungeonEditorTest, Battle) {
    DungeonEditor editor;
    auto bear = std::make_shared<Bear>("Grizzly", 5, 5);
    auto desman = std::make_shared<Desman>("Desman", 7, 7);

    editor.addNPC(bear);
    editor.addNPC(desman);

    editor.startBattle(5); 

    std::ostringstream oss;
    editor.printAll();
    std::string result = oss.str();

    EXPECT_NE(result.find("Bear Grizzly"), std::string::npos);
    EXPECT_EQ(result.find("Desman Desman"), std::string::npos);
}

TEST(ObserverTest, Notify) {
    DungeonEditor editor;

    std::shared_ptr<Observer> consoleObserver = std::make_shared<ConsoleObserver>();
    std::shared_ptr<Observer> fileObserver = std::make_shared<FileObserver>("test_events.log");

    editor.addObserver(consoleObserver);
    editor.addObserver(fileObserver);

    EXPECT_NO_THROW(editor.notifyObservers("Test event"));
}