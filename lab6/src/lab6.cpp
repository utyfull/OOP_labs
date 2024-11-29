#include "lab6.h"

int main() {
    // Тест 1: Проверка создания NPC
    std::shared_ptr<NPC> bear = std::make_shared<Bear>("Grizzly", 5, 5);
    std::shared_ptr<NPC> bittern = std::make_shared<Bittern>("Bittern", 10, 10);
    std::shared_ptr<NPC> desman = std::make_shared<Desman>("Desman", 15, 15);

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
    DungeonEditor loadedEditor;
    loadedEditor.loadFromFile("npcs.txt");
    loadedEditor.printAll();

    // Тест 3: Проверка наблюдателей
    std::shared_ptr<Observer> consoleObserver = std::make_shared<ConsoleObserver>();
    std::shared_ptr<Observer> fileObserver = std::make_shared<FileObserver>("events.log");

    editor.addObserver(consoleObserver);
    editor.addObserver(fileObserver);

    std::cout << "\nТест 3: Наблюдатели\n";
    editor.notifyObservers("NPCs have been loaded and saved.");

    // Тест 4: Бои между NPC
    std::cout << "\nТест 4: Проведение боев\n";
    editor.startBattle(20);

    // Тест 5: Бой между NPC с близким расстоянием
    std::cout << "\nТест 5: Бой на близком расстоянии\n";
    editor.addNPC(std::make_shared<Bear>("Bear1", 1, 1));
    editor.addNPC(std::make_shared<Desman>("Desman1", 2, 2)); // В пределах боя
    editor.addNPC(std::make_shared<Bittern>("Bittern1", 10, 10)); // Вне зоны боя
    editor.startBattle(3);

    // Тест 6: Сражения на дальнем расстоянии
    std::cout << "\nТест 6: Бой на дальнем расстоянии\n";
    editor.addNPC(std::make_shared<Bear>("Bear2", 50, 50));
    editor.addNPC(std::make_shared<Desman>("Desman2", 45, 45)); // В пределах боя
    editor.startBattle(10);

    // Тест 7: Удаление NPC после боя
    std::cout << "\nТест 7: Проверка удаления NPC после боя\n";
    editor.addNPC(std::make_shared<Bear>("Bear3", 5, 5));
    editor.addNPC(std::make_shared<Desman>("Desman3", 6, 6));
    editor.startBattle(2);

    // Тест 8: Проверка работы разных типов взаимодействий
    std::cout << "\nТест 8: Проверка взаимодействий между типами NPC\n";
    std::shared_ptr<NPC> newBear = std::make_shared<Bear>("NewBear", 10, 10);
    std::shared_ptr<NPC> newDesman = std::make_shared<Desman>("NewDesman", 12, 12);
    std::shared_ptr<NPC> newBittern = std::make_shared<Bittern>("NewBittern", 15, 15);
    editor.addNPC(newBear);
    editor.addNPC(newDesman);
    editor.addNPC(newBittern);
    editor.startBattle(5);

    // Тест 9: Проверка сохранения после боев
    std::cout << "\nТест 9: Сохранение NPC после боев\n";
    editor.saveToFile("updated_npcs.txt");

    // Тест 10: Проверка повторной загрузки
    std::cout << "\nТест 10: Повторная загрузка NPC из файла\n";
    DungeonEditor reloadEditor;
    reloadEditor.loadFromFile("updated_npcs.txt");
    reloadEditor.printAll();

    // Все тесты завершены
    std::cout << "\nВсе тесты завершены.\n";

    return 0;
}