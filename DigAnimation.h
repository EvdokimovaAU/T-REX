#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class DigAnimation
{
private:
    std::vector<sf::Texture> frames; // вектор текстур для кажров анимации
    sf::Sprite currentSprite; // спрайт для отображения текущего слайда
    int currentFrame; 

    float frameDuration; 
    float elapsedTime; 
   
    float scale; 
    float totalDuration; 
    float currentTime; 

    bool isPlaying; 
    bool animationFinished; 

public:
    DigAnimation();
    void loadFrames(const std::vector<std::string>& framePaths); 
    void setPosition(const sf::Vector2f& position); 
    void setScale(float newScale);
    void play(); 
    void update(float deltaTime); // deltaTime - время, прошедшее с предыдущего кадра
    void draw(sf::RenderWindow& window);
    bool isPlayingAnimation() const;
    bool isAnimationFinished() const;
    void setTotalDuration(float duration);
};