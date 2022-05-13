#ifndef BST_HPP
#define BST_HPP

#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class BST
{

private:
	//Variables
	sf::RenderWindow	*window;
	sf::Event			sfEvent;
	sf::Clock			dtClock;
	float				dt;
	//Initiaziler functions
	void	initWindow();

public:
	BST(/* args */);
	virtual ~BST();
	//Function
	void		updateDt();
	void		updateSFMLEvents();
	void		update();
	void		render();
	void		run();
};

#endif