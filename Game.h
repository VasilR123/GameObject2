#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>
#include <random>

#include "ConsoleUtils.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
private:
    // Game objects
    Player player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::list<std::unique_ptr<Bullet>> bullets;

    // Game state
    int score;
    int level;
    bool running;
    bool paused;
    std::map<int, std::string> levelMessages;

    // Game parameters
    std::chrono::milliseconds enemyUpdateInterval;
    std::chrono::milliseconds enemyShootInterval;
    int enemyRows;
    int enemyCols;

    // Timer variables
    std::chrono::time_point<std::chrono::steady_clock> lastEnemyUpdate;
    std::chrono::time_point<std::chrono::steady_clock> lastEnemyShoot;

    // Random number generator
    std::random_device rd;
    std::mt19937 gen;

public:
    // Constructors and destructor
    Game();
    ~Game();

    // Game initialization and main loop
    void initialize();
    void run();

    // Game state management
    void pause();
    void resume();
    void reset();

    // Input handling
    void processInput();

    // Game logic
    void update();
    void updateEnemies();
    void updateBullets();
    void checkCollisions();

    // Level management
    void nextLevel();
    void setLevelParameters();

    // Enemy management
    void initializeEnemies();
    void handleEnemyShoot();

    // Rendering
    void render() const;
    void renderStatusBar() const;
    void renderGameOver() const;
    void renderLevelTransition() const;

    // Helper methods
    bool checkLevelComplete() const;
    bool checkGameOver() const;
};

#endif // GAME_H
