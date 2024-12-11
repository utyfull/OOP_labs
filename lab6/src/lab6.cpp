#include "lab6.h"

int main() {
    DungeonEditor editor;
    
    // Добавим наблюдателей
    editor.addObserver(std::make_shared<ConsoleObserver>());
    editor.addObserver(std::make_shared<FileObserver>("game_log.txt"));

    // Демонстрация сохранения/загрузки.
    // Сначала создадим несколько NPC вручную:
    editor.addNPC(std::make_shared<Bear>("Bear_Manual", 10, 10));
    editor.addNPC(std::make_shared<Bittern>("Bittern_Manual", 20, 20));
    editor.addNPC(std::make_shared<Desman>("Desman_Manual", 30, 30));
    
    // Сохраним текущее состояние в файл
    editor.saveToFile("initial_state.txt");

    // Очистим NPC из редактора и загрузим из файла для демонстрации
    editor.getNPCs().clear();
    editor.loadFromFile("initial_state.txt");

    std::cout << "NPCs after loading from file:" << std::endl;
    editor.printAll();
    std::cout << "-----" << std::endl;
    
    // Теперь создадим 50 случайных NPC для игры
    {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> distX(0, 99);
        std::uniform_int_distribution<int> distY(0, 99);
        std::vector<std::string> possibleTypes = {"Медведь", "Выпь", "Выхухоль"};
        std::uniform_int_distribution<int> typeDist(0,(int)possibleTypes.size()-1);

        for (int i = 0; i < 50; ++i) {
            std::string t = possibleTypes[typeDist(rng)];
            int x = distX(rng);
            int y = distY(rng);
            if (t == "Медведь") {
                editor.addNPC(std::make_shared<Bear>("Bear_Rand_"+std::to_string(i), x, y));
            } else if (t == "Выпь") {
                editor.addNPC(std::make_shared<Bittern>("Bittern_Rand_"+std::to_string(i), x, y));
            } else {
                editor.addNPC(std::make_shared<Desman>("Desman_Rand_"+std::to_string(i), x, y));
            }
        }
    }

    gNPCsPtr = &editor.getNPCs();

    // Перед стартом игры выведем состояние всех NPC
    std::cout << "NPCs at the start of the game:" << std::endl;
    editor.printAll();
    std::cout << "-----" << std::endl;

    // Запускаем потоки
    std::thread fightT(fightThreadFunc);
    std::thread moveT(moveThreadFunc);
    std::thread printT(printThreadFunc);

    // Игра длится 30 секунд
    std::this_thread::sleep_for(std::chrono::seconds(30));

    // Останавливаем игру
    gameRunning = false;
    {
        std::lock_guard<std::mutex> qLock(fightQueueMutex);
        fightThreadRunning = false;
        fightQueueCV.notify_all();
    }

    moveT.join();
    printT.join();
    fightT.join();

    // Итог: список выживших
    {
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        std::cout << "Survivors after 30 seconds:" << std::endl;
        for (auto &npc : *gNPCsPtr) {
            if (npc->isAlive()) {
                std::cout << npc->getType() << " " << npc->getName() << " ("
                          << npc->getX() << ", " << npc->getY() << ")\n";
            }
        }
    }

    std::cout << "Game finished. Logs are saved in game_log.txt" << std::endl;
    return 0;
}