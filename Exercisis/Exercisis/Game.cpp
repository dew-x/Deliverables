#include "Game.h"


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
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS) {
	
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
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPositionGame");
	_colorProgram.addAttribute("vertexColor");
		//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Initialize the position and the color of the different vertices that have to be rendered
*/
void Game::createPrimitivesToRender() {
	geo.loadScene("resources/figures2.txt");
	data = geo.getData();
	/*triangle3DPosition=glm::vec3(0.4,0.3,0);	//Center the triangle in the middle of the screen
	triangleRadius=0.2;
	
	data[0].setPosition(triangle3DPosition.x + 0, triangle3DPosition.y+0.2, 0.0f);
	data[0].setColor(0, 255, 0, 255);

	data[1].setPosition(triangle3DPosition.x - 0.1*sqrt(3.0f), triangle3DPosition.y - 0.1f, 0.0f);
	data[1].setColor(255, 0, 0, 255);

	data[2].setPosition(triangle3DPosition.x + 0.1*sqrt(3.0f), triangle3DPosition.y - 0.1f, 0.0f);
	data[2].setColor(0, 0, 255, 255);*/

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
			//Execute pending actions
		//updateGameObjects();
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
		case SDL_MOUSEMOTION:
			cout << "(" << evnt.motion.x << ", " << evnt.motion.y << ")" << endl;
			break;
		case SDL_MOUSEBUTTONUP:
			cout << "Button up" << endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			cout << "Button down" << endl;
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

		//Pass the matrix information to the shader
			//Get the uniform variable location
			//Pass the matrix
				//1st parameter: the location
				//2nd parameter: the number of matrices
				//3rd parameter: if we want to tranpose the matrix
				//4th parameter: the matrix data
	GLuint modelMatrixUniform = _colorProgram.getUniformLocation("modelMatrix");
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		//Send data to GPU
	_openGLBuffers.sendDataToGPU(&data[0], data.size());

		//Unbind the program
	_colorProgram.unuse();

		//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

/*
* Execute the actions that must update the game objects
*/
void Game::updateGameObjects() {

	/*
	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	printf("%f, %f, %f\n", result.x, result.y, result.z);
	*/
	
//	glm::mat4 identityMatrix;
	//The animation consists in randomly rotating the triangle. The operations must be done in the inverse order that we want to do
		//Scale the triangle
	//modelMatrix = glm::scale(identityMatrix, glm::vec3(1.25, 1, 1));

		//3rd step: Restore the triangle to its original position
	modelMatrix = glm::translate(modelMatrix, glm::vec3(triangle3DPosition.x, triangle3DPosition.y, 0.0f));
	
		//2nd: Rotate 90º along the z-axis
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		//1st: Move the triangle to the center
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-triangle3DPosition.x, -triangle3DPosition.y, 0.0f));	

}