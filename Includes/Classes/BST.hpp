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
#include "../../../Util/BinarySearchTree.hpp"

namespace ft{
struct Circle{
	sf::CircleShape	shape;
	sf::Text		text;
	sf::Font		font;

	Circle(){
		this->font.loadFromFile("./fonts/Roboto-Black.ttf");
		this->shape.setRadius(15);

		this->text.setFont(this->font);
		this->text.setCharacterSize(12);
		this->text.setFillColor(sf::Color::Black);
		this->shape.setFillColor(sf::Color::White);

	}


	void setCircle(std::string text, sf::Vector2f circlePos){
		this->text.setString(text);
		this->text.setPosition(sf::Vector2f(circlePos.x + 7, circlePos.y + 7));
		this->shape.setPosition(circlePos);
	}

	void draw(sf::RenderWindow &window){
		window.draw(this->shape);
		window.draw(this->text);
	}

};


class Input{
	private:
		sf::RectangleShape	body;
		sf::Text			text;
	sf::Font		font;
	public:
		bool				hasFocus;
		std::string			buffer;

		Input(float width, float height){
			this->font.loadFromFile("./fonts/Roboto-Black.ttf");
			this->text.setFillColor(sf::Color::Black);
			this->text.setFont(this->font);
			this->text.setCharacterSize(30);
			this->body.setFillColor(sf::Color::White);
			this->body.setSize(sf::Vector2f(width, height));
			this->hasFocus = false;
		}

		~Input(){

		}

		std::string getBuffer(){
			std::string r = this->buffer;
			this->buffer.clear();
			return (r);
		}

		void setPosition(float x, float y){
			this->body.setPosition(sf::Vector2f(x - this->body.getSize().x / 2, y - this->body.getSize().y / 2));
			this->text.setPosition(sf::Vector2f(
				this->body.getPosition().x + (this->body.getSize().x / 2) - (this->text.getGlobalBounds().width / 2),
				this->body.getPosition().y + (this->body.getSize().y / 2) - (this->text.getGlobalBounds().height / 2)
			));
		}


		void update(sf::RenderWindow *window){
			this->text.setPosition(sf::Vector2f(
				this->body.getPosition().x + (this->body.getSize().x / 2) - (this->text.getGlobalBounds().width / 2),
				this->body.getPosition().y + (this->body.getSize().y / 2) - (this->text.getGlobalBounds().height / 2)
			));
			if (this->body.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)){
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					this->hasFocus = true;
					std::cout << "Input ta com Focus\n";
				}
			}else{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					this->hasFocus = false;
					std::cout << "Input perdeu o Focus\n";
				}
			}
			if (this->hasFocus){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
					if (this->buffer.length() - 1 > 0){
						this->buffer.erase(this->buffer.length() - 1);
					}
				}
			}
		}

		void getInput(sf::Event e){
			if (e.type == sf::Event::TextEntered){
				if (this->hasFocus && std::isalnum(e.text.unicode)){
					char tmp[1] = {e.text.unicode};
					this->buffer.append(tmp);
				}
			}
			
		}

		void render(sf::RenderTarget *target){
			this->text.setString(this->buffer);
			target->draw(this->body);
			target->draw(this->text);
		}
};

}

class BST
{

private:
	//Variables
	sf::RenderWindow						*window;
	ft::Input								input;
	// ft::BinarySearchTree<int>				tree;
	ft::RedBlackTree<int, int>				tree;
	sf::CircleShape							view;
	ft::Circle								circle;
	// sf::RectangleShape						background;
	sf::Event								sfEvent;
	sf::Clock								dtClock;
	int										n;
	float									dt;
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
	void		drawTree(ft::Node<int, int> *node, float x, float y);
	void		drawLine(float x1, float y1, float x2, float y2);
	void		updateKeys();

};

#endif