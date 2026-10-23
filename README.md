
<div align="center">

# T-REX

### My First Game

**C++ · SFML · 2D · Solo Development**

*Explore different biomes, uncover ancient treasures and manage your resources.*

---

**My first independently developed game, created entirely in C++ using the SFML library.**

</div>

---

## About the Game

**T-REX** is a 2D excavation game and my very first game development project.

The player takes on the role of an explorer searching for fossils and other discoveries across different environments.

To progress, the player must explore excavation sites, use digging tools, collect valuable items and manage limited resources.

Discovered objects can be sold at the museum to earn money, which can then be spent on supplies and equipment.

The project was developed independently, from implementing the core mechanics to connecting the individual gameplay systems.

---

## Gameplay Features

### 01. Exploration & Biomes

The game features three different excavation environments:

- Desert
- Jungle
- Arctic

Each environment has its own excavation implementation and can affect the player's experience.

### 02. Excavation System

Players can excavate buried objects using different digging tools.

The system includes:

- Excavation sites.
- Different collectible items.
- Digging progress.
- Object states, including buried, excavated and broken.
- Tool-specific digging animations.

### 03. Digging Tools

Three tools are available:

- Brush
- Shovel
- Pickaxe

Each tool has its own durability, introducing an additional resource-management element.

### 04. Collectibles & Inventory

The game features several collectible item types:

- Bones
- Plants
- Teeth
- Unicorn-related discoveries

Collected items are tracked through the player's inventory.

### 05. Museum & Economy

Players can sell collected discoveries at the museum.

Different collectible types have different values.

Money can then be used to purchase supplies and equipment in the shop.

### 06. Survival Elements

The player must manage hunger alongside their available money and supplies.

These mechanics connect exploration with the game's economy and progression.

### 07. Save System

The project includes functionality for saving and loading game progress using a local text file.

---

## Technical Implementation

The game was programmed independently in C++ using SFML.

Its functionality is divided into several classes responsible for individual gameplay systems.

| Class | Responsibility |
|---|---|
| `Game` | Main game loop and gameplay management |
| `Excavation` | Excavation mechanics and biome-specific logic |
| `Loot` | Collectible objects and excavation states |
| `DigAnimation` | Frame-based digging animations |
| `Teleport` | Transitions between game areas |
| `UIText` | Text rendering and interface elements |

### Object-Oriented Design

Different excavation environments inherit from a common `Excavation` base class.

The project includes separate implementations for the desert, jungle and Arctic environments.

### Game State Management

The main game system manages:

- Player statistics.
- Money and hunger.
- Available supplies.
- Tool durability.
- Inventory contents.
- Current game screen.
- Saving and loading progress.

---

## Project Structure

```text
T-REX/
│
├── ДИНОЗАВР.cpp
│
├── Game.cpp
├── Game.h
│
├── Excavation.cpp
├── Excavation.h
│
├── Loot.cpp
├── Loot.h
│
├── DigAnimation.cpp
├── DigAnimation.h
│
├── Teleport.cpp
├── Teleport.h
│
├── UIText.cpp
├── UIText.h
│
└── save.txt
```

---

## Technologies

| Technology | Application |
|---|---|
| C++ | Core gameplay programming |
| SFML | Graphics, window management and input |
| OOP | Game system architecture |
| File I/O | Saving and loading game progress |

---

## Development Experience

T-REX was my first experience developing a game independently.

Working on this project helped me understand how separate gameplay mechanics interact and how to organize a game without relying on a full-featured game engine.

It was an important starting point for my subsequent work with Unity, Unreal Engine and more complex gameplay systems.

---

# На русском

## О проекте

**T-REX — мой самый первый игровой проект, полностью самостоятельно разработанный на C++ с использованием библиотеки SFML.**

Это двухмерная игра, посвящённая исследованию различных территорий и поиску древних находок.

Игроку предстоит посещать раскопки, находить ценные предметы, следить за состоянием инструментов, управлять ограниченными ресурсами и продавать обнаруженные находки в музее.

Заработанные деньги можно потратить на покупку необходимых припасов и оборудования.

## Основные игровые механики

### Исследование территорий

В игре предусмотрены три типа локаций:

- Пустыня.
- Джунгли.
- Арктика.

Для каждой территории предусмотрена отдельная реализация системы раскопок.

### Система раскопок

Игрок взаимодействует с закопанными объектами, используя различные инструменты.

Реализованы состояния предметов, процесс раскопки и соответствующие анимации.

### Инструменты

В игре присутствуют:

- Кисточка.
- Лопата.
- Кирка.

Инструменты имеют ограниченную прочность.

### Инвентарь

Реализована система сбора и хранения найденных объектов, включая кости, растения, зубы и другие находки.

### Экономика

Игрок может продавать находки в музее, получать деньги и покупать необходимые предметы в магазине.

### Элементы выживания

Реализованы показатели голода, денежных средств и доступных припасов.

### Система сохранений

Предусмотрена возможность сохранения и загрузки игрового прогресса через текстовый файл.

---

## Техническая реализация

**Язык:** C++  
**Библиотека:** SFML  
**Тип разработки:** Индивидуальный проект

В рамках разработки самостоятельно реализовала:

- Основной игровой цикл.
- Обработку пользовательского ввода.
- Перемещение игрока.
- Систему переходов между игровыми экранами.
- Механики раскопок.
- Работу с игровыми объектами.
- Покадровые анимации инструментов.
- Инвентарь и экономику.
- Управление игровыми ресурсами.
- Сохранение и загрузку прогресса.

## Значение проекта

T-REX стал моей отправной точкой в разработке игр.

Именно в процессе его создания я получила первый практический опыт организации игровых систем, объектно-ориентированного программирования и разработки полноценного игрового процесса на C++ без использования готового игрового движка.

---

<div align="center">

**My First Game · My Starting Point in Game Development**

</div>
