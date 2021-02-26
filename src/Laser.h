#ifndef SPACEINVADERS_LASER_H
#define SPACEINVADERS_LASER_H

#include "Vector2.h"
#include <SFML/Graphics.hpp>

class Laser
{
 public:
  Laser();
  ~Laser();

  void setTexture(sf::Texture& texture);
  sf::Sprite* getSprite();
  bool isInPlay();
  void setState(bool state);
  void setPos(float x, float y);
  void moveLaser(float dt);

 private:
  bool in_play;
  float speed = 700.0;
  Vector2 vector = {0.0,0.0};
  sf::Sprite* sprite;

};

#endif // SPACEINVADERS_LASER_H
