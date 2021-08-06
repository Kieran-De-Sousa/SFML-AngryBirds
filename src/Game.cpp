
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::initNewGame()
{
  initText();
  initImages();
  initGameObjects();
  initNewGameVariables();

  return true;
}

bool Game::initNextLevel()
{
  initText();
  initImages();
  initGameObjects();
  initNextLevelVariables();

  return true;
}

bool Game::initText()
{
  //Checks for fonts loading correctly
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font could not be loaded!\n";
  }
  start_text.setString("Press enter to start the game");
  start_text.setFont(font);
  start_text.setCharacterSize(30);
  start_text.setFillColor(sf::Color::White);
  start_text.setPosition(window.getSize().x/2 - start_text.getGlobalBounds().width/2,
                         window.getSize().y/1.2 - start_text.getGlobalBounds().height/2);

  instructions_text.setString("Press and hold Mouse 1 to move the bird, release to launch!");
  instructions_text.setFont(font);
  instructions_text.setCharacterSize(30);
  instructions_text.setFillColor(sf::Color::White);
  instructions_text.setPosition(window.getSize().x/2 - instructions_text.getGlobalBounds().width/2,
                                window.getSize().y/1.1 - instructions_text.getGlobalBounds().height/2);

  level_text.setString("Current level: Level 1");
  level_text.setFont(font);
  level_text.setCharacterSize(30);
  level_text.setFillColor(sf::Color::Green);
  level_text.setPosition(window.getSize().x/2 - level_text.getGlobalBounds().width/2,
                         window.getSize().y/10 - level_text.getGlobalBounds().height/2);

  win_text.setString("Congratulations! Onto the next level!");
  win_text.setFont(font);
  win_text.setCharacterSize(30);
  win_text.setFillColor(sf::Color::Green);
  win_text.setPosition(window.getSize().x/2 - win_text.getGlobalBounds().width/2,
                         window.getSize().y/1.2 - win_text.getGlobalBounds().height/2);

  lose_text.setString("Failure! Better luck next time");
  lose_text.setFont(font);
  lose_text.setCharacterSize(30);
  lose_text.setFillColor(sf::Color::Red);
  lose_text.setPosition(window.getSize().x/2 - lose_text.getGlobalBounds().width/2,
                         window.getSize().y/1.2 - lose_text.getGlobalBounds().height/2);

  score_text.setString("Score: " + std::to_string(player_score));
  score_text.setFont(font);
  score_text.setCharacterSize(20);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(score_text.getGlobalBounds().width/10, 0);

  highscore_text.setString("High score: " + std::to_string(high_score));
  highscore_text.setFont(font);
  highscore_text.setCharacterSize(20);
  highscore_text.setFillColor(sf::Color::Green);
  highscore_text.setPosition(window.getSize().x - highscore_text.getGlobalBounds().width * 1.5, 0);

  return true;
}
bool Game::initImages()
{
  main_menu.setSprite(image_menu, "Data/Images/menu.jpg");
  main_menu.setScreenScale(main_menu, image_menu.getSize(), window.getSize());

  level_1.setSprite(image_lvl1, "Data/Images/lvl1.png");
  level_1.setScreenScale(level_1, image_lvl1.getSize(), window.getSize());

  level_2.setSprite(image_lvl2, "Data/Images/lvl2.png");
  level_2.setScreenScale(level_2, image_lvl2.getSize(), window.getSize());

  level_3.setSprite(image_lvl3, "Data/Images/lvl3.png");
  level_3.setScreenScale(level_3, image_lvl3.getSize(), window.getSize());

  slingshot.setSprite(image_slingshot, "Data/Images/slingshot.png");
  slingshot.getSprite()->setPosition(slingshot_coords[0] - (window.getSize().x/7),
                                     window.getSize().y - slingshot.getSprite()->getGlobalBounds().height);

  return true;
}

bool Game::initGameObjects()
{
  bird = new GameObject[num_birds];
  for (int i = 0; i < num_birds; i++)
  {
    bird[i].setSprite(bird_texture, "Data/Images/kenney_animalpackredux/PNG/Round (outline)/parrot.png");
    bird[i].getSprite()->setScale(0.4f, 0.4f);
    bird[i].setVisibility(true);
    bird[i].setMoving(false);
    bird[i].setDirection({bird_direction[0], bird_direction[1]});
    if (i == 0)
    {
      bird[i].setActive(true);
      bird[i].getSprite()->setPosition(slingshot_coords[0],slingshot_coords[1]);
    }
    else
    {
      bird[i].setActive(false);
      bird[i].getSprite()->setPosition(i * (window.getSize().x/20),window.getSize().y - bird[i].getSprite()->getGlobalBounds().height);
    }
  }

  pig = new GameObject[num_pigs];
  for (int j = 0; j < num_pigs; j++)
  {

    pig[j].setSprite(pig_texture, "Data/Images/kenney_animalpackredux/PNG/Round (outline)/pig.png");
    pig[j].getSprite()->setScale(0.45f, 0.45f);
    pig[j].setVisibility(true);
    //Determines pigs location based on level currently
    if (game_level == gameLevel::LEVEL_1)
    {
      pig[j].getSprite()->setPosition((window.getSize().x - pig[j].getSprite()->getGlobalBounds().width) - (window.getSize().x/8 * j),
                                      window.getSize().y - pig[j].getSprite()->getGlobalBounds().height);
    }
    else if (game_level == gameLevel::LEVEL_2)
    {
      pig[j].getSprite()->setPosition((window.getSize().x - pig[j].getSprite()->getGlobalBounds().width) - (window.getSize().x/5 * j),
                                      (window.getSize().y - pig[j].getSprite()->getGlobalBounds().height) - (window.getSize().y/4 * j));
    }
    else if (game_level == gameLevel::LEVEL_3)
    {
      pig[j].getSprite()->setPosition((window.getSize().x - pig[j].getSprite()->getGlobalBounds().width) - (window.getSize().x/8 * j),
                                      0 + (pig[j].getSprite()->getGlobalBounds().height * (j*j)));
    }
  }
  return true;
}

// Used when the player loses the game or when first initialising game
bool Game::initNewGameVariables()
{
  dead_birds = 0;
  dead_pigs = 0;
  game_state = gameScreen::START_SCREEN;
  if (player_score > high_score)
  {
    high_score = player_score;
  }

  player_score = 0;

  return true;
}

// Used when the player is transitioning from levels (lvl1 -> lvl2 -> lvl3 -> lv1)
bool Game::initNextLevelVariables()
{
  dead_birds = 0;
  dead_pigs = 0;
  game_state = gameScreen::START_SCREEN;
  if (player_score > high_score)
  {
    high_score = player_score;
  }
}

// Updates text that requires string changes to display different information
void Game::updateText()
{
  score_text.setString("Score: " + std::to_string(player_score));
  highscore_text.setString("High score: " + std::to_string(high_score));

  if (game_level == gameLevel::LEVEL_1)
  {
    level_text.setString("Current level: Level 1");
  }
  else if (game_level == gameLevel::LEVEL_2)
  {
    level_text.setString("Current level: Level 2");
  }
  else if (game_level == gameLevel::LEVEL_3)
  {
    level_text.setString("Current level: Level 3");
  }
}

// Updates bird and pig gameobjects, additionally controls game win and lose conditions
void Game::updateGameObjects(float dt)
{
  if (game_state == gameScreen::GAME_SCREEN)
  {
    // Win condition
    if (dead_pigs == num_pigs)
    {
      game_state = gameScreen::WIN_SCREEN;
      // Game level transitions
      if (game_level == gameLevel::LEVEL_1)
      {
        game_level = gameLevel::LEVEL_2;
      }
      else if (game_level == gameLevel::LEVEL_2)
      {
        game_level = gameLevel::LEVEL_3;
      }
      else if (game_level == gameLevel::LEVEL_3)
      {
        game_level = gameLevel::LEVEL_1;
      }
    }
    // Lose condition
    else if (dead_birds == num_birds)
    {
      game_state = gameScreen::LOSE_SCREEN;
      game_level = gameLevel::LEVEL_1;
    }
    //Updates major game functions requiring bird array
    for (int i = 0; i < num_birds; i++)
    {
      //Only updates birds on slingshot to reduce computational power required
      if (bird[i].getActive())
      {
        updateBirds(dt, i);
        collisionDetection(i);
      }
    }
  }
}

//Updates birds location if they are moving/launched
void Game::updateBirds(float dt, int i)
{
  if (bird[i].getMoving())
  {
    bird[i].setDirection({bird[i].getDirection().x,
                           static_cast<float>(bird[i].getDirection().y + 1.2)});

    bird[i].getSprite()->move(bird[i].getDirection().x * dt,
                              bird[i].getDirection().y * dt);
  }
}

//Collision detection for birds and pigs
void Game::collisionDetection(int i)
{
  if (bird[i].getVisibility())
  {
    if (bird[i].getMoving())
    {
      // If bird crosses right or bottom borders of window, remove them from play
      if (bird[i].getSprite()->getPosition().x - bird[i].getSprite()->getGlobalBounds().width < 0 ||
          bird[i].getSprite()->getPosition().y - bird[i].getSprite()->getGlobalBounds().height > window.getSize().y)
      {
        collisionDetectionResult(false, i, 0);
      }
      // If bird hits right most border, reverses the X direction
      else if (bird[i].getSprite()->getPosition().x + bird[i].getSprite()->getGlobalBounds().width > window.getSize().x)
      {
        bird[i].setDirection({-bird[i].getDirection().x, bird[i].getDirection().y});
      }
      else
      {
        for (int j = 0; j < num_pigs; j++)
        {
          //Alive pigs are the only ones visible
          if (pig[j].getVisibility())
          {
            if (bird[i].getSprite()->getGlobalBounds().intersects(pig[j].getSprite()->getGlobalBounds()))
            {
              collisionDetectionResult(true, i, j);
            }
          }
        }
      }
    }
  }
}

//Reduces code complexity in new function that checks outcome of bird collision
void Game::collisionDetectionResult(bool success, int i, int j)
{
  if (success)
  {
    pig[j].setVisibility(false);
    dead_pigs += 1;
    player_score += 10;
  }
  else if (!success)
  {
    player_score -= 5;
  }

  dead_birds += 1;
  bird[i].setVisibility(false);
  bird[i].setMoving(false);
  bird[i].setActive(false);
  // Should trigger only if dead pigs do not equal total number of pigs (avoids array overflow with
  // setting next birds sprite location)
  if (dead_birds < num_birds)
  {
    bird[i+1].setActive(true);
    bird[i+1].getSprite()->setPosition(slingshot_coords[0], slingshot_coords[1]);
  }
}

void Game::render()
{
  if (game_state == gameScreen::START_SCREEN)
  {
    renderStartScreen();
  }
  else if(game_state == gameScreen::GAME_SCREEN)
  {
    renderGameScreen();
  }
  else if (game_state == gameScreen::WIN_SCREEN)
  {
    renderWinScreen();
  }
  else if (game_state == gameScreen::LOSE_SCREEN)
  {
    renderLoseScreen();
  }
}

void Game::renderStartScreen()
{
  window.draw(*main_menu.getSprite());
  window.draw(start_text);
  window.draw(instructions_text);
  window.draw(level_text);
  window.draw(highscore_text);
}

void Game::renderGameScreen()
{
  // Loads different backgrounds based on players current level
  if (game_level == gameLevel::LEVEL_1)
  {
    window.draw(*level_1.getSprite());
  }
  else if (game_level == gameLevel::LEVEL_2)
  {
    window.draw(*level_2.getSprite());
  }
  else if (game_level == gameLevel::LEVEL_3)
  {
    window.draw(*level_3.getSprite());
  }

  // Universal gameplay elements
  window.draw(score_text);
  window.draw(*slingshot.getSprite());

  //Bird and pig sprite array loading
  for (int i = 0; i < num_birds; i++)
  {
    if (bird[i].getVisibility())
    {
      window.draw(*bird[i].getSprite());
    }
  }
  for (int j = 0; j < num_pigs; j++)
  {
    if (pig[j].getVisibility())
    {
      window.draw(*pig[j].getSprite());
    }
  }

  // Placed here due to level 3 pigs location
  window.draw(highscore_text);
}

void Game::renderWinScreen()
{
  window.draw(*main_menu.getSprite());
  window.draw(win_text);
  window.draw(level_text);
  window.draw(highscore_text);
}

void Game::renderLoseScreen()
{
  window.draw(*main_menu.getSprite());
  window.draw(lose_text);
  window.draw(level_text);
  window.draw(highscore_text);
}

void Game::mouseClicked()
{
  //Get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // Game screen transition checks
  if (game_state == gameScreen::WIN_SCREEN ||
      game_state == gameScreen::LOSE_SCREEN)
  {
    if (game_state == gameScreen::WIN_SCREEN)
    {
      initNextLevel();
    }
    else if (game_state == gameScreen::LOSE_SCREEN)
    {
      initNewGame();
    }
  }
  else if (game_state == gameScreen::GAME_SCREEN)
  {
    birdSlingshotPosition(click);
  }
}

void Game::mouseReleased()
{
  //Get the release position
  sf::Vector2i release = sf::Mouse::getPosition(window);

  if (game_state == gameScreen::GAME_SCREEN)
  {
    birdSlingshotPosition(release);
    for (int i = 0; i < num_birds; i++)
    {
      if (bird[i].getActive())
      {
        // Bird enters launched state, movement is determined in updateBirds function
        bird[i].setMoving(true);
      }
    }
  }
}

void Game::birdSlingshotPosition(sf::Vector2i mouse_pos)
{
  for (int i = 0; i < num_birds; i++)
  {
    // Entry checks ensuring valid bird is the one to move with mouse pos
    if (bird[i].getActive())
    {
      if (!bird[i].getMoving())
      {
        // Beyond right side pulling distance
        if (mouse_pos.x > (slingshot_coords[0] + max_pull[0]))
        {
          bird[i].getSprite()->setPosition(slingshot_coords[0] + max_pull[0], bird[i].getSprite()->getPosition().y);
        }
        // Beyond left side pulling distance
        else if (mouse_pos.x < (slingshot_coords[0] - max_pull[0]))
        {
          bird[i].getSprite()->setPosition(slingshot_coords[0] - max_pull[0], bird[i].getSprite()->getPosition().y);
        }
        // Beyond below pulling distance
        else if (mouse_pos.y > (slingshot_coords[1] + max_pull[1]))
        {
          bird[i].getSprite()->setPosition(bird[i].getSprite()->getPosition().x, slingshot_coords[1] + max_pull[1]);
        }
        // Beyond above pulling distance
        else if (mouse_pos.y < (slingshot_coords[1] - max_pull[1]))
        {
          bird[i].getSprite()->setPosition(bird[i].getSprite()->getPosition().x, slingshot_coords[1] - max_pull[1]);
        }
        // Within the square range of the maximum pulling distance
        else
        {
          bird[i].getSprite()->setPosition(mouse_pos.x, mouse_pos.y);
        }

        //Determines strength of birds launch based on how far back slingshot is pulled
        pull_force[0] = (slingshot_coords[0] - mouse_pos.x) * 0.012;
        pull_force[1] = (slingshot_coords[1] - mouse_pos.y) * 0.012;

        // Bird goes from right side of slingshot to launched toward the left side
        if (pull_force[0] > 0)
        {
          bird[i].setDirection({bird_direction[0] * pull_force[0], bird[i].getDirection().y});
        }
          // Bird goes from left side of slingshot to launched toward the right side
        else if (pull_force[0] < 0)
        {
          bird[i].setDirection({-bird_direction[0] * -pull_force[0], bird[i].getDirection().y});
        }
        // If X pos of mouse is equal to slingshot center cords
        else
        {
          bird[i].setDirection({0, bird[i].getDirection().y});
        }
        // Bird goes from above slingshot to launched toward the ground
        if (pull_force[1] > 0)
        {
          bird[i].setDirection({bird[i].getDirection().x, bird_direction[1] * pull_force[1]});
        }
          // Bird goes from below slingshot to launched toward the sky
        else if (pull_force[1] < 0)
        {
          bird[i].setDirection({bird[i].getDirection().x, -bird_direction[1] * -pull_force[1]});
        }
          // If Y pos of mouse is equal to slingshot center cords
        else
        {
          bird[i].setDirection({bird[i].getDirection().x, 0});
        }
      }
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  //Closes game no matter gamestate in
  if (event.key.code == sf::Keyboard::Q)
  {
    window.close();
  }

  if (event.key.code == sf::Keyboard::Enter)
  {
    if (game_state == gameScreen::START_SCREEN)
    {
      game_state = gameScreen::GAME_SCREEN;
    }
    else if (game_state == gameScreen::WIN_SCREEN ||
             game_state == gameScreen::LOSE_SCREEN)
    {
      if (game_state == gameScreen::WIN_SCREEN)
      {
        //Keeps player score during transition
        initNextLevel();
      }
      else if (game_state == gameScreen::LOSE_SCREEN)
      {
        //Player score is reset upon transition
        initNewGame();
      }
    }
  }
}


