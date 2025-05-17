#include "Enemy.h"

// Default constructor
Enemy::Enemy() : GameObject(), direction(1), points(10), shootProbability(0.01) {}

// Parameterized constructor
Enemy::Enemy(int x, int y, char symbol, COLORS color, int direction, int points, double shootProbability)
    : GameObject(x, y, symbol, color), direction(direction), points(points), shootProbability(shootProbability) {}

// Copy constructor
Enemy::Enemy(const Enemy& other)
    : GameObject(other), direction(other.direction), points(other.points), shootProbability(other.shootProbability) {}

// Move constructor
Enemy::Enemy(Enemy&& other) noexcept
    : GameObject(std::move(other)), direction(other.direction), points(other.points), shootProbability(other.shootProbability) {
    other.direction = 0;
    other.points = 0;
    other.shootProbability = 0.0;
}

// Destructor
Enemy::~Enemy() {}

// Copy assignment operator
Enemy& Enemy::operator=(const Enemy& other) {
    if (this != &other) {
        GameObject::operator=(other);
        direction = other.direction;
        points = other.points;
        shootProbability = other.shootProbability;
    }
    return *this;
}

// Move assignment operator
Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        direction = other.direction;
        points = other.points;
        shootProbability = other.shootProbability;

        other.direction = 0;
        other.points = 0;
        other.shootProbability = 0.0;
    }
    return *this;
}

// Getters
int Enemy::getDirection() const { return direction; }
int Enemy::getPoints() const { return points; }
double Enemy::getShootProbability() const { return shootProbability; }

// Setters
void Enemy::setDirection(int direction) { this->direction = direction; }

// Update method
void Enemy::update() {
    x += direction;

    // Change direction if hitting wall
    if (x <= 0 || x >= POLE_COLS - 1) {
        direction = -direction;
        y++;  // Move down when changing direction
    }
}

// Shooting method
std::unique_ptr<Bullet> Enemy::shoot() const {
    return std::make_unique<Bullet>(x, y + 1, 'v', RED, 1);
}

// Check if enemy should shoot
bool Enemy::shouldShoot() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen) < shootProbability;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << static_cast<const GameObject&>(enemy);
    os << ", Direction: " << enemy.direction << ", Points: " << enemy.points;
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, Enemy& enemy) {
    is >> static_cast<GameObject&>(enemy);
    is >> enemy.direction >> enemy.points;
    return is;
}

// EnemyType1 implementation
EnemyType1::EnemyType1(int x, int y)
    : Enemy(x, y, '&', RED, 1, 10, 0.005) {}

EnemyType1::EnemyType1(const EnemyType1& other) : Enemy(other) {}

EnemyType1::EnemyType1(EnemyType1&& other) noexcept
    : Enemy(std::move(other)) {}

EnemyType1::~EnemyType1() {}

EnemyType1& EnemyType1::operator=(const EnemyType1& other) {
    Enemy::operator=(other);
    return *this;
}

EnemyType1& EnemyType1::operator=(EnemyType1&& other) noexcept {
    Enemy::operator=(std::move(other));
    return *this;
}

// EnemyType2 implementation
EnemyType2::EnemyType2(int x, int y)
    : Enemy(x, y, '@', PURPLE, 1, 20, 0.01) {}

EnemyType2::EnemyType2(const EnemyType2& other) : Enemy(other) {}

EnemyType2::EnemyType2(EnemyType2&& other) noexcept
    : Enemy(std::move(other)) {}

EnemyType2::~EnemyType2() {}

EnemyType2& EnemyType2::operator=(const EnemyType2& other) {
    Enemy::operator=(other);
    return *this;
}

EnemyType2& EnemyType2::operator=(EnemyType2&& other) noexcept {
    Enemy::operator=(std::move(other));
    return *this;
}

// EnemyType3 implementation
EnemyType3::EnemyType3(int x, int y)
    : Enemy(x, y, '#', CYAN, 1, 30, 0.015) {}

EnemyType3::EnemyType3(const EnemyType3& other) : Enemy(other) {}

EnemyType3::EnemyType3(EnemyType3&& other) noexcept
    : Enemy(std::move(other)) {}

EnemyType3::~EnemyType3() {}

EnemyType3& EnemyType3::operator=(const EnemyType3& other) {
    Enemy::operator=(other);
    return *this;
}

EnemyType3& EnemyType3::operator=(EnemyType3&& other) noexcept {
    Enemy::operator=(std::move(other));
    return *this;
}

// EnemyType4 implementation
EnemyType4::EnemyType4(int x, int y)
    : Enemy(x, y, '$', YELLOW, 1, 40, 0.02) {}

EnemyType4::EnemyType4(const EnemyType4& other) : Enemy(other) {}

EnemyType4::EnemyType4(EnemyType4&& other) noexcept
    : Enemy(std::move(other)) {}

EnemyType4::~EnemyType4() {}

EnemyType4& EnemyType4::operator=(const EnemyType4& other) {
    Enemy::operator=(other);
    return *this;
}

EnemyType4& EnemyType4::operator=(EnemyType4&& other) noexcept {
    Enemy::operator=(std::move(other));
    return *this;
}
