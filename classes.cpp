#include <SFML/Graphics.hpp>
#include "classes.hpp"

Pair::Pair(int setX, int setY)
{
  x = setX;
  y = setY;
}

Pair addPair(Pair const &addOne, Pair const &addTwo)
{
  return Pair(addOne.x + addTwo.x, addOne.y + addTwo.y);
}

Pair scalarPair(int scalar, Pair const &onePair)
{
  return Pair(scalar * onePair.x, scalar * onePair.y);
}
