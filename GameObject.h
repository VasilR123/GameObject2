#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "ConsoleUtils.h"
#include <iostream>

class GameObject {
protected:
    int x, y;
    char symbol;
    COLORS color;

public:
    // Constructors - Big Five rule
    GameObject();
    GameObject(int x, int y, char symbol, COLORS color);
    GameObject(const GameObject& other);             // Copy constructor
    GameObject(GameObject&& other) noexcept;         // Move constructor
    virtual ~GameObject();                           // Destructor

    // Assignment operator
    GameObject& operator=(const GameObject& other);
    GameObject& operator=(GameObject&& other) noexcept;

    // Getters and Setters
    int getX() const;
    int getY() const;
    char getSymbol() const;
    COLORS getColor() const;
    void setX(int x);
    void setY(int y);
    void setSymbol(char symbol);
    void setColor(COLORS color);

    // Virtual methods for updating and rendering
    virtual void update() = 0;
    virtual void render() const;

    // Collision detection
    bool collidesWith(const GameObject& other) const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const GameObject& obj);
    friend std::istream& operator>>(std::istream& is, GameObject& obj);
};

#endif // GAME_OBJECT_H
