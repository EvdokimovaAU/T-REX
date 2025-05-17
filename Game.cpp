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
    currentTool(Tool::NONE),
    hungerText("Hunger: 10/10", 36, sf::Color::White, 20.f, 30.f),  // Увеличено
    moneyText("Money: $1000", 36, sf::Color::White, 20.f, 80.f),     // Увеличено
    fossilsText("Fossils: 0", 36, sf::Color::White, 20.f, 130.f),    // Увеличено
    suppliesText("Supplies: 0", 36, sf::Color::White, 20.f, 180.f),  // Увеличено
    excavatedText("", 36, sf::Color::White, 20.f, 230.f),            // Увеличено
    moneyWarningText("Not enough money!", 42, sf::Color::Red, 0.f, 0.f),  // Увеличено
    wasMouseClicked(false),
    inShopScreen(false), // Добавляем инициализацию флага
    digCooldown(0.3f)
{
    initShopItems();
    initVariables();
    initWindow();
    initPlayer();
    initScreens();
    initBackgrounds();
    initLootTextures();
    initDigSites();
    initAnimations();
    initExcavations();

    if (!debugFont.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/Arial.ttf")) {
        debugFont = sf::Font();
    }
}

Game::~Game() {
    delete window;
}

void Game::initVariables() {
    window = nullptr;
}

void Game::initWindow() {
    videoMode.height = 1080;
    videoMode.width = 1920;
    window = new sf::RenderWindow(videoMode, "Paleontolog", sf::Style::Default);
    window->setFramerateLimit(60);
}

void Game::initPlayer() {
    if (!playerTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/dino.png")) {
        sf::Image placeholder;
        placeholder.create(64, 64, sf::Color::Red);
        playerTexture.loadFromImage(placeholder);
    }
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(250.f / playerTexture.getSize().x, 170.f / playerTexture.getSize().y);
    playerSprite.setPosition(1920 / 2 - 125, 1080 / 2 - 85);  // Обновлено для 1920x1080
}

void Game::initExcavations() {
    excavations.clear();
    excavations[3] = std::make_unique<DesertExcavation>(this);
    excavations[4] = std::make_unique<JungleExcavation>(this);
    excavations[5] = std::make_unique<ArcticaExcavation>(this);
}

void Game::initAnimations() {
    // Кисть (E)
    brushAnimation.loadFrames({
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/b1.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/b2.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/b3.png"
        });
    brushAnimation.setScale(0.2f);

    // Лопата (R)
    shovelAnimation.loadFrames({
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/l1.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/l2.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/l3.png"
        });
    shovelAnimation.setScale(0.2f);

    // Кирка (T)
    pickaxeAnimation.loadFrames({
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/k1.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/k2.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/k3.png"
        });
    pickaxeAnimation.setScale(0.2f);
}

void Game::initBackgrounds() {
    backgroundTextures.resize(6);
    backgroundSprites.resize(6);

    vector<string> texturePaths = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/locations/baza.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/locations/shop.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/locations/museum.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/locations/desert.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/locations/jungle.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/locations/arctica.jpg"
    };

    for (int i = 0; i < 6; ++i) {
        if (!backgroundTextures[i].loadFromFile(texturePaths[i])) {
            sf::Image placeholder;
            placeholder.create(1920, 1080, sf::Color::Red);  // Обновлено
            backgroundTextures[i].loadFromImage(placeholder);
        }
        backgroundSprites[i].setTexture(backgroundTextures[i]);
        backgroundSprites[i].setScale(
            1920.f / backgroundTextures[i].getSize().x,  // Обновлено
            1080.f / backgroundTextures[i].getSize().y   // Обновлено
        );
    }
}

void Game::initShopItems() {
    // Загрузка текстур
    if (!buyBrushTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/buybrash.jpg")) {
        sf::Image img;
        img.create(100, 100, sf::Color::Red);
        buyBrushTex.loadFromImage(img);
    }
    if (!buyShovelTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/buyshovel.jpg")) {
        sf::Image img;
        img.create(100, 100, sf::Color::Blue);
        buyShovelTex.loadFromImage(img);
    }
    if (!buyPickaxeTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/buypickaxe.jpg")) {
        sf::Image img;
        img.create(100, 100, sf::Color::Yellow);
        buyPickaxeTex.loadFromImage(img);
    }
    if (!buyEatTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/buyeat.jpg")) {
        sf::Image img;
        img.create(100, 100, sf::Color::Green);
        buyEatTex.loadFromImage(img);
    }

    // Размеры и позиционирование
    const float itemSize = 200.0f; // Увеличили размер иконок
    const float spacing = 50.0f;  // Увеличили расстояние

    // Центрирование
    const float totalWidth = 2 * itemSize + spacing;
    const float totalHeight = 2 * itemSize + spacing;
    const float startX = (1920 - totalWidth) / 2 - 23;  // Центр по горизонтали
    const float startY = (1080 - totalHeight) / 2 + 90; // Центр по вертикали

    // Кисточка (верх-лево)
    buyBrushSpr.setTexture(buyBrushTex);
    buyBrushSpr.setScale(
        itemSize / buyBrushTex.getSize().x,
        itemSize / buyBrushTex.getSize().y
    );
    buyBrushSpr.setPosition(startX, startY);

    // Лопата (верх-право)
    buyShovelSpr.setTexture(buyShovelTex);
    buyShovelSpr.setScale(
        itemSize / buyShovelTex.getSize().x,
        itemSize / buyShovelTex.getSize().y
    );
    buyShovelSpr.setPosition(startX + itemSize + spacing, startY);

    // Кирка (низ-лево)
    buyPickaxeSpr.setTexture(buyPickaxeTex);
    buyPickaxeSpr.setScale(
        itemSize / buyPickaxeTex.getSize().x,
        itemSize / buyPickaxeTex.getSize().y
    );
    buyPickaxeSpr.setPosition(startX, startY + itemSize + spacing);

    // Еда (низ-право)
    buyEatSpr.setTexture(buyEatTex);
    buyEatSpr.setScale(
        itemSize / buyEatTex.getSize().x,
        itemSize / buyEatTex.getSize().y
    );
    buyEatSpr.setPosition(startX + itemSize + spacing, startY + itemSize + spacing);
}

void Game::initScreens() {
    screens.resize(6);
    const float windowWidth = 1920.f;  // Обновлено
    const float windowHeight = 1080.f; // Обновлено
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
    // Загрузка текстур для закопанных объектов
    string buriedPaths[3] = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootdes.png",  // DESERT
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootjun.png",  // JUNGLE
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootarc.png"   // ARCTICA
    };

    for (int i = 0; i < 3; ++i) {
        if (!buriedTextures[i].loadFromFile(buriedPaths[i])) {
            sf::Image placeholder;
            placeholder.create(128, 128,
                i == 0 ? sf::Color(210, 180, 140) :  // Песок
                (i == 1 ? sf::Color(34, 139, 34) :   // Зеленый
                    sf::Color(173, 216, 230)));      // Голубой
            buriedTextures[i].loadFromImage(placeholder);
        }
    }

    // Загрузка текстур для раскопанных объектов
    string dugOutPaths[5] = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/bones.png",    // BONES
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/plant.png",    // PLANT
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/tooth.png",    // TOOTH
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/unicorn.png",  // UNICORN
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/nothing.png"   // NOTHING
    };

    for (int i = 0; i < 5; ++i) {
        if (!dugOutTextures[i].loadFromFile(dugOutPaths[i])) {
            sf::Image placeholder;
            placeholder.create(128, 128,
                i == 0 ? sf::Color(139, 69, 19) :    // Кости
                (i == 1 ? sf::Color(0, 100, 0) :     // Растения
                    (i == 2 ? sf::Color(210, 180, 140) : // Зубы
                        (i == 3 ? sf::Color(255, 192, 203) : // Единорог
                            sf::Color(200, 200, 200)))));
            dugOutTextures[i].loadFromImage(placeholder);
        }
    }

    // Загрузка текстуры для промежуточного состояния (используем ту же, что и закопанный, но темнее)
    if (!diggingTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/lootinprocess.png")) {
        sf::Image placeholder;
        placeholder.create(128, 128, sf::Color(150, 150, 150)); // Серый цвет для промежуточного состояния
        diggingTexture.loadFromImage(placeholder);
    }

    if (!brokenLootTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/brokeloot.png")) {
        sf::Image placeholder;
        placeholder.create(128, 128, sf::Color(100, 100, 100));
        brokenLootTexture.loadFromImage(placeholder);
    }
}

void Game::resetDigSites(int screen) {
    if (screen < 3 || screen > 5) return;

    digSites[screen].clear();
    const float windowWidth = 1920.f;
    const float windowHeight = 1080.f;
    vector<sf::Vector2f> positions;
    BiomeType biome;

    if (screen == 3) { // Пустыня - более компактное расположение
        positions = {
            {windowWidth * 0.3f, windowHeight * 0.4f},
            {windowWidth * 0.7f, windowHeight * 0.4f},
            {windowWidth * 0.4f, windowHeight * 0.7f},
            {windowWidth * 0.6f, windowHeight * 0.7f}
        };
        biome = BiomeType::DESERT;
    }
    else if (screen == 4) { // Джунгли
        positions = {
            {windowWidth * 0.35f, windowHeight * 0.35f},
            {windowWidth * 0.65f, windowHeight * 0.35f},
            {windowWidth * 0.35f, windowHeight * 0.65f},
            {windowWidth * 0.65f, windowHeight * 0.65f}
        };
        biome = BiomeType::JUNGLE;
    }
    else if (screen == 5) { // Арктика
        positions = {
            {windowWidth * 0.3f, windowHeight * 0.3f},
            {windowWidth * 0.8f, windowHeight * 0.3f},
            {windowWidth * 0.2f, windowHeight * 0.7f},
            {windowWidth * 0.6f, windowHeight * 0.6f}
        };
        biome = BiomeType::ARCTICA;
    }

    for (int i = 0; i < 4; ++i) {
        LootType type = currentExcavation ? currentExcavation->generateLoot() : LootType::NOTHING;
        digSites[screen].emplace_back(
            buriedTextures[static_cast<int>(biome)],
            dugOutTextures[static_cast<int>(type)],
            brokenLootTexture,
            positions[i],
            type,
            biome
        );
    }
}

void Game::handleDigging() {
    // Проверка базовых условий
    if (currentScreen < 3 || currentScreen > 5) return;
    if (hunger <= 0) return;
    if (digClock.getElapsedTime().asSeconds() < digCooldown) return;

    // Проверяем события нажатия клавиш
    bool ePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    bool rPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    bool tPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::T);

    // Если нет нажатий - выходим
    if (!ePressed && !rPressed && !tPressed) return;

    // Поиск ближайшего доступного лута
    Loot* targetLoot = nullptr;
    float minDistance = 200.f;
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

    for (auto& loot : digSites[currentScreen]) {
        if (loot.getIsDug() || loot.getIsBroken()) continue;

        sf::FloatRect lootBounds = loot.getGlobalBounds();
        if (!playerBounds.intersects(lootBounds)) continue;

        sf::Vector2f playerCenter = {
            playerBounds.left + playerBounds.width / 2,
            playerBounds.top + playerBounds.height / 2
        };
        sf::Vector2f lootCenter = {
            lootBounds.left + lootBounds.width / 2,
            lootBounds.top + lootBounds.height / 2
        };

        float distance = std::sqrt(
            std::pow(playerCenter.x - lootCenter.x, 2) +
            std::pow(playerCenter.y - lootCenter.y, 2)
        );

        if (distance < minDistance) {
            minDistance = distance;
            targetLoot = &loot;
        }
    }

    if (!targetLoot) return;

    // Обработка инструментов
    bool digAttemptMade = false;
    sf::Vector2f animPos = targetLoot->getPosition();
    animPos.x -= 45.f;
    animPos.y -= 25.f;

    if (ePressed && tools.brushDurability > 0) {
        brushAnimation.setPosition(animPos);
        brushAnimation.play();

        if (rand() % 100 < 70) { // 70% успех
            targetLoot->startDigging();
        }
        else {
            targetLoot->breakLoot();
        }
        tools.brushDurability--;
        updateHunger(-1);
        digAttemptMade = true;
    }
    else if (rPressed && tools.shovelDurability > 0) {
        shovelAnimation.setPosition(animPos);
        shovelAnimation.play();

        if (rand() % 100 < 50) { // 50% успех
            targetLoot->startDigging();
        }
        else {
            targetLoot->breakLoot();
        }
        tools.shovelDurability--;
        updateHunger(-1);
        digAttemptMade = true;
    }
    else if (tPressed && tools.pickaxeDurability > 0) {
        pickaxeAnimation.setPosition(animPos);
        pickaxeAnimation.play();

        if (rand() % 100 < 30) { // 30% успех
            targetLoot->startDigging();
        }
        else {
            targetLoot->breakLoot();
        }
        tools.pickaxeDurability--;
        updateHunger(-1);
        digAttemptMade = true;
    }

    if (digAttemptMade) {
        digClock.restart();
    }
}

void Game::updateHunger(int change) {
    hunger += change;
    hunger = std::clamp(hunger, 0, 10);

    if (hunger <= 0) {
        isPlayerDead = true; // Персонаж умирает
        deathTimer.restart();
    }
    hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
}

void Game::updateMoney(int change) {
    money += change;
    money = std::max(money, 0);
    moneyText.setContent("Money: $" + std::to_string(money));
}

void Game::updateFossils(int change) {
    fossils += change;
    fossils = std::max(fossils, 0);
    fossilsText.setContent("Fossils: " + std::to_string(fossils));
}

void Game::updateSupplies(int change) {
    supplies += change;
    supplies = std::max(supplies, 0);
    suppliesText.setContent("Supplies: " + std::to_string(supplies));
}

void Game::pollEvents() {

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();

        // Обработка клавиш раскопок даже в магазине (если нужно)
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::E) handleDigging();
            if (event.key.code == sf::Keyboard::R) handleDigging();
            if (event.key.code == sf::Keyboard::T) handleDigging();
        }
    }
    // Если мы в магазине, обрабатываем все события
    if (inShopScreen) {
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
            case sf::Event::MouseButtonPressed:
                wasMouseClicked = true;
                break;
            case sf::Event::MouseButtonReleased:
                wasMouseClicked = false;
                break;
            }
        }
        return;
    }

    // Для других экранов обрабатываем только закрытие
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

    float deltaTime = clock.restart().asSeconds();
    if (deltaTime > 0.1f) deltaTime = 0.1f;

    // Обновляем анимации инструментов
    brushAnimation.update(deltaTime);
    shovelAnimation.update(deltaTime);
    pickaxeAnimation.update(deltaTime);


    // Обработка магазина только если мы в нем
    if (inShopScreen) {
        handleShopItems();
        pollEvents(); // Обрабатываем события только для магазина
        return; // Выходим, чтобы не обрабатывать движение и раскопки
    }

    // Если игрок умер
    if (isPlayerDead) {
        if (deathTimer.getElapsedTime().asSeconds() >= deathDelay) {
            resetGame();
        }
        return;
    }

    // Обновление состояния раскопок
    if (currentScreen >= 3 && currentScreen <= 5) {
        for (auto& loot : digSites[currentScreen]) {
            loot.update(deltaTime);

            if (loot.getIsDug() && !loot.getWasCounted()) {
                if (loot.getType() != LootType::NOTHING) {
                    updateFossils(1);
                }
                loot.setWasCounted(true);
            }
        }
    }

    // Обработка ввода
    pollEvents();

    // Обработка магазина (добавлено)
    if (currentScreen == 1) {
        handleShopItems();
    }

    // Движение игрока
    if (!isPlayerDead) {
        float speed = moveSpeed * deltaTime * 60.f;
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;

        playerSprite.move(movement);

        // Ограничение позиции игрока
        sf::Vector2f pos = playerSprite.getPosition();
        float width = playerSprite.getGlobalBounds().width;
        float height = playerSprite.getGlobalBounds().height;

        playerSprite.setPosition(
            std::max(0.f, std::min(pos.x, 1920.f - width)),
            std::max(0.f, std::min(pos.y, 1080.f - height))
        );
    }

    // Телепортация
    if (canUsePortal && !isPlayerDead) {
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

    // Проверка смерти игрока
    checkPlayerDeath();
}

void Game::render() {
    window->clear();

    // Отрисовка фона
    window->draw(backgroundSprites[currentScreen]);

    // Отрисовка предметов магазина (добавлено)
    if (currentScreen == 1) {
        window->draw(buyBrushSpr);
        window->draw(buyShovelSpr);
        window->draw(buyPickaxeSpr);
        window->draw(buyEatSpr);
    }

    // Отрисовка лута (только на экранах раскопок)
    if (currentScreen >= 3 && currentScreen <= 5) {
        for (const auto& loot : digSites[currentScreen]) {
            loot.draw(*window);
        }
    }

    // Отрисовка анимаций инструментов
    brushAnimation.draw(*window);
    shovelAnimation.draw(*window);
    pickaxeAnimation.draw(*window);

    // Отрисовка игрока (если не умер)
    if (!isPlayerDead) {
        window->draw(playerSprite);
    }

    // Отрисовка UI
    renderUI();

    // Отрисовка экрана смерти
    if (isPlayerDead) {
        sf::RectangleShape overlay(sf::Vector2f(1920, 1080));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window->draw(overlay);

        sf::Text deathText;
        deathText.setFont(debugFont);
        deathText.setString("You died from starvation!\nRestarting in " +
            std::to_string(static_cast<int>(deathDelay - deathTimer.getElapsedTime().asSeconds())) + "...");
        deathText.setCharacterSize(50);
        deathText.setFillColor(sf::Color::Red);
        deathText.setPosition(800, 500);
        window->draw(deathText);
    }

    window->display();
}

void Game::renderUI() {
    hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
    moneyText.setContent("Money: $" + std::to_string(money));
    fossilsText.setContent("Fossils: " + std::to_string(fossils));
    suppliesText.setContent("Supplies: " + std::to_string(supplies));

    // Счетчик раскопок
    if (currentScreen >= 3 && currentScreen <= 5) {
        int dugCount = countDugLoots();
        excavatedText.setContent("Excavated: " + std::to_string(dugCount) + "/4");
    }
    else {
        excavatedText.setContent("");
    }

    // Отрисовка основных элементов UI
    hungerText.draw(*window);
    moneyText.draw(*window);
    fossilsText.draw(*window);
    suppliesText.draw(*window);
    excavatedText.draw(*window);

    // Предупреждение о недостатке денег
    if (showMoneyWarning && moneyWarningClock.getElapsedTime().asSeconds() < 2.0f) {
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

    // Отображение текущего инструмента
    std::string toolText;

    UIText toolInfoText(toolText, 20, sf::Color::White, 10.f, 180.f);
    toolInfoText.draw(*window);

    // Отображение состояния инструментов в правом верхнем углу
    // Отображение состояния инструментов в правом верхнем углу
    const float rightMargin = 50.f;  // Увеличено расстояние от края
    const float topMargin = 50.f;    // Увеличено расстояние сверху
    const float toolSpacing = 50.f;  // Увеличено расстояние между элементами

    // Кисточка (E)
    UIText brushText(
        "E: Brush " + std::to_string(tools.brushDurability) + "/5",
        36,
        tools.brushDurability > 0 ? sf::Color::White : sf::Color::Red,
        window->getSize().x - rightMargin - 300.f,
        topMargin
    );
    brushText.draw(*window);

    // Лопата (R)
    UIText shovelText(
        "R: Shovel " + std::to_string(tools.shovelDurability) + "/10",
        36,
        tools.shovelDurability > 0 ? sf::Color::White : sf::Color::Red,
        window->getSize().x - rightMargin - 300.f,
        topMargin + toolSpacing
    );
    shovelText.draw(*window);

    // Кирка (T)
    UIText pickaxeText(
        "T: Pickaxe " + std::to_string(tools.pickaxeDurability) + "/10",
        36,
        tools.pickaxeDurability > 0 ? sf::Color::White : sf::Color::Red,
        window->getSize().x - rightMargin - 300.f,
        topMargin + toolSpacing * 2
    );
    pickaxeText.draw(*window);

}

void Game::changeScreen(int newScreen, sf::Vector2f newPosition) {

    inShopScreen = (newScreen == 1);

    // При возврате на базу (экран 0) восстанавливаем инструменты
    if (newScreen == 0) {
        tools.brushDurability = 5;
        tools.shovelDurability = 10;
        tools.pickaxeDurability = 10;
    }

    // Проверка стоимости перехода
    if (excavations.find(newScreen) != excavations.end()) {
        if (money < excavations[newScreen]->getCost()) {
            showMoneyWarning = true;
            moneyWarningClock.restart();
            return;
        }
        updateMoney(-excavations[newScreen]->getCost());

        // Создаем новый экземпляр экспедиции при каждом входе
        switch (newScreen) {
        case 3:
            currentExcavation = std::make_unique<DesertExcavation>(this);
            break;
        case 4:
            currentExcavation = std::make_unique<JungleExcavation>(this);
            break;
        case 5:
            currentExcavation = std::make_unique<ArcticaExcavation>(this);
            break;
        }

        // Генерация нового лута для экспедиции
        resetDigSites(newScreen);
    }

    // Сохранение истории позиций
    if (currentScreen >= 3 && currentScreen <= 5) {
        ScreenHistory history;
        history.screen = currentScreen;
        history.position = playerSprite.getPosition();
        previousPositions.push_back(history);
    }

    currentScreen = newScreen;
    playerSprite.setPosition(newPosition);
}

void Game::initDigSites() {
    digSites.resize(6);
    const float windowWidth = 1920.f;
    const float windowHeight = 1080.f;

    // Пустыня - лут ближе друг к другу (новые позиции)
    vector<sf::Vector2f> desertPositions = {
        {windowWidth * 0.4f, windowHeight * 0.3f},  // Ближе к центру по горизонтали
        {windowWidth * 0.6f, windowHeight * 0.3f},
        {windowWidth * 0.4f, windowHeight * 0.7f},
        {windowWidth * 0.6f, windowHeight * 0.7f}
    };

    // Джунгли - оставляем как было
    vector<sf::Vector2f> junglePositions = {
        {windowWidth * 0.35f, windowHeight * 0.35f},
        {windowWidth * 0.65f, windowHeight * 0.35f},
        {windowWidth * 0.35f, windowHeight * 0.65f},
        {windowWidth * 0.65f, windowHeight * 0.65f}
    };

    // Арктика - немного дальше друг от друга
    vector<sf::Vector2f> arcticaPositions = {
        {windowWidth * 0.3f, windowHeight * 0.3f},
        {windowWidth * 0.7f, windowHeight * 0.3f},
        {windowWidth * 0.3f, windowHeight * 0.7f},
        {windowWidth * 0.7f, windowHeight * 0.7f}
    };

    // Остальной код без изменений
    auto initLootForBiome = [&](int screen, BiomeType biome, const vector<sf::Vector2f>& positions) {
        for (int i = 0; i < 4; ++i) {
            LootType type = static_cast<LootType>(rand() % 5);
            digSites[screen].emplace_back(
                buriedTextures[static_cast<int>(biome)],
                dugOutTextures[static_cast<int>(type)],
                brokenLootTexture,
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

string Game::getLocationName(int screenIndex) const {
    static const vector<string> names = {
        "Base",
        "Shop",
        "Museum",
        "Desert",
        "Jungle",
        "Arctica"
    };
    return names[screenIndex];
}

void Game::applyHungerEffect(int amount) {
    updateHunger(-amount);
}

void Game::applySuppliesEffect(int amount) {
    updateSupplies(-amount);
}

void Game::applySpeedModifier(float modifier) {
    moveSpeed *= modifier;
}

int Game::getSuppliesCount() const {
    return supplies;
}

void Game::checkPlayerDeath() {
    if (hunger <= 0 && !isPlayerDead) {
        isPlayerDead = true;
        deathTimer.restart();
        std::cout << "Player died from starvation!" << std::endl;
    }
}

void Game::resetGame() {
    // Сбрасываем все игровые параметры
    hunger = 10;
    money = 1000;
    fossils = 0;
    supplies = 0;
    currentScreen = 0;
    isPlayerDead = false;

    // Сбрасываем позицию игрока
    playerSprite.setPosition(1024 / 2 - 125, 577 / 2 - 85);

    // Очищаем и пересоздаем раскопки
    initDigSites();
    initExcavations();

    // Обновляем UI
    hungerText.setContent("Hunger: 10/10");
    moneyText.setContent("Money: $1000");
    fossilsText.setContent("Fossils: 0");
    suppliesText.setContent("Supplies: 0");
}

void Game::handleShopItems() {
    if (currentScreen != 1) return;
    if (!inShopScreen) return; // Дополнительная проверка

    // Проверяем состояние кнопки мыши
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // Если кнопка только что была нажата (не была нажата в предыдущем кадре)
    if (isMousePressed && !wasMouseClicked) {
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (buyBrushSpr.getGlobalBounds().contains(mousePos) && money >= 200) {
            money -= 200;
            tools.brushDurability = 5;
            moneyText.setContent("Money: $" + std::to_string(money));
        }
        else if (buyShovelSpr.getGlobalBounds().contains(mousePos) && money >= 300) {
            money -= 300;
            tools.shovelDurability = 10;
            moneyText.setContent("Money: $" + std::to_string(money));
        }
        else if (buyPickaxeSpr.getGlobalBounds().contains(mousePos) && money >= 350) {
            money -= 350;
            tools.pickaxeDurability = 10;
            moneyText.setContent("Money: $" + std::to_string(money));
        }
        else if (buyEatSpr.getGlobalBounds().contains(mousePos) && money >= 50) {
            money -= 50;
            hunger = std::min(10, hunger + 2);
            hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
            moneyText.setContent("Money: $" + std::to_string(money));
        }
    }

    // Обновляем состояние флага для следующего кадра
    wasMouseClicked = isMousePressed;
}