#pragma once // защита от повторного включения

#include "Teleport.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

// Структура для хранения истории переходов между экранами
struct ScreenHistory 
{
	int screen; // номер экрана
	sf::Vector2f position; // позиция игрока на этом экране
};

class Game
{
private:
	sf::RenderWindow* window; // окно (указатель, тк создаем через new)
	sf::Event event; 
	sf::VideoMode videoMode; 

	
	// персонаж
	sf::Texture playerTexture ; // текстура персонажа
	sf::Sprite playerSprite; // спрайт 
	float moveSpeed = 5.0f; // скорость перемещения

	// фоны
	vector<sf::Texture> backgroundTextures; 
	vector<sf::Sprite> backgroundSprites;

	// система экранов
	int currentScreen;
	void initScreens(); // инициализая экранов и переходов
	void changeScreen(int newScreen, sf::Vector2f newPosition); // смена экрана
	vector<vector<Teleport>> screens; // зоны для каждого экрана
	vector<ScreenHistory> previousPositions; //Вектор векторов зон телепортации

	// инициализация
	void initaializeVariables();
	void initWindow();
	void loadBackgrounds();

public:
	Game();
	virtual ~Game();

	//функции доступа
	const bool running() const; // проверка, открыто ли окно

	void pollEvents(); // обработка событий (нажатий и тд)
	void update(); // обновление игры
	void render(); // отрисовка графики
	void initPlayer();
};

