#include "GameObject.h"

// Default constructor
GameObject::GameObject() : x(0), y(0), symbol(' '), color(WHITE) {}

// Parameterized constructor
GameObject::GameObject(int x, int y, char symbol, COLORS color)
    : x(x), y(y), symbol(symbol), color(color) {}

// Copy constructor
GameObject::GameObject(const GameObject& other)
    : x(other.x), y(other.y), symbol(other.symbol), color(other.color) {}

// Move constructor
GameObject::GameObject(GameObject&& other) noexcept
    : x(other.x), y(other.y), symbol(other.symbol), color(other.color) {
    other.x = 0;
    other.y = 0;
    other.symbol = ' ';
    other.color = WHITE;
}

// Destructor
GameObject::~GameObject() {}

// Copy assignment operator
GameObject& GameObject::operator=(const GameObject& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        symbol = other.symbol;
        color = other.color;
    }
    return *this;
}

// Move assignment operator
GameObject& GameObject::operator=(GameObject&& other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
        symbol = other.symbol;
        color = other.color;

        other.x = 0;
        other.y = 0;
        other.symbol = ' ';
        other.color = WHITE;
    }
    return *this;
}

// Getters
int GameObject::getX() const { return x; }
int GameObject::getY() const { return y; }
char GameObject::getSymbol() const { return symbol; }
COLORS GameObject::getColor() const { return color; }

// Setters
void GameObject::setX(int x) { this->x = x; }
void GameObject::setY(int y) { this->y = y; }
void GameObject::setSymbol(char symbol) { this->symbol = symbol; }
void GameObject::setColor(COLORS color) { this->color = color; }

// Render the game object
void GameObject::render() const {
    drawCharAtPosition(x, y, symbol, color);
}

// Collision detection
bool GameObject::collidesWith(const GameObject& other) const {
    return (x == other.x && y == other.y);
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const GameObject& obj) {
    os << "Position: (" << obj.x << ", " << obj.y << "), Symbol: " << obj.symbol;
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, GameObject& obj) {
    is >> obj.x >> obj.y >> obj.symbol;
    return is;
}