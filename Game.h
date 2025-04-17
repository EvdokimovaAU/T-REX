#pragma once // çàùèòà îò ïîâòîðíîãî âêëþ÷åíèÿ

#include "Teleport.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

// Ñòðóêòóðà äëÿ õðàíåíèÿ èñòîðèè ïåðåõîäîâ ìåæäó ýêðàíàìè
struct ScreenHistory
{
	int screen; // íîìåð ýêðàíà
	sf::Vector2f position; // ïîçèöèÿ èãðîêà íà ýòîì ýêðàíå
};

class Game
{
private:
	sf::RenderWindow* window; // îêíî (óêàçàòåëü, òê ñîçäàåì ÷åðåç new)
	sf::Event event;
	sf::VideoMode videoMode;
	std::vector<sf::Texture> backgroundTextures;
	std::vector<sf::Sprite> backgroundSprites;
	

	// ïåðñîíàæ
	sf::Texture playerTexture; // òåêñòóðà ïåðñîíàæà
	sf::Sprite playerSprite; // ñïðàéò 
	float moveSpeed = 5.0f; // ñêîðîñòü ïåðåìåùåíèÿ

	void initBackgrounds(); // Добавляем объявление метода
	// ñèñòåìà ýêðàíîâ
	int currentScreen;
	void initScreens(); // èíèöèàëèçàÿ ýêðàíîâ è ïåðåõîäîâ
	void changeScreen(int newScreen, sf::Vector2f newPosition); // ñìåíà ýêðàíà
	vector<vector<Teleport>> screens; // çîíû äëÿ êàæäîãî ýêðàíà
	vector<ScreenHistory> previousPositions; //Âåêòîð âåêòîðîâ çîí òåëåïîðòàöèè

	// èíèöèàëèçàöèÿ
	void initaializeVariables();
	void initWindow();
	sf::Clock clock;  // Таймер для расчета deltaTime
	

public:
	Game();
	virtual ~Game();

	//ôóíêöèè äîñòóïà
	const bool running() const; // ïðîâåðêà, îòêðûòî ëè îêíî

	void pollEvents(); // îáðàáîòêà ñîáûòèé (íàæàòèé è òä)
	void update(); // îáíîâëåíèå èãðû
	void render(); // îòðèñîâêà ãðàôèêè
	void initPlayer();
};