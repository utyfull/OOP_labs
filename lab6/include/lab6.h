#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <cmath>
#include <map>
#include <cassert>
#include <algorithm>
#include <random>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <atomic>
#include <string>

// Константы карты и времени
static const int MAP_WIDTH = 100;
static const int MAP_HEIGHT = 100;
static const int GAME_DURATION = 30; 

// Структура расстояний для NPC
struct NPCDistances {
    int moveDist;
    int killDist;
};

// Таблица дистанций для трех типов NPC
static std::map<std::string, NPCDistances> distanceTable = {
    {"B", {20, 10}}, // Bear
    {"I", {5, 5}},   // Bittern
    {"D", {10, 10}}  // Desman
};

// Абстрактный класс NPC
class NPC {
public:
    virtual ~NPC() = default;
    virtual const std::string& getType() const = 0;
    virtual const std::string& getName() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual void setX(int nx) = 0;
    virtual void setY(int ny) = 0;
    virtual void accept(class NPCVisitor& visitor) = 0;
    virtual bool canFight(const NPC& other) const = 0;
    virtual bool fight(NPC& other) = 0; 
    virtual bool isAlive() const = 0;
    virtual void kill() = 0;
};

class Bear : public NPC {
    std::string name;
    int x, y;
    bool alive = true;
    std::string type = "B"; // Bear = B
public:
    Bear(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    const std::string& getType() const override { return type; }
    const std::string& getName() const override { return name; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    void setX(int nx) override { x = nx; }
    void setY(int ny) override { y = ny; }
    void accept(class NPCVisitor& visitor) override;
    bool canFight(const NPC& other) const override {
        return (other.getType() != "B");
    }
    bool fight(NPC& other) override {
        (void)other;
        return true; 
    }
    bool isAlive() const override { return alive; }
    void kill() override { alive = false; }
};

class Bittern : public NPC {
    std::string name;
    int x, y;
    bool alive = true;
    std::string type = "I"; // Bittern = I
public:
    Bittern(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    const std::string& getType() const override { return type; }
    const std::string& getName() const override { return name; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    void setX(int nx) override { x = nx; }
    void setY(int ny) override { y = ny; }
    void accept(class NPCVisitor& visitor) override;
    bool canFight(const NPC&) const override { 
        return false; 
    }
    bool fight(NPC&) override { return false; }
    bool isAlive() const override { return alive; }
    void kill() override { alive = false; }
};

class Desman : public NPC {
    std::string name;
    int x, y;
    bool alive = true;
    std::string type = "D"; // Desman = D
public:
    Desman(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    const std::string& getType() const override { return type; }
    const std::string& getName() const override { return name; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    void setX(int nx) override { x = nx; }
    void setY(int ny) override { y = ny; }
    void accept(class NPCVisitor& visitor) override;
    bool canFight(const NPC& other) const override {
        return (other.getType() == "B");
    }
    bool fight(NPC&) override {
        return true; 
    }
    bool isAlive() const override { return alive; }
    void kill() override { alive = false; }
};

class NPCVisitor {
public:
    virtual void visit(NPC& npc) = 0;
};

class BattleVisitor : public NPCVisitor {
public:
    void visit(NPC&) override {
    }
};

void Bear::accept(NPCVisitor& visitor) { visitor.visit(*this); }
void Bittern::accept(NPCVisitor& visitor) { visitor.visit(*this); }
void Desman::accept(NPCVisitor& visitor) { visitor.visit(*this); }

// Observer
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& event) = 0;
};

class ConsoleObserver : public Observer {
public:
    static std::mutex& getCoutMutex() {
        static std::mutex coutMutex;
        return coutMutex;
    }
    void update(const std::string& event) override {
        std::lock_guard<std::mutex> lockCout(getCoutMutex());
        std::cout << "[LOG] " << event << std::endl;
    }
};

class FileObserver : public Observer {
    std::ofstream logFile;
public:
    FileObserver(const std::string& fileName) : logFile(fileName, std::ios::app) {
    }
    void update(const std::string& event) override {
        logFile << event << std::endl;
    }
};

// Factory
class NPCFactory {
public:
    virtual ~NPCFactory() = default;
    virtual std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) = 0;
};

class BearFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_shared<Bear>(name, x, y);
    }
};

class BitternFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_shared<Bittern>(name, x, y);
    }
};

class DesmanFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_shared<Desman>(name, x, y);
    }
};

// DungeonEditor
class DungeonEditor {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void addNPC(std::shared_ptr<NPC> npc) {
        npcs.push_back(npc);
    }

    void saveToFile(const std::string& fileName) {
        std::ofstream file(fileName);
        for (const auto& npc : npcs) {
            file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
        }
    }

    void loadFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        std::string type, name;
        int x, y;
        while (file >> type >> name >> x >> y) {
            if (type == "B") addNPC(std::make_shared<Bear>(name, x, y));
            else if (type == "I") addNPC(std::make_shared<Bittern>(name, x, y));
            else if (type == "D") addNPC(std::make_shared<Desman>(name, x, y));
            notifyObservers("Loaded NPC: " + type + " " + name + " (" + std::to_string(x) + "," + std::to_string(y) + ")");
        }
    }

    void printAll() const {
        for (const auto& npc : npcs) {
            std::cout << npc->getType() << " " << npc->getName() << " (" << npc->getX() << ", " << npc->getY() << ")";
            if (!npc->isAlive()) std::cout << " [Dead]";
            std::cout << "\n";
        }
    }

    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void notifyObservers(const std::string& event) {
        for (const auto& observer : observers) {
            observer->update(event);
        }
    }

    std::vector<std::shared_ptr<NPC>>& getNPCs() { return npcs; }
};

// Глобальные переменные для многопоточности
std::shared_mutex npcsMutex;
std::mutex fightQueueMutex;
std::condition_variable fightQueueCV;
std::mutex coutMutex;
std::atomic<bool> gameRunning(true);
std::atomic<bool> fightThreadRunning(true);

struct FightTask {
    int npcIndexA;
    int npcIndexB;
};

std::vector<std::shared_ptr<NPC>> *gNPCsPtr = nullptr; 
std::vector<FightTask> fightQueue;

inline std::shared_ptr<NPC> getNPCSafe(size_t idx) {
    std::shared_lock lock(npcsMutex);
    if (gNPCsPtr && idx < gNPCsPtr->size()) {
        return (*gNPCsPtr)[idx];
    }
    return nullptr;
}

// Поток боёв
void fightThreadFunc() {
    std::unique_lock<std::mutex> qLock(fightQueueMutex, std::defer_lock);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> diceDist(1,6);

    while (fightThreadRunning) {
        qLock.lock();
        fightQueueCV.wait(qLock, []{ return !fightThreadRunning || !fightQueue.empty(); });
        if (!fightThreadRunning) {
            qLock.unlock();
            break;
        }

        FightTask task = fightQueue.back();
        fightQueue.pop_back();
        qLock.unlock();

        auto npcA = getNPCSafe(task.npcIndexA);
        auto npcB = getNPCSafe(task.npcIndexB);

        if (!npcA || !npcB) continue; 
        if (!npcA->isAlive() || !npcB->isAlive()) continue;

        int attackRoll = diceDist(rng);
        int defenseRoll = diceDist(rng);
        if (attackRoll > defenseRoll) {
            std::lock_guard<std::shared_mutex> lock(npcsMutex); 
            if (npcB->isAlive()) {
                npcB->kill();
            }
        }
    }
}

// Поток перемещения NPC
void moveThreadFunc() {
    std::mt19937 rng(std::random_device{}());

    while (gameRunning) {
        {
            std::unique_lock<std::shared_mutex> lock(npcsMutex); 
            for (size_t i = 0; i < gNPCsPtr->size(); ++i) {
                auto &npc = (*gNPCsPtr)[i];
                if (!npc->isAlive()) continue;
                int dist = 1;
                if (distanceTable.find(npc->getType()) != distanceTable.end()) {
                    dist = distanceTable[npc->getType()].moveDist;
                }
                int dx = (rng()%3 - 1)*dist; 
                int dy = (rng()%3 - 1)*dist; 
                int newX = npc->getX() + dx;
                int newY = npc->getY() + dy;
                if (newX < 0) newX = 0;
                if (newX >= MAP_WIDTH) newX = MAP_WIDTH - 1;
                if (newY < 0) newY = 0;
                if (newY >= MAP_HEIGHT) newY = MAP_HEIGHT - 1;
                npc->setX(newX);
                npc->setY(newY);
            }
        }

        {
            std::shared_lock<std::shared_mutex> lock(npcsMutex);
            for (size_t i = 0; i < gNPCsPtr->size(); ++i) {
                auto npcA = (*gNPCsPtr)[i];
                if (!npcA->isAlive()) continue;
                int killDistA = 10; 
                if (distanceTable.find(npcA->getType()) != distanceTable.end()) {
                    killDistA = distanceTable[npcA->getType()].killDist;
                }

                for (size_t j = i+1; j < gNPCsPtr->size(); ++j) {
                    auto npcB = (*gNPCsPtr)[j];
                    if (!npcB->isAlive()) continue;
                    int killDistB = 10;
                    if (distanceTable.find(npcB->getType()) != distanceTable.end()) {
                        killDistB = distanceTable[npcB->getType()].killDist;
                    }

                    int dx = npcA->getX() - npcB->getX();
                    int dy = npcA->getY() - npcB->getY();
                    int distSq = dx*dx + dy*dy;
                    if ((npcA->canFight(*npcB) || npcB->canFight(*npcA)) &&
                        (distSq <= killDistA*killDistA || distSq <= killDistB*killDistB)) 
                    {
                        std::lock_guard<std::mutex> qLock(fightQueueMutex);
                        fightQueue.push_back({(int)i, (int)j});
                        fightQueueCV.notify_one();
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
    }
}

// Поток печати карты
void printThreadFunc() {
    while (gameRunning) {
        {
            std::shared_lock<std::shared_mutex> lock(npcsMutex);

            std::vector<std::string> map(MAP_HEIGHT, std::string(MAP_WIDTH, '.'));

            int minX = MAP_WIDTH, maxX = 0;
            int minY = MAP_HEIGHT, maxY = 0;

            for (auto &npc : *gNPCsPtr) {
                if (npc->isAlive()) {
                    int x = npc->getX();
                    int y = npc->getY();
                    char c = npc->getType()[0]; 
                    map[y][x] = c;
                    if (x < minX) minX = x;
                    if (x > maxX) maxX = x;
                    if (y < minY) minY = y;
                    if (y > maxY) maxY = y;
                }
            }

            {
                std::lock_guard<std::mutex> lockCout(coutMutex);
                
                if (minX == MAP_WIDTH && maxX == 0 && minY == MAP_HEIGHT && maxY == 0) {
                    std::cout << "No NPC alive.\n----\n";
                } else {
                    int padding = 2;
                    minX = std::max(0, minX - padding);
                    minY = std::max(0, minY - padding);
                    maxX = std::min(MAP_WIDTH - 1, maxX + padding);
                    maxY = std::min(MAP_HEIGHT - 1, maxY + padding);

                    for (int y = minY; y <= maxY; ++y) {
                        for (int x = minX; x <= maxX; ++x) {
                            std::cout << map[y][x];
                        }
                        std::cout << "\n";
                    }
                    std::cout << "----\n";
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

