
#ifndef ANGRYBIRDSSFML_GAMEOBJECT_H
#define ANGRYBIRDSSFML_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  bool setSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  bool setScreenScale(GameObject image,sf::Vector2u texture, sf::Vector2u window);
  void* setVisibility(bool visibility);
  bool getVisibility();
  void* setMoving(bool moving);
  bool getMoving();
  void* setDirection(Vector2 object_direction);
  Vector2 getDirection();
  void* setActive(bool active);
  bool getActive();

 private:
  sf::Sprite* sprite = nullptr;
  float scaleX;
  float scaleY;
  bool is_visible;
  bool is_moving;
  Vector2 direction = {0, 0};
  bool is_active;
};

#endif // ANGRYBIRDSSFML_GAMEOBJECT_H
