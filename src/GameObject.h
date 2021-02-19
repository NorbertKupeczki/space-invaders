#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <SFML/Graphics.hpp>

class Alien
{
 public:
  Alien();
  ~Alien();

  void setTexture(sf::Texture& texture);
  sf::Sprite* getSprite();

 private:
  sf::Sprite* sprite = nullptr;
};


#endif // SPACEINVADERS_GAMEOBJECT_H
