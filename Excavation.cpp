#include "Excavation.h"
#include "Game.h"

// DesertExcavation
DesertExcavation::DesertExcavation(Game* game) : Excavation(game) {
    possibleLootTypes = { LootType::NOTHING, LootType::BONES, LootType::PLANT };
}

LootType DesertExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

void DesertExcavation::applyEffects() {
    game->applyHungerEffect(1);
}

int DesertExcavation::getCost() const { return 300; }
std::string DesertExcavation::getName() const { return "Desert Expedition"; }

// JungleExcavation
JungleExcavation::JungleExcavation(Game* game) : Excavation(game) {
    possibleLootTypes = { LootType::NOTHING, LootType::UNICORN, LootType::PLANT };
}

LootType JungleExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

void JungleExcavation::applyEffects() {
    game->applySpeedModifier(0.8f);
}

int JungleExcavation::getCost() const { return 400; }
std::string JungleExcavation::getName() const { return "Jungle Expedition"; }

// ArcticaExcavation
ArcticaExcavation::ArcticaExcavation(Game* game) : Excavation(game) {
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::TOOTH };
}

LootType ArcticaExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

void ArcticaExcavation::applyEffects() {
    if (game->getSuppliesCount() > 0) {
        game->applySuppliesEffect(1);
    }
    else {
        game->applyHungerEffect(2);
    }
}

int ArcticaExcavation::getCost() const { return 550; }
std::string ArcticaExcavation::getName() const { return "Arctic Expedition"; }