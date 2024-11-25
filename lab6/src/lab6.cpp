#include "lab6.h"

int main() {
    // Тест 1: Проверка создания NPC
    std::shared_ptr<NPC> bear = std::make_shared<Bear>("Grizzly", 5, 5);
    std::shared_ptr<NPC> bittern = std::make_shared<Bittern>("Bittern", 10, 10);
    std::shared_ptr<NPC> desman = std::make_shared<Desman>("Desman", 15, 15);

    // Выводим информацию о NPC
    std::cout << "Тест 1: Создание NPC\n";
    std::cout << bear->getType() << " " << bear->getName() << " (" << bear->getX() << ", " << bear->getY() << ")\n";
    std::cout << bittern->getType() << " " << bittern->getName() << " (" << bittern->getX() << ", " << bittern->getY() << ")\n";
    std::cout << desman->getType() << " " << desman->getName() << " (" << desman->getX() << ", " << desman->getY() << ")\n";

    // Тест 2: Сохранение и загрузка NPC из файла
    DungeonEditor editor;
    editor.addNPC(bear);
    editor.addNPC(bittern);
    editor.addNPC(desman);

    std::cout << "\nТест 2: Сохранение NPC в файл\n";
    editor.saveToFile("npcs.txt");

    std::cout << "\nТест 2: Загрузка NPC из файла\n";
    DungeonEditor newEditor;
    newEditor.loadFromFile("npcs.txt");
    newEditor.printAll();

    // Тест 3: Наблюдатели
    std::shared_ptr<Observer> consoleObserver = std::make_shared<ConsoleObserver>();
    std::shared_ptr<Observer> fileObserver = std::make_shared<FileObserver>("events.log");

    editor.addObserver(consoleObserver);
    editor.addObserver(fileObserver);

    std::cout << "\nТест 3: Наблюдатели\n";
    editor.notifyObservers("NPCs have been loaded and saved.");

    // Тест 4: Бои между NPC
    std::cout << "\nТест 4: Проведение боев\n";
    editor.startBattle(20); // Бой на расстоянии 20

    // Тест 5: Проверка сражений
    std::cout << "\nТест 5: Проверка сражений между NPC\n";
    assert(bear->canFight(*desman) == true);  // Медведь может сражаться с выхухолем
    assert(bittern->canFight(*bear) == false); // Выпь не может сражаться
    assert(desman->canFight(*bear) == true);  // Выхухоль может сражаться с медведем

    std::cout << "\nВсе тесты прошли успешно!\n";

    return 0;
}