#include "Game.h"
#include <iostream>
#include <cmath>

// -------------------------------- PUBLIC --------------------------------
Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  move_type = STRAIGHT;
  game_state = IN_MENU;
  game_over_menu = TRY_ANOTHER;
  enemy_count = GRID_SIZE_Y * GRID_SIZE_X;
  menu_sbf.loadFromFile("Data/Sound/menu.wav");
  menu_snd.setBuffer(menu_sbf);
}

Game::~Game()
{
  delete[] aliens;
}

bool Game::init()
{
  initTextures();
  initMenus();
  initPlayer();
  initFont();
  return true;
}

void Game::update(float dt)
{
  player_score.setString("Score: " + std::to_string(player.getScore()));
  if(game_state == IN_GAME)
  {
    moveBackground(dt);
    if (moveShips(dt))
    {
      changeAlienDirection();
    }
    movePlayer(dt);
    if (player.isFiring())
    {
      player.fireLaser();
    }
    collisionCheck();
  }
}

void Game::render()
{
  window.draw(bg_sprite);
  renderProjectiles();
  window.draw(*player.getSprite());
  renderAliens();
  window.draw(player_score);

  if (game_state == IN_MENU)
  {
    window.draw(menu_bg);
    window.draw(straight_button);
    window.draw(gravity_button);
    window.draw(quadratic_button);
    window.draw(sine_button);
  }

  if (game_state == GAME_OVER)
  {
    window.draw(game_over_bg);
    window.draw(another_button);
    window.draw(quit_button);
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if(game_state == IN_MENU)
  {
    if (event.key.code == sf::Keyboard::Up)
    {
      menu_snd.play();
      if (move_type == STRAIGHT)
      {
        move_type = SINE_CURVE;
        straight_button.setTexture(straight_inactive);
        sine_button.setTexture(sine_active);
      }
      else if (move_type == GRAVITY)
      {
        move_type = STRAIGHT;
        gravity_button.setTexture(gravity_inactive);
        straight_button.setTexture(straight_active);
      }
      else if (move_type == QUADRATIC)
      {
        move_type = GRAVITY;
        quadratic_button.setTexture(quadratic_inactive);
        gravity_button.setTexture(gravity_active);
      }
      else if (move_type == SINE_CURVE)
      {
        move_type = QUADRATIC;
        sine_button.setTexture(sine_inactive);
        quadratic_button.setTexture(quadratic_active);
      }
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
      menu_snd.play();
      if (move_type == STRAIGHT)
      {
        move_type = GRAVITY;
        straight_button.setTexture(straight_inactive);
        gravity_button.setTexture(gravity_active);
      }
      else if (move_type == GRAVITY)
      {
        move_type = QUADRATIC;
        gravity_button.setTexture(gravity_inactive);
        quadratic_button.setTexture(quadratic_active);
      }
      else if (move_type == QUADRATIC)
      {
        move_type = SINE_CURVE;
        quadratic_button.setTexture(quadratic_inactive);
        sine_button.setTexture(sine_active);
      }
      else if (move_type == SINE_CURVE)
      {
        move_type = STRAIGHT;
        sine_button.setTexture(sine_inactive);
        straight_button.setTexture(straight_active);
      }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
      menu_snd.play();
      game_state = IN_GAME;
      initAliens();
    }
  }

  else if (game_state == IN_GAME)
  {
    if (event.key.code == sf::Keyboard::Left)
    {
      player.setDir(-1.0);
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
      player.setDir(1.0);
    }

    if (event.key.code == sf::Keyboard::Space)
    {
      player.setFiringState(true);
    }
  }

  else if (game_state == GAME_OVER)
  {
    if (event.key.code == sf::Keyboard::Up ||
        event.key.code == sf::Keyboard::Down)
    {
      menu_snd.play();
      if (game_over_menu == TRY_ANOTHER)
      {
        game_over_menu = QUIT;
        another_button.setTexture(another_inactive);
        quit_button.setTexture(quit_active);
      }
      else
      {
        game_over_menu = TRY_ANOTHER;
        another_button.setTexture(another_active);
        quit_button.setTexture(quit_inactive);
      }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
      menu_snd.play();
      if (game_over_menu == TRY_ANOTHER)
      {
        resetGame();
      }
      else
      {
        window.close();
      }
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Left ||
      event.key.code == sf::Keyboard::Right)
  {
    player.setDir(0.0);
  }

  if (event.key.code == sf::Keyboard::Space)
  {
    player.setFiringState(false);
  }
}

// -------------------------------- PRIVATE --------------------------------

void Game::loadTexture(sf::Texture& texture,sf::Sprite& sprite, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
  sprite.setTexture(texture);
}

void Game::loadTexture(sf::Texture& texture, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
}

void Game::initTextures()
{
  loadTexture(bg_texture, bg_sprite, "Data/Images/bground.png");
  loadTexture(menu_texture, menu_bg, "Data/Images/menu_bg.png");
  loadTexture(game_over_texture, game_over_bg, "Data/Images/gameover_bg.png");
  loadTexture(straight_active, straight_button, "Data/Images/straight_active.png");
  loadTexture(straight_inactive, "Data/Images/straight_inactive.png");
  loadTexture(gravity_inactive, gravity_button, "Data/Images/gravity_inactive.png");
  loadTexture(gravity_active, "Data/Images/gravity_active.png");
  loadTexture(quadratic_inactive, quadratic_button, "Data/Images/quadratic_inactive.png");
  loadTexture(quadratic_active, "Data/Images/quadratic_active.png");
  loadTexture(sine_inactive, sine_button, "Data/Images/sine_inactive.png");
  loadTexture(sine_active, "Data/Images/sine_active.png");
  loadTexture(another_active, another_button, "Data/Images/another_active.png");
  loadTexture(another_inactive, "Data/Images/another_inactive.png");
  loadTexture(quit_inactive, quit_button, "Data/Images/quit_inactive.png");
  loadTexture(quit_active, "Data/Images/quit_active.png");
  loadTexture(player_ship, "Data/Images/playerShip.png");
  loadTexture(alien_ship, "Data/Images/alienShip.png");
  loadTexture(laser_green, "Data/Images/laser_green.png");

  bg_texture.setRepeated(true);
  bg_sprite.setTextureRect(
    sf::IntRect( 0.0,0.0,
                 window.getSize().x,
                 bg_texture.getSize().y * 5));
  bg_sprite.setPosition(0,-256);
}

void Game::initMenus()
{
  float centre_x = window.getSize().x / 2;
  float centre_y = window.getSize().y /2;

  menu_bg.setPosition(centre_x - menu_bg.getGlobalBounds().width /2,
                      centre_y - menu_bg.getGlobalBounds().height /2);
  straight_button.setPosition(
    centre_x - straight_button.getGlobalBounds().width /2,
    centre_y - straight_button.getGlobalBounds().height /2 -
    straight_button.getGlobalBounds().height * 1.65
    );
  gravity_button.setPosition(
      centre_x - gravity_button.getGlobalBounds().width /2,
      centre_y - gravity_button.getGlobalBounds().height /2 -
        gravity_button.getGlobalBounds().height * 0.55
      );
  quadratic_button.setPosition(
      centre_x - quadratic_button.getGlobalBounds().width /2,
      centre_y - quadratic_button.getGlobalBounds().height /2 +
        quadratic_button.getGlobalBounds().height * 0.55
      );
  sine_button.setPosition(
      centre_x - sine_button.getGlobalBounds().width /2,
      centre_y - sine_button.getGlobalBounds().height /2 +
        sine_button.getGlobalBounds().height * 1.65
      );

  game_over_bg.setPosition(centre_x - game_over_bg.getGlobalBounds().width /2,
                           centre_y - game_over_bg.getGlobalBounds().height /2);

  another_button.setPosition(
      centre_x - another_button.getGlobalBounds().width /2,
      centre_y - another_button.getGlobalBounds().height /2 -
        another_button.getGlobalBounds().height * 0.8
      );
  quit_button.setPosition(
      centre_x - quit_button.getGlobalBounds().width /2,
      centre_y - quit_button.getGlobalBounds().height /2 +
        quit_button.getGlobalBounds().height * 0.8
      );
}

void Game::initPlayer()
{
  player.setTexture(player_ship);
  player.setLaserTexture(laser_green);
  player.resetShip(window.getSize().x, window.getSize().y);
}

void Game::initAliens()
{
  aliens = new Alien[GRID_SIZE_X * GRID_SIZE_Y];
  int offset = (window.getSize().x - GRID_SIZE_X * alien_ship.getSize().x) / 2;
  for (int i = 0; i < GRID_SIZE_Y; ++i)
  {
    for (int j = 0; j < GRID_SIZE_X; ++j)
    {
      aliens[GRID_SIZE_X * i + j].setTexture(alien_ship);
      if (move_type == STRAIGHT || move_type == GRAVITY)
      {
        aliens[GRID_SIZE_X * i + j].getSprite()->setPosition(
          offset+ j * aliens[GRID_SIZE_X * i + j].getSprite()->getGlobalBounds().width,
          10.0 + i * aliens[GRID_SIZE_X * i + j].getSprite()->getGlobalBounds().height);
      }
      else if (move_type == QUADRATIC)
      {
        aliens[GRID_SIZE_X * i + j].getSprite()->setPosition(
          offset+ j * aliens[GRID_SIZE_X * i + j].getSprite()->getGlobalBounds().width,
          offset / 1.9 + i * aliens[GRID_SIZE_X * i + j].getSprite()->getGlobalBounds().height);
        aliens[GRID_SIZE_X * i + j].getSprite()->move(
          0.0,
          -pow(0.02 * aliens[GRID_SIZE_X * i + j].getSprite()->getPosition().x - 10,2)
          );
      }
      else if (move_type == SINE_CURVE)
      {
        aliens[GRID_SIZE_X * i + j].getSprite()->setPosition(
          offset+ j*aliens[GRID_SIZE_X * i + j].getSprite()->getGlobalBounds().width,
          offset / 4 +i*aliens[GRID_SIZE_X * i + j].getSprite()->getGlobalBounds().height);
        aliens[GRID_SIZE_X * i + j].getSprite()->move(
          0.0,
          -20 * sin(aliens[GRID_SIZE_X * i + j].getSprite()->getPosition().x/10)
        );
      }
    }
  }
}

void Game::initFont()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load \n";
  }

  player_score.setString("Score: " + std::to_string(player.getScore()));
  player_score.setFont(font);
  player_score.setCharacterSize(20);
  player_score.setFillColor(sf::Color(200,200,200,200));
  player_score.setPosition(5.0,5.0);
}

void Game::renderAliens()
{
  if (aliens != nullptr)
  {
    for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; ++i)
    {
      if (aliens[i].isInGame())
      {
        window.draw(*aliens[i].getSprite());
      }
    }
  }
}

void Game::renderProjectiles()
{
  for (int i = 0; i < player.getMaxProjectile(); ++i)
  {
    if (player.projectiles()[i].isInPlay())
    {
      window.draw(*player.projectiles()[i].getSprite());
    }
  }
}

void Game::moveBackground(float dt)
{
  bg_sprite.move(0,50 * dt);
  if (bg_sprite.getPosition().y >= 0.0)
  {
    bg_sprite.setPosition(0,-256);
  }
}

bool Game::moveShips(float dt)
{
  bool reverse_direction = false;
  for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; ++i)
  {
    if (aliens[i].moveAliens(window.getSize().x, dt, move_type))
    {
      reverse_direction = true;
    }
  }
  return reverse_direction;
}

void Game::changeAlienDirection()
{
  for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; ++i)
  {
    aliens[i].changeDirection(move_type);
  }
}

void Game::increaseAlienSpeed()
{
  for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; ++i)
  {
    aliens[i].addSpeed(5.0);
  }
}

void Game::movePlayer(float dt)
{
  player.movePlayer(window.getSize().x, dt);

  for (int i = 0; i < player.getMaxProjectile(); ++i)
  {
    if (player.projectiles()[i].isInPlay())
    {
      player.projectiles()[i].moveLaser(dt);
    }
  }
}

void Game::collisionCheck()
{
  // Player collision with aliens
  for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; ++i)
  {
    if (
      aliens[i].getSprite()->getGlobalBounds().intersects(
        player.getSprite()->getGlobalBounds()) &&
      aliens[i].isInGame())
    {
      if (
        getDistance(
          aliens[i].getSprite()->getPosition(),
          player.getSprite()->getPosition(),
          *aliens[i].getSprite(),
          *player.getSprite()) <= 60.0)
      {
        game_state = GAME_OVER;
      }
    }
    else if (
      (aliens[i].getSprite()->getPosition().y +
       aliens[i].getSprite()->getGlobalBounds().height) >= window.getSize().y &&
      aliens[i].isInGame())
    {
      game_state = GAME_OVER;
    }
  }

  // Lasers collision with aliens
  for (int i = 0; i < player.getMaxProjectile(); ++i)
  {
    if (player.projectiles()[i].isInPlay())
    {
      for (int j = 0; j < GRID_SIZE_X * GRID_SIZE_Y; ++j)
      {
        if (
          player.projectiles()[i].getSprite()->getGlobalBounds().intersects(
            aliens[j].getSprite()->getGlobalBounds()) &&
          aliens[j].isInGame())
        {
          if (getDistance(
                aliens[j].getSprite()->getPosition(),
                player.projectiles()[i].getSprite()->getPosition(),
                *aliens[j].getSprite(),
                *player.projectiles()[i].getSprite()) <= 30.0
             )
          {
            player.projectiles()[i].setState(false);
            aliens[j].destroyAlien();
            increaseAlienSpeed();
            player.addScore(aliens[j].getValue());
            enemy_count -= 1;
            if (enemy_count <= 0)
            {
              game_state = GAME_OVER;
            }
          }
        }
      }
    }
  }
}

void Game::resetGame()
{
  delete[] aliens;
  aliens = nullptr;
  player.resetShip(window.getSize().x, window.getSize().y);
  player.resetScore();
  for (int i = 0; i < player.getMaxProjectile(); ++i)
  {
    player.projectiles()[i].setState(false);
  }
  enemy_count = GRID_SIZE_X * GRID_SIZE_Y;

  game_state = IN_MENU;
}

float Game::getDistance(sf::Vector2<float> obj1_pos,
                        sf::Vector2<float> obj2_pos,
                        sf::Sprite obj1_spr,
                        sf::Sprite obj2_spr
                       )
{
  float x = (obj1_pos.x + obj1_spr.getGlobalBounds().width / 2) -
            (obj2_pos.x + obj2_spr.getGlobalBounds().width / 2);
  float y = (obj1_pos.y + obj1_spr.getGlobalBounds().height / 2) -
            (obj2_pos.y + obj2_spr.getGlobalBounds().height / 2);
  float distance = sqrt(pow(x,2) + pow(y,2));
  return distance;
}