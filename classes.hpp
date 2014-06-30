#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define GRAVITY 10

class Pair
{
public:
  int x;
  int y;
  Pair(int setX, int setY);
  Pair();
};

Pair addPair(Pair const &addOne, Pair const &addTwo);
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
  void move(Pair units);
  void draw(sf::RenderWindow& window);
};

class Ball
{
  sf::CircleShape circle;
  sf::Color color;
  Pair location;
  int radius;
  Pair velocity;
public:
  Ball(Pair setLocation, Pair setVelocity, int setRadius, sf::Color setColor);
  void move(Pair units);
  void update();
  void draw(sf::RenderWindow& window);
};
#endif
