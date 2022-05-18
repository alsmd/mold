#include "../../Includes/Classes/BST.hpp"


//Inicializer functions

void	BST::initWindow()
{
	std::fstream	ifs("./Config/window.ini");

	std::string		title = "None";
	sf::VideoMode	window_bounds(800, 600);
	unsigned		framerate_limit = 120;
	bool			vertical_sync_enabled = false;
	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}
	ifs.close();
	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);

}

//Constructor / Destroctor

BST::BST() : input(500, 50)
{
	this->initWindow();
	this->input.setPosition(this->window->getSize().x / 2, 50);
	for (int i = 0; i < 5; i++)
		this->tree.insert(i + 1);
/* 	this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->background.setFillColor(sf::Color::White); */
}

BST::~BST()
{
	delete this->window;
}


//Functions

void	BST::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

void	BST::updateKeys(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->view.move(sf::Vector2f(0, -100 * this->dt));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->view.move(sf::Vector2f(0, 100 * this->dt));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->view.move(sf::Vector2f(-100 * this->dt, 0));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->view.move(sf::Vector2f(100 * this->dt, 0));
}


void	BST::update()
{
	std::string buffer;
	int			value;

	this->input.update();
	this->updateSFMLEvents();
	this->updateKeys();

	/* std::cout << "> ";
	std::cin >> buffer;
	if (buffer == "add"){
		std::cout << "new node: ";
		std::cin >> value;
		this->tree.insert(value);
	}else if (buffer == "del"){
		std::cout << "delete node: ";
		std::cin >> value;
		this->tree.remove(value);
	} */


}

void	BST::updateDt()
{
	//Update delta variable with the time that it took to render 1 frame
	this->dt = this->dtClock.restart().asSeconds();
}

void	BST::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close(); 
	}
}

void	BST::drawTree(ft::Node<int> *node, float x, float y){
	if (node == NULL)
		return ;
	std::stringstream	buffer;
	buffer << node->value;
	if (node->color == ft::Color::Black)
		this->circle.shape.setFillColor(sf::Color::Cyan);
	else
		this->circle.shape.setFillColor(sf::Color::Red);
	this->circle.setCircle(buffer.str(), sf::Vector2f(x + this->view.getPosition().x, y + this->view.getPosition().y));
	this->n += 1;
	int holder = this->n;
	if (node->left)
		this->drawLine(x + 15 + this->view.getPosition().x,  y + 15 + this->view.getPosition().y,  (x - ((this->n % 2 == 0) ? 50 : 100)) + 15 + this->view.getPosition().x, y + 80 + 15 + this->view.getPosition().y);
	this->circle.draw(*this->window);
	this->drawTree(node->left, x - ((this->n % 2 == 0) ? 50 : 100), y + 80);
	this->n = holder;
	if (node->right)
		this->drawLine(x +15 + this->view.getPosition().x, y + 15 + this->view.getPosition().y,  (x + ((this->n % 2 == 0) ? 50 : 100)) + 15 + this->view.getPosition().x, (y + 80) + 15 + this->view.getPosition().y);
	this->drawTree(node->right, x + ((this->n % 2 == 0) ? 50 : 100), y + 80);
}

void	BST::drawLine(float x1, float y1, float x2, float y2){
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};

	this->window->draw(line, 2, sf::Lines);
}
void	BST::render()
{
	this->window->clear();
	this->input.render(this->window);
	// Create a text
	if (this->tree.root){
		this->n = 0;
		this->drawTree(this->tree.root, (this->window->getSize().x / 2) - 30, 80);
	}
	this->window->display();
}
