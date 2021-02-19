
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include "Player.h"


class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

 private:
  void loadTexture(sf::Texture& texture,sf::Sprite& sprite, std::string path);
  void loadTexture(sf::Texture& texture, std::string path);
  void initTextures();
  void moveBackground(float dt);

  sf::RenderWindow& window;
  sf::Sprite bg_sprite;
  sf::Texture bg_texture;


  sf::Texture player_ship;
  sf::Texture alien_blue;
  sf::Texture alien_red;
  sf::Texture alien_green;
  sf::Texture alien_yellow;

  Alien* aliens;
  PlayerShip player;

};

#endif // SPACEINVADERS_GAME_H
