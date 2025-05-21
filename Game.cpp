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
    hungerText("Hunger: 10/10", 36, sf::Color::White, 20.f, 30.f),  
    moneyText("Money: $1000", 36, sf::Color::White, 20.f, 80.f),     
    fossilsText("Fossils: 0", 36, sf::Color::White, 20.f, 130.f),    
    suppliesText("Supplies: 0", 36, sf::Color::White, 20.f, 180.f),  
    excavatedText("", 36, sf::Color::White, 20.f, 230.f),            
    moneyWarningText("Not enough money!", 42, sf::Color::Red, 0.f, 0.f),  
    wasMouseClicked(false),
    inShopScreen(false), 
    digCooldown(0.3f),
    bonesCount(0),
    plantCount(0),
    toothCount(0),
    unicornCount(0),
    bonesText("Bones: 0", 36, sf::Color::White, 20.f, 280.f),
    plantText("Plants: 0", 36, sf::Color::White, 20.f, 330.f),
    toothText("Teeth: 0", 36, sf::Color::White, 20.f, 380.f),
    unicornText("Unicorns: 0", 36, sf::Color::White, 20.f, 430.f)
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
    initMuseumItems();
    loadGame();

    if (!debugFont.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/Arial.ttf")) {
        debugFont = sf::Font();
    }
}

Game::~Game() 
{
    saveGame();
    delete window;
}

// механика
void Game::initVariables() 
{
    window = nullptr;
}

void Game::initWindow() 
{
    videoMode.height = 1080;
    videoMode.width = 1920;
    window = new sf::RenderWindow(videoMode, "Paleontolog", sf::Style::Default);
    window->setFramerateLimit(60);
}

void Game::initScreens() 
{
    screens.resize(6);
    const float windowWidth = 1920.f;  
    const float windowHeight = 1080.f; 
    const float playerWidth = playerSprite.getGlobalBounds().width;
    const float playerHeight = playerSprite.getGlobalBounds().height;

    
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

// игрок
void Game::initPlayer() 
{
    if (!playerTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/dino.png")) {
        sf::Image placeholder;
        placeholder.create(64, 64, sf::Color::Red);
        playerTexture.loadFromImage(placeholder);
    }
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(250.f / playerTexture.getSize().x, 170.f / playerTexture.getSize().y);
    playerSprite.setPosition(1920 / 2 - 125, 1080 / 2 - 85);  
}

// карты
void Game::initBackgrounds() 
{
    backgroundTextures.resize(6);
    backgroundSprites.resize(6);

    vector<string> texturePaths = 
    {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/baza.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/shop.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/museum.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/desert.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/jungle.jpg",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/arctica.jpg"
    };

    for (int i = 0; i < 6; ++i) 
    {
        if (!backgroundTextures[i].loadFromFile(texturePaths[i])) 
        {
            sf::Image placeholder;
            placeholder.create(1920, 1080, sf::Color::Red);
            backgroundTextures[i].loadFromImage(placeholder);
        }
        backgroundSprites[i].setTexture(backgroundTextures[i]);
        backgroundSprites[i].setScale(
            1920.f / backgroundTextures[i].getSize().x,
            1080.f / backgroundTextures[i].getSize().y
        );
    }
}

// экспедиции
void Game::initExcavations() 
{
    excavations.clear();
    excavations[3] = std::make_unique<DesertExcavation>(this);
    excavations[4] = std::make_unique<JungleExcavation>(this);
    excavations[5] = std::make_unique<ArcticaExcavation>(this);
}

void Game::initDigSites() 
{
    digSites.resize(6);
    const float windowWidth = 1920.f;
    const float windowHeight = 1080.f;

    vector<sf::Vector2f> desertPositions = 
    {
        {windowWidth * 0.4f, windowHeight * 0.3f},  
        {windowWidth * 0.6f, windowHeight * 0.3f},
        {windowWidth * 0.4f, windowHeight * 0.7f},
        {windowWidth * 0.6f, windowHeight * 0.7f}
    };

    vector<sf::Vector2f> junglePositions = 
    {
        {windowWidth * 0.35f, windowHeight * 0.35f},
        {windowWidth * 0.65f, windowHeight * 0.35f},
        {windowWidth * 0.35f, windowHeight * 0.65f},
        {windowWidth * 0.65f, windowHeight * 0.65f}
    };

    vector<sf::Vector2f> arcticaPositions = 
    {
        {windowWidth * 0.3f, windowHeight * 0.3f},
        {windowWidth * 0.7f, windowHeight * 0.3f},
        {windowWidth * 0.3f, windowHeight * 0.7f},
        {windowWidth * 0.7f, windowHeight * 0.7f}
    };

    
    auto initLootForBiome = [&](int screen, BiomeType biome, const vector<sf::Vector2f>& positions) 
        {
        for (int i = 0; i < 4; ++i) 
        {
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

void Game::initLootTextures() 
{
   // закопанные
    string buriedPaths[3] = {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures//lootdes.png",  
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/lootjun.png",  
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/lootarc.png"   
    };

    // заглушки
    for (int i = 0; i < 3; ++i) {
        if (!buriedTextures[i].loadFromFile(buriedPaths[i])) {
            sf::Image placeholder;
            placeholder.create(128, 128,
                i == 0 ? sf::Color(210, 180, 140) :  
                (i == 1 ? sf::Color(34, 139, 34) :   
                    sf::Color(173, 216, 230)));      
            buriedTextures[i].loadFromImage(placeholder);
        }
    }

    // раскопанные
    string dugOutPaths[5] = 
    {
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/bones.png",    
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/plant.png",    
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/tooth.png",    
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/unicorn.png",  
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/nothing.png"   
    };

    // заглушки
    for (int i = 0; i < 5; ++i) 
    {
        if (!dugOutTextures[i].loadFromFile(dugOutPaths[i])) 
        {
            sf::Image placeholder;
            placeholder.create(128, 128,
                i == 0 ? sf::Color(139, 69, 19) :   
                (i == 1 ? sf::Color(0, 100, 0) :     
                    (i == 2 ? sf::Color(210, 180, 140) : 
                        (i == 3 ? sf::Color(255, 192, 203) : 
                            sf::Color(200, 200, 200)))));
            dugOutTextures[i].loadFromImage(placeholder);
        }
    }

    // во время анимации
    if (!diggingTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/lootinprocess.png")) {
        sf::Image placeholder;
        placeholder.create(128, 128, sf::Color(150, 150, 150)); 
        diggingTexture.loadFromImage(placeholder);
    }
    
    // разрушенный
    if (!brokenLootTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/brokeloot.png")) {
        sf::Image placeholder;
        placeholder.create(128, 128, sf::Color(100, 100, 100));
        brokenLootTexture.loadFromImage(placeholder);
    }
}

void Game::initAnimations() 
{
    brushAnimation.loadFrames({
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/b1.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/b2.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/b3.png"
        });
    brushAnimation.setScale(0.2f);

    
    shovelAnimation.loadFrames({
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/l1.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/l2.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/l3.png"
        });
    shovelAnimation.setScale(0.2f);

    
    pickaxeAnimation.loadFrames({
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/k1.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/k2.png",
        "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/k3.png"
        });
    pickaxeAnimation.setScale(0.2f);
}

// музей и магазин
void Game::initShopItems() 
{
    // картинки 
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

    // расположение
    const float itemSize = 200.0f; 
    const float spacing = 50.0f;  
    const float totalWidth = 2 * itemSize + spacing;
    const float totalHeight = 2 * itemSize + spacing;
    const float startX = (1920 - totalWidth) / 2 - 23;  
    const float startY = (1080 - totalHeight) / 2 + 90; 

    // кисточка
    buyBrushSpr.setTexture(buyBrushTex);
    buyBrushSpr.setScale(
        itemSize / buyBrushTex.getSize().x,
        itemSize / buyBrushTex.getSize().y
    );
    buyBrushSpr.setPosition(startX, startY);

    // лопата
    buyShovelSpr.setTexture(buyShovelTex);
    buyShovelSpr.setScale(
        itemSize / buyShovelTex.getSize().x,
        itemSize / buyShovelTex.getSize().y
    );
    buyShovelSpr.setPosition(startX + itemSize + spacing, startY);

    // кирка
    buyPickaxeSpr.setTexture(buyPickaxeTex);
    buyPickaxeSpr.setScale(
        itemSize / buyPickaxeTex.getSize().x,
        itemSize / buyPickaxeTex.getSize().y
    );
    buyPickaxeSpr.setPosition(startX, startY + itemSize + spacing);

    // еда
    buyEatSpr.setTexture(buyEatTex);
    buyEatSpr.setScale(
        itemSize / buyEatTex.getSize().x,
        itemSize / buyEatTex.getSize().y
    );
    buyEatSpr.setPosition(startX + itemSize + spacing, startY + itemSize + spacing);
}

void Game::initMuseumItems() 
{
    // кртинки
    if (!museumBonesTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/bonessell.jpg")) {
        sf::Image img; img.create(100, 100, sf::Color(139, 69, 19));
        museumBonesTex.loadFromImage(img);
    }
    if (!museumPlantTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/plantsell.jpg")) {
        sf::Image img; img.create(100, 100, sf::Color(0, 100, 0));
        museumPlantTex.loadFromImage(img);
    }
    if (!museumToothTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/toothsell.jpg")) {
        sf::Image img; img.create(100, 100, sf::Color(210, 180, 140));
        museumToothTex.loadFromImage(img);
    }
    if (!museumUnicornTex.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/textures/unicornsell.jpg")) {
        sf::Image img; img.create(100, 100, sf::Color(255, 192, 203));
        museumUnicornTex.loadFromImage(img);
    }

    // расположениее
    const float itemSize = 200.0f;
    const float horizontalSpacing = 250.0f; 
    const float verticalSpacing = 50.0f;   
    const float startX = (1920 - (2 * itemSize + horizontalSpacing)) / 2 - 110;
    const float startY = (1080 - (2 * itemSize + verticalSpacing)) / 2 + 90;

    // кость
    museumBonesSpr.setTexture(museumBonesTex);
    museumBonesSpr.setScale(itemSize / museumBonesTex.getSize().x, itemSize / museumBonesTex.getSize().y);
    museumBonesSpr.setPosition(startX, startY);

    // растение
    museumPlantSpr.setTexture(museumPlantTex);
    museumPlantSpr.setScale(itemSize / museumPlantTex.getSize().x, itemSize / museumPlantTex.getSize().y);
    museumPlantSpr.setPosition(startX + itemSize + horizontalSpacing, startY);

    // зуб
    museumToothSpr.setTexture(museumToothTex);
    museumToothSpr.setScale(itemSize / museumToothTex.getSize().x, itemSize / museumToothTex.getSize().y);
    museumToothSpr.setPosition(startX, startY + itemSize + verticalSpacing);

    // единорог
    museumUnicornSpr.setTexture(museumUnicornTex);
    museumUnicornSpr.setScale(itemSize / museumUnicornTex.getSize().x, itemSize / museumUnicornTex.getSize().y);
    museumUnicornSpr.setPosition(startX + itemSize + horizontalSpacing, startY + itemSize + verticalSpacing);
}


// добыча 
void Game::handleDigging() 
{
    if (currentScreen < 3 || currentScreen > 5) return; 
    if (hunger <= 0) return; 
    if (digClock.getElapsedTime().asSeconds() < digCooldown) return; // задержка

    // нажатие клавиш инструментов
    bool ePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E); 
    bool rPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R); 
    bool tPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::T); 

    if (!ePressed && !rPressed && !tPressed) return; // если ничего не нажато

    // ближайший лут
    Loot* targetLoot = nullptr;
    float minDistance = 200.f;
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

    for (auto& loot : digSites[currentScreen]) 
    {
        if (loot.getIsDug() || loot.getIsBroken()) continue; // пропускаем раскопанное/сломанное

        sf::FloatRect lootBounds = loot.getGlobalBounds();
        if (!playerBounds.intersects(lootBounds)) continue; // нет рядом с игроком

        // расстояние между центрами
        sf::Vector2f playerCenter = 
        {
            playerBounds.left + playerBounds.width / 2,
            playerBounds.top + playerBounds.height / 2
        };

        sf::Vector2f lootCenter = 
        {
            lootBounds.left + lootBounds.width / 2,
            lootBounds.top + lootBounds.height / 2
        };

        float distance = std::sqrt
        (
            std::pow(playerCenter.x - lootCenter.x, 2) +
            std::pow(playerCenter.y - lootCenter.y, 2)
        );

        if (distance < minDistance) 
        {
            minDistance = distance;
            targetLoot = &loot;
        }
    }

    if (!targetLoot) return; // нет лута

    // позиция для анимации инструмента
    sf::Vector2f animPos = targetLoot->getPosition();
    animPos.x -= 45.f;
    animPos.y -= 25.f;

    // успешность раскопок
    bool digAttemptMade = false;
    const int BRUSH_CHANCE = 80;    
    const int SHOVEL_CHANCE = 70;   
    const int PICKAXE_CHANCE = 50;  

    if (ePressed && tools.brushDurability > 0)  //при неудаче кисточка просто не раскапывает
    {
        brushAnimation.setPosition(animPos);
        brushAnimation.play();

        if (rand() % 100 < BRUSH_CHANCE) 
        {
            targetLoot->startDigging(); // успешная раскопка
        }

        tools.brushDurability--;
        updateHunger(-1);
        digAttemptMade = true;
    }

    else if (rPressed && tools.shovelDurability > 0) //  неудача лопата
    {
        shovelAnimation.setPosition(animPos);
        shovelAnimation.play();

        if (rand() % 100 < SHOVEL_CHANCE) 
        {
            targetLoot->startDigging(); 
        }
        else 
        {
            targetLoot->breakLoot();  
        }

        tools.shovelDurability--;
        updateHunger(-1);
        digAttemptMade = true;
    }

    else if (tPressed && tools.pickaxeDurability > 0) // неудача кирка
    {
        pickaxeAnimation.setPosition(animPos);
        pickaxeAnimation.play();

        if (rand() % 100 < PICKAXE_CHANCE) {
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
        digClock.restart(); // сброс задержки
    }
}

// клики магазин и музей
void Game::handleMuseumItems() 
{
    if (currentScreen != 2) return; 

    // позицию мыши в координатах окна
    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    // состояние левой кнопки мыши
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isMousePressed && !wasMousePressed) 
    {
        if (museumBonesSpr.getGlobalBounds().contains(mousePos)) 
        {
            if (bonesCount > 0) 
            {
                bonesCount--;
                money += museumBonesPrice;
                updateBonesCount(0);
                updateMoney(0);
            }
        }
        else if (museumPlantSpr.getGlobalBounds().contains(mousePos)) {
            if (plantCount > 0) {
                plantCount--;
                money += museumPlantPrice;
                updatePlantCount(0);
                updateMoney(0);
            }
        }
        else if (museumToothSpr.getGlobalBounds().contains(mousePos)) {
            if (toothCount > 0) {
                toothCount--;
                money += museumToothPrice;
                updateToothCount(0);
                updateMoney(0);
            }
        }
        else if (museumUnicornSpr.getGlobalBounds().contains(mousePos)) {
            if (unicornCount > 0) {
                unicornCount--;
                money += museumUnicornPrice;
                updateUnicornCount(0);
                updateMoney(0);
            }
        }
    }

    // обновление кнопки мыши для следующего кадра
    wasMousePressed = isMousePressed;
}

void Game::handleShopItems()
{
    if (currentScreen != 1) return;

    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // Обработка только момент нажатия 
    if (isMousePressed && !wasMousePressed) 
    {
        // проверка какая кнопка нажата
        if (buyBrushSpr.getGlobalBounds().contains(mousePos)) 
        {
            // покупка кисточки
            if (money >= 200) 
            {
                money -= 200;
                tools.brushDurability = 5;
                moneyText.setContent("Money: $" + std::to_string(money));
            }
            else 
            {
                showMoneyWarning = true;
                moneyWarningClock.restart();
            }
        }

        else if (buyShovelSpr.getGlobalBounds().contains(mousePos)) 
        {
            // покупка лопаты
            if (money >= 300) 
            {
                money -= 300;
                tools.shovelDurability = 10;
                moneyText.setContent("Money: $" + std::to_string(money));
            }
            else 
            {
                showMoneyWarning = true;
                moneyWarningClock.restart();
            }
        }

        else if (buyPickaxeSpr.getGlobalBounds().contains(mousePos)) 
        {
            // покупка кирки 
            if (money >= 350)
            {
                money -= 350;
                tools.pickaxeDurability = 10;
                moneyText.setContent("Money: $" + std::to_string(money));
            }
            else 
            {
                showMoneyWarning = true;
                moneyWarningClock.restart();
            }
        }
        else if (buyEatSpr.getGlobalBounds().contains(mousePos)) 
        {
            // покупка еды 
            if (money >= 50) 
            {
                money -= 50;
                hunger = std::min(10, hunger + 2);
                hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
                moneyText.setContent("Money: $" + std::to_string(money));
            }
            else 
            {
                showMoneyWarning = true;
                moneyWarningClock.restart();
            }
        }
    }

    wasMousePressed = isMousePressed;
}


// обновление счетчиков
void Game::updateHunger(int change) 
{
    hunger += change;
    hunger = std::clamp(hunger, 0, 10);

    if (hunger <= 0) {
        isPlayerDead = true; 
        deathTimer.restart();
    }
    hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
}

void Game::updateMoney(int change) 
{
    money += change;
    money = std::max(money, 0);
    moneyText.setContent("Money: $" + std::to_string(money));
}

void Game::updateFossils(int change) 
{
    fossils += change;
    fossils = std::max(fossils, 0);
    fossilsText.setContent("Fossils: " + std::to_string(fossils));
}

void Game::updateSupplies(int change) 
{
    supplies += change;
    supplies = std::max(supplies, 0);
    suppliesText.setContent("Supplies: " + std::to_string(supplies));
}

void Game::updateBonesCount(int change) 
{
    bonesCount += change;
    bonesText.setContent("Bones: " + std::to_string(bonesCount));
}

void Game::updatePlantCount(int change) 
{
    plantCount += change;
    plantText.setContent("Plants: " + std::to_string(plantCount));
}

void Game::updateToothCount(int change) 
{
    toothCount += change;
    toothText.setContent("Teeth: " + std::to_string(toothCount));
}

void Game::updateUnicornCount(int change) 
{
    unicornCount += change;
    unicornText.setContent("Unicorns: " + std::to_string(unicornCount));
}

// обновление игры
void Game::update() 
{
    float deltaTime = clock.restart().asSeconds();
    if (deltaTime > 0.1f) deltaTime = 0.1f;

    // обновление анимации инструментов
    brushAnimation.update(deltaTime);
    shovelAnimation.update(deltaTime);
    pickaxeAnimation.update(deltaTime);

    pollEvents(); // обработка событий

    if (isPlayerDead) 
    {
        if (deathTimer.getElapsedTime().asSeconds() >= deathDelay) 
        {
            resetGame(); // сброс игры
        }
        return;
    }

    // обработка магазина
    if (isShopScreen()) 
    {
        handleShopItems();
    }

    // обработка музея
    if (currentScreen == 2) 
    { 
        handleMuseumItems();
    }

    // игрок двигается везде
    else {
        // обновление раскопок (экраны 3-5)
        if (currentScreen >= 3 && currentScreen <= 5) 
        {
            for (auto& loot : digSites[currentScreen]) 
            {
                loot.update(deltaTime);
                if (loot.getIsDug() && !loot.getWasCounted()) 
                {
                    if (loot.getType() != LootType::NOTHING) 
                    {
                        updateFossils(1);
                        // Обновление счетчиков видов лута
                        switch (loot.getType()) 
                        {
                        case LootType::BONES:
                            updateBonesCount(1);
                            break;
                        case LootType::PLANT:
                            updatePlantCount(1);
                            break;
                        case LootType::TOOTH:
                            updateToothCount(1);
                            break;
                        case LootType::UNICORN:
                            updateUnicornCount(1);
                            break;
                        default:
                            break;
                        }
                    }
                    loot.setWasCounted(true);
                }
            }
        }
    }

    // движение игрока
    float speed = moveSpeed * deltaTime * 60.f;
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;

    playerSprite.move(movement);

    // ограничение позиции
    sf::Vector2f pos = playerSprite.getPosition();
    float width = playerSprite.getGlobalBounds().width;
    float height = playerSprite.getGlobalBounds().height;

    playerSprite.setPosition(
        std::max(0.f, std::min(pos.x, 1920.f - width)),
        std::max(0.f, std::min(pos.y, 1080.f - height))
    );

    // телепортация 
    if (canUsePortal && !isPlayerDead) 
    {
        for (const auto& portal : screens[currentScreen]) 
        {
            if (playerSprite.getGlobalBounds().intersects(portal.getZoneRect())) 
            {
                changeScreen(portal.getTargetScreen(), portal.getTargetPosition());
                canUsePortal = false;
                portalClock.restart();
                break;
            }
        }
    }
    else if (portalClock.getElapsedTime().asSeconds() > 0.5f) 
    {
        canUsePortal = true;
    }
}

// отрисовка
void Game::render() 
{
    window->clear();

    // отрисовка фона
    window->draw(backgroundSprites[currentScreen]);

    // отрисовка предметов магазина
    if (currentScreen == 1) 
    {
        window->draw(buyBrushSpr);
        window->draw(buyShovelSpr);
        window->draw(buyPickaxeSpr);
        window->draw(buyEatSpr);
    }

    // отрисовка лута 
    if (currentScreen >= 3 && currentScreen <= 5) 
    {
        for (const auto& loot : digSites[currentScreen]) 
        {
            loot.draw(*window);
        }
    }

    // отрисовка анимаций инструментов
    brushAnimation.draw(*window);
    shovelAnimation.draw(*window);
    pickaxeAnimation.draw(*window);

    // отрисовка игрока
    if (!isPlayerDead) 
    {
        window->draw(playerSprite);
    }

    // отрисовка UI
    renderUI();

    // отрисовка экрана смерти
    if (isPlayerDead) 
    {
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

    if (currentScreen == 2) 
    {
        window->draw(museumBonesSpr);
        window->draw(museumPlantSpr);
        window->draw(museumToothSpr);
        window->draw(museumUnicornSpr);

        
        UIText bonesPriceText("Cost: $" + std::to_string(museumBonesPrice) + "\nRare item", 24, sf::Color::Black,
            museumBonesSpr.getPosition().x + itemSize + 10, museumBonesSpr.getPosition().y);
        bonesPriceText.draw(*window);

        UIText bonesCountText("x" + std::to_string(bonesCount), 36, sf::Color::Yellow,
            museumBonesSpr.getPosition().x + itemSize - 30, museumBonesSpr.getPosition().y + itemSize - 40);
        bonesCountText.draw(*window);

        UIText plantPriceText("Cost: $" + std::to_string(museumPlantPrice) + "\nCommon item", 24, sf::Color::Black,
            museumPlantSpr.getPosition().x + itemSize + 10, museumPlantSpr.getPosition().y);
        plantPriceText.draw(*window);

        UIText plantCountText("x" + std::to_string(plantCount), 36, sf::Color::Yellow,
            museumPlantSpr.getPosition().x + itemSize - 30, museumPlantSpr.getPosition().y + itemSize - 40);
        plantCountText.draw(*window);

        UIText toothPriceText("Cost: $" + std::to_string(museumToothPrice) + "\nUncommon item", 24, sf::Color::Black,
            museumToothSpr.getPosition().x + itemSize + 10, museumToothSpr.getPosition().y);
        toothPriceText.draw(*window);

        UIText toothCountText("x" + std::to_string(toothCount), 36, sf::Color::Yellow,
            museumToothSpr.getPosition().x + itemSize - 30, museumToothSpr.getPosition().y + itemSize - 40);
        toothCountText.draw(*window);

        UIText unicornPriceText("Cost: $" + std::to_string(museumUnicornPrice) + "\nLegendary item", 24, sf::Color::Black,
            museumUnicornSpr.getPosition().x + itemSize + 10, museumUnicornSpr.getPosition().y);
        unicornPriceText.draw(*window);

        UIText unicornCountText("x" + std::to_string(unicornCount), 36, sf::Color::Yellow,
            museumUnicornSpr.getPosition().x + itemSize - 30, museumUnicornSpr.getPosition().y + itemSize - 40);
        unicornCountText.draw(*window);
    }

    window->display();
}

void Game::renderUI() {
    hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
    moneyText.setContent("Money: $" + std::to_string(money));
  
    // отрисовка UI
    hungerText.draw(*window);
    moneyText.draw(*window);
    excavatedText.draw(*window);
    bonesText.draw(*window);
    plantText.draw(*window);
    toothText.draw(*window);
    unicornText.draw(*window);

    // предупреждение о недостатке денег
    if (showMoneyWarning && moneyWarningClock.getElapsedTime().asSeconds() < 2.0f) 
    {
        sf::FloatRect bounds = moneyWarningText.getBounds();
        moneyWarningText.setPosition
        (
            (window->getSize().x - bounds.width) / 2,
            window->getSize().y / 2
        );
        moneyWarningText.draw(*window);
    }
    else 
    {
        showMoneyWarning = false;
    }

    // отображение текущего инструмента
    std::string toolText;

    UIText toolInfoText(toolText, 20, sf::Color::White, 10.f, 180.f);
    toolInfoText.draw(*window);

    const float rightMargin = 50.f;  
    const float topMargin = 50.f;    
    const float toolSpacing = 50.f;  

    // Кисточка 
    UIText brushText
    (
        "E: Brush " + std::to_string(tools.brushDurability) + "/5",
        36,
        tools.brushDurability > 0 ? sf::Color::White : sf::Color::Red,
        window->getSize().x - rightMargin - 300.f,
        topMargin
    );
    brushText.draw(*window);

    // Лопата
    UIText shovelText
    (
        "R: Shovel " + std::to_string(tools.shovelDurability) + "/10",
        36,
        tools.shovelDurability > 0 ? sf::Color::White : sf::Color::Red,
        window->getSize().x - rightMargin - 300.f,
        topMargin + toolSpacing
    );
    shovelText.draw(*window);

    // Кирка
    UIText pickaxeText
    (
        "T: Pickaxe " + std::to_string(tools.pickaxeDurability) + "/10",
        36,
        tools.pickaxeDurability > 0 ? sf::Color::White : sf::Color::Red,
        window->getSize().x - rightMargin - 300.f,
        topMargin + toolSpacing * 2
    );

    pickaxeText.draw(*window);
}

// обработка событий 
void Game::pollEvents() 
{
    while (window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) window->close();

        // Enter = перезапуск
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) 
        {
            resetGame();
        }

        // обработка клавиш раскопок
        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::E) handleDigging();
            if (event.key.code == sf::Keyboard::R) handleDigging();
            if (event.key.code == sf::Keyboard::T) handleDigging();
            if (event.key.code == sf::Keyboard::Escape) window->close();
        }

        // обработка кликов мыши только в магазине
        if (inShopScreen) 
        {
            switch (event.type) 
            {
            case sf::Event::MouseButtonPressed:
                wasMouseClicked = true;
                break;
            case sf::Event::MouseButtonReleased:
                wasMouseClicked = false;
                break;
            }
        }
    }
}

// экраны
void Game::changeScreen(int newScreen, sf::Vector2f newPosition) {

    inShopScreen = (newScreen == 1);

    // проверка стоимости перехода
    if (excavations.find(newScreen) != excavations.end()) {
        if (money < excavations[newScreen]->getCost()) {
            showMoneyWarning = true;
            moneyWarningClock.restart();
            return;
        }
        updateMoney(-excavations[newScreen]->getCost());

        // каждый раз новая экспедиция
        switch (newScreen) 
        {
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

        // новый лут для экспедиции
        resetDigSites(newScreen);
    }

    // сохранение истории позиций
    if (currentScreen >= 3 && currentScreen <= 5) 
    {
        ScreenHistory history;
        history.screen = currentScreen;
        history.position = playerSprite.getPosition();
        previousPositions.push_back(history);
    }

    currentScreen = newScreen;
    playerSprite.setPosition(newPosition);
}

// сброс мест раскопак на экране
void Game::resetDigSites(int screen) 
{
    if (screen < 3 || screen > 5) return;

    digSites[screen].clear();
    const float windowWidth = 1920.f;
    const float windowHeight = 1080.f;
    vector<sf::Vector2f> positions;
    BiomeType biome;

    // пустыня
    if (screen == 3) 
    { 
        positions = 
        {
            {windowWidth * 0.3f, windowHeight * 0.4f},
            {windowWidth * 0.7f, windowHeight * 0.4f},
            {windowWidth * 0.4f, windowHeight * 0.7f},
            {windowWidth * 0.6f, windowHeight * 0.7f}
        };
        biome = BiomeType::DESERT;
    }
    // джунгли
    else if (screen == 4) 
    { 
        positions = 
        {
            {windowWidth * 0.35f, windowHeight * 0.35f},
            {windowWidth * 0.65f, windowHeight * 0.35f},
            {windowWidth * 0.35f, windowHeight * 0.65f},
            {windowWidth * 0.65f, windowHeight * 0.65f}
        };
        biome = BiomeType::JUNGLE;
    }
    // арктика
    else if (screen == 5) 
    { 
        positions = 
        {
            {windowWidth * 0.3f, windowHeight * 0.3f},
            {windowWidth * 0.8f, windowHeight * 0.3f},
            {windowWidth * 0.2f, windowHeight * 0.7f},
            {windowWidth * 0.6f, windowHeight * 0.6f}
        };
        biome = BiomeType::ARCTICA;
    }

    for (int i = 0; i < 4; ++i) 
    {
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

// сброс игры 
void Game::resetGame() 
{
    hunger = 10;
    money = 1000;
    fossils = 0;
    supplies = 0;
    bonesCount = 0;
    plantCount = 0;
    toothCount = 0;
    unicornCount = 0;
    tools.brushDurability = 5;
    tools.shovelDurability = 10;
    tools.pickaxeDurability = 10;
    currentScreen = 0;
    isPlayerDead = false;

    // сброс позиции игрока
    playerSprite.setPosition(1920 / 2 - 125, 1080 / 2 - 85);

    // Очистка и пересоздание раскопкок
    initDigSites();
    initExcavations();

    // обновление UI
    hungerText.setContent("Hunger: 10/10");
    moneyText.setContent("Money: $1000");
    fossilsText.setContent("Fossils: 0");
    suppliesText.setContent("Supplies: 0");
    bonesText.setContent("Bones: 0");
    plantText.setContent("Plants: 0");
    toothText.setContent("Teeth: 0");
    unicornText.setContent("Unicorns: 0");

    // удаляем файл сохранения
    std::remove(SAVE_FILE.c_str());
}

// сохранение игры
void Game::saveGame() 
{
    std::ofstream out(SAVE_FILE);
    if (out.is_open()) 
    {
        out << money << "\n";
        out << hunger << "\n";
        out << bonesCount << "\n";
        out << plantCount << "\n";
        out << toothCount << "\n";
        out << unicornCount << "\n";
        out << tools.brushDurability << "\n";
        out << tools.shovelDurability << "\n";
        out << tools.pickaxeDurability << "\n";
        out.close();
    }
}

// загрузка игры
void Game::loadGame() 
{
    std::ifstream in(SAVE_FILE);
    if (in.is_open()) 
    {
        in >> money;
        in >> hunger;
        in >> bonesCount;
        in >> plantCount;
        in >> toothCount;
        in >> unicornCount;
        in >> tools.brushDurability;
        in >> tools.shovelDurability;
        in >> tools.pickaxeDurability;
        in.close();

        // обновляем UI
        updateMoney(0);
        updateHunger(0);
        updateBonesCount(0);
        updatePlantCount(0);
        updateToothCount(0);
        updateUnicornCount(0);
    }
}

const bool Game::running() const {
    return window->isOpen();
}

void Game::checkPlayerDeath() 
{
    if (hunger <= 0 && !isPlayerDead) 
    {
        isPlayerDead = true;
        deathTimer.restart();
        std::cout << "Player died from starvation!" << std::endl;
    }
}

//  счетчик выкопанных предметов
int Game::countDugLoots() 
{
    if (currentScreen < 3 || currentScreen > 5) return 0;

    int count = 0;
    for (const auto& loot : digSites[currentScreen]) {
        if (loot.getIsDug()) count++;
    }
    return count;
}

void Game::applyHungerEffect(int amount) 
{
    updateHunger(-amount);
}

void Game::applySuppliesEffect(int amount) 
{
    updateSupplies(-amount);
}

void Game::applySpeedModifier(float modifier) 
{
    moveSpeed *= modifier;
}

string Game::getLocationName(int screenIndex) const 
{
    static const vector<string> names = 
    {
        "Base",
        "Shop",
        "Museum",
        "Desert",
        "Jungle",
        "Arctica"
    };
    return names[screenIndex];
}

int Game::getSuppliesCount() const 
{
    return supplies;
}