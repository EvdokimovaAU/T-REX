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
	this->videoMode.height = 577;
	this->videoMode.width = 1024;
	// задаем окно
	this->window = new sf::RenderWindow(this->videoMode, "Paleontolog", sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::loadBackgrounds()
{
	backgroundTextures.clear();
	backgroundSprites.clear();

	vector<string>bgPaths = {
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/baza.jpg",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/shop.jpg",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/museum.jpg",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/desert.jpg",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/jungle.jpg",
		"C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/arctica.jpg"
	};

	for (const auto& path : bgPaths) {
		sf::Texture texture;
		if (!texture.loadFromFile(path)) {
			std::cerr << "Error loading: " << path << std::endl;
			// Создаем текстуру-заглушку
			texture.create(1024, 577);
			sf::Image img;
			img.create(1024, 577, sf::Color(100, 100, 150)); // Серый
			texture.loadFromImage(img);
		}
		backgroundTextures.push_back(texture);
		backgroundSprites.emplace_back(backgroundTextures.back());
	}

	if (backgroundSprites.size() != 6) {
		std::cerr << "Warning: Not all backgrounds loaded! Loaded: "
			<< backgroundSprites.size() << "/6" << std::endl;
	}
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
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			window->close();
	}
}

// персонаж
void Game::initPlayer()
{
	if (!playerTexture.loadFromFile("C:/Users/admin/Desktop/ДИНОЗАВР/ДИНОЗАВР/x64/Debug/dino.png")) {
		std::cerr << "Failed to load player texture!" << std::endl;
		sf::Image img;
		img.create(50, 50, sf::Color::Green);
		playerTexture.loadFromImage(img);
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(0.5f, 0.5f);
	playerSprite.setPosition(512, 288); 
	
}



// реализация системы экранов
void Game::initScreens()
{
	screens.resize(6);

	// Главный экран (0)
	screens[0].emplace_back(sf::FloatRect(0, 200, 50, 300), sf::Vector2f(974, 300), 1); // Влево
	screens[0].emplace_back(sf::FloatRect(974, 200, 50, 300), sf::Vector2f(50, 300), 2); // Вправо
	screens[0].emplace_back(sf::FloatRect(400, 557, 200, 20), sf::Vector2f(512, 50), 5); // Вниз
	screens[0].emplace_back(sf::FloatRect(400, 0, 200, 50), sf::Vector2f(512, 527), 3); // Вверх-лево
	screens[0].emplace_back(sf::FloatRect(800, 0, 200, 50), sf::Vector2f(112, 527), 4); // Вверх-право

	// Левый экран (1)
	screens[1].emplace_back(sf::FloatRect(974, 200, 50, 300), sf::Vector2f(50, 300), 0);

	// Правый экран (2)
	screens[2].emplace_back(sf::FloatRect(0, 200, 50, 300), sf::Vector2f(974, 300), 0);

	// Верхний левый экран (3)
	screens[3].emplace_back(sf::FloatRect(0, 527, 1024, 50), sf::Vector2f(512, 50), 0);

	// Верхний правый экран (4)
	screens[4].emplace_back(sf::FloatRect(0, 527, 1024, 50), sf::Vector2f(512, 50), 0);

	// Нижний экран (5)
	screens[5].emplace_back(sf::FloatRect(0, 0, 1024, 50), sf::Vector2f(512, 527), 0);
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




