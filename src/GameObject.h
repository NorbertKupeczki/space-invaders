#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"

class Alien
{
 public:
  Alien();
  ~Alien();

  void setTexture(sf::Texture& texture);
  sf::Sprite* getSprite();
  bool moveAliens(float screen_w, float dt, int move_type);
  void changeDirection(int move_type);
  bool isInGame();
  void destroyAlien();
  int getValue();
  void addSpeed(float speed_up);
  void setYSpeed(float new_speed);

 private:
  bool in_game;
  sf::Sprite* sprite = nullptr;
  float speed;
  Vector2 vector = {1.0,0.0};
  int value;
  const float GRAVITY = 1.008;

  sf::Sound explosion_snd;
  sf::SoundBuffer explosion_sbf;
};


#endif // SPACEINVADERS_GAMEOBJECT_H
