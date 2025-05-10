#include "Game.h"

Game::Game() :
    hunger(10),
    money(1000),
    fossils(0),
    supplies(0),
    moveSpeed(8.0f),
    currentScreen(0),
    canUsePortal(true),
    showMoneyWarning(false),
    hungerText("Hunger: 10/10", 24, sf::Color::White, 10.f, 30.f),
    moneyText("Money: $1000", 24, sf::Color::White, 10.f, 60.f),
    fossilsText("Fossils: 0", 24, sf::Color::White, 10.f, 90.f),
    suppliesText("Supplies: 0", 24, sf::Color::White, 10.f, 120.f),
    excavatedText("", 24, sf::Color::White, 10.f, 150.f),
    moneyWarningText("Not enough money!", 28, sf::Color::Red, 0.f, 0.f)
{
    initaializeVariables();
    initWindow();
    initPlayer();
    initScreens();
    initBackgrounds();
    initLootTextures();
    initDigSites();

    if (!debugFont.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/Arial.ttf")) {
        debugFont = sf::Font();
    }
}

Game::~Game() {
    delete window;
}

void Game::initaializeVariables() {
    window = nullptr;
}

void Game::initWindow() {
    videoMode.height = 577;
    videoMode.width = 1024;
    window = new sf::RenderWindow(videoMode, "Paleontolog", sf::Style::Default);
    window->setFramerateLimit(144);
}

void Game::initPlayer() {
    std::string texturePath = "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/dino.png";
    if (!playerTexture.loadFromFile(texturePath)) {
        sf::Image placeholder;
        placeholder.create(64, 64, sf::Color::Red);
        playerTexture.loadFromImage(placeholder);
    }
    playerSprite.setTexture(playerTexture);

    sf::Vector2f desiredSize(250.f, 170.f);
    sf::Vector2u textureSize = playerTexture.getSize();
    sf::Vector2f scale(desiredSize.x / textureSize.x, desiredSize.y / textureSize.y);
    playerSprite.setScale(scale);
    playerSprite.setPosition(1024 / 2 - 125, 577 / 2 - 85);
}

string Game::getLocationName(int screenIndex) const {
    static const vector<string> names = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/baza.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/shop.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/museum.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/desert.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/jungle.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/arctica.jpg"
    };
    return names[screenIndex];
}

void Game::initBackgrounds() {
    backgroundTextures.resize(6);
    backgroundSprites.resize(6);

    vector<string> texturePaths = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/baza.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/shop.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/museum.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/desert.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/jungle.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/arctica.jpg"
    };

    for (int i = 0; i < 6; ++i) {
        if (!backgroundTextures[i].loadFromFile(texturePaths[i])) {
            sf::Image placeholder;
            placeholder.create(1024, 577, sf::Color::Red);
            backgroundTextures[i].loadFromImage(placeholder);
        }
        backgroundSprites[i].setTexture(backgroundTextures[i]);

        float scaleX = 1024.f / backgroundTextures[i].getSize().x;
        float scaleY = 577.f / backgroundTextures[i].getSize().y;
        backgroundSprites[i].setScale(scaleX, scaleY);
    }
}

void Game::initScreens() {
    screens.resize(6);
    const float windowWidth = 1024.f;
    const float windowHeight = 577.f;
    const float playerWidth = playerSprite.getGlobalBounds().width;
    const float playerHeight = playerSprite.getGlobalBounds().height;

    // Base (0) transitions
    screens[0].emplace_back(sf::FloatRect(0.f, 0.f, 10.f, windowHeight),
        sf::Vector2f(windowWidth - playerWidth - 10.f, windowHeight / 2 - playerHeight / 2), 1);
    screens[0].emplace_back(sf::FloatRect(windowWidth - 10.f, 0.f, 10.f, windowHeight),
        sf::Vector2f(30.f, windowHeight / 2 - playerHeight / 2), 2);
    screens[0].emplace_back(sf::FloatRect(0.f, windowHeight - 10.f, windowWidth, 10.f),
        sf::Vector2f(windowWidth / 2 - playerWidth / 2, 50.f), 5);
    screens[0].emplace_back(sf::FloatRect(0.f, 0.f, windowWidth / 2, 10.f),
        sf::Vector2f(windowWidth / 2, windowHeight - 50.f), 3);
    screens[0].emplace_back(sf::FloatRect(windowWidth / 2, 0.f, windowWidth / 2, 10.f),
        sf::Vector2f(60.f, windowHeight - 70.f), 4);

    // Other screens transitions back to base
    screens[1].emplace_back(sf::FloatRect(windowWidth - 10.f, 0.f, 10.f, windowHeight),
        sf::Vector2f(10.f, windowHeight / 2 - playerHeight / 2), 0);
    screens[2].emplace_back(sf::FloatRect(0.f, 0.f, 15.f, windowHeight),
        sf::Vector2f(windowWidth - 60.f, windowHeight / 2 - playerHeight / 2), 0);
    screens[3].emplace_back(sf::FloatRect(0.f, windowHeight - 15.f, windowWidth, 15.f),
        sf::Vector2f(windowWidth / 4, 30.f), 0);
    screens[4].emplace_back(sf::FloatRect(0.f, windowHeight - 8.f, windowWidth, 8.f),
        sf::Vector2f(windowWidth / 2, 50.f), 0);
    screens[5].emplace_back(sf::FloatRect(0.f, 0.f, windowWidth, 15.f),
        sf::Vector2f(windowWidth / 2 - playerWidth / 2, windowHeight - 60.f), 0);
}

void Game::initLootTextures() {
    string buriedPaths[3] = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootdes.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootjun.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootarc.png"
    };

    for (int i = 0; i < 3; ++i) {
        if (!buriedTextures[i].loadFromFile(buriedPaths[i])) {
            sf::Image placeholder;
            placeholder.create(128, 128, i == 0 ? sf::Color(210, 180, 140) :
                (i == 1 ? sf::Color(34, 139, 34) : sf::Color(173, 216, 230)));
            buriedTextures[i].loadFromImage(placeholder);
        }
    }

    string dugOutPaths[4] = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/bones.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/plant.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/nothing.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/unicorn.png"
    };

    for (int i = 0; i < 4; ++i) {
        if (!dugOutTextures[i].loadFromFile(dugOutPaths[i])) {
            sf::Image placeholder;
            placeholder.create(128, 128, i == 0 ? sf::Color(139, 69, 19) :
                (i == 1 ? sf::Color(0, 100, 0) :
                    (i == 2 ? sf::Color(255, 255, 255) : sf::Color(255, 192, 203))));
            dugOutTextures[i].loadFromImage(placeholder);
        }
    }
}

void Game::initDigSites() {
    digSites.resize(6);
    const float windowWidth = 1024.f;
    const float windowHeight = 577.f;

    // Уменьшаем количество раскопок до 4 для каждого биома
    // Позиции для пустыни (ромб)
    vector<sf::Vector2f> desertPositions = {
        {windowWidth * 0.5f, windowHeight * 0.3f},
        {windowWidth * 0.3f, windowHeight * 0.5f},
        {windowWidth * 0.7f, windowHeight * 0.5f},
        {windowWidth * 0.5f, windowHeight * 0.7f}
    };

    // Позиции для джунглей (квадрат)
    vector<sf::Vector2f> junglePositions = {
        {windowWidth * 0.3f, windowHeight * 0.3f},
        {windowWidth * 0.7f, windowHeight * 0.3f},
        {windowWidth * 0.3f, windowHeight * 0.7f},
        {windowWidth * 0.7f, windowHeight * 0.7f}
    };

    // Позиции для арктики (линия)
    vector<sf::Vector2f> arcticaPositions = {
        {windowWidth * 0.3f, windowHeight * 0.4f},
        {windowWidth * 0.5f, windowHeight * 0.5f},
        {windowWidth * 0.7f, windowHeight * 0.4f},
        {windowWidth * 0.5f, windowHeight * 0.6f}
    };

    auto initLootForBiome = [&](int screen, BiomeType biome, const vector<sf::Vector2f>& positions) {
        for (int i = 0; i < 4; ++i) {  // Теперь создаем 4 раскопки вместо 5
            LootType type = static_cast<LootType>(rand() % 5);
            digSites[screen].emplace_back(
                buriedTextures[static_cast<int>(biome)],
                dugOutTextures[static_cast<int>(type)],
                positions[i],
                type,
                biome
            );
        }
        };

    initLootForBiome(3, BiomeType::DESERT, desertPositions);
    initLootForBiome(4, BiomeType::JUNGLE, junglePositions);
    initLootForBiome(5, BiomeType::ARCTICA, arcticaPositions);
}

void Game::updateHunger(int change) {
    hunger += change;
    hunger = std::clamp(hunger, 0, 10);
}

void Game::updateMoney(int change) {
    money += change;
    money = std::max(money, 0);
}

void Game::updateFossils(int change) {
    fossils += change;
    fossils = std::max(fossils, 0); // Защита от отрицательных значений
    fossilsText.setContent("Fossils: " + std::to_string(fossils)); // Сразу обновляем текст
}

void Game::updateSupplies(int change) {
    supplies += change;
    supplies = std::max(supplies, 0);
}

void Game::handleDigging() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        if (currentScreen >= 3 && currentScreen <= 5 && hunger > 0) {
            sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

            for (auto& loot : digSites[currentScreen]) {
                if (!loot.getIsDug() && playerBounds.intersects(loot.getGlobalBounds())) {
                    loot.dig();
                    updateHunger(-1);

                    if (loot.getType() != LootType::NOTHING) {
                        updateFossils(1);
                    }
                    break;
                }
            }
        }
    }
}

void Game::handleTravelCost() {
    if (currentScreen == 3) updateMoney(-DESERT_COST);
    else if (currentScreen == 4) updateMoney(-JUNGLE_COST);
    else if (currentScreen == 5) updateMoney(-ARCTICA_COST);
}

void Game::renderUI() {
    // 1. Обновляем текстовые элементы
    hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
    moneyText.setContent("Money: $" + std::to_string(money));
    fossilsText.setContent("Fossils: " + std::to_string(fossils));
    suppliesText.setContent("Supplies: " + std::to_string(supplies));

    // 2. Отображаем счетчик раскопок только на экранах с лут-объектами
    if (currentScreen >= 3 && currentScreen <= 5) {
        int dugCount = 0;
        if (currentScreen < digSites.size()) {
            for (const auto& loot : digSites[currentScreen]) {
                if (loot.getIsDug()) dugCount++;
            }
        }
        excavatedText.setContent("Excavated: " + std::to_string(dugCount) + "/4");
    }
    else {
        excavatedText.setContent("");
    }

    // 3. Отрисовка основных элементов UI
    hungerText.draw(*window);
    moneyText.draw(*window);
    fossilsText.draw(*window);
    suppliesText.draw(*window);
    excavatedText.draw(*window);

    // 4. Предупреждение о недостатке денег
    if (showMoneyWarning && moneyWarningClock.getElapsedTime().asSeconds() < 2.0f) {
        // Центрируем предупреждение
        sf::FloatRect bounds = moneyWarningText.getBounds();
        moneyWarningText.setPosition(
            (window->getSize().x - bounds.width) / 2,
            window->getSize().y / 2
        );
        moneyWarningText.draw(*window);
    }
    else {
        showMoneyWarning = false;
    }

    // 5. Отладочная информация (только в debug-режиме)
#ifdef _DEBUG
    UIText debugText(
        "Debug: Screen " + std::to_string(currentScreen),
        14,
        sf::Color::Green,
        10.f,
        window->getSize().y - 30.f
    );
    debugText.draw(*window);
#endif
}

void Game::changeScreen(int newScreen, sf::Vector2f newPosition) {
    int cost = 0;
    if (newScreen == 3) cost = DESERT_COST;
    else if (newScreen == 4) cost = JUNGLE_COST;
    else if (newScreen == 5) cost = ARCTICA_COST;

    if (cost > 0 && money < cost) {
        showMoneyWarning = true;
        moneyWarningClock.restart();
        return;
    }

    ScreenHistory history;
    history.screen = currentScreen;
    history.position = playerSprite.getPosition();
    previousPositions.push_back(history);

    currentScreen = newScreen;
    playerSprite.setPosition(newPosition);

    if (cost > 0) {
        updateMoney(-cost);
    }
}

void Game::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game::update() {
    pollEvents();

    float deltaTime = clock.restart().asSeconds();
    float speed = moveSpeed * deltaTime * 60.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerSprite.move(-speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerSprite.move(speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerSprite.move(0, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerSprite.move(0, speed);

    playerSprite.setPosition(
        std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - playerSprite.getGlobalBounds().width)),
        std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - playerSprite.getGlobalBounds().height))
    );

    if (canUsePortal) {
        for (const auto& portal : screens[currentScreen]) {
            if (playerSprite.getGlobalBounds().intersects(portal.getZoneRect())) {
                changeScreen(portal.getTargetScreen(), portal.getTargetPosition());
                canUsePortal = false;
                portalClock.restart();
                break;
            }
        }
    }
    else if (portalClock.getElapsedTime().asSeconds() > 0.5f) {
        canUsePortal = true;
    }

    handleDigging();
}

void Game::render() {
    window->clear(sf::Color(30, 30, 30));

    // Отрисовка фона
    if (currentScreen >= 0 && currentScreen < static_cast<int>(backgroundSprites.size())) {
        window->draw(backgroundSprites[currentScreen]);
    }

    // Отрисовка раскопок
    if (currentScreen >= 3 && currentScreen <= 5) {
        for (const auto& loot : digSites[currentScreen]) {
            loot.draw(*window);  // Эта строка отрисовывает раскопки
        }
    }

    // Отрисовка игрока и UI
    window->draw(playerSprite);
    renderUI();
    window->display();
}

int Game::countDugLoots() {
    if (currentScreen < 3 || currentScreen > 5) return 0;

    int count = 0;
    for (const auto& loot : digSites[currentScreen]) {
        if (loot.getIsDug()) count++;
    }
    return count;
}

const bool Game::running() const {
    return window->isOpen();
}