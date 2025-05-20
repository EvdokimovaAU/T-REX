#pragma once 

#include "Teleport.h"
#include "Loot.h"
#include "UIText.h"
#include "DigAnimation.h"
#include "Excavation.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <unordered_map>

using std::vector;
using std::string;

struct ScreenHistory
{
    int screen;
    sf::Vector2f position;
};

class Game
{
private:

    int museumBonesPrice = 600;
    int museumPlantPrice = 300;
    int museumToothPrice = 400;
    int museumUnicornPrice = 700;

    sf::Texture museumBonesTex, museumPlantTex, museumToothTex, museumUnicornTex;
    sf::Sprite museumBonesSpr, museumPlantSpr, museumToothSpr, museumUnicornSpr;

    void initMuseumItems();
    void handleMuseumItems();

    int bonesCount;
    int plantCount;
    int toothCount;
    int unicornCount;

    UIText bonesText;
    UIText plantText;
    UIText toothText;
    UIText unicornText;
    void updateBonesCount(int change);
    void updatePlantCount(int change);
    void updateToothCount(int change);
    void updateUnicornCount(int change);

    bool wasMousePressed; // Добавьте это в private секцию

    struct {
        int brushDurability = 5;
        int shovelDurability = 10;
        int pickaxeDurability = 10;
    } tools;

    sf::Texture brokenLootTexture;
    sf::Texture diggingTexture;

    bool isPlayerDead; // Флаг смерти игрока
    sf::Clock deathTimer; // Таймер перед перезапуском
    const float deathDelay = 3.0f; // Задержка перед перезапуском

    void resetGame(); // Метод для сброса игры
    void checkPlayerDeath(); // Проверка состояния игрока
    bool isShopScreen() const { return currentScreen == 1; }
    // Анимации инструментов
    DigAnimation brushAnimation;   // Кисть (E)
    DigAnimation shovelAnimation; // Лопата (R)
    DigAnimation pickaxeAnimation; // Кирка (T)

    // Игровые состояния
    enum class Tool { BRUSH, SHOVEL, PICKAXE, NONE };
    Tool currentTool;

    // Основные компоненты
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;

    // Графика
    vector<sf::Texture> backgroundTextures;
    vector<sf::Sprite> backgroundSprites;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    // Игровые системы
    vector<vector<Teleport>> screens;
    vector<ScreenHistory> previousPositions;
    vector<vector<Loot>> digSites;

    // Текстуры
    sf::Texture buriedTextures[3];
    sf::Texture dugOutTextures[5];

    // Система раскопок
    std::unique_ptr<Excavation> currentExcavation;
    std::unordered_map<int, std::unique_ptr<Excavation>> excavations;

    // UI элементы
    UIText hungerText;
    UIText moneyText;
    UIText fossilsText;
    UIText suppliesText;
    UIText excavatedText;
    UIText moneyWarningText;

    // Игровые переменные
    int hunger;
    int money;
    int fossils;
    int supplies;
    float moveSpeed;
    int currentScreen;

    // Флаги состояния
    bool canUsePortal;
    bool showMoneyWarning;

    sf::Clock digClock;
    const float digCooldown = 0.3f;
    // Таймеры
    sf::Clock clock;
    sf::Clock portalClock;
    sf::Clock moneyWarningClock;

    // Шрифты
    sf::Font debugFont;

    // Текстуры и спрайты для магазина
    sf::Texture buyBrushTex, buyShovelTex, buyPickaxeTex, buyEatTex;
    sf::Sprite buyBrushSpr, buyShovelSpr, buyPickaxeSpr, buyEatSpr;

    bool wasMouseClicked; // Флаг для отслеживания клика
    bool inShopScreen; // Добавляем флаг для отслеживания магазина

    // Метод для обработки магазина
    void handleShopItems();
    void initShopItems();
    void initVariables();
    void initWindow();
    void initPlayer();
    void initScreens();
    void initBackgrounds();
    void initLootTextures();
    void initDigSites();
    void initAnimations();
    void initExcavations();
    void updateHunger(int change);
    void updateMoney(int change);
    void updateFossils(int change);
    void updateSupplies(int change);
    void handleDigging();
    void resetDigSites(int screen);
    void renderUI();

public:
    Game();
    virtual ~Game();

    static Game& instance() {
        static Game instance;
        return instance;
    }

    int getSupplies() const { return supplies; }
    void updateMoveSpeed(float modifier) { moveSpeed *= modifier; }

    const bool running() const;
    int countDugLoots();
    void pollEvents();
    void update();
    void render();
    string getLocationName(int screenIndex) const;
    void changeScreen(int newScreen, sf::Vector2f newPosition);

    void applyHungerEffect(int amount);
    void applySuppliesEffect(int amount);
    void applySpeedModifier(float modifier);
    int getSuppliesCount() const;
    const sf::Texture& getDiggingTexture() const { return diggingTexture; }

};