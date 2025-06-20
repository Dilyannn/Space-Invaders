# Space Invaders (C++ / raylib)

**Space Invaders** е ретро аркадна игра, реализирана на C++ с помощта на библиотеката **raylib**. В този README ще намерите подробно описание на файловата структура, йерархията на класовете, функционалността на всеки клас и метод, главната логика на програмата и настройките за нива.

---

## 📂 Файлова структура

```
Space-Invaders/
│
├── CMakeLists.txt            # Конфигуриране на CMake, вкарва raylib
├── main.cpp                  # Точка на вход: инициализация, главен цикъл
│
├── header/                   # Декларации на кла­со­ве и интерфейси
│   ├── Game.hpp              # Управление на цялостната игра
│   ├── GameObject.hpp        # Базов клас за позиция и рендер
│   ├── Player.hpp            # Играч (космически кораб)
│   ├── Enemy.hpp             # Извънземен (враг)
│   ├── Bullet.hpp            # Куршум
│   └── Barrier.hpp           # Бариери и блокове
│
├── source/                   # Имплементация на методите
│   ├── Game.cpp
│   ├── GameObject.cpp
│   ├── Player.cpp
│   ├── Enemy.cpp
│   ├── Bullet.cpp
│   └── Barrier.cpp
│
├── source/images/            # Графични ресурси (.png)
│
└── source/fonts/             # Шрифтове (.otf)
```

---

## 🏗 Основна йерархия на класовете

```plaintext
Game
├─ Player : GameObject
├─ Enemy  : GameObject
├─ Bullet : GameObject
└─ Barrier
    └─ Block

GameObject
└─ (базов клас за Player, Enemy, Bullet)
```

* **Game**: централен контролер, управлява състоянието и обектите.
* **GameObject**: дефинира позиции `x, y` и виртуални методи `update()`, `render()`.
* **Player**, **Enemy**, **Bullet** наследяват `GameObject`.
* **Barrier** съдържа **Block** обекти (не наследява `GameObject`).

---

## 📋 Подробно описание на класовете и методите

### `Game`

**Отговорности**: управление на жизнения цикъл, нивата, точките и животите.

| Метод               | Описание                                                                               |
| ------------------- | -------------------------------------------------------------------------------------- |
| `Game()`            | Конструктор: извиква `initializeGame()`.                                               |
| `~Game()`           | Деструктор: освобождава ресурси при нужда.                                             |
| `initializeGame()`  | Нулира вектори, презарежда бариери и врагове, задава начален брой животи и точки.      |
| `reset()`           | Рестарт на играта: повтаря `initializeGame()`.                                         |
| `gameOver()`        | Спира играта (`runningGame = false`).                                                  |
| `input()`           | Чете клавиши: A/←, D/→ за движение; SPACE за стрелба; ENTER за рестарт (при край).     |
| `update()`          | Премества врагове, обновява куршуми, стреля враг, проверява колизии и смяна на ниво.   |
| `checkCollisions()` | Ръчно обработва сблъсъци: куршуми vs. врагове/бариери и враг–куршум vs. играч/бариери. |
| `render()`          | Рендерира всички обекти и HUD (точки, животи, ниво, съобщения).                        |
| `run()`             | Главен цикъл:                                                                          |

```cpp
while(runningGame && !WindowShouldClose()) {
    input(); update(); render();
}
```

\| `createBarriers()` (статичен)  | Генерира 4 бариери от блокове според дефиниран `grid`.                                     |
\| `createEnemies()`              | Поставя враговете в решетка (rows×cols) с равномерни интервали.                            |
\| `moveEnemies()`                | Хоризонтално мести всички врагове и обръща посоката при достигане на край на екрана.        |
\| `moveDownEnemies(int d)`       | Придвижва враговете надолу при обръщане на посоката.                                        |
\| `enemyShoot()`                 | Произволен „долен“ извънземен изстрелва куршум надолу.                                      |
\| `deleteInactiveBullets()`      | Премахва неактивни куршуми (играч и враг) от вектори.                                       |

**Поля**:

* `Player player`
* `std::vector<Enemy> enemies`
* `std::vector<Barrier> barriers`
* `std::vector<Bullet> enemyBullets`
* `int level, enemyDirection`
* `float timeLastEnemyShot, enemyShotInterval`
* `bool runningGame`

---

### `GameObject`

**Роля**: дефинира общи координати и интерфейс за рендер/ъпдейт.

| Поле/Метод            | Описание                                   |
| --------------------- | ------------------------------------------ |
| `int x, y;`           | Координати на обекта.                      |
| `getX()/getY()`       | Връщат текущата позиция.                   |
| `setX(int)/setY(int)` | Задават нова позиция.                      |
| `virtual update()`    | Логика за ъпдейт (по подразбиране празен). |
| `virtual render()`    | Логика за рендер (по подразбиране празен). |

---

### `Player : GameObject`

**Управлява космическия кораб** — движение, стрелба, живот и точки.

| Метод                         | Описание                                                                            |
| ----------------------------- | ----------------------------------------------------------------------------------- |
| `Player()`                    | Конструктор: зарежда `spaceship.png` и позиционира кораба централно в долната част. |
| `moveLeft()/moveRight()`      | Придвижва кораба в рамките на прозореца.                                            |
| `shoot()`                     | Създава `Bullet` със скорост нагоре и го добавя в `bullets`.                        |
| `draw()`                      | Рисува кораба (`DrawTexture`).                                                      |
| `getRect()`                   | Връща `Rectangle{x,y,width,height}` за колизии.                                     |
| `getPlayerLives()/Score()`    | Гетъри за животи и точки.                                                           |
| `setPlayerLives()/Score()`    | Сетъри за животи и точки.                                                           |
| `reset()`                     | Нулира позицията и параметрите след загубен живот.                                  |
| `std::vector<Bullet> bullets` | Контейнер на изстреляни куршуми.                                                    |

---

### `Enemy : GameObject`

**Враг-извънземен** със собствен тип и текстура.

| Метод                        | Описание                                                      |
| ---------------------------- | ------------------------------------------------------------- |
| `Enemy(int type, x, y)`      | Зарежда текстура според `type` (лилава/зелена/червена/жълта). |
| `update()`                   | Логика за движение (Game::moveEnemies го придвижва).          |
| `render()`                   | Рендерира врага.                                              |
| `getRect()`                  | Връща `Rectangle` за колизии.                                 |
| `static Texture2D images[4]` | Споделен масив от текстури за всички типове врагове.          |
| `static UnloadImages()`      | Освобождава заредените текстури при край на играта.           |

---

### `Bullet : GameObject`

**Проектил** от играча или врага.

| Поле/Метод          | Описание                                                      |
| ------------------- | ------------------------------------------------------------- |
| `Vector2 direction` | Позиция и посока (куршум лети нагоре/надолу).                 |
| `int speed`         | Скорост по Y ос.                                              |
| `Color color`       | Цвят: `MAROON` за играча, случаен за враг.                    |
| `bool active`       | Флаг дали куршумът е активен.                                 |
| `update()`          | Актуализира позицията и деактивира при излизане извън екрана. |
| `render()`          | Рисува куршум на играча.                                      |
| `renderEnemy()`     | Рисува вражески куршум с рандом цвят.                         |
| `getRect()`         | Връща `Rectangle` за сблъсъци.                                |

---

### `Barrier` & `Block`

**Защитни бариери** от малки 6×6 блокчета.

| Клас/Метод         | Описание                                                             |
| ------------------ | -------------------------------------------------------------------- |
| `Barrier()`        | Генерира `blocks` по статична `grid` матрица (1 = блок, 0 = празно). |
| `render()`         | Изчертава всички блокове.                                            |
| `Block({x,y})`     | Конструктор: позиция.                                                |
| `Block::render()`  | Рисува 6×6 пиксела блок.                                             |
| `Block::getRect()` | `Rectangle` за колизии.                                              |

---

## 🕹 Главна логика и цикъл

1. **Инициализация** (`main.cpp`):

   * Създава прозорец, зарежда шрифтове и текстури.
   * `Game game;` → `initializeGame()`.
   * `SetTargetFPS(60);`

2. **Основен цикъл (`run()`)**:

   ```cpp
   while (!WindowShouldClose()) {
       input();
       update();
       BeginDrawing();
         ClearBackground(BLACK);
         render();
       EndDrawing();
   }
   ```

3. **input()**: A/←, D/→ за движение; SPACE за стрелба; ENTER за рестарт.

4. **update()**:

   * `moveEnemies()`
   * `player.bullets` ъпдейт + почистване
   * `enemyShoot()` → `enemyBullets` ъпдейт + почистване
   * `checkCollisions()`
   * Ако `enemies.empty()`:

     * `level++`; ускорява скорост и стрелба;
     * ако `level > 3`, `gameOver()`.

5. **render()**:

   * `player.draw()`, `enemy.render()`, `barrier.render()`, `bullet.render()`
   * HUD: **Score**, **Lives**, **Level**
   * Ако !`runningGame`: показва **GAME OVER** или **YOU WON!!!** и ENTER за рестарт.

---

## 📈 Нива и скалируемост

* **Начално**:
  `enemyDirection = 1.0f;`
  `enemyShotInterval = 0.75f;`
* **След всяко ниво**:

  * `enemyDirection *= 1.2f;`
  * `enemyShotInterval *= 0.9f;`
* **Максимум 3 нива** → победа (You Won).

---

## 📜 Лиценз

Този проект е лицензираан под **MIT License**.
Виж **LICENSE** за подробности.

---

## 👤 Автор

*Вашето Име* — Първи курс, *Университет*, 2025.
