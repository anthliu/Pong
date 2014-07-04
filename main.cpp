#include <iostream>
#include <SFML/Graphics.hpp>
#include "classes.hpp"

#define WINDOW_LENGTH 640
#define WINDOW_HEIGHT 480

#define UNIT_WIDTH 20

#define PADDLE_LENGTH 80
#define PADDLE_SPEED 10

#define INIT_BALL_SPEED 10
#define BALL_ACCELERATION 5
#define BALL_SIZE 15

bool game_over(int left, int right);

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Pong");
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(30);

  sf::Color white(255, 255, 255);
  int upper_limit = 0;
  int lower_limit = WINDOW_HEIGHT;

  int left_paddle_contact = UNIT_WIDTH;
  int right_paddle_contact = WINDOW_LENGTH - UNIT_WIDTH;

  Wall left_paddle(Pair(0, WINDOW_HEIGHT / 2 - PADDLE_LENGTH / 2), Pair(UNIT_WIDTH, PADDLE_LENGTH), white);
  Wall right_paddle(Pair(right_paddle_contact, WINDOW_HEIGHT / 2 - PADDLE_LENGTH / 2), Pair(UNIT_WIDTH, PADDLE_LENGTH), white);

  Pair ball_location(WINDOW_LENGTH / 2, WINDOW_HEIGHT / 2);
  Pair ball_velocity(INIT_BALL_SPEED, 0);

  Ball ball(ball_location, ball_velocity, BALL_SIZE, white);

  int left_score = 0;
  int right_score = 0;

  while (window.isOpen() and !game_over(left_score, right_score))
    {
      sf::Event event;
      while(window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      window.clear(sf::Color::Black);
      left_paddle.draw(window);
      right_paddle.draw(window);
      ball.draw(window);
      window.display();
      
    }

  if (window.isOpen())
    window.close();

  return 0;
}

bool game_over(int left, int right)
{
  if (left >= 11 or right >= 11)
    {
      if ( (left - right) >= 2 or (right - left >= 2))
	return true;
    }
  return false;
}
