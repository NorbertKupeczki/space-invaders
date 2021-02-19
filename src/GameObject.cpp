#include "GameObject.h"

Alien::Alien()
{
  sprite = new sf::Sprite;
}
Alien::~Alien()
{
  delete sprite;
}

void Alien::setTexture(sf::Texture& texture)
{
  sprite->setTexture(texture);
}

sf::Sprite* Alien::getSprite()
{
  return sprite;
}

