#include "Game.h"

// конструктор и деструктор
Game::Game()
{
	this->initaializeVariables();
	this->initWindow();
	this->initPlayer();
	this->initScreens();

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
	this->videoMode.height = 600;
	this->videoMode.width = 800;
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
	playerSprite.setPosition(400, 300);
}



// реализация системы экранов
void Game::initScreens()
{
	screens.resize(6);

	/// ГЛАВНЫЙ ЭКРАН (0) ///
	// Левый переход (центр) → экран 1
	screens[0].emplace_back(
		sf::FloatRect(0, 250, 40, 200),   // Зона перехода слева
		sf::Vector2f(760, 300),           // Появление на экране 1
		1
	);

	// Правый переход (центр) → экран 2
	screens[0].emplace_back(
		sf::FloatRect(760, 250, 40, 200), // Зона перехода справа
		sf::Vector2f(40, 300),            // Появление на экране 2
		2
	);

	// Нижний переход → экран 5
	screens[0].emplace_back(
		sf::FloatRect(350, 580, 100, 20), // Зона перехода внизу
		sf::Vector2f(400, 20),            // Появление на экране 5
		5
	);

	// Верхний левый угол → экран 3
	screens[0].emplace_back(
		sf::FloatRect(0, 0, 90, 90),      // Зона перехода
		sf::Vector2f(710, 510),           // Появление на экране 3
		3
	);

	// Верхний правый угол → экран 4
	screens[0].emplace_back(
		sf::FloatRect(710, 0, 90, 90),    // Зона перехода
		sf::Vector2f(90, 510),            // Появление на экране 4
		4
	);

	/// ЛЕВЫЙ ЭКРАН (1) ///
	// Возврат в основной - справа (зеркально главному экрану)
	screens[1].emplace_back(
		sf::FloatRect(760, 250, 40, 200), // Зона перехода справа
		sf::Vector2f(40, 300),            // Появление на экране 0 (где был вход на экран 1)
		0
	);

	/// ПРАВЫЙ ЭКРАН (2) ///
	// Возврат в основной - слева (зеркально главному экрану)
	screens[2].emplace_back(
		sf::FloatRect(0, 250, 40, 200),   // Зона перехода слева
		sf::Vector2f(760, 300),           // Появление на экране 0 (где был вход на экран 2)
		0
	);

	/// ВЕРХНИЙ ЛЕВЫЙ ЭКРАН (3) ///
	// Возврат в основной - внизу справа (зеркально главному экрану)
	screens[3].emplace_back(
		sf::FloatRect(710, 510, 90, 90),  // Зона перехода внизу справа
		sf::Vector2f(90, 90),             // Появление на экране 0 (где был вход на экран 3)
		0
	);

	/// ВЕРХНИЙ ПРАВЫЙ ЭКРАН (4) ///
	// Возврат в основной - внизу слева (зеркально главному экрану)
	screens[4].emplace_back(
		sf::FloatRect(0, 510, 90, 90),   // Зона перехода внизу слева
		sf::Vector2f(710, 90),            // Появление на экране 0 (где был вход на экран 4)
		0
	);

	/// НИЖНИЙ ЭКРАН (5) ///
	// Возврат в основной - сверху (зеркально главному экрану)
	screens[5].emplace_back(
		sf::FloatRect(350, 0, 100, 20),  // Зона перехода сверху
		sf::Vector2f(400, 580),          // Появление на экране 0 (где был вход на экран 5)
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

	// Управление персонажем
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		playerSprite.move(-moveSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		playerSprite.move(moveSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		playerSprite.move(0, -moveSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		playerSprite.move(0, moveSpeed);

	// Проверка переходов между экранами
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	for (const auto& teleport : screens[currentScreen])
	{
		if (teleport.checkCollision(playerBounds))
		{
			changeScreen(teleport.getTargetScreen(), teleport.getTargetPosition());
			break;
		}
	}

	// Границы экрана
	sf::Vector2f position = playerSprite.getPosition();
	sf::Vector2f size(playerBounds.width, playerBounds.height);

	position.x = std::max(0.f, std::min(position.x, videoMode.width - size.x));
	position.y = std::max(0.f, std::min(position.y, videoMode.height - size.y));
	playerSprite.setPosition(position);
}

// отрисовка игры
void Game::render()
{
	window->clear();

	// Добавляем проверку границ массива
	if (!backgroundSprites.empty() && currentScreen >= 0 && currentScreen < backgroundSprites.size()) {
		window->draw(backgroundSprites[currentScreen]);
	}
	else {
		// Резервный фон, если что-то пошло не так
		window->clear(sf::Color::Blue);
	}

	window->draw(playerSprite);
	window->display();
}