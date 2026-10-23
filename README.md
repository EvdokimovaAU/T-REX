
<div align="center">

# RED ICE

### A Choice-Driven Console Strategy Game

**C++ · JSON · Console Application · Resource Management**

*Every decision has consequences.*

</div>

---

## About the Game

**Red Ice** is a text-based console strategy game developed in C++.

The player takes on the role of a cartel leader who must maintain their influence, manage available resources and make strategic decisions while dealing with rival criminal organizations.

Throughout the game, players encounter different scenarios requiring them to choose between alternative approaches, evaluate risks and consider the consequences of their actions.

The game combines branching narrative elements with resource management, combat encounters and progression across multiple levels.

---

## Core Gameplay

### 01. Decision-Making

The player encounters different situations and selects how to respond.

Available choices can affect the outcome of an encounter, available resources and further progression.

### 02. Resource Management

The player must keep track of several parameters:

- Cartel influence.
- Cartel strength / HP.
- Money.
- Available weapons and ammunition.

Managing these resources is an important part of progressing through the game.

### 03. Combat System

The game features encounters with opposing groups.

Enemy health and received damage are handled through a dedicated enemy system.

Different equipment types are represented within the combat mechanics.

### 04. Shop and Equipment

Players can purchase equipment using their available money.

The shop includes:

- Ammunition.
- Grenades.
- RPG ammunition.

Some equipment becomes available only after reaching specific levels.

### 05. Level Progression

The game is organized into five levels, managed through a dedicated GameManager.

The player's decisions and available resources influence their ability to continue.

---

## Technical Implementation

The project was developed using C++, with gameplay logic divided into separate classes.

### Main Components

| Component | Responsibility |
|---|---|
| `GameManager` | Level progression and game flow |
| `PlayerController` | Player statistics and resources |
| `Enemies` | Enemy health and damage handling |
| `Shop` | Equipment purchasing |
| `Level_1` – `Level_5` | Individual level scenarios |
| `Text` | Loading and accessing text content |
| `texts.json` | Dialogue and narrative data |

### JSON-Based Narrative Content

The game's text content is stored separately from the main C++ gameplay logic.

The `texts.json` file contains dialogue, player-facing messages, shop descriptions and level-related narrative content.

This approach separates textual data from program logic and makes it easier to edit the game's narrative without modifying the corresponding C++ strings.

---

## Project Structure

```text
Red-Ice/
│
└── TestRedIce/
    │
    ├── TestRedIce.sln
    │
    └── TestRedIce/
        │
        ├── TestRedIce.cpp
        │
        ├── GameManager.cpp / .h
        ├── PlayerController.cpp / .h
        ├── Enemies.cpp / .h
        ├── Shop.cpp / .h
        ├── Text.cpp / .h
        │
        ├── Level_1.cpp / .h
        ├── Level_2.cpp / .h
        ├── Level_3.cpp / .h
        ├── Level_4.cpp / .h
        ├── Level_5.cpp / .h
        │
        └── texts.json
```

---

## Technologies

| Technology | Purpose |
|---|---|
| C++ | Gameplay programming |
| JSON | Narrative and text storage |
| Visual Studio | Development environment |
| Windows Console | User interaction and output |

---

## How to Run

1. Clone or download the repository.
2. Open `TestRedIce/TestRedIce.sln` in Visual Studio.
3. Restore the project's dependencies if prompted.
4. Build the solution.
5. Make sure `texts.json` is located in the executable's working directory.
6. Run the console application.

The project uses Windows console functions to configure UTF-8 input and output.

---

# На русском

## О проекте

**Red Ice** — текстовая консольная стратегическая игра, написанная на C++.

Игрок принимает на себя роль главы картеля, которому предстоит управлять ресурсами своей организации, поддерживать влияние, противостоять конкурирующим группировкам и принимать решения в различных сюжетных ситуациях.

Игровой процесс строится вокруг выбора стратегии и последствий принятых решений.

## Основные механики

### Система выбора

Игроку предлагаются различные варианты действий, влияющие на развитие событий и исход игровых ситуаций.

### Управление ресурсами

В игре реализованы:

- Влияние картеля.
- Сила организации (HP).
- Денежные средства.
- Инвентарь с оружием и боеприпасами.

### Боевая система

Противники обладают запасом здоровья и получают урон в зависимости от используемого снаряжения и игровых действий.

### Магазин

Игрок может приобретать боеприпасы и дополнительное вооружение.

Часть товаров становится доступной по мере прохождения уровней.

### Система уровней

Игра содержит пять уровней, управление переходами между которыми реализовано через `GameManager`.

---

## Архитектура проекта

Логика игры разделена между несколькими классами:

- `GameManager` — управление игровым процессом и уровнями.
- `PlayerController` — характеристики игрока и управление ресурсами.
- `Enemies` — логика здоровья и получения урона противниками.
- `Shop` — система магазина.
- `Level_1` – `Level_5` — отдельные игровые сценарии.
- `Text` — работа с текстовыми данными.

### Использование JSON

Текстовое наполнение игры вынесено в отдельный файл `texts.json`.

В нём хранятся диалоги, сообщения, описания и сюжетные события.

Такое разделение позволяет изменять текстовую составляющую отдельно от основной логики на C++.

---

## Цель разработки

Практическое применение C++ для создания игры с несколькими взаимосвязанными системами.

В рамках проекта реализованы управление игровым состоянием, обработка пользовательского выбора, система ресурсов, взаимодействие с противниками и загрузка текстовых данных из JSON.

---

<div align="center">

**C++ · Game Logic · Narrative Systems · Resource Management**

</div>
