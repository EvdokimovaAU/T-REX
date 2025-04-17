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
			placeholder.create(800, 600, sf::Color::Red);
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

	/// ГЛАВНЫЙ ЭКРАН (0) ///
	// Левый переход в магазин (увеличил высоту)
	screens[0].emplace_back(
		sf::FloatRect(0, 150, 80, 300),    // Узкая (40px) но высокая (300px) зона
		sf::Vector2f(940, 300),            // Появление справа
		1
	);

	// Правый переход в музей (увеличил высоту)
	screens[0].emplace_back(
		sf::FloatRect(944, 150, 80, 300),  // Узкая (40px) но высокая (300px) зона
		sf::Vector2f(80, 300),             // Появление слева
		2
	);

	// Нижний переход (широкий)
	screens[0].emplace_back(
		sf::FloatRect(462, 557, 100, 20),  // Широкая нижняя зона (324px)
		sf::Vector2f(462, 20),             // Появление сверху
		5
	);

	// Верхний левый (широкий)
	screens[0].emplace_back(
		sf::FloatRect(100, 0, 150, 50),    // Широкая верхняя зона (300px)
		sf::Vector2f(774, 527),            // Появление снизу
		3
	);

	// Верхний правый (широкий)
	screens[0].emplace_back(
		sf::FloatRect(774, 0, 150, 50),    // Широкая верхняя зона (300px)
		sf::Vector2f(100, 527),            // Появление снизу
		4
	);

	/// ОБРАТНЫЕ ПЕРЕХОДЫ ///
	// Магазин (1) → главный
	screens[1].emplace_back(
		sf::FloatRect(940, 150, 80, 300),  // Зеркальная зона
		sf::Vector2f(80, 300),
		0
	);
	
	// Музей (2) → главный
	screens[2].emplace_back(
		sf::FloatRect(0, 150, 80, 300),
		sf::Vector2f(940, 300),
		0
	);

	// Пустыня (3) → главный
	screens[3].emplace_back(
		sf::FloatRect(300, 520, 400, 50),  // Широкая нижняя зона
		sf::Vector2f(350, 50),
		0
	);

	// Джунгли (4) → главный
	screens[4].emplace_back(
		sf::FloatRect(100, 527, 150, 50),  // Широкая нижняя зона
		sf::Vector2f(774, 50),
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
// игровая логика
void Game::update()
{
	this->pollEvents();
	// Управление с учетом времени кадра
	float deltaTime = clock.restart().asSeconds();  // Теперь работает правильно
	float currentSpeed = moveSpeed * deltaTime * 60;
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		playerSprite.move(-currentSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		playerSprite.move(currentSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		playerSprite.move(0, -currentSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		playerSprite.move(0, currentSpeed);

	// Проверка переходов
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	for (const auto& teleport : screens[currentScreen]) {
		if (teleport.checkCollision(playerBounds)) {
			sf::Vector2f newPos = teleport.getTargetPosition();

			if (newPos.x < 50) newPos.x = 80;
			if (newPos.x > 974) newPos.x = 940;
			if (newPos.y < 50) newPos.y = 100;
			if (newPos.y > 477) newPos.y = 400;

			changeScreen(teleport.getTargetScreen(), newPos);
			break;
		}
	}

	// Границы с учетом размера спрайта
	sf::Vector2f pos = playerSprite.getPosition();
	sf::Vector2f size = playerSprite.getGlobalBounds().getSize();

	pos.x = std::clamp(pos.x, 0.f, 1024.f - size.x);
	pos.y = std::clamp(pos.y, 0.f, 577.f - size.y);
	playerSprite.setPosition(pos);
}

// отрисовка игры
void Game::render()
{
	this->window->clear();

	// Отрисовка фона текущего экрана
	this->window->draw(backgroundSprites[currentScreen]);

	// Отрисовка персонажа
	this->window->draw(this->playerSprite);

	// Отладочная отрисовка зон перехода (можно отключить)
	sf::RectangleShape debugZone;
	debugZone.setFillColor(sf::Color(0, 255, 0, 120));
	for (const auto& teleport : screens[currentScreen]) {
		auto rect = teleport.getZoneRect();
		debugZone.setPosition(rect.left, rect.top);
		debugZone.setSize(sf::Vector2f(rect.width, rect.height));
		window->draw(debugZone);
	} // <- Эта скобка была пропущена

	this->window->display();

} 