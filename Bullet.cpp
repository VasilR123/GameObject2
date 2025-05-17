#include "Bullet.h"

// Default constructor
Bullet::Bullet() : GameObject(), direction(-1) {
    symbol = '^';
    color = YELLOW;
}

// Parameterized constructor
Bullet::Bullet(int x, int y, char symbol, COLORS color, int direction)
    : GameObject(x, y, symbol, color), direction(direction) {}

// Copy constructor
Bullet::Bullet(const Bullet& other)
    : GameObject(other), direction(other.direction) {}

// Move constructor
Bullet::Bullet(Bullet&& other) noexcept
    : GameObject(std::move(other)), direction(other.direction) {
    other.direction = 0;
}

// Destructor
Bullet::~Bullet() {}

// Copy assignment operator
Bullet& Bullet::operator=(const Bullet& other) {
    if (this != &other) {
        GameObject::operator=(other);
        direction = other.direction;
    }
    return *this;
}

// Move assignment operator
Bullet& Bullet::operator=(Bullet&& other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        direction = other.direction;

        other.direction = 0;
    }
    return *this;
}

// Getters
int Bullet::getDirection() const { return direction; }

// Setters
void Bullet::setDirection(int direction) { this->direction = direction; }

// Update method
void Bullet::update() {
    y += direction;
}

// Check if bullet is out of bounds
bool Bullet::isOutOfBounds() const {
    return y < 0 || y >= POLE_ROWS;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Bullet& bullet) {
    os << static_cast<const GameObject&>(bullet);
    os << ", Direction: " << bullet.direction;
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, Bullet& bullet) {
    is >> static_cast<GameObject&>(bullet);
    is >> bullet.direction;
    return is;
}
