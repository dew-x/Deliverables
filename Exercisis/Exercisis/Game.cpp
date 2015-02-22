#include "Game.h"

void loadObjModel(std::string filename, vector<Vertex> &data) {
	int a, b, c;
	std::ifstream inputFile(filename, std::ios::in);
	if (!inputFile)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);
	}
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (line.substr(0, 2) == "v "){
			std::istringstream v(line.substr(2));
			
			double x, y, z;
			v >> x; v >> y; v >> z;
			Vertex vert;
			vert.setPosition(x / 1000, y / 1000, z / 1000);
			vert.setColor(255, 0, 255, 255);
			data.push_back(vert);
		}
		else if (line.substr(0, 2) == "f "){
			std::string lineVals = line.substr(2);
			std::string val0 = lineVals.substr(0, lineVals.find_first_of(' '));
			// Get first group of values
			std::string g1 = val0.substr(0, val0.find(' '));
			std::istringstream v1(g1);
			v1 >> a;
			// Get second group of values
			std::string g2 = line.substr(line.find(' ') + 2);
			g2 = g2.substr(g2.find(' ') + 1);
			std::istringstream v2(g2);
			v2 >> b;
			// Get third group of values
			g2 = g2.substr(0, g2.find(' '));
			std::string g3 = line.substr(line.find_last_of(' ') + 1);
			std::istringstream v3(g3);
			v3 >> c;
			//faceIndex.push_back(glm::i32vec3(a, b, c));
		}
	}

}


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle), 
	_screenWidth(screenWidth), 
	_screenHeight(screenHeight),
	_gameState(GameState::INIT), 
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS),
	_time(0){
}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);		
		//Compile and Link shader
	loadShaders();
		//Load the current scenario
	_openGLBuffers.initializeBuffers(_colorProgram);
		//Create several vertex
	createPrimitivesToRender();
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::loadShaders() {
		//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.vert");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.frag");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
		//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Initialize the position and the color of the different vertices that have to be rendered
*/
void Game::createPrimitivesToRender() {

	float x = -0.5;
	float y = -0.5;

	float width = 1;
	float height = 1;
	data = vector<Vertex>(0);
	loadObjModel("resources/teapot.obj", data);
	std::cout << data.size() << std::endl;
	std::cout << data.size() << std::endl;
	std::cout << data.size() << std::endl;
	/*
	//First triangle
	data[0].setPosition(x + width, y + height, 0.0f);
	data[0].setColor(0, 255, 0, 255);

	data[1].setPosition(x, y + height, 0.0f);
	data[1].setColor(255, 0, 0, 255);

	data[2].setPosition(x, y, 0.0f);
	data[2].setColor(0, 0, 255, 255);

	//Second triangle
	data[3].setPosition(x, y, 0.0f);
	data[3].setColor(255, 255, 255, 255);

	data[4].setPosition(x + width, y, 0.0f);
	data[4].setColor(255, 255, 255, 255);

	data[5].setPosition(x + width, y + height, 0.0f);
	data[5].setColor(255, 255, 255, 255);

	//Set the color to magenta
	for (int i = 0; i < 6; i++) {
		data[i].setColor(255, 0, 255, 255);
	}
	//Set the color of the 1st coordinate to blue
	data[1].setColor(0, 0, 255, 255);
	//Set the color of the 4th coordinate to green
	data[4].setColor(0, 255, 0, 255);*/
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {		
			//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
			//Process the input information (keyboard and mouse)
		processInput();
			//Draw the objects on the screen
		drawGame();	
			//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		default:
			break;
		}
	}
}

/**
* Draw the sprites on the screen
*/
void Game::drawGame() {
		//Set the base depth to 1.0
	glClearDepth(1.0);

		//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();

		//Set the new value for the uniform variable
		//Important: If time is not used in the shader, we will get an error because GLSL will delete it for us. Then, we need to comment the following three lines
	_time = _time+0.05f;
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation,_time);

		//Send data to GPU
	_openGLBuffers.sendDataToGPU(&data[0],data.size());

		//Unbind the program
	_colorProgram.unuse();

		//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

