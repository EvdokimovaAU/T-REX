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
#include <fstream>

using std::vector;
using std::string;

// история переходов между экранами
struct ScreenHistory
{
    int screen;
    sf::Vector2f position;
};

class Game 
{
private:

    // Системные
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    const std::string SAVE_FILE = "save.txt";

    // Состояние игры
    bool isPlayerDead;
    bool canUsePortal;
    bool showMoneyWarning;
    bool wasMousePressed;
    bool wasMouseClicked;
    bool inShopScreen;

    // Таймеры
    sf::Clock clock;
    sf::Clock portalClock;
    sf::Clock moneyWarningClock;
    sf::Clock digClock;
    sf::Clock deathTimer;
    const float digCooldown = 0.3f;
    const float deathDelay = 3.0f;

    // Игровые параметры
    int hunger;
    int money;
    int fossils;
    int supplies;
    float moveSpeed;
    int currentScreen;

    // Инструменты
    struct 
    {
        int brushDurability = 5;
        int shovelDurability = 10;
        int pickaxeDurability = 10;
    } tools;

    enum class Tool { BRUSH, SHOVEL, PICKAXE, NONE };
    Tool currentTool;

    // Инвентарь
    int bonesCount;
    int plantCount;
    int toothCount;
    int unicornCount;
    const float itemSize = 200.0f;

    // Музейные цены
    int museumBonesPrice = 600;
    int museumPlantPrice = 300;
    int museumToothPrice = 400;
    int museumUnicornPrice = 700;

    // Текстуры
    sf::Texture brokenLootTexture;
    sf::Texture diggingTexture;
    sf::Texture museumBonesTex, museumPlantTex, museumToothTex, museumUnicornTex;
    sf::Texture buyBrushTex, buyShovelTex, buyPickaxeTex, buyEatTex;
    sf::Texture buriedTextures[3];
    sf::Texture dugOutTextures[5];
    sf::Texture playerTexture;
    vector<sf::Texture> backgroundTextures;

    // Спрайты
    sf::Sprite museumBonesSpr, museumPlantSpr, museumToothSpr, museumUnicornSpr;
    sf::Sprite buyBrushSpr, buyShovelSpr, buyPickaxeSpr, buyEatSpr;
    sf::Sprite playerSprite;
    vector<sf::Sprite> backgroundSprites;

    // Анимации
    DigAnimation brushAnimation;
    DigAnimation shovelAnimation;
    DigAnimation pickaxeAnimation;

    // UI элементы
    UIText bonesText;
    UIText plantText;
    UIText toothText;
    UIText unicornText;
    UIText hungerText;
    UIText moneyText;
    UIText fossilsText;
    UIText suppliesText;
    UIText excavatedText;
    UIText moneyWarningText;
    sf::Font debugFont;

    // Игровые системы
    vector<vector<Teleport>> screens;
    vector<ScreenHistory> previousPositions;
    vector<vector<Loot>> digSites;
    std::unique_ptr<Excavation> currentExcavation;
    std::unordered_map<int, std::unique_ptr<Excavation>> excavations;

    // Инициализация
    void initVariables();
    void initWindow();
    void initPlayer();
    void initScreens();
    void initBackgrounds();
    void initLootTextures();
    void initDigSites();
    void initAnimations();
    void initExcavations();
    void initShopItems();
    void initMuseumItems();

    // Обновление состояния
    void updateHunger(int change);
    void updateMoney(int change);
    void updateFossils(int change);
    void updateSupplies(int change);
    void updateBonesCount(int change);
    void updatePlantCount(int change);
    void updateToothCount(int change);
    void updateUnicornCount(int change);

    // Логика игры
    void handleDigging();
    void handleShopItems();
    void handleMuseumItems();
    void resetDigSites(int screen);
    void checkPlayerDeath();
    void resetGame();

    // Вспомогательные
    bool isShopScreen() const { return currentScreen == 1; }
    void renderUI();
    void saveGame();
    void loadGame();

public:
   
    // Конструктор и Деструктор
    Game();
    virtual ~Game();

    // Управление игрой
    static Game& instance();
    const bool running() const;
    void pollEvents();
    void update();
    void render();

    
    // Работа с экранами
    void changeScreen(int newScreen, sf::Vector2f newPosition);
    string getLocationName(int screenIndex) const;

    
    // Работа с инвентарем
    int getSupplies() const;
    int getSuppliesCount() const;
    int countDugLoots();

    
    // Изменение состояния
    void applyHungerEffect(int amount);
    void applySuppliesEffect(int amount);
    void applySpeedModifier(float modifier);
    void updateMoveSpeed(float modifier);

    
    // Доступ к ресурсам
    const sf::Texture& getDiggingTexture() const;
};



inline Game& Game::instance() {
    static Game instance;
    return instance;
}

inline int Game::getSupplies() const {
    return supplies;
}

inline void Game::updateMoveSpeed(float modifier) {
    moveSpeed *= modifier;
}

inline const sf::Texture& Game::getDiggingTexture() const {
    return diggingTexture;
}