#include "Game.h"

// конструктор и деструктор
Game::Game()
{
	this->initaializeVariables();
	this->initWindow();
	this->initPlayer();
	this->initScreens();
	this->initBackgrounds();
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
		sf::FloatRect(994, 250, 30, 150),   // Правая зона
		sf::Vector2f(30, 350),              // Появление слева в музее
		2
	);

	screens[0].emplace_back(
		sf::FloatRect(462, 557, 100, 20),  // Широкая нижняя зона (324px)
		sf::Vector2f(462, 20),             // Появление сверху
		5
	);

	// Верхний левый переход в пустыню
	screens[0].emplace_back(
		sf::FloatRect(0, 0, 300, 60),      // Верхняя левая зона
		sf::Vector2f(724, 517),            // Появление снизу в пустыне
		3
	);

	// Верхний правый переход в джунгли
	screens[0].emplace_back(
		sf::FloatRect(windowWidth - 100.f, 0.f, 100.f, 60.f),  // Маленькая зона в правом верхнем углу
		sf::Vector2f(50.f, windowHeight - playerHeight - 10.f),      // Появление внизу слева в джунглях
		4
	);

	screens[1].emplace_back(
		sf::FloatRect(windowWidth - 10.f, 0.f, 10.f, windowHeight),  // Узкая 10px полоса справа
		sf::Vector2f(10.f, windowHeight / 2 - playerHeight / 2),         // Левая сторона главного экрана
		0
	);

	// Музей (2) → главный
	screens[2].emplace_back(
		sf::FloatRect(462, 547, 100, 30),
		sf::Vector2f(462, 30),
		0
	);

	// Пустыня (3) → главный
	screens[3].emplace_back(
		sf::FloatRect(300, 520, 400, 50),
		sf::Vector2f(350, 50),
		0
	);

	// Джунгли (4) → главный
	screens[4].emplace_back(
		sf::FloatRect(0.f, playerHeight - 30.f, 150.f, 30.f),  // Узкая полоса внизу слева
		sf::Vector2f(windowWidth - 60.f, 40.f),              // Появление вверху справа на главном
		0
	);

	// Арктика (5) → главный
	screens[5].emplace_back(
		sf::FloatRect(800, 527, 150, 50),    // Широкая верхняя зона
		sf::Vector2f(100, 50),
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

	// Получаем точные границы спрайта
	sf::FloatRect bounds = playerSprite.getGlobalBounds();
	float spriteWidth = bounds.width;
	float spriteHeight = bounds.height;

	// Границы движения для каждого экрана
	switch (currentScreen) {
	case 0: // Главный экран (база)
		playerSprite.setPosition(
			std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - spriteWidth)),
			std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - spriteHeight))
		);
		break;

	case 1: // Магазин
		playerSprite.setPosition(
			std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - spriteWidth)),
			std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - spriteHeight))
		);
		break;

	case 2: // Музей
		playerSprite.setPosition(
			std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - spriteWidth)),
			std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - spriteHeight))
		);
		break;

	case 3: // Пустыня
		playerSprite.setPosition(
			std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - spriteWidth)),
			std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - spriteHeight))
		);
		break;

	case 4: // Джунгли
		playerSprite.setPosition(
			std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - spriteWidth)),
			std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - spriteHeight))
		);
		break;

	case 5: // Арктика
		playerSprite.setPosition(
			std::max(0.f, std::min(playerSprite.getPosition().x, 1024.f - spriteWidth)),
			std::max(0.f, std::min(playerSprite.getPosition().y, 577.f - spriteHeight))
		);
		break;
	}

	// Проверка телепортов с учетом точных границ
	for (const auto& portal : screens[currentScreen]) {
		if (bounds.intersects(portal.getZoneRect())) {
			changeScreen(portal.getTargetScreen(), portal.getTargetPosition());
			break;
		}
	}
}

// отрисовка игры
void Game::render()
{
	window->clear();
	window->draw(backgroundSprites[currentScreen]);

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
