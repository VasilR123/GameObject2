#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject {
private:
    int direction;  // -1 for up (player bullet), 1 for down (enemy bullet)

public:
    // Constructors - Big Five rule
    Bullet();
    Bullet(int x, int y, char symbol, COLORS color, int direction);
    Bullet(const Bullet& other);
    Bullet(Bullet&& other) noexcept;
    ~Bullet() override;

    // Assignment operator
    Bullet& operator=(const Bullet& other);
    Bullet& operator=(Bullet&& other) noexcept;

    // Getters and Setters
    int getDirection() const;
    void setDirection(int direction);

    // Update method - override from GameObject
    void update() override;

    // Check if bullet is out of bounds
    bool isOutOfBounds() const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Bullet& bullet);
    friend std::istream& operator>>(std::istream& is, Bullet& bullet);
};

#endif // BULLET_H


