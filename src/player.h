#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H
#include "Laser.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>

class PlayerShip
{
 public:
  PlayerShip();
  ~PlayerShip();

  void setTexture(sf::Texture& texture);
  void setLaserTexture(sf::Texture& texture);
  void resetShip(float screen_width, float screen_height);
  sf::Sprite* getSprite();
  void setDir(float dir);
  void movePlayer(float screen_width, float dt);
  void fireLaser();
  int getMaxProjectile();
  Laser* projectiles();
  int getScore();
  void addScore(int points);
  void resetScore();
  void setFiringState(bool state);
  bool isFiring();

 private:
  Vector2 direction = {0.0,0.0};
  float speed;
  sf::Sprite* sprite = nullptr;
  float cooldown;
  int score;
  bool firing = false;

  Laser* laser = nullptr;
  const int MAX_PROJECTILE = 5;
  const float RATE_OF_FIRE = 0.3;

};

#endif // SPACEINVADERS_PLAYER_H
