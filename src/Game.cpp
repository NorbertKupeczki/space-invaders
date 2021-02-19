
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
  bg_texture.setRepeated(true);
  bg_sprite.setTextureRect(
    sf::IntRect( 0.0,0.0,
                window.getSize().x,
                bg_texture.getSize().y * 5));
  bg_sprite.setPosition(0,-256);
  aliens = new Alien[4];
  aliens[0].setTexture(alien_blue);
  aliens[1].setTexture(alien_red);
  aliens[2].setTexture(alien_green);
  aliens[3].setTexture(alien_yellow);

  for (int i = 0; i < 4; ++i)
  {
    aliens[i].getSprite()->setPosition(
      200.0 * (i+1),
      window.getSize().y/2 - aliens[i].getSprite()->getGlobalBounds().height
      );
  }

  player.setTexture(player_ship);
  player.resetShip(window.getSize().x, window.getSize().y);
  return true;
}

void Game::update(float dt)
{
  moveBackground(dt);
}

void Game::render()
{
  window.draw(bg_sprite);
  window.draw(*player.getSprite());
  for (int i = 0; i < 4; ++i)
  {
    window.draw(*aliens[i].getSprite());
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }
}

void Game::keyReleased(sf::Event event)
{

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
  loadTexture(alien_blue, "Data/Images/ufoBlue.png");
  loadTexture(alien_red, "Data/Images/ufoRed.png");
  loadTexture(alien_green, "Data/Images/ufoGreen.png");
  loadTexture(alien_yellow, "Data/Images/ufoYellow.png");
}

void Game::moveBackground(float dt)
{
  bg_sprite.move(0,50 * dt);
  if (bg_sprite.getPosition().y >= 0.0)
  {
    bg_sprite.setPosition(0,-256);
  }
}
