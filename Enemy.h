#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Bullet.h"
#include <memory>
#include <random>

class Enemy : public GameObject {
protected:
    int direction;  // 1 for right, -1 for left
    int points;     // Points awarded when destroyed
    double shootProbability;

public:
    // Constructors - Big Five rule
    Enemy();
    Enemy(int x, int y, char symbol, COLORS color, int direction, int points, double shootProbability);
    Enemy(const Enemy& other);
    Enemy(Enemy&& other) noexcept;
    virtual ~Enemy() override;

    // Assignment operator
    Enemy& operator=(const Enemy& other);
    Enemy& operator=(Enemy&& other) noexcept;

    // Getters and Setters
    int getDirection() const;
    int getPoints() const;
    double getShootProbability() const;
    void setDirection(int direction);

    // Update method - override from GameObject
    void update() override;

    // Shooting method
    std::unique_ptr<Bullet> shoot() const;

    // Check if enemy should shoot based on probability
    bool shouldShoot() const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
    friend std::istream& operator>>(std::istream& is, Enemy& enemy);
};

// Different types of enemies
class EnemyType1 : public Enemy {
public:
    EnemyType1(int x, int y);
    EnemyType1(const EnemyType1& other);
    EnemyType1(EnemyType1&& other) noexcept;
    ~EnemyType1() override;

    EnemyType1& operator=(const EnemyType1& other);
    EnemyType1& operator=(EnemyType1&& other) noexcept;
};

class EnemyType2 : public Enemy {
public:
    EnemyType2(int x, int y);
    EnemyType2(const EnemyType2& other);
    EnemyType2(EnemyType2&& other) noexcept;
    ~EnemyType2() override;

    EnemyType2& operator=(const EnemyType2& other);
    EnemyType2& operator=(EnemyType2&& other) noexcept;
};

class EnemyType3 : public Enemy {
public:
    EnemyType3(int x, int y);
    EnemyType3(const EnemyType3& other);
    EnemyType3(EnemyType3&& other) noexcept;
    ~EnemyType3() override;

    EnemyType3& operator=(const EnemyType3& other);
    EnemyType3& operator=(EnemyType3&& other) noexcept;
};

class EnemyType4 : public Enemy {
public:
    EnemyType4(int x, int y);
    EnemyType4(const EnemyType4& other);
    EnemyType4(EnemyType4&& other) noexcept;
    ~EnemyType4() override;

    EnemyType4& operator=(const EnemyType4& other);
    EnemyType4& operator=(EnemyType4&& other) noexcept;
};

#endif // ENEMY_H