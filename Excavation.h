#pragma once
#include "Loot.h"
#include <vector>
#include <random>
#include <memory>

// Предварительное объявление
class Game;

class Excavation {
protected:
    std::vector<LootType> possibleLootTypes;
    Game* game;

public:
    explicit Excavation(Game* game) : game(game) {}
    virtual ~Excavation() = default;

    virtual LootType generateLoot() = 0;
    virtual void applyEffects() = 0;
    virtual int getCost() const = 0;
    virtual std::string getName() const = 0;
};

class DesertExcavation : public Excavation {
public:
    explicit DesertExcavation(Game* game);
    LootType generateLoot() override;
    void applyEffects() override;
    int getCost() const override;
    std::string getName() const override;
};

class JungleExcavation : public Excavation {
public:
    explicit JungleExcavation(Game* game);
    LootType generateLoot() override;
    void applyEffects() override;
    int getCost() const override;
    std::string getName() const override;
};

class ArcticaExcavation : public Excavation {
public:
    explicit ArcticaExcavation(Game* game);
    LootType generateLoot() override;
    void applyEffects() override;
    int getCost() const override;
    std::string getName() const override;
};