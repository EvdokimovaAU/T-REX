#include "DigAnimation.h"
#include <iostream>

DigAnimation::DigAnimation()
    : currentFrame(0), frameDuration(0.1f), elapsedTime(0.f),
    isPlaying(false), scale(1.0f) {
}

void DigAnimation::loadFrames(const std::vector<std::string>& framePaths) {
    frames.clear();
    for (const auto& path : framePaths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            frames.push_back(texture);
        }
        else {
            std::cerr << "Failed to load animation frame: " << path << std::endl;
        }
    }
    if (!frames.empty()) {
        currentSprite.setTexture(frames[0]);
        currentSprite.setScale(scale, scale);
    }
}

void DigAnimation::setPosition(const sf::Vector2f& position) {
    currentSprite.setPosition(position);
}

void DigAnimation::setScale(float newScale) {
    scale = newScale;
    currentSprite.setScale(scale, scale);
}

void DigAnimation::play() {
    if (!frames.empty()) {
        currentFrame = 0;
        elapsedTime = 0.f;
        isPlaying = true;
        currentSprite.setTexture(frames[0]);
        currentSprite.setScale(scale, scale);
    }
}

void DigAnimation::update(float deltaTime) {
    if (!isPlaying || frames.empty()) return;

    elapsedTime += deltaTime;
    if (elapsedTime >= frameDuration) {
        elapsedTime = 0.f;
        currentFrame++;
        if (currentFrame >= frames.size()) {
            isPlaying = false;
        }
        else {
            currentSprite.setTexture(frames[currentFrame]);
            currentSprite.setScale(scale, scale);
        }
    }
}

void DigAnimation::draw(sf::RenderWindow& window) {
    if (isPlaying) {
        window.draw(currentSprite);
    }
}

bool DigAnimation::isPlayingAnimation() const {
    return isPlaying;
}