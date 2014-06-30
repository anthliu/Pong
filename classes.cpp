#include <SFML/Graphics.hpp>
#include "classes.hpp"

Pair::Pair(int setX, int setY)
{
  x = setX;
  y = setY;
}

Pair::Pair()
{
  x = 0;
  y = 0;
}

Pair addPair(Pair const &addOne, Pair const &addTwo)
{
  return Pair(addOne.x + addTwo.x, addOne.y + addTwo.y);
}

Pair scalarPair(int scalar, Pair const &onePair)
{
  return Pair(scalar * onePair.x, scalar * onePair.y);
}

//-------------------

Wall::Wall(Pair setLocation, Pair setSize, sf::Color setColor)
{
  location = setLocation;
  size = setSize;
  color = setColor;

  rectangle.setPosition(location.x, location.y);
  rectangle.setFillColor(color);
}

Pair Wall::getLocation()
{
  return location;
}

Pair Wall::getSize()
{
  return size;
}

void Wall::move(Pair units)
{
  location = addPair(location, units);
  rectangle.setPosition(location.x, location.y);
}

void Wall::draw(sf::RenderWindow& window)
{
  window.draw(rectangle);
}

//--------------------------

Ball::Ball(Pair setLocation, Pair setVelocity, int setRadius, sf::Color setColor)
{
  location = setLocation;
  circle.setPosition(location.x, location.y);
  radius = setRadius;
  circle.setRadius(radius);
  velocity = setVelocity;
  color = setColor;
  circle.setFillColor(color);
}

void Ball::move(Pair units)
{
  location = addPair(location, units);
  circle.setPosition(location.x, location.y);
}

void Ball::update()
{
  move(velocity);
}

void Ball::draw(sf::RenderWindow& window)
{
  window.draw(circle);
}
