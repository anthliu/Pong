#include <SFML/Graphics.hpp>
#include <cmath>
#include "classes.hpp"

int round(float number)
{
  return (int) floor(number + 0.5);
}

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

Pair rotate(Pair const &vector, float degree)
{
  Pair rotated_vector;
  rotated_vector.x = round(vector.x * cos(degree) - vector.y * sin(degree));
  rotated_vector.y = round(vector.y * cos(degree) + vector.x * sin(degree));
  return rotated_vector;
}
  
//-------------------

Wall::Wall(Pair setLocation, Pair setSize, sf::Color setColor)
{
  location = setLocation;
  size = setSize;
  color = setColor;

  rectangle.setPosition(location.x, location.y);
  rectangle.setSize(sf::Vector2f(size.x, size.y));
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
  radius = setRadius;
  circle.setRadius(radius);
  location = setLocation;
  circle.setPosition(location.x - radius, location.y - radius);
  velocity = setVelocity;
  color = setColor;
  circle.setFillColor(color);
}

void Ball::setPos(Pair newLocation)
{
  location = newLocation;
  circle.setPosition(location.x - radius, location.y - radius);
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
