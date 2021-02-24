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

 private:
  Vector2 direction = {0.0,0.0};
  float speed = 150.0;
  sf::Sprite* sprite = nullptr;
  int rate_of_fire;

  Laser* laser = nullptr;
  const int MAX_PROJECTILE = 10;

};

#endif // SPACEINVADERS_PLAYER_H
