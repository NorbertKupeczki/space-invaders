#include "Player.h"

PlayerShip::PlayerShip()
{
  sprite = new sf::Sprite;
}

PlayerShip::~PlayerShip()
{
  delete sprite;
}

void PlayerShip::setTexture(sf::Texture& texture)
{
  sprite->setTexture(texture);
}

void PlayerShip::resetShip(float screen_width, float screen_height)
{
  sprite->setPosition(screen_width/2 - sprite->getGlobalBounds().width/2,
                      screen_height - sprite->getGlobalBounds().height * 1.5);
}

sf::Sprite* PlayerShip::getSprite()
{
  return sprite;
}
