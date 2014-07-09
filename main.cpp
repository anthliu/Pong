#include <iostream>
#include <SFML/Graphics.hpp>
#include "classes.hpp"

#define WINDOW_LENGTH 640
#define WINDOW_HEIGHT 480

#define UNIT_WIDTH 20

#define PADDLE_LENGTH 80
#define PADDLE_SPEED 10

#define INIT_BALL_SPEED 5
#define BALL_ACCELERATION 5
#define BALL_SIZE 15

#define SCORE_SIZE 40

bool game_over(int left, int right);
void reset(Pair& location, Pair& velocity, bool direction);

int main()
{
  sf::Font font;
  if(!font.loadFromFile("arial.ttf"))
    {
      std::cout << "Font arial not loaded!\n";
      std::exit(0);
    }

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

  int left_move = 0;
  int right_move = 0;

  int paddle_height;
  int collide_height;

  sf::Text left_text;
  sf::Text right_text;

  left_text.setFont(font);
  right_text.setFont(font);

  left_text.setCharacterSize(SCORE_SIZE);
  right_text.setCharacterSize(SCORE_SIZE);

  left_text.setColor(white);
  right_text.setColor(white);

  left_text.setPosition(WINDOW_LENGTH / 3, UNIT_WIDTH);
  right_text.setPosition(2 * WINDOW_LENGTH / 3, UNIT_WIDTH);

  while (window.isOpen() and !game_over(left_score, right_score))
    {
      sf::Event event;
      while(window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      left_move = 0;
      right_move = 0;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
	  right_move -= PADDLE_SPEED;
        } 
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
	  right_move += PADDLE_SPEED;
        } 
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
	  left_move -= PADDLE_SPEED;
        } 
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
	  left_move += PADDLE_SPEED;
        }

      left_paddle.move(Pair(0, left_move));
      right_paddle.move(Pair(0, right_move));


      if (ball_location.y + ball_velocity.y - BALL_SIZE < upper_limit)
	{
	  ball_location.y = 2 * (upper_limit) - ball_location.y + 2 * BALL_SIZE - ball_velocity.y;
	  ball_velocity.y *= -1;
	  ball_location.x += ball_velocity.x;
	} else if (ball_location.y + ball_velocity.y + BALL_SIZE > lower_limit)
	{
	  ball_location.y = 2 * (lower_limit) - ball_location.y - 2 * BALL_SIZE - ball_velocity.y;
	  ball_velocity.y *= -1;
	  ball_location.x += ball_velocity.x;
	} else if (ball_location.x + ball_velocity.x + BALL_SIZE > right_paddle_contact)
	{
	  paddle_height = right_paddle.getLocation().y + PADDLE_LENGTH / 2;
	  collide_height = ball_location.y + round((double)(ball_velocity.y)) * ((double)(right_paddle_contact - BALL_SIZE - ball_location.x) / ((double)ball_velocity.x));
	  if ((paddle_height + PADDLE_LENGTH / 2 < collide_height) or (paddle_height - PADDLE_LENGTH / 2 > collide_height))
	    {
	      left_score++;
	      reset(ball_location, ball_velocity, true);
	    } else
	    {
	      ball_location.x = 2 * (right_paddle_contact) - ball_location.x - 2 * BALL_SIZE - ball_velocity.x;
	      ball_velocity.x *= -1;
	      ball_location.y += ball_velocity.y;	  
	    }
	} else if (ball_location.x + ball_velocity.x - BALL_SIZE < left_paddle_contact)
	{
	  paddle_height = left_paddle.getLocation().y + PADDLE_LENGTH / 2;
	  collide_height = ball_location.y + round((double)(ball_velocity.y)) * ((double)(left_paddle_contact - BALL_SIZE - ball_location.x) / ((double)ball_velocity.x));
	  if ((paddle_height + PADDLE_LENGTH / 2 < collide_height) or (paddle_height - PADDLE_LENGTH / 2 > collide_height))
	    {
	      right_score++;
	      reset(ball_location, ball_velocity, false);
	    } else
	    {
	      ball_location.x = 2 * (left_paddle_contact) - ball_location.x + 2 * BALL_SIZE- ball_velocity.x;
	      ball_velocity.x *= -1;
	      ball_location.y += ball_velocity.y;
	    }
	} else
	{
	  ball_location.x += ball_velocity.x;
	  ball_location.y += ball_velocity.y;
	}

      ball.setPos(ball_location);

      left_text.setString(std::to_string(left_score));
      right_text.setString(std::to_string(right_score));

      window.clear(sf::Color::Black);
      window.draw(left_text);
      window.draw(right_text);
      left_paddle.draw(window);
      right_paddle.draw(window);
      ball.draw(window);
      window.display();
      
    }

  if (window.isOpen())
    {
      if (left_score > right_score)
	std::cout << "Left wins!\n";
      else
	std::cout << "Right wins!\n";
      window.close();
    }

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

void reset(Pair& location, Pair& velocity, bool direction)
{
  location.x = WINDOW_LENGTH / 2;
  location.y = WINDOW_HEIGHT / 2;
  //direction true: start right, false: start left
  if (direction)
    velocity.x = INIT_BALL_SPEED;
  else
    velocity.x = -1 * INIT_BALL_SPEED;
  velocity.y = 0;
}
