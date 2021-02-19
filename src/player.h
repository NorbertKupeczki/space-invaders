#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class PlayerShip
{
 public:
  PlayerShip();
  ~PlayerShip();

  void setTexture(sf::Texture& texture);
  void resetShip(float screen_width, float screen_height);
  sf::Sprite* getSprite();

 private:
  Vector2 direction = {0.0,0.0};
  float speed = 20.0;
  sf::Sprite* sprite = nullptr;
};

class Laser
{

};

#endif // SPACEINVADERS_PLAYER_H
