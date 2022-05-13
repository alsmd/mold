#include <fstream>
#include <sstream>
#include <iostream>

int	main()
{
	std::fstream	ifs("./teste");
	int	a;
	int	b;
	if (ifs.is_open())
	{
		ifs >> a >> b;
	}
	std::cout << a << " " << b << std::endl;
}