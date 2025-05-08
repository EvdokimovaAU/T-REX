#include "Game.h"

// конструктор и деструктор
Game::Game() :
	hunger(10),
	money(1000),
	fossils(0),
	supplies(0),
	moveSpeed(8.0f),
	currentScreen(0),
	canUsePortal(true),
	showMoneyWarning(false),
	showDebugInfo(true),
	locationText("Location: Base", 16, sf::Color::White, 10.f, 10.f),
	hungerText("Hunger: 10/10", 16, sf::Color::White, 10.f, 30.f),
	moneyText("Money: $1000", 16, sf::Color::White, 10.f, 50.f),
	fossilsText("Fossils: 0", 16, sf::Color::White, 10.f, 70.f),
	suppliesText("Supplies: 0", 16, sf::Color::White, 10.f, 90.f),
	excavatedText("", 16, sf::Color::White, 10.f, 110.f),
	controlsText("Controls: WASD - move, Y - dig", 14, sf::Color::White, 10.f, 527.f),
	moneyWarningText("Not enough money!", 20, sf::Color::Red, 0.f, 0.f)
{
	initaializeVariables();
	initWindow();
	initPlayer();
	initScreens();
	initBackgrounds();
	initLootTextures();
	initDigSites();

	if (!debugFont.loadFromFile("fonts/arial.ttf")) {
		debugFont = sf::Font();
	}
}

Game::~Game()
{
	delete this->window;
}


// private
// инициализация переменных (это присвоение начального значения переменной при её объявлении)
void Game::initaializeVariables()
{
	this->window = nullptr; // обнуляем указатель на окно
}

// создание окна
void Game::initWindow()
{
	this->videoMode.height = 577;
	this->videoMode.width = 1024;
	// задаем окно
	this->window = new sf::RenderWindow(this->videoMode, "Paleontolog", sf::Style::Default);

	this->window->setFramerateLimit(144);
}


//public
// проверка, открыто ли окно
const bool Game::running() const
{
	return this->window->isOpen();
}

int Game::countDugLoots()
{
	if (currentScreen < 3 || currentScreen > 5) return 0;

	int count = 0;
	for (const auto& loot : digSites[currentScreen]) {
		if (loot.getIsDug()) count++;
	}
	return count;
}

// обработка (закрытие с помощью крестика и Escape)
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event)) // обработкаа событий
	{
		switch (this->event.type)
		{
			// закрытие окна - крестик
		case sf::Event::Closed:
			this->window->close();
			break;

			// закрытие окна - нажатие клавиши 
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

// персонаж
void Game::initPlayer()
{

	std::string texturePath = "C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/dino.png"; // УКАЖИТЕ РЕАЛЬНЫЙ ПУТЬ!
	if (!playerTexture.loadFromFile(texturePath)) {
		std::cerr << "FATAL ERROR: Failed to load texture at: " << texturePath << "\n";
		// Создаём красный квадрат как заглушку
		sf::Image placeholder;
		placeholder.create(64, 64, sf::Color::Red);
		playerTexture.loadFromImage(placeholder);
	}
	playerSprite.setTexture(playerTexture);

	// Установка нового размера (в пикселях)
	sf::Vector2f desiredSize(250.f, 170.f); // ширина, высота

	// Рассчитываем масштаб
	sf::Vector2u textureSize = playerTexture.getSize();
	sf::Vector2f scale(
		desiredSize.x / textureSize.x,
		desiredSize.y / textureSize.y
	);

	playerSprite.setScale(scale);
	playerSprite.setPosition(1024 / 2 - 125, 577 / 2 - 85); // Центр минус половина размеров спрайта
}

string Game::getLocationName(int screenIndex) const
{
	static const std::vector<std::string> names = {
		"Base",
		"Shop",
		"Museum",
		"Desert",
		"Jungle",
		"Arctica"
	};
	return names[screenIndex];
}

void Game::initBackgrounds()
{
	backgroundTextures.resize(6);
	backgroundSprites.resize(6);

	// Загрузка текстур для каждого экрана
	std::vector<std::string> texturePaths = {
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/baza.jpg",  // Главный экран
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/shop.jpg",  // Левый экран
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/museum.jpg",  // Правый экран
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/desert.jpg",  // Верхний левый экран
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/jungle.jpg",  // Верхний правый экран
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/arctica.jpg"   // Нижний экран
	};

	for (int i = 0; i < 6; ++i) {
		if (!backgroundTextures[i].loadFromFile(texturePaths[i])) {
			std::cerr << "Failed to load background " << i << " from: " << texturePaths[i] << "\n";
			// Создаём красный квадрат как заглушку
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

// реализация системы экранов
void Game::initScreens()
{
	screens.resize(6);

	// Размеры окна
	const float windowWidth = 1024.f;
	const float windowHeight = 577.f;
	const float playerWidth = playerSprite.getGlobalBounds().width;
	const float playerHeight = playerSprite.getGlobalBounds().height;

	/// ГЛАВНЫЙ ЭКРАН (0) -> МАГАЗИН (1) ///
	// Упрощенный переход (левая граница экрана)
	screens[0].emplace_back(
		sf::FloatRect(0.f, 0.f, 10.f, windowHeight),  // Узкая 10px полоса по всей высоте слева
		sf::Vector2f(windowWidth - playerWidth - 10.f, windowHeight / 2 - playerHeight / 2),  // Правая сторона магазина
		1
	);

	// Правый переход в музей
	screens[0].emplace_back(
		sf::FloatRect(windowWidth - 10.f, 0.f, 10.f, windowHeight),
		sf::Vector2f(30.f, windowHeight / 2 - playerHeight / 2),
		2
	);

	screens[0].emplace_back(
		sf::FloatRect(0.f, windowHeight - 10.f, windowWidth, 10.f), // Полоса шириной во весь экран, высотой 10px
		sf::Vector2f(windowWidth / 2 - playerWidth / 2, 50.f), // Появление сверху по центру
		5
	);

	// Верхний левый переход в пустыню
	screens[0].emplace_back(
		sf::FloatRect(0.f, 0.f, windowWidth / 2, 10.f), // Половина ширины экрана, высота 10px
		sf::Vector2f(windowWidth / 2, windowHeight - 50.f), // Появление внизу по центру
		3
	);

	// Верхний правый переход в джунгли
	screens[0].emplace_back(
		sf::FloatRect(windowWidth / 2, 0.f, windowWidth / 2, 10.f),  // От середины до правого края, высота 5px
		sf::Vector2f(60.f, windowHeight - 70.f),  // Появление внизу слева в джунглях
		4
	);

	screens[1].emplace_back(
		sf::FloatRect(windowWidth - 10.f, 0.f, 10.f, windowHeight),  // Узкая 10px полоса справа
		sf::Vector2f(10.f, windowHeight / 2 - playerHeight / 2),         // Левая сторона главного экрана
		0
	);

	// Музей (2) → главный
	screens[2].emplace_back(
		sf::FloatRect(0.f, 0.f, 15.f, windowHeight), // 15px для лучшего обнаружения
		sf::Vector2f(windowWidth - 60.f, windowHeight / 2 - playerHeight / 2), // Появление с отступом от правого края
		0
	);

	// Пустыня (3) → главный
	screens[3].emplace_back(
		sf::FloatRect(0.f, windowHeight - 15.f, windowWidth, 15.f), // Полоса вдоль всего низа
		sf::Vector2f(windowWidth / 4, 30.f), // Появление вверху слева
		0
	);

	// Джунгли (4) → главный
	screens[4].emplace_back(
		sf::FloatRect(0.f, windowHeight - 8.f, windowWidth, 8.f),  // Тонкая полоса 8px вдоль низа
		sf::Vector2f(windowWidth / 2, 50.f),  // Появление сверху по центру на главном
		0
	);

	// Арктика (5) → главный
	screens[5].emplace_back(
		sf::FloatRect(0.f, 0.f, windowWidth, 15.f), // Узкая полоса сверху
		sf::Vector2f(windowWidth / 2 - playerWidth / 2, windowHeight - 60.f),
		0
	);
}

// выбор экрана
void Game::changeScreen(int newScreen, sf::Vector2f newPosition) {
	// Проверяем, является ли новый экран локацией раскопок
	bool isDigSite = (newScreen == 3 || newScreen == 4 || newScreen == 5);

	// Определяем стоимость перехода
	int travelCost = 0;
	if (newScreen == 3) travelCost = DESERT_COST;
	else if (newScreen == 4) travelCost = JUNGLE_COST;
	else if (newScreen == 5) travelCost = ARCTICA_COST;

	// Проверяем достаточно ли денег для перехода на локацию раскопок
	if (isDigSite && money < travelCost) {
		showMoneyWarning = true;
		moneyWarningClock.restart();
		return;
	}

	// Сохраняем историю переходов
	ScreenHistory history;
	history.screen = currentScreen;
	history.position = playerSprite.getPosition();
	previousPositions.push_back(history);

	// Списываем деньги только при успешном переходе на локацию раскопок
	if (isDigSite) {
		updateMoney(-travelCost);
	}

	currentScreen = newScreen;
	playerSprite.setPosition(newPosition);
}

// Инициализация текстур лута
void Game::initLootTextures() {
	// Загрузка текстур закопанного лута для каждого биома
	std::string buriedPaths[3] = {
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootdes.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootjun.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootarc.png"
	};

	for (int i = 0; i < 3; ++i) {
		if (!buriedTextures[i].loadFromFile(buriedPaths[i])) {
			std::cerr << "Failed to load buried texture for biome " << i << "\n";
			// Создаём заглушку с маркировкой биома
			sf::Image placeholder;
			placeholder.create(128, 128, i == 0 ? sf::Color(210, 180, 140) :
				(i == 1 ? sf::Color(34, 139, 34) :
					sf::Color(173, 216, 230)));
			buriedTextures[i].loadFromImage(placeholder);
		}
	}


	// Загрузка текстур раскопанного лута
	std::string dugOutPaths[4] = {
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/bones.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/plant.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/nothing.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/unicorn.png"
	};

	for (int i = 0; i < 4; ++i) {
		if (!dugOutTextures[i].loadFromFile(dugOutPaths[i])) {
			std::cerr << "Failed to load dug out texture " << i << "\n";
			// Создаём заглушку с маркировкой типа лута
			sf::Image placeholder;
			placeholder.create(128, 128, i == 0 ? sf::Color(139, 69, 19) :
				(i == 1 ? sf::Color(0, 100, 0) :
					(i == 2 ? sf::Color(255, 255, 255) :
						sf::Color(255, 192, 203))));
			dugOutTextures[i].loadFromImage(placeholder);
		}
	}
}


void Game::initDigSites() {
	digSites.resize(6); // Для всех экранов

	const float windowWidth = 1024.f;
	const float windowHeight = 577.f;

	// Пустыня (экран 3) - 5 лутов в форме буквы X
	std::vector<sf::Vector2f> desertPositions = {
		{windowWidth * 0.3f, windowHeight * 0.3f},  // Левый верх
		{windowWidth * 0.7f, windowHeight * 0.3f},  // Правый верх
		{windowWidth * 0.5f, windowHeight * 0.5f},  // Центр
		{windowWidth * 0.3f, windowHeight * 0.7f},  // Левый низ
		{windowWidth * 0.7f, windowHeight * 0.7f}   // Правый низ
	};

	// Джунгли (экран 4) - 5 лутов в форме плюса
	std::vector<sf::Vector2f> junglePositions = {
		{windowWidth * 0.5f, windowHeight * 0.2f},  // Верх
		{windowWidth * 0.2f, windowHeight * 0.5f},  // Лево
		{windowWidth * 0.5f, windowHeight * 0.5f},  // Центр
		{windowWidth * 0.8f, windowHeight * 0.5f},  // Право
		{windowWidth * 0.5f, windowHeight * 0.8f}   // Низ
	};

	// Арктика (экран 5) - 5 лутов в форме дома
	std::vector<sf::Vector2f> arcticaPositions = {
		{windowWidth * 0.5f, windowHeight * 0.2f},  // Крыша верх
		{windowWidth * 0.3f, windowHeight * 0.4f},  // Крыша лево
		{windowWidth * 0.7f, windowHeight * 0.4f},  // Крыша право
		{windowWidth * 0.4f, windowHeight * 0.7f},  // Фундамент лево
		{windowWidth * 0.6f, windowHeight * 0.7f}   // Фундамент право
	};

	// Инициализация для каждого биома (теперь по 5 лутов)
	auto initLootForBiome = [&](int screen, BiomeType biome, const std::vector<sf::Vector2f>& positions) {
		for (int i = 0; i < 5; ++i) {  // Теперь 5 лутов
			LootType type = static_cast<LootType>(rand() % 5);
			int textureIndex = type == LootType::NOTHING ? 0 : static_cast<int>(type);
			digSites[screen].emplace_back(
				buriedTextures[static_cast<int>(biome)],
				dugOutTextures[textureIndex],
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

// Обработка раскопок
void Game::handleDigging() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		if (currentScreen == 3 || currentScreen == 4 || currentScreen == 5) {
			sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
			sf::Vector2f playerCenter(
				playerBounds.left + playerBounds.width / 2,
				playerBounds.top + playerBounds.height / 2
			);

			for (auto& loot : digSites[currentScreen]) {
				sf::FloatRect lootBounds = loot.getGlobalBounds();

				// Уменьшенный радиус взаимодействия (соответствует новому размеру)
				const float interactionRadius = 60.0f;  // Было 100.0f

				sf::Vector2f lootCenter(
					lootBounds.left + lootBounds.width / 2,
					lootBounds.top + lootBounds.height / 2
				);

				float distance = std::sqrt(
					std::pow(playerCenter.x - lootCenter.x, 2) +
					std::pow(playerCenter.y - lootCenter.y, 2)
				);

				if (!loot.getIsDug() && distance < interactionRadius) {
					loot.dig();
					// Можно добавить звук раскопок
					break;
				}
			}
		}
	}
}

void Game::updateMoney(int change) {
	money += change;
	// Защита от отрицательных значений
	if (money < 0) money = 0;

	// Немедленное обновление текста
	moneyText.setContent("Money: $" + std::to_string(money));
}

void Game::update() {
	// Обработка событий
	pollEvents();

	// Движение персонажа
	float deltaTime = clock.restart().asSeconds();
	float speed = moveSpeed * deltaTime * 60.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerSprite.move(-speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerSprite.move(speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerSprite.move(0, -speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerSprite.move(0, speed);

	// Границы движения для всех экранов
	playerSprite.setPosition(
		std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - playerSprite.getGlobalBounds().width)),
		std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - playerSprite.getGlobalBounds().height))
	);

	// Проверка телепортов с защитой от мгновенного возврата
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

void Game::renderUI() {
	locationText.setContent("Location: " + getLocationName(currentScreen));
	hungerText.setContent("Hunger: " + std::to_string(hunger) + "/10");
	moneyText.setContent("Money: $" + std::to_string(money));
	fossilsText.setContent("Fossils: " + std::to_string(fossils));
	suppliesText.setContent("Supplies: " + std::to_string(supplies));

	if (currentScreen >= 3 && currentScreen <= 5) {
		excavatedText.setContent("Excavated: " + std::to_string(countDugLoots()) + "/5");
	}
	else {
		excavatedText.setContent("");
	}

	locationText.draw(*window);
	hungerText.draw(*window);
	moneyText.draw(*window);
	fossilsText.draw(*window);
	suppliesText.draw(*window);
	excavatedText.draw(*window);
	controlsText.draw(*window);

	if (showMoneyWarning && moneyWarningClock.getElapsedTime().asSeconds() < 2.0f) {
		float xPos = (videoMode.width - moneyWarningText.getBounds().width) / 2;
		moneyWarningText.setPosition(xPos, videoMode.height / 2);
		moneyWarningText.draw(*window);
	}
	else {
		showMoneyWarning = false;
	}

	if (showDebugInfo) {
		static sf::Clock fpsClock;
		static int frameCount = 0;
		static float fps = 60.0f;

		frameCount++;
		if (fpsClock.getElapsedTime().asSeconds() >= 0.5f) {
			fps = frameCount / fpsClock.restart().asSeconds();
			frameCount = 0;
		}

		UIText fpsText("FPS: " + std::to_string(static_cast<int>(fps)),
			16, sf::Color::Green, videoMode.width - 80.f, 10.f);
		fpsText.draw(*window);
	}
}

void Game::render()
{
	// 1. Очистка окна
	window->clear(sf::Color(30, 30, 30));

	// 2. Отрисовка фона
	if (currentScreen >= 0 && currentScreen < static_cast<int>(backgroundSprites.size())) {
		window->draw(backgroundSprites[currentScreen]);
	}

	// 3. Отрисовка лутов (для экранов 3-5)
	if (currentScreen >= 3 && currentScreen <= 5 &&
		currentScreen < static_cast<int>(digSites.size())) {

		for (const auto& loot : digSites[currentScreen]) {
			loot.draw(*window);

			// Отладочная информация
			if (showDebugInfo) {
				sf::Text lootText;
				lootText.setFont(debugFont);
				lootText.setCharacterSize(10);
				lootText.setFillColor(sf::Color::Cyan);

				char lootChar = '?';
				switch (loot.getType()) {
				case LootType::BONES: lootChar = 'B'; break;
				case LootType::PLANT: lootChar = 'P'; break;
				case LootType::TOOTH: lootChar = 'T'; break;
				case LootType::UNICORN: lootChar = 'U'; break;
				case LootType::NOTHING: lootChar = 'N'; break;
				}

				lootText.setString(std::string(1, lootChar));
				sf::Vector2f pos = loot.getPosition();
				lootText.setPosition(pos.x - 5, pos.y - 15);

				window->draw(lootText);
			}
		}
	}

	// 4. Отрисовка игрока
	window->draw(playerSprite);

	// 5. Отрисовка интерфейса
	renderUI();

	// 6. Отображение FPS (если включен debug)
	if (showDebugInfo) {
		static sf::Clock fpsClock;
		static int frameCount = 0;
		static float fps = 60.0f;

		frameCount++;
		if (fpsClock.getElapsedTime().asSeconds() >= 0.5f) {
			fps = frameCount / fpsClock.restart().asSeconds();
			frameCount = 0;
		}

		sf::Text fpsText;
		fpsText.setFont(debugFont);
		fpsText.setCharacterSize(14);
		fpsText.setFillColor(sf::Color::Green);
		fpsText.setPosition(window->getSize().x - 80, 10);
		fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

		window->draw(fpsText);
	}

	// 7. Отображение всего
	window->display();
}