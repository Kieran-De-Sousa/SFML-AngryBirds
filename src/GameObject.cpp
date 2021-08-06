
#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

 // SPRITE //
bool GameObject::setSprite(sf::Texture& texture, std::string filename)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "Texture could not be loaded\n";
  }
  sprite = new sf::Sprite();
  sprite->setTexture(texture);

  sprite->setPosition(0,0);

  return true;
}
sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

// Used for main menu and different menus to scale the texture to the size of the render window
bool GameObject::setScreenScale(GameObject image, sf::Vector2u texture, sf::Vector2u window)
{
  float scaleX = (float) window.x / texture.x;
  float scaleY = (float) window.y / texture.y;

  image.getSprite()->setScale(scaleX, scaleY);

  return true;
}
 // VISIBILITY //
void* GameObject::setVisibility(bool visibility)
{
  is_visible = visibility;
}
bool GameObject::getVisibility()
{
  return is_visible;
}

// Used for setting an angry bird to move
void* GameObject::setMoving(bool moving)
{
  is_moving = moving;
}
bool GameObject::getMoving()
{
  return is_moving;
}

// DIRECTION //
void* GameObject::setDirection(Vector2 object_direction)
{
  direction = object_direction;
}
Vector2 GameObject::getDirection()
{
  return direction;
}

// Active means the bird is in the slingshot, ready to be launched
void* GameObject::setActive(bool active)
{
  is_active = active;
}
bool GameObject::getActive()
{
  return is_active;
}