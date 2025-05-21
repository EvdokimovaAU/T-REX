#include "Excavation.h"
#include "Game.h"

// тип лута для каждой карты
DesertExcavation::DesertExcavation(Game* game) : Excavation(game) 
{
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::BONES }; 
}

JungleExcavation::JungleExcavation(Game* game) : Excavation(game) 
{
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::UNICORN }; 
}

ArcticaExcavation::ArcticaExcavation(Game* game) : Excavation(game) 
{
    possibleLootTypes = { LootType::NOTHING, LootType::PLANT, LootType::TOOTH }; 
}

// эффекты от местности
void DesertExcavation::applyEffects() {
    // Пустыня больше не тратит голод здесь
}

void JungleExcavation::applyEffects() {
    game->applySpeedModifier(0.8f); // замедление
}

void ArcticaExcavation::applyEffects() {
    if (game->getSuppliesCount() > 0) {
        game->applySuppliesEffect(1); 
    }
    
}


// стоимость экспедиции
int DesertExcavation::getCost() const { return 300; }
std::string DesertExcavation::getName() const { return "Desert Expedition"; }

int JungleExcavation::getCost() const { return 400; }
std::string JungleExcavation::getName() const { return "Jungle Expedition"; }

int ArcticaExcavation::getCost() const { return 550; }
std::string ArcticaExcavation::getName() const { return "Arctic Expedition"; }

// генерация лута
LootType DesertExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

LootType JungleExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}

LootType ArcticaExcavation::generateLoot() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, possibleLootTypes.size() - 1);
    return possibleLootTypes[dist(gen)];
}
