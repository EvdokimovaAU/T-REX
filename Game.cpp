#include "Game.h"

// конструктор и деструктор
Game::Game()
{
	this->initaializeVariables();
	this->initWindow();
	this->initPlayer();
	this->initScreens();
	this->initBackgrounds();
	this->initLootTextures();
	this->initDigSites();
	moveSpeed = 8.0f;
	currentScreen = 0;
	previousPositions.reserve(10);  // Зарезервируем память для 10 позиций

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
		"baza",
		"shop",
		"museum",
		"desert",
		"jungle",
		"arctica"
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
void Game::changeScreen(int newScreen, sf::Vector2f newPosition)
{
	// Создаем объект ScreenHistory
	ScreenHistory history;
	history.screen = currentScreen; // Сохраняем текущий экран
	history.position = playerSprite.getPosition(); // Сохраняем текущую позицию

	// Добавляем в вектор
	previousPositions.push_back(history); // Теперь тип совпадает

	currentScreen = newScreen;
	playerSprite.setPosition(newPosition);


}

// Инициализация текстур лута
void Game::initLootTextures() {
	// Загрузка текстур закопанного лута для каждого биома
	std::string buriedPaths[3] = {
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootjun.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootarc.png",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/lootdes.png"
	};

	for (int i = 0; i < 3; ++i) {
		if (!buriedTextures[i].loadFromFile(buriedPaths[i])) {
			// Обработка ошибки загрузки
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
			// Обработка ошибки загрузки
		}
	}
}

// Инициализация зон раскопок
void Game::initDigSites() {
	digSites.resize(6); // Для всех экранов, но заполним только 3,4,5

	// Пустыня (экран 3)
	for (int i = 0; i < 4; ++i) {
		sf::Vector2f pos(100 + i * 200, 150 + (i % 2) * 200);
		LootType type = static_cast<LootType>(rand() % 5); // Случайный тип лута
		digSites[3].emplace_back(buriedTextures[0], dugOutTextures[static_cast<int>(type)], pos, type);
	}

	// Джунгли (экран 4)
	for (int i = 0; i < 4; ++i) {
		sf::Vector2f pos(150 + i * 180, 100 + (i % 2) * 250);
		LootType type = static_cast<LootType>(rand() % 5);
		digSites[4].emplace_back(buriedTextures[1], dugOutTextures[static_cast<int>(type)], pos, type);
	}

	// Арктика (экран 5)
	for (int i = 0; i < 4; ++i) {
		sf::Vector2f pos(80 + i * 220, 120 + (i % 2) * 220);
		LootType type = static_cast<LootType>(rand() % 5);
		digSites[5].emplace_back(buriedTextures[2], dugOutTextures[static_cast<int>(type)], pos, type);
	}
}

// Обработка раскопок
void Game::handleDigging() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		// Проверяем, находится ли игрок на экране с раскопками
		if (currentScreen == 3 || currentScreen == 4 || currentScreen == 5) {
			// Проверяем пересечение с зонами раскопок
			sf::Vector2f playerCenter = playerSprite.getPosition();
			playerCenter.x += playerSprite.getGlobalBounds().width / 2;
			playerCenter.y += playerSprite.getGlobalBounds().height / 2;

			for (auto& loot : digSites[currentScreen]) {
				if (!loot.getIsDug() && loot.contains(playerCenter)) {
					loot.dig();
					// Можно добавить звук или эффект раскопок
					break; // Раскапываем только один лут за раз
				}
			}
		}
	}
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

// отрисовка игры
void Game::render()
{
	window->clear();
	window->draw(backgroundSprites[currentScreen]);

	// Отрисовка зон раскопок для текущего экрана
	if (currentScreen == 3 || currentScreen == 4 || currentScreen == 5) {
		for (const auto& loot : digSites[currentScreen]) {
			loot.draw(*window);
		}
	}

	// Временная отрисовка зон перехода (для отладки)
	sf::RectangleShape debugZone;
	debugZone.setFillColor(sf::Color(255, 0, 0, 120)); // Полупрозрачный красный

	for (const auto& portal : screens[currentScreen]) {
		sf::FloatRect zone = portal.getZoneRect();
		debugZone.setPosition(zone.left, zone.top);
		debugZone.setSize(sf::Vector2f(zone.width, zone.height));
		window->draw(debugZone);
	}

	window->draw(playerSprite);
	window->display();

}