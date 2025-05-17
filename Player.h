#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Bullet.h"
#include <vector>
#include <memory>

class Player : public GameObject {
private:
    int lives;
    int score;

public:
    // Constructors - Big Five rule
    Player();
    Player(int x, int y, char symbol = 'A', COLORS color = GREEN);
    Player(const Player& other);
    Player(Player&& other) noexcept;
    ~Player() override;

    // Assignment operator
    Player& operator=(const Player& other);
    Player& operator=(Player&& other) noexcept;

    // Getters and Setters
    int getLives() const;
    int getScore() const;
    void setLives(int lives);
    void setScore(int score);

    // Movement and shooting methods
    void moveLeft();
    void moveRight();
    std::unique_ptr<Bullet> shoot() const;

    // Override update method
    void update() override;

    // Operator overloading for score management
    Player& operator+(int points);
    Player& operator-(int points);

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    friend std::istream& operator>>(std::istream& is, Player& player);
};

#endif // PLAYER_H
