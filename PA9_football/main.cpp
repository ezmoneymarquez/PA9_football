/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Programmers: Josh Marquez, Iyke Odum												 *
*	Class: CptS 122, Spring 2026  Lab Section 1											 *
*	Programming Assignment: PA 9 2D Football Game Application							 *
*	Date: April 27, 2026																 *
*	Description: This program runs a simple 2D football game.							 *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "Game.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    
    //sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    Game game;
    game.run();

    //while (window.isOpen())
    //{
    //    while (const std::optional event = window.pollEvent())
    //    {
    //        if (event->is<sf::Event::Closed>())
    //            window.close();
    //    }

    //    window.clear();
    //    window.draw(shape);
    //    window.display();
    //}
}