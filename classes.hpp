#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <SFML/Graphics.hpp>
#define GRAVITY 10

class Pair
{
public:
  int x;
  int y;
  Pair(int setX, int setY);
};

Pair addPair(Pair addOne, Pair addTwo);
Pair scalarPair(int scalar, Pair onePair);

class Wall
{
  sf::RectangleShape rectangle;
  sf::Color color;
  Pair location;
  Pair size;
public:
  Wall(Pair setLocation, Pair setSize, sf::Color setColor);
  Pair getLocation();
  Pair getSize();
};

#endif
