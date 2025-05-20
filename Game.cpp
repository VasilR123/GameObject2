#include "Game.h"

// Constructor
Game::Game()
    : score(0), level(1), running(true), paused(false),
    enemyUpdateInterval(std::chrono::milliseconds(500)), enemyShootInterval(std::chrono::milliseconds(1000)),
    enemyRows(5), enemyCols(10),
    gen(rd()) {

    // Initialize level messages
    levelMessages[1] = "Level 1: Basic Invasion";
    levelMessages[2] = "Level 2: Aggressive Attack";
    levelMessages[3] = "Level 3: Final Assault";

    initialize();
}


Game::~Game() {}

void Game::initialize() {
    clearScreen();
    hideCursor();

    player = Player(POLE_COLS / 2, POLE_ROWS - 5, 'A', GREEN);
    player.setLives(3);
    player.setScore(0);

    initializeEnemies();

    bullets.clear();

    lastEnemyUpdate = std::chrono::steady_clock::now();
    lastEnemyShoot = std::chrono::steady_clock::now();

    setLevelParameters();
}

void Game::run() {
    renderLevelTransition();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (running) {
        if (!paused) {
            // Process input, update game state, and render
            processInput();
            update();
            render();

            // Check for level completion or game over
            if (checkLevelComplete()) {
                level++;
                if (level > 3) {
                    // Player has won the game
                    clearScreen();
                    drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2, "CONGRATULATIONS! YOU WON!", YELLOW);
                    drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2 + 2, "Final Score: " + std::to_string(player.getScore()), WHITE);
                    drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2 + 4, "Press any key to exit...", LIGHT_GREY);
                    _getch();
                    running = false;
                }
                else {
                    renderLevelTransition();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    nextLevel();
                }
            }

            if (checkGameOver()) {
                renderGameOver();
                _getch();
                running = false;
            }
        }
        else {
            // Game is paused, just wait for input
            drawTextAtPosition(POLE_COLS / 2 - 10, POLE_ROWS / 2, "GAME PAUSED", YELLOW);
            drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2 + 2, "Press P to resume", WHITE);

            char key = _getch();
            if (key == 'p' || key == 'P') {
                paused = false;
                clearScreen();
            }
            else if (key == 27) { // ESC key
                running = false;
            }
        }

        // Limit frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// Process user input
void Game::processInput() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a':
        case 'A':
        case 75: // Left arrow
            player.moveLeft();
            break;

        case 'd':
        case 'D':
        case 77: // Right arrow
            player.moveRight();
            break;

        case ' ': // Space bar
            bullets.push_back(player.shoot());
            break;

        case 'p':
        case 'P':
            paused = true;
            break;

        case 27: // ESC key
            running = false;
            break;
        }
    }
}

// Update game state
void Game::update() {
    auto currentTime = std::chrono::steady_clock::now();

    // Update player
    player.update();

    // Update enemies at intervals based on level
    if (currentTime - lastEnemyUpdate >= enemyUpdateInterval) {
        updateEnemies();
        lastEnemyUpdate = currentTime;
    }

    // Handle enemy shooting
    if (currentTime - lastEnemyShoot >= enemyShootInterval) {
        handleEnemyShoot();
        lastEnemyShoot = currentTime;
    }

    // Update bullets
    updateBullets();

    // Check collisions
    checkCollisions();
}

// Update enemies
void Game::updateEnemies() {
    bool shouldMoveDown = false;

    // Check if any enemy is at the edge
    for (const auto& enemy : enemies) {
        if (enemy->getX() <= 0 || enemy->getX() >= POLE_COLS - 1) {
            shouldMoveDown = true;
            break;
        }
    }

    // Update enemy positions
    for (auto& enemy : enemies) {
        if (shouldMoveDown) {
            enemy->setDirection(-enemy->getDirection());
            enemy->setY(enemy->getY() + 1);
        }
        enemy->update();
    }
}

// Update bullets
void Game::updateBullets() {
    // Update bullet positions
    for (auto& bullet : bullets) {
        bullet->update();
    }

    // Remove out-of-bounds bullets
    bullets.remove_if([](const std::unique_ptr<Bullet>& bullet) {
        return bullet->isOutOfBounds();
        });
}

// Handle enemy shooting
void Game::handleEnemyShoot() {
    std::uniform_int_distribution<> dis(0, enemies.size() - 1);

    // Allow enemies to shoot based on their probability
    for (const auto& enemy : enemies) {
        if (enemy->shouldShoot()) {
            bullets.push_back(enemy->shoot());
            // Limit the number of enemy bullets to avoid overwhelming the player
            break;
        }
    }
}

// Check collisions between game objects
void Game::checkCollisions() {
    // Check for collisions between player bullets and enemies
    auto bulletIt = bullets.begin();
    while (bulletIt != bullets.end()) {
        bool bulletHit = false;

        // If it's a player bullet (moving upward)
        if ((*bulletIt)->getDirection() < 0) {
            auto enemyIt = enemies.begin();
            while (enemyIt != enemies.end()) {
                if ((*bulletIt)->collidesWith(**enemyIt)) {
                    // Add points to player's score
                    player.setScore(player.getScore() + (*enemyIt)->getPoints());

                    // Remove enemy and bullet
                    enemyIt = enemies.erase(enemyIt);
                    bulletIt = bullets.erase(bulletIt);
                    bulletHit = true;
                    break;
                }
                else {
                    ++enemyIt;
                }
            }
        }
        // If it's an enemy bullet (moving downward)
        else if ((*bulletIt)->getDirection() > 0) {
            if ((*bulletIt)->collidesWith(player)) {
                // Player is hit, lose a life
                player.setLives(player.getLives() - 1);

                // Remove bullet
                bulletIt = bullets.erase(bulletIt);
                bulletHit = true;
            }
        }

        if (!bulletHit) {
            ++bulletIt;
        }
    }

    // Check if any enemy has reached the player's level
    for (const auto& enemy : enemies) {
        if (enemy->getY() >= player.getY()) {
            player.setLives(0); // Game over if enemies reach the bottom
            break;
        }
    }

    // Check for awarded extra lives (at 300 points)
    static bool extraLifeAwarded = false;
    if (player.getScore() >= 300 && !extraLifeAwarded) {
        player.setLives(player.getLives() + 1);
        extraLifeAwarded = true;
    }
}

// Initialize enemies
void Game::initializeEnemies() {
    enemies.clear();

    // Calculate spacing between enemies
    int startX = (POLE_COLS - (enemyCols * 3)) / 2;
    int startY = 5;

    for (int row = 0; row < enemyRows; ++row) {
        for (int col = 0; col < enemyCols; ++col) {
            int x = startX + col * 3;
            int y = startY + row * 2;

            // Create different types of enemies based on row
            if (row == 0) {
                enemies.push_back(std::make_unique<EnemyType4>(x, y));
            }
            else if (row == 1) {
                enemies.push_back(std::make_unique<EnemyType3>(x, y));
            }
            else if (row == 2 || row == 3) {
                enemies.push_back(std::make_unique<EnemyType2>(x, y));
            }
            else {
                enemies.push_back(std::make_unique<EnemyType1>(x, y));
            }
        }
    }
}

// Render the game
void Game::render() const {
    clearScreen();

    // Render player
    player.render();

    // Render enemies
    for (const auto& enemy : enemies) {
        enemy->render();
    }

    // Render bullets
    for (const auto& bullet : bullets) {
        bullet->render();
    }

    // Render status bar
    renderStatusBar();
}

// Render status bar
void Game::renderStatusBar() const {
    std::string statusText = "Score: " + std::to_string(player.getScore()) +
        " | Lives: " + std::to_string(player.getLives()) +
        " | Level: " + std::to_string(level);

    drawTextAtPosition(2, POLE_ROWS - 2, statusText, WHITE);

    // Instructions
    std::string instructions = "A/D: Move | Space: Shoot | P: Pause | ESC: Exit";
    drawTextAtPosition(POLE_COLS - instructions.length() - 2, POLE_ROWS - 2, instructions, LIGHT_GREY);
}

// Render game over screen
void Game::renderGameOver() const {
    clearScreen();
    drawTextAtPosition(POLE_COLS / 2 - 5, POLE_ROWS / 2 - 2, "GAME OVER", RED);
    drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2, "Final Score: " + std::to_string(player.getScore()), WHITE);
    drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2 + 2, "Level Reached: " + std::to_string(level), WHITE);
    drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2 + 4, "Press any key to exit...", LIGHT_GREY);
}

// Render level transition
void Game::renderLevelTransition() const {
    clearScreen();

    std::string levelMsg = levelMessages.at(level);
    drawTextAtPosition(POLE_COLS / 2 - levelMsg.length() / 2, POLE_ROWS / 2, levelMsg, YELLOW);

    if (level == 1) {
        drawTextAtPosition(POLE_COLS / 2 - 20, POLE_ROWS / 2 + 2, "Get ready for the invasion!", WHITE);
    }
    else if (level == 2) {
        drawTextAtPosition(POLE_COLS / 2 - 23, POLE_ROWS / 2 + 2, "Enemies are getting more aggressive!", WHITE);
    }
    else if (level == 3) {
        drawTextAtPosition(POLE_COLS / 2 - 15, POLE_ROWS / 2 + 2, "This is the final battle!", WHITE);
    }
}

// Check if level is complete
bool Game::checkLevelComplete() const {
    return enemies.empty();
}

// Check if game is over
bool Game::checkGameOver() const {
    return player.getLives() <= 0;
}

// Move to next level
void Game::nextLevel() {
    // Reset enemies and bullets
    initializeEnemies();
    bullets.clear();

    // Update game parameters for the new level
    setLevelParameters();
}

// Set level parameters
void Game::setLevelParameters() {
    switch (level) {
    case 1:
        enemyUpdateInterval = std::chrono::milliseconds(500);
        enemyShootInterval = std::chrono::milliseconds(1500);
        enemyRows = 5;
        enemyCols = 8;
        break;

    case 2:
        enemyUpdateInterval = std::chrono::milliseconds(350);
        enemyShootInterval = std::chrono::milliseconds(1000);
        enemyRows = 6;
        enemyCols = 10;
        break;

    case 3:
        enemyUpdateInterval = std::chrono::milliseconds(200);
        enemyShootInterval = std::chrono::milliseconds(750);
        enemyRows = 7;
        enemyCols = 12;
        break;
    }
}

// Pause the game
void Game::pause() {
    paused = true;
}

// Resume the game
void Game::resume() {
    paused = false;
}

// Reset the game
void Game::reset() {
    level = 1;
    score = 0;
    initialize();
}
