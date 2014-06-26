#include <iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_LENGTH 640
#define WINDOW_HEIGHT 480

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Pong");
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(30);

  while (window.isOpen())
    {
      sf::Event event;
      while(window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      window.clear(sf::Color::Black);
      window.display();
      
    }

  return 0;
}
