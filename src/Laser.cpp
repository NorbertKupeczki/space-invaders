#include "Laser.h"

Laser::Laser()
{
  sprite = new sf::Sprite;
  in_play = false;
}

Laser::~Laser()
{
  delete sprite;
}

void Laser::setTexture(sf::Texture& texture)
{
  sprite->setTexture(texture);
}

sf::Sprite * Laser::getSprite()
{
  return sprite;
}

bool Laser::isInPlay()
{
  return in_play;
}

void Laser::setState(bool state)
{
  in_play = state;
}

void Laser::setPos(float x, float y)
{
  sprite->setPosition(x - sprite->getGlobalBounds().width / 2,
                      y + sprite->getGlobalBounds().height / 2);
  vector.y = -1.0;
}

void Laser::moveLaser(float dt)
{
  sprite->move(0.0, vector.y * speed * dt);
  if (sprite->getPosition().y < -sprite->getGlobalBounds().height)
  {
    in_play = false;
  }
}