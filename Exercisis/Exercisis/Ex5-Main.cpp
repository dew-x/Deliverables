#include "Game.h"


int main(int argc, char ** argv) {
	Game game("Example 01.Hello Triangle", 800, 600,true,60,true);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}