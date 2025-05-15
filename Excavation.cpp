#include "Excavation.h"
#include "Game.h"

// DesertExcavation
DesertExcavation::DesertExcavation(Game* game) : Excavation(game) {
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::BONES }; // Пустыня: plant, nothing и bones
}

// JungleExcavation
JungleExcavation::JungleExcavation(Game* game) : Excavation(game) {
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::UNICORN }; // Джунгли: plant, nothing и unicorn
}

// ArcticaExcavation
ArcticaExcavation::ArcticaExcavation(Game* game) : Excavation(game) {
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::TOOTH }; // Арктика: plant, nothing и tooth
}

// DesertExcavation
void DesertExcavation::applyEffects() {
    // Пустыня больше не тратит голод здесь
}

// JungleExcavation
void JungleExcavation::applyEffects() {
    game->applySpeedModifier(0.8f); // Только эффект замедления
}

// ArcticaExcavation
void ArcticaExcavation::applyEffects() {
    if (game->getSuppliesCount() > 0) {
        game->applySuppliesEffect(1); // Только трата припасов
    }
    // Без эффекта голода
}

LootType DesertExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

int DesertExcavation::getCost() const { return 300; }
std::string DesertExcavation::getName() const { return "Desert Expedition"; }

LootType JungleExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

int JungleExcavation::getCost() const { return 400; }
std::string JungleExcavation::getName() const { return "Jungle Expedition"; }

LootType ArcticaExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

int ArcticaExcavation::getCost() const { return 550; }
std::string ArcticaExcavation::getName() const { return "Arctic Expedition"; }