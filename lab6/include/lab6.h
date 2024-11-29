#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <cmath>
#include <map>
#include <cassert>
#include <algorithm>

// *** Абстрактный класс NPC ***
class NPC {
public:
    virtual ~NPC() = default;
    virtual const std::string& getType() const = 0;
    virtual const std::string& getName() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual void accept(class NPCVisitor& visitor) = 0;
    virtual bool canFight(const NPC& other) const = 0;
    virtual bool fight(NPC& other) = 0; 
};

// *** Классы-конкретные NPC ***
class Bear : public NPC {
    std::string name;
    int x, y;
public:
    Bear(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    const std::string& getType() const override { static std::string type = "Bear"; return type; }
    const std::string& getName() const override { return name; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    void accept(NPCVisitor& visitor) override;
    bool canFight(const NPC& other) const override {
        return other.getType() != "Bittern"; 
    }
    bool fight(NPC& other) override {
        if (other.getType() == "Bear") return false; 
        if (other.getType() == "Desman") return false; 
        return true; 
    }
};

class Bittern : public NPC {
    std::string name;
    int x, y;
public:
    Bittern(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    const std::string& getType() const override { static std::string type = "Bittern"; return type; }
    const std::string& getName() const override { return name; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    void accept(NPCVisitor& visitor) override;
    bool canFight(const NPC& other) const override { return false; }
    bool fight(NPC&) override { return false; }
};

class Desman : public NPC {
    std::string name;
    int x, y;
public:
    Desman(const std::string& name, int x, int y) : name(name), x(x), y(y) {}
    const std::string& getType() const override { static std::string type = "Desman"; return type; }
    const std::string& getName() const override { return name; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    void accept(NPCVisitor& visitor) override;
    bool canFight(const NPC& other) const override {
        return other.getType() == "Bear"; 
    }
    bool fight(NPC& other) override {
        return true; 
    }
};

// *** Visitor для проведения боя ***
class NPCVisitor {
public:
    virtual void visit(NPC& npc) = 0;
};

class BattleVisitor : public NPCVisitor {
    std::vector<std::shared_ptr<NPC>>& npcs;
    int range;
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs, int range) : npcs(npcs), range(range) {}

    void removeDefeated(const std::vector<std::shared_ptr<NPC>>& defeatedNPCs) {
        npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
            [&defeatedNPCs](const std::shared_ptr<NPC>& npc) {
                return std::find(defeatedNPCs.begin(), defeatedNPCs.end(), npc) != defeatedNPCs.end();
            }), 
            npcs.end());
    }

    void visit(NPC& npc) override {
        std::vector<std::shared_ptr<NPC>> defeatedNPCs;

        for (auto& other : npcs) {
            if (&npc == other.get()) continue; 
            int dist = std::sqrt(std::pow(npc.getX() - other->getX(), 2) + 
                                std::pow(npc.getY() - other->getY(), 2));
            if (dist <= range && npc.canFight(*other)) {
                if (!npc.fight(*other)) {
                    defeatedNPCs.push_back(other); 
                }
            }
        }

        removeDefeated(defeatedNPCs);
    }

};

// Реализация метода accept
void Bear::accept(NPCVisitor& visitor) { visitor.visit(*this); }
void Bittern::accept(NPCVisitor& visitor) { visitor.visit(*this); }
void Desman::accept(NPCVisitor& visitor) { visitor.visit(*this); }

// *** Observer ***
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& event) = 0;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& event) override {
        std::cout << event << std::endl;
    }
};

class FileObserver : public Observer {
    std::ofstream logFile;
public:
    FileObserver(const std::string& fileName) : logFile(fileName, std::ios::app) {}
    void update(const std::string& event) override {
        logFile << event << std::endl;
    }
};

// *** Factory для создания NPC ***
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

// *** Главный класс-редактор ***
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
            if (type == "Bear") addNPC(std::make_shared<Bear>(name, x, y));
            else if (type == "Bittern") addNPC(std::make_shared<Bittern>(name, x, y));
            else if (type == "Desman") addNPC(std::make_shared<Desman>(name, x, y));
        }
    }

    void printAll() const {
        for (const auto& npc : npcs) {
            std::cout << npc->getType() << " " << npc->getName() << " (" << npc->getX() << ", " << npc->getY() << ")\n";
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

    void startBattle(int range) {
        BattleVisitor battleVisitor(npcs, range);
        for (auto it = npcs.begin(); it != npcs.end();) {
            (*it)->accept(battleVisitor);
            ++it; 
        }
    }
};
