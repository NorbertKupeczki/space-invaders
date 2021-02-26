
#include "Game.h"
#include <iostream>

// -------------------------------- PUBLIC --------------------------------
Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
  delete[] aliens;
}

bool Game::init()
{
  initTextures();
  initAliens();
  initPlayer();
  initFont();
  return true;
}

void Game::update(float dt)
{
  player_score.setString("Score: " + std::to_string(player.getScore()));
  moveBackground(dt);
  if (moveShips(dt))
  {
    changeAlienDirection();
  }
  movePlayer(dt);
  if(player.isFiring())
  {
    player.fireLaser();
  }
  collisionCheck();
}

void Game::render()
{
  window.draw(bg_sprite);
  window.draw(*player.getSprite());
  for (int i = 0; i < GRID_SIZE*GRID_SIZE/2; ++i)
  {
    if (aliens[i].isInGame())
    {
      window.draw(*aliens[i].getSprite());
    }
  }
  for (int i = 0; i < player.getMaxProjectile(); ++i)
  {
    if (player.projectiles()[i].isInPlay())
    {
      window.draw(*player.projectiles()[i].getSprite());
    }
  }
  window.draw(player_score);
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

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
  loadTexture(player_ship, "Data/Images/playerShip.png");
  loadTexture(alien_ship, "Data/Images/alienShip.png");
  loadTexture(laser_green, "Data/Images/laser_green.png");
  loadTexture(alien_blue, "Data/Images/ufoBlue.png");
  loadTexture(alien_red, "Data/Images/ufoRed.png");
  loadTexture(alien_green, "Data/Images/ufoGreen.png");
  loadTexture(alien_yellow, "Data/Images/ufoYellow.png");

  bg_texture.setRepeated(true);
  bg_sprite.setTextureRect(
    sf::IntRect( 0.0,0.0,
                 window.getSize().x,
                 bg_texture.getSize().y * 5));
  bg_sprite.setPosition(0,-256);
}

void Game::initPlayer()
{
  player.setTexture(player_ship);
  player.setLaserTexture(laser_green);
  player.resetShip(window.getSize().x, window.getSize().y);
}

void Game::initAliens()
{
  aliens = new Alien[GRID_SIZE*GRID_SIZE/2];
  int offset = (window.getSize().x - GRID_SIZE * alien_blue.getSize().x) / 2;
  for (int i = 0; i < GRID_SIZE / 2; ++i)
  {
    for (int j = 0; j < GRID_SIZE; ++j)
    {
      aliens[GRID_SIZE * i + j].setTexture(alien_ship);
      aliens[GRID_SIZE * i + j].getSprite()->setPosition(
        offset + j * aliens[GRID_SIZE * i + j].getSprite()->getGlobalBounds().width,
        offset/4 + i * aliens[GRID_SIZE * i + j].getSprite()->getGlobalBounds().height);
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
  for (int i = 0; i < GRID_SIZE*GRID_SIZE/2; ++i)
  {
    if (aliens[i].moveAliens(window.getSize().x,dt))
    {
      reverse_direction = true;
    }
  }
  return reverse_direction;
}

void Game::changeAlienDirection()
{
  for (int i = 0; i < GRID_SIZE*GRID_SIZE/2; ++i)
  {
    aliens[i].changeDirection();
  }
}

void Game::increaseAlienSpeed()
{
  for (int i = 0; i < GRID_SIZE*GRID_SIZE/2; ++i)
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
  for (int i = 0; i < GRID_SIZE*GRID_SIZE/2; ++i)
  {
    if (aliens[i].getSprite()->getGlobalBounds().intersects(
          player.getSprite()->getGlobalBounds())&&
        aliens[i].isInGame())
    {
      std::cout << "Game Over";
    }
  }

  // Lasers collision with aliens
  for (int i = 0; i < player.getMaxProjectile(); ++i)
  {
    if (player.projectiles()[i].isInPlay())
    {
      for (int j = 0; j < GRID_SIZE * GRID_SIZE / 2; ++j)
      {
        if (
          player.projectiles()[i].getSprite()->getGlobalBounds().intersects(
            aliens[j].getSprite()->getGlobalBounds()) &&
          aliens[j].isInGame())
        {
          player.projectiles()[i].setState(false);
          aliens[j].destroyAlien();
          increaseAlienSpeed();
          player.addScore(aliens[j].getValue());
        }
      }
    }
  }
}