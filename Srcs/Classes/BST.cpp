#include <Classes/BST.hpp>


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

BST::BST()
{
	this->initWindow();
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

void	BST::update()
{
	this->updateSFMLEvents();

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

void	BST::render()
{
	this->window->clear();


	this->window->display(); 
}
