#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Alien
{
 public:
  Alien();
  ~Alien();

  void setTexture(sf::Texture& texture);
  sf::Sprite* getSprite();
  bool moveAliens(float screen_w, float dt);
  void changeDirection();
  bool isInGame();
  void destroyAlien();
  int getValue();
  void addSpeed(float speed_up);

 private:
  bool in_game;
  sf::Sprite* sprite = nullptr;
  float speed;
  Vector2 vector = {1.0,0.0};
  int value;
};


#endif // SPACEINVADERS_GAMEOBJECT_H
