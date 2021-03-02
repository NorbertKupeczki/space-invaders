
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
  void initMenus();
  void initPlayer();
  void initAliens();
  void initFont();
  void renderAliens();
  void renderProjectiles();
  void moveBackground(float dt);
  bool moveShips(float dt);
  void changeAlienDirection();
  void increaseAlienSpeed();
  void movePlayer(float dt);
  void collisionCheck();
  void resetGame();
  float getDistance(sf::Vector2<float> obj1_pos,
                    sf::Vector2<float> obj2_pos,
                    sf::Sprite obj1_spr,
                    sf::Sprite obj2_spr);

  sf::Font font;
  sf::Text player_score;

  sf::RenderWindow& window;
  sf::Sprite bg_sprite;
  sf::Texture bg_texture;
  sf::Sprite menu_bg;
  sf::Texture menu_texture;
  sf::Sprite game_over_bg;
  sf::Texture game_over_texture;
  sf::Sprite straight_button;
  sf::Texture straight_active;
  sf::Texture straight_inactive;
  sf::Sprite gravity_button;
  sf::Texture gravity_active;
  sf::Texture gravity_inactive;
  sf::Sprite quadratic_button;
  sf::Texture quadratic_active;
  sf::Texture quadratic_inactive;
  sf::Sprite sine_button;
  sf::Texture sine_active;
  sf::Texture sine_inactive;
  sf::Sprite another_button;
  sf::Texture another_active;
  sf::Texture another_inactive;
  sf::Sprite quit_button;
  sf::Texture quit_active;
  sf::Texture quit_inactive;

  sf::Texture player_ship;
  sf::Texture alien_ship;
  sf::Texture laser_green;

  sf::Sound menu_snd;
  sf::SoundBuffer menu_sbf;

  Alien* aliens = nullptr;
  PlayerShip player;
  const int GRID_SIZE_X = 10;
  const int GRID_SIZE_Y = 2;
  int enemy_count;

  enum GameState
  {
    IN_MENU = 0,
    IN_GAME = 1,
    GAME_OVER = 2
  };

  enum MoveType
  {
    STRAIGHT = 0,
    GRAVITY = 1,
    QUADRATIC = 2,
    SINE_CURVE = 3
  };

  enum GameOver
  {
    TRY_ANOTHER = 0,
    QUIT = 1
  };

  MoveType move_type;
  GameState game_state;
  GameOver game_over_menu;
};

#endif // SPACEINVADERS_GAME_H
