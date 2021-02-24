#include "Player.h"

PlayerShip::PlayerShip()
{
  sprite = new sf::Sprite;
  laser = new Laser[MAX_PROJECTILE];
}

PlayerShip::~PlayerShip()
{
  delete sprite;
  delete[] laser;
}

void PlayerShip::setTexture(sf::Texture& texture)
{
  sprite->setTexture(texture);
}

void PlayerShip::setLaserTexture(sf::Texture& texture)
{
  for (int i = 0; i < MAX_PROJECTILE; ++i)
  {
    laser[i].setTexture(texture);
  }
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

void PlayerShip::setDir(float dir)
{
  direction.x = dir;
}

void PlayerShip::movePlayer(float screen_width, float dt)
{
  float ship_pos_l = sprite->getPosition().x;
  float ship_pos_r = sprite->getPosition().x
                       + sprite->getGlobalBounds().width;

  if (ship_pos_l + speed * direction.x * dt < 0.0)
  {
    sprite->setPosition(0.0, sprite->getPosition().y);
  }
  else if (ship_pos_r + speed * direction.x * dt > screen_width)
  {
    sprite->setPosition(
      screen_width - sprite->getGlobalBounds().width,
      sprite->getPosition().y
    );
  }
  else
  {
    sprite->move(speed * direction.x * dt, 0.0);
  }
}

void PlayerShip::fireLaser()
{
  for (int i = 0; i < MAX_PROJECTILE; ++i)
  {
    if (!laser[i].isInPlay())
    {
      laser[i].setState(true);
      laser[i].setPos(sprite->getPosition().x + sprite->getGlobalBounds().width / 2,
                      sprite->getPosition().y);
      break;
    }
  }
}

int PlayerShip::getMaxProjectile()
{
  return MAX_PROJECTILE;
}

Laser * PlayerShip::projectiles()
{
  return laser;
}