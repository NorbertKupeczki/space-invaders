#include "GameObject.h"
#include <cmath>

Alien::Alien()
{
  sprite = new sf::Sprite;
  speed = 50.0;
  in_game = true;
  value = 10;

  explosion_sbf.loadFromFile("Data/Sound/explosion.ogg");
  explosion_snd.setBuffer(explosion_sbf);
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

bool Alien::moveAliens(float screen_w, float dt, int move_type)
{
  bool reverse_direction = false;
  if (move_type == 0) //STRAIGHT
  {
    sprite->move(vector.x * speed * dt, vector.y * speed * dt);
  }
  else if (move_type == 1)//GRAVITY
  {
    vector.y += GRAVITY;
    sprite->move(vector.x * speed * dt, vector.y);
  }
  else if (move_type == 2) //QUADRATIC
  {
    float curr_y = pow(0.02 * sprite->getPosition().x -10,2);
    float new_y = pow(0.02 * (sprite->getPosition().x + vector.x * speed * dt) - 10,2);
    float diff = curr_y - new_y;
    vector.y = diff;
    sprite->move(vector.x * speed * dt, vector.y);
  }
  else if (move_type == 3) //SINE CURVE
  {
    float curr_y = 20 * sin(sprite->getPosition().x / 10);
    float new_y = 20 * sin((sprite->getPosition().x + vector.x * speed * dt)/10);
    float diff = curr_y - new_y;
    vector.y = diff;
    sprite->move(vector.x * speed * dt, vector.y);
  }

  if ((sprite->getPosition().x <= 0.0 ||
      sprite->getPosition().x + sprite->getGlobalBounds().width >= screen_w) &&
      in_game)
  {
    reverse_direction = true;
  }
  return reverse_direction;
}

void Alien::changeDirection(int move_type)
{
  vector.x = -vector.x;
  if (move_type != 1)
  {
    sprite->move(0.0, sprite->getGlobalBounds().height / 3);
  }
}

bool Alien::isInGame()
{
  return in_game;
}

void Alien::destroyAlien()
{
  explosion_snd.play();
  in_game = false;
}

int Alien::getValue()
{
  return value;
}

void Alien::addSpeed(float speed_up)
{
  speed += speed_up;
}