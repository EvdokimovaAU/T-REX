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
		sf::FloatRect(0, 250, 30, 150),    // Узкая (40px) но высокая (300px) зона
		sf::Vector2f(994, 300),            // Появление справа
		1
	);

	// Правый переход в музей (увеличил высоту)
	screens[0].emplace_back(
		sf::FloatRect(994, 250, 30, 150),  // Узкая (40px) но высокая (300px) зона
		sf::Vector2f(30, 350),             // Появление слева
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
		sf::FloatRect(0, 0, 300, 60),    // Широкая верхняя зона (300px)
		sf::Vector2f(724, 517),            // Появление снизу
		3
	);

	// Верхний правый (широкий)
	screens[0].emplace_back(
		sf::FloatRect(664, 0, 300, 60),    // Широкая верхняя зона (300px)
		sf::Vector2f(100, 517),            // Появление снизу
		4
	);

	/// ОБРАТНЫЕ ПЕРЕХОДЫ ///
	// Магазин (1) → главный
	screens[1].emplace_back(
		sf::FloatRect(994, 250, 30, 150),  // Зеркальная зона
		sf::Vector2f(0, 300),
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
		sf::FloatRect(300, 520, 400, 50),  // Широкая нижняя зона
		sf::Vector2f(350, 50),
		0
	);

	// Джунгли (4) → главный
	screens[4].emplace_back(
		sf::FloatRect(100, 517, 300, 60),  // Широкая нижняя зона
		sf::Vector2f(664, 60),
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

void Game::update()
{
	// 1. Обработка событий (нажатия клавиш, закрытие окна)
	this->pollEvents();

	// 2. Расчет времени между кадрами для плавного движения
	float deltaTime = clock.restart().asSeconds();
	float currentSpeed = moveSpeed * deltaTime * 60; // Нормализация скорости

	// 3. Управление персонажем
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		playerSprite.move(-currentSpeed, 0); // Движение влево
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		playerSprite.move(currentSpeed, 0);  // Движение вправо
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		playerSprite.move(0, -currentSpeed); // Движение вверх
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		playerSprite.move(0, currentSpeed);  // Движение вниз
	}

	// 4. Получаем текущие границы спрайта
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	const float buffer = 5.f; // Отступ от краев экрана

	// 5. Ограничение движения в зависимости от текущего экрана
	switch (currentScreen) {
	case 0: // Главный экран
		playerSprite.setPosition(
			std::max(buffer, std::min(playerSprite.getPosition().x, 1024.f - playerBounds.width - buffer)),
			std::max(buffer, std::min(playerSprite.getPosition().y, 577.f - playerBounds.height - buffer))
		);
		break;

	case 1: // Магазин (ограничение слева для выхода)
		playerSprite.setPosition(
			std::max(30.f + buffer, std::min(playerSprite.getPosition().x, 1024.f - playerBounds.width - buffer)),
			std::max(buffer, std::min(playerSprite.getPosition().y, 577.f - playerBounds.height - buffer))
		);
		break;

	case 2: // Музей (ограничение справа для выхода)
		playerSprite.setPosition(
			std::max(buffer, std::min(playerSprite.getPosition().x, 1024.f - playerBounds.width - 30.f - buffer)),
			std::max(buffer, std::min(playerSprite.getPosition().y, 577.f - playerBounds.height - buffer))
		);
		break;

	case 3: // Пустыня (дополнительное ограничение сверху)
		playerSprite.setPosition(
			std::max(buffer, std::min(playerSprite.getPosition().x, 1024.f - playerBounds.width - buffer)),
			std::max(50.f + buffer, std::min(playerSprite.getPosition().y, 577.f - playerBounds.height - buffer))
		);
		break;

	case 4: // Джунгли (дополнительное ограничение снизу)
		playerSprite.setPosition(
			std::max(buffer, std::min(playerSprite.getPosition().x, 1024.f - playerBounds.width - buffer)),
			std::max(buffer, std::min(playerSprite.getPosition().y, 577.f - playerBounds.height - 50.f - buffer))
		);
		break;

	case 5: // Арктика
		playerSprite.setPosition(
			std::max(buffer, std::min(playerSprite.getPosition().x, 1024.f - playerBounds.width - buffer)),
			std::max(buffer, std::min(playerSprite.getPosition().y, 577.f - playerBounds.height - buffer))
		);
		break;
	}

	// 6. Проверка переходов между экранами
	for (const auto& teleport : screens[currentScreen]) {
		if (teleport.checkCollision(playerBounds)) {
			// Корректировка позиции для предотвращения залипания
			sf::Vector2f newPos = teleport.getTargetPosition();

			// Дополнительные проверки для разных экранов
			switch (teleport.getTargetScreen()) {
			case 0: // Возврат на главный
				newPos.x = std::clamp(newPos.x, buffer, 1024.f - playerBounds.width - buffer);
				newPos.y = std::clamp(newPos.y, buffer, 577.f - playerBounds.height - buffer);
				break;

			case 1: // Магазин
				newPos.x = std::max(30.f + buffer, newPos.x);
				break;

			case 2: // Музей
				newPos.x = std::min(newPos.x, 1024.f - playerBounds.width - 30.f - buffer);
				break;
			}

			// Выполняем переход
			changeScreen(teleport.getTargetScreen(), newPos);

			// Прерываем проверку после первого найденного перехода
			break;
		}
	}

	// 7. Дополнительные проверки (по желанию)
	// Например: проверка столкновений с объектами, сбор предметов и т.д.
}

// отрисовка игры
void Game::render()
{
	// 1. Очистка экрана
	window->clear(sf::Color(50, 50, 50)); // Темно-серый фон вместо черного

	// 2. Отрисовка фона
	window->draw(backgroundSprites[currentScreen]);

	// 3. Всегда отображаем порталы (без DEBUG_MODE)
	sf::RectangleShape portalShape;
	portalShape.setOutlineThickness(1.5f);
	portalShape.setOutlineColor(sf::Color(255, 255, 0, 200)); // Ярко-желтая граница
	portalShape.setFillColor(sf::Color(255, 255, 0, 40));     // Полупрозрачная заливка

	for (const auto& portal : screens[currentScreen]) {
		sf::FloatRect rect = portal.getZoneRect();
		portalShape.setPosition(rect.left, rect.top);
		portalShape.setSize(sf::Vector2f(rect.width, rect.height));
		window->draw(portalShape);
	}

	// 4. Отрисовка персонажа с уменьшенными отступами
	const float margin = 2.f; // Меньший отступ (было 5.f)
	sf::FloatRect bounds = playerSprite.getGlobalBounds();

	// Корректировка позиции
	playerSprite.setPosition(
		std::clamp(playerSprite.getPosition().x, margin, 1024.f - bounds.width - margin),
		std::clamp(playerSprite.getPosition().y, margin, 577.f - bounds.height - margin)
	);

	window->draw(playerSprite);


	

	// 6. Отображение кадра
	window->display();
}
