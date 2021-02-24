#include "GameObject.h"

Alien::Alien()
{
  sprite = new sf::Sprite;
  speed = 20.0;
  in_game = true;
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

bool Alien::moveAliens(float screen_w, float dt)
{
  bool reverse_direction = false;
  sprite->move(vector.x * speed * dt,vector.y * speed * dt);
  if (sprite->getPosition().x <= 0.0 ||
      sprite->getPosition().x + sprite->getGlobalBounds().width >= screen_w &&
      in_game)
  {
    reverse_direction = true;
  }
  return reverse_direction;
}

void Alien::changeDirection()
{
  vector.x = -vector.x;
  sprite->move(0.0, sprite->getGlobalBounds().height / 2);
}

bool Alien::isInGame()
{
  return in_game;
}
