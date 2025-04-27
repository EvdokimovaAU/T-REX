#pragma once 

#include "Teleport.h"
#include "Loot.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

struct ScreenHistory
{
	int screen; 
	sf::Vector2f position; 
};

class Game
{
private:
	sf::RenderWindow* window; 
	sf::Event event;
	sf::VideoMode videoMode;
	std::vector<sf::Texture> backgroundTextures;
	std::vector<sf::Sprite> backgroundSprites;


	
	sf::Texture playerTexture; 
	sf::Sprite playerSprite;
	float moveSpeed = 5.0f; 

	void initBackgrounds(); 
	
	int currentScreen;
	void initScreens(); 
	void changeScreen(int newScreen, sf::Vector2f newPosition); 
	vector<vector<Teleport>> screens; 
	vector<ScreenHistory> previousPositions; 

	
	void initaializeVariables();
	void initWindow();

	sf::Clock clock;
	sf::Clock portalClock;
	bool canUsePortal = true;

	std::vector<std::vector<Loot>> digSites; // Для каждого экрана (3,4,5)
	sf::Texture buriedTextures[3]; // Текстуры закопанного лута для 3 биомов
	sf::Texture dugOutTextures[4]; // Текстуры раскопанного лута (кости, растение, зуб, единорог)

	void initLootTextures();
	void initDigSites();
	void handleDigging();
	sf::Clock frameClock;
	bool showDebugInfo; // Флаг для отображения отладочной информации
	sf::Font debugFont;  // Шрифт для отладочного текста

public:
	Game();
	virtual ~Game();

	
	const bool running() const; 
	int countDugLoots();
	void pollEvents();
	void update(); 
	void render();
	void initPlayer();
	string getLocationName(int screenIndex) const;


};