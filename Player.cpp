#include "Player.h"

// Default constructor
Player::Player() : GameObject(), lives(3), score(0) {
    symbol = 'A';
    color = GREEN;
}

// Parameterized constructor
Player::Player(int x, int y, char symbol, COLORS color)
    : GameObject(x, y, symbol, color), lives(3), score(0) {}

// Copy constructor
Player::Player(const Player& other)
    : GameObject(other), lives(other.lives), score(other.score) {}

// Move constructor
Player::Player(Player&& other) noexcept
    : GameObject(std::move(other)), lives(other.lives), score(other.score) {
    other.lives = 0;
    other.score = 0;
}

// Destructor
Player::~Player() {}

// Copy assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        GameObject::operator=(other);
        lives = other.lives;
        score = other.score;
    }
    return *this;
}

// Move assignment operator
Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        lives = other.lives;
        score = other.score;

        other.lives = 0;
        other.score = 0;
    }
    return *this;
}

// Getters
int Player::getLives() const { return lives; }
int Player::getScore() const { return score; }

// Setters
void Player::setLives(int lives) { this->lives = lives; }
void Player::setScore(int score) { this->score = score; }

// Movement methods
void Player::moveLeft() {
    if (x > 0) {
        x--;
    }
}

void Player::moveRight() {
    if (x < POLE_COLS - 1) {
        x++;
    }
}

// Shooting method
std::unique_ptr<Bullet> Player::shoot() const {
    return std::make_unique<Bullet>(x, y - 1, '^', YELLOW, -1);
}

// Update method
void Player::update() {
    // Player logic update (could be empty if only controlled by input)
}

// Operator overloading for score management
Player& Player::operator+(int points) {
    score += points;
    return *this;
}

Player& Player::operator-(int points) {
    score -= points;
    if (score < 0) score = 0;
    return *this;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << static_cast<const GameObject&>(player);
    os << ", Lives: " << player.lives << ", Score: " << player.score;
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, Player& player) {
    is >> static_cast<GameObject&>(player);
    is >> player.lives >> player.score;
    return is;
}
