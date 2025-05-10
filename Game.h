#pragma once 
#include "Teleport.h"
#include "Loot.h"
#include "UIText.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

struct ScreenHistory {
    int screen;
    sf::Vector2f position;
};

class Game {
private:
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
    sf::Texture dugOutTextures[4];

    // UI элементы
    UIText locationText;
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

    // Стоимости переходов
    const int DESERT_COST = 300;
    const int JUNGLE_COST = 400;
    const int ARCTICA_COST = 550;

    // Флаги состояния
    bool canUsePortal;
    bool showMoneyWarning;

    // Таймеры
    sf::Clock clock;
    sf::Clock portalClock;
    sf::Clock moneyWarningClock;
    sf::Clock frameClock;

    // Шрифты
    sf::Font debugFont;

    // Приватные методы
    void initaializeVariables();
    void initWindow();
    void initPlayer();
    void initScreens();
    void initBackgrounds();
    void initLootTextures();
    void initDigSites();
    void updateHunger(int change);
    void updateMoney(int change);
    void updateFossils(int change);
    void updateSupplies(int change);
    void handleDigging();
    void handleTravelCost();
    void renderUI();

public:
    Game();
    virtual ~Game();

    const bool running() const;
    int countDugLoots();
    void pollEvents();
    void update();
    void render();
    string getLocationName(int screenIndex) const;
    void changeScreen(int newScreen, sf::Vector2f newPosition);
};