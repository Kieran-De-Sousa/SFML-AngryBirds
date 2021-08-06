
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool initNewGame();
  bool initNextLevel();
  bool initText();
  bool initImages();
  bool initGameObjects();
  bool initNewGameVariables();
  bool initNextLevelVariables();
  void updateText();
  void updateGameObjects(float dt);
  void updateBirds(float dt, int bird_num);
  void collisionDetection(int bird_num);
  void collisionDetectionResult(bool success, int bird_num, int pig_num);
  void render();
  void renderStartScreen();
  void renderGameScreen();
  void renderWinScreen();
  void renderLoseScreen();
  void mouseClicked();
  void mouseReleased();
  void birdSlingshotPosition(sf::Vector2i mouse_pos);
  void keyPressed(sf::Event event);

 private:
  // Screens //
  sf::RenderWindow& window;
  enum gameScreen
  {
    START_SCREEN,
    GAME_SCREEN,
    PAUSE_SCREEN,
    WIN_SCREEN,
    LOSE_SCREEN
  };
  enum gameScreen game_state = gameScreen::START_SCREEN;

  enum gameLevel
  {
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
  };
  enum gameLevel game_level = gameLevel::LEVEL_1;

  // Images //
  GameObject main_menu;
  sf::Texture image_menu;

  GameObject level_1;
  sf::Texture image_lvl1;

  GameObject level_2;
  sf::Texture image_lvl2;

  GameObject level_3;
  sf::Texture image_lvl3;

  GameObject slingshot;
  sf::Texture image_slingshot;

  // Text //
  sf::Font font;
  sf::Text start_text;
  sf::Text instructions_text;
  sf::Text level_text;
  sf::Text score_text;
  sf::Text highscore_text;
  sf::Text win_text;
  sf::Text lose_text;

  // Game Objects //
  static const int num_birds = 5;
  int dead_birds = 0;
  GameObject* bird = nullptr;
  sf::Texture bird_texture;

  static const int num_pigs = 3;
  int dead_pigs = 0;
  GameObject* pig = nullptr;
  sf::Texture pig_texture;

  // Game Variables //
  int player_score = 0;
  int high_score = 0;
  float bird_direction[2] = {100, 175};
  float slingshot_coords[2] = {static_cast<float>(window.getSize().x / 4),
                               static_cast<float>(window.getSize().y / 1.5)};
  float max_pull[2] = {static_cast<float>(window.getSize().x / 6), static_cast<float>(window.getSize().y / 6)};
  float pull_force[2] = {0,0};

};

#endif // ANGRYBIRDS_GAME_H
