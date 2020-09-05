#include <iostream>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>

class GameState{
public:
	GameState(){}
	bool menuScreen = true;		//men screen
	bool gameCompleted = false;	//end screen
	bool gameOver = false;		//end screen modifier
	bool ingame = false;		//ingame

	int level = -1;				//-1 = no level

};

class Brick : public sf::Sprite{
public:
	Brick(sf::Vector2f pos_, sf::Texture& tex_, std::string type_);
	std::string type;	//neutrual or spikes
};

Brick::Brick(sf::Vector2f pos_, sf::Texture& tex_, std::string type_){
	setPosition(pos_);
	setTexture(tex_);
	type = type_;
}

class AnimatedSprite : public sf::Sprite{
public:
	AnimatedSprite(){};
	virtual ~AnimatedSprite() = default;

	bool toRemove;
	std::string type;
	virtual void animate()=0;

};

class Enemy : public AnimatedSprite{
public:
	Enemy(){};
	virtual ~Enemy() = default;
	virtual void animate(){};
	int frametime;	//changing and randomising movement patterns
	int speed;
	std::string type;
};

class EnemySnail : public Enemy{
public:
	EnemySnail(sf::Vector2f pos_, sf::Texture& tex_);
	virtual void animate() override;
};

EnemySnail::EnemySnail(sf::Vector2f pos_, sf::Texture& tex_){
	setPosition(pos_);
	setTexture(tex_);
	toRemove = false;
	frametime = rand()%50+100;
	speed = rand()%1+1;
	type = "snail";
}

void EnemySnail::animate(){

	if(frametime < 100) {move( speed,0);}
	if(frametime > 100) {move(-speed,0);}
	if(frametime == 200){frametime = 0;}

	frametime++;
}

class EnemyFly : public Enemy{
public:
	EnemyFly(sf::Vector2f pos_, sf::Texture& tex_);
	virtual void animate() override;
};

EnemyFly::EnemyFly(sf::Vector2f pos_, sf::Texture& tex_){
	setPosition(pos_);
	setTexture(tex_);
	toRemove = false;
	frametime = rand()%50+100;
	speed = rand()%1+1;
	type = "fly";
}

void EnemyFly::animate(){
	if(frametime < 100) {move(0, speed);}
	if(frametime > 100) {move(0,-speed);}
	if(frametime == 200){frametime = 0;}

	frametime++;
}

class Coin : public Enemy{
public:
	Coin(sf::Vector2f pos_, sf::Texture& tex_, std::string type_);
	virtual void animate(){};
};

Coin::Coin(sf::Vector2f pos_, sf::Texture& tex_, std::string type_){
	this->setPosition(pos_);
	this->setTexture(tex_);
	toRemove = false;
	type = type_;
}

class Player : public sf::Sprite{
public:
	Player(sf::Vector2f pos_);
	void steer(const std::vector<Brick>& brickObjVec, std::vector<std::unique_ptr<Enemy>>& enemyPtrVec);	//handles collision and movement
	void updateTexture(const std::vector<sf::Texture>& txtVector);											//updating texure as player is walking
	void killPlayer();																						//resets player velocity and acceleration
	void recalculateColl();																					//clears and recalculates collision containers

	float speed = 7;																						//todo: add modifiers
	int points = 0;
	int life = 3;
	bool hasReachedGoal = false;

private:
	bool isCollCalculated;	//collsion containers state
	float gravity = 1;		//todo: add modifiers
	float drag = 1;
	float velX = 0;
	float velY = 0;
	float accX = 0;
	float accY = 0;
	float walkStep;			//texture index
	bool isFalling;			//movement and collision bools
	bool canMoveRight;
	bool canMoveLeft;
	bool canJump;

protected:
	float texture_correction_offset = 1.3f;					//needed after changing player size
	std::vector<std::pair<float,float>>walkableGroundPos;	//ground collision vector
	std::vector<std::pair<float,float>>deathPoints;			//spikes collision vector
	sf::Vector2f goalPos;									//goal block position

};

Player::Player(sf::Vector2f pos_){
	setPosition(pos_);
	isCollCalculated = false;
}

void Player::recalculateColl(){
	isCollCalculated = false;
	walkableGroundPos.clear();
	deathPoints.clear();
	goalPos.x = 0;
	goalPos.y = 0;
}

void Player::killPlayer(){
	velX = 0;
	velY = 0;
	accX = 0;
	accY = 0;
	life--;
}

void Player::steer(const std::vector<Brick>& brickObjVec, std::vector<std::unique_ptr<Enemy>>& enemyPtrVec){

	const auto bounds = this->getGlobalBounds();

	canJump = true;
	isFalling = true;

	float x = getPosition().x;
	float y = getPosition().y;

	if(!isCollCalculated){
		for(size_t i = 0; i<brickObjVec.size(); i++){
			float currX = 0;
			if(brickObjVec[i].type == "grass"){
				currX = brickObjVec[i].getGlobalBounds().left + brickObjVec[i].getGlobalBounds().width;
				walkableGroundPos.emplace_back(std::make_pair(currX-70,brickObjVec[i].getGlobalBounds().top-texture_correction_offset*brickObjVec[i].getGlobalBounds().height));
			}
			if(brickObjVec[i].type == "grassC"){
				currX = brickObjVec[i].getGlobalBounds().left + brickObjVec[i].getGlobalBounds().width;
				walkableGroundPos.emplace_back(std::make_pair(currX-70,brickObjVec[i].getGlobalBounds().top-texture_correction_offset*brickObjVec[i].getGlobalBounds().height));
			}
			if(brickObjVec[i].type == "death"){
				currX = brickObjVec[i].getGlobalBounds().left + brickObjVec[i].getGlobalBounds().width;
				deathPoints.emplace_back(std::make_pair(currX-70,brickObjVec[i].getGlobalBounds().top-texture_correction_offset*brickObjVec[i].getGlobalBounds().height));
			}
			if(brickObjVec[i].type == "goal"){
				currX = brickObjVec[i].getGlobalBounds().left + brickObjVec[i].getGlobalBounds().width;
				walkableGroundPos.emplace_back(std::make_pair(currX-70,brickObjVec[i].getGlobalBounds().top-texture_correction_offset*brickObjVec[i].getGlobalBounds().height));
				goalPos = sf::Vector2f(currX-70,brickObjVec[i].getGlobalBounds().top-texture_correction_offset*brickObjVec[i].getGlobalBounds().height);
			}
		}
		isCollCalculated = true;
	}

	for(const auto &p : walkableGroundPos){
		if(x >= p.first-70 && x < p.first+70){
			if( y == p.second ){
				isFalling = false;
				velY = 0;
				break;
			}
		}
	}

	for(const auto &dp : deathPoints){
		if(x >=dp.first && x < dp.first+70){
			if( y > dp.second+50){
				x = 70;
				y = 0;
				killPlayer();
				break;
			}
		}
	}

	for(const auto &en : enemyPtrVec){
		if(en->getGlobalBounds().intersects(bounds)){
			if(en->type == "snail"){
				x = 70;
				y = 0;
				killPlayer();
			}
			if(en->type == "fly"){
				x = 70;
				y = 0;
				killPlayer();
			}
			if(en->type == "coinS"){
				points += 100;
				en->toRemove = true;
			}
			if(en->type == "coinG"){
				points += 300;
				en->toRemove = true;
			}
		}
	}

	for(const auto &b : brickObjVec){
		auto objB = b.getGlobalBounds();
		if(objB.contains(x-1,y)){
			velX = 0;
			accX = 0;
			canMoveLeft = false;
		}
		if(objB.contains(x+70,y)){
			velX = 0;
			accX = 0;
			canMoveRight = false;
		}
		if(objB.contains(x,y-1)){
			velY = 0;
			accY = 0;
		}
	}

	if(getPosition().x >= goalPos.x && y == goalPos.y){
		hasReachedGoal = true;
	}

	//CONTROLS START HERE
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && velX >= 0 && canMoveRight){
		velX = speed;
		walkStep += 0.25;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			if(accX <= 0) velX = speed*2;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && velX <= 0 && canMoveLeft){
		velX = -speed;
		walkStep += 0.25;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			if(accX >= 0) velX = -speed*2;
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isFalling && canJump){
		isFalling = true;
		velY = -speed*3;
	}

	//ADDING DRAG BEACUSE WE REALISTHICCCC AF
	if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && velX > 0){
		velX -= drag;
		accX = 0;
	}

	if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && velX < 0){
		velX += drag;
		accX = 0;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && std::abs(velX)>0){
		accX = 0;
		velX = 0;
	}

	canMoveLeft = true;
	canMoveRight = true;

	velX += accX;
	velY += accY;
	if(isFalling && velY < speed) velY += gravity;

	x += velX;
	y += velY;

	setPosition(x,y);
}

void Player::updateTexture(const std::vector<sf::Texture> &txtVector){

	if( isFalling)	setTexture(txtVector[11]);
	if(!isFalling)	setTexture(txtVector[int(walkStep)]);

	if(walkStep >= 10) {walkStep = 0;}
}

std::vector<std::string>levelLoader(const std::string &file_){

	std::vector<std::string>levelVec;

	std::ifstream level(file_);

	if(level.is_open()){
		std::string line;
		while(std::getline(level,line)){
			levelVec.emplace_back(line);
		}
	}
	level.close();

	return levelVec;
}

std::vector<Brick>levelCreator(const std::vector<std::string> &level_, std::vector<sf::Texture>& tex_){

	std::vector<Brick>brickObjVec;

	for(size_t i=0; i<level_.size(); i++){
		for(size_t j=0; j<level_[0].size(); j++){
			if(level_[i][j] == '1'){
				brickObjVec.emplace_back(Brick(sf::Vector2f(j*tex_[0].getSize().x,i*tex_[0].getSize().y),tex_[0],"grass"));	// grass
			}
			if(level_[i][j] == '2'){
				brickObjVec.emplace_back(Brick(sf::Vector2f(j*tex_[1].getSize().x,i*tex_[1].getSize().y),tex_[1],"death"));	//death block
			}
			if(level_[i][j] == '3'){
				brickObjVec.emplace_back(Brick(sf::Vector2f(j*tex_[0].getSize().x,i*tex_[0].getSize().y),tex_[3],"grassC")); //grass center
			}
			if(level_[i][j] == 'g'){
				brickObjVec.emplace_back(Brick(sf::Vector2f(j*tex_[1].getSize().x,i*tex_[1].getSize().y),tex_[2],"goal"));  //goal
			}
			if(level_[i][j] == 'h'){
				brickObjVec.emplace_back(Brick(sf::Vector2f(j*tex_[0].getSize().x,i*tex_[0].getSize().y),tex_[0],"grass"));	//snail
			}
		}
	}

	return brickObjVec;
}

std::vector<std::unique_ptr<Enemy>>enemyCreator(const std::vector<std::string> &level_, std::vector<sf::Texture>& tex_){

	float offset = 70;

	std::vector<std::unique_ptr<Enemy>>enemyPtrVec;

	for(size_t i=0; i<level_.size(); i++){
		for(size_t j=0; j<level_[0].size(); j++){
			if(level_[i][j] == 'h'){
				enemyPtrVec.emplace_back(std::make_unique<EnemySnail>(sf::Vector2f(j*offset,i*offset-tex_[0].getSize().y),tex_[0]));
			}
			if(level_[i][j] == 's'){
				enemyPtrVec.emplace_back(std::make_unique<Coin>(sf::Vector2f(j*offset,i*offset-tex_[0].getSize().y+30),tex_[1],"coinS"));
			}
			if(level_[i][j] == 'd'){
				enemyPtrVec.emplace_back(std::make_unique<Coin>(sf::Vector2f(j*offset,i*offset-tex_[0].getSize().y+30),tex_[3],"coinG"));
			}
			if(level_[i][j] == 'f'){
				enemyPtrVec.emplace_back(std::make_unique<EnemyFly>(sf::Vector2f(j*offset,i*offset-tex_[0].getSize().y-30),tex_[2]));
			}
		}
	}

	return enemyPtrVec;
}

int main(){

	int width = 900;
	int height = 700;
	int frames = 60;

	srand(time(NULL));

	std::string list[3] = {"lvl1.txt", "lvl2.txt", "lvl3.txt"};	//level name list
	std::string levelname;

	//cointainers
	std::vector<sf::Sprite>drawableObj;				//main drawable - all objects inheriting from sf::Drawable
	std::vector<Brick>brickObjVec;					//level: structure
	std::vector<std::unique_ptr<Enemy>>enemyPtrVec;	//level: enemies
	std::vector<Brick>loadedBrickVec;				//used to calculate collision
	std::vector<sf::Texture>txtPlayerWalk;			//player texture container

	//textures
	sf::Texture txtGrassMid;		txtGrassMid.loadFromFile("grassMid.png");
	sf::Texture txtGrassCenter;		txtGrassCenter.loadFromFile("grassCenter.png");
	sf::Texture txtSpikes;			txtSpikes.loadFromFile("spikes.png");
	sf::Texture txtGoal;			txtGoal.loadFromFile("boxItem.png");
	sf::Texture txtCoinS;			txtCoinS.loadFromFile("coinSilver.png");
	sf::Texture txtCoinG;			txtCoinG.loadFromFile("coinGold.png");
	sf::Texture txtSnail;			txtSnail.loadFromFile("snailWalk1.png");
	sf::Texture txtFly;				txtFly.loadFromFile("flyFly1.png");

	//player walk textures
	for(int i = 0; i<10; i++){
		txtPlayerWalk.emplace_back(sf::Texture());
			txtPlayerWalk[i].loadFromFile("p1_walk0"+std::to_string(i)+".png");
	}
	txtPlayerWalk.emplace_back(sf::Texture());
	txtPlayerWalk[10].loadFromFile("p1_walk10.png");
	sf::Texture txtPlayerJump;		txtPlayerJump.loadFromFile("p1_jump.png");
	txtPlayerWalk.emplace_back(txtPlayerJump);

	//ground textures
	std::vector<sf::Texture>groundTxtVec;
	groundTxtVec.emplace_back(txtGrassMid);
	groundTxtVec.emplace_back(txtSpikes);
	groundTxtVec.emplace_back(txtGoal);
	groundTxtVec.emplace_back(txtGrassCenter);

	//enemy textures
	std::vector<sf::Texture>enemyTxtVec;
	enemyTxtVec.emplace_back(txtSnail);
	enemyTxtVec.emplace_back(txtCoinS);
	enemyTxtVec.emplace_back(txtFly);
	enemyTxtVec.emplace_back(txtCoinG);

	//fonts
	sf::Font font;
	font.loadFromFile("Pangolin-Regular.ttf");
	sf::Text lifeText;
	lifeText.setFont(font);

	//creating player
	Player playerObj(sf::Vector2f(70,0));
	playerObj.setTextureRect(sf::IntRect(0,0,71,97));

	//creating view
	sf::View view;
	view.setSize(width,height);

	//sfml renderwindow + frame limiter
	sf::RenderWindow window(sf::VideoMode(width,height),"sfml");
	window.setFramerateLimit(frames);

	//initialising gamestate manager
	GameState gamestate;

	int frameN = 0;
	int time = 0;

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed){window.close();}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))  {playerObj.setPosition(sf::Vector2f(70,0)); playerObj.recalculateColl();}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))  {window.close();}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && gamestate.menuScreen == true &&gamestate.level != -1){
				//entering a level
				gamestate.menuScreen   = false;
				gamestate.gameOver = false;
				gamestate.ingame = true;

				levelname = list[gamestate.level];

				//clearing containers and recalculating player collision
				loadedBrickVec.clear();
				drawableObj.clear();
				brickObjVec.clear();
				enemyPtrVec.clear();
				playerObj.recalculateColl();

				//loading level from a file
				loadedBrickVec =  levelCreator(levelLoader(levelname),groundTxtVec);
				std::copy(loadedBrickVec.begin(),loadedBrickVec.end(),std::back_inserter(drawableObj));
				enemyPtrVec = enemyCreator(levelLoader(levelname),enemyTxtVec);
			}
		}

		window.clear(sf::Color(65, 130, 135));

		if(gamestate.menuScreen){
			window.clear();

			sf::Text welcomeText;
			welcomeText.setFont(font);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){gamestate.level = 0;}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){gamestate.level = 1;}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){gamestate.level = 2;}


			if(gamestate.level == -1){
				welcomeText.setString("Projekt PSiO\n"
									  "Simple SFML Platformer Game Engine \n\n\n\n\n\n"
									  "Choose level by pressing 1,2 or 3 \n"
									  "Press O to exit the game."
									   "\nIf player gets stuck, press Q to return to spawn position (0,0)");
			}

			if(gamestate.level != -1){
				welcomeText.setString("Projekt PSiO\n"
									  "Simple SFML Platformer Game Engine \n\n\n\n\n\n"
									  "Selected level:"+std::to_string(gamestate.level+1)+
									  "\nPress 'Enter' to start the game"
									  "\nPress 'O' to exit the game."
									  "\nIf player gets stuck, press Q to return to spawn position (0,0)");
			}

			window.draw(welcomeText);
		}

		if(gamestate.gameCompleted){
			window.clear();
			window.setView(window.getDefaultView());

			sf::Text ggText;
			ggText.setFont(font);

			std::string isDead;

			gamestate.gameOver ? isDead = "Game over!!!\n" : isDead = "Level completed!\n";

			ggText.setString(isDead +
							 "Score: "+std::to_string(playerObj.points)+
							 "\nTime: "+std::to_string(time)+
							 "\nPress E to exit the game"
							 "\nPress R to play again\n");

			window.draw(ggText);

			//próbowałem poprawić wygląd dwóch następnych warunków - poległem
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
				gamestate.ingame = false;
				gamestate.menuScreen = true;
				gamestate.gameCompleted = false;
				gamestate.gameOver = false;
				time = 0;
				playerObj.hasReachedGoal = false;
				playerObj.setPosition(70,0);
				playerObj.points = 0;
				playerObj.life = 3;

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
				gamestate.ingame = true;
				gamestate.gameCompleted = false;
				gamestate.gameOver = false;
				time = 0;
				playerObj.hasReachedGoal = false;
				playerObj.setPosition(70,0);
				playerObj.points = 0;
				playerObj.life = 3;
			}

		}

		if(gamestate.ingame){

			//niezgadzający się czas to pretekst do kupna mocniejzego CPU :)
			frameN++;
			if(frameN == 59){
				frameN = 0;
				time++;
			}

			window.clear(sf::Color(65, 130, 135));

			//view stuff
			view.setCenter(playerObj.getPosition().x,playerObj.getPosition().y-50);
			window.setView(view);

			//drawing player and level
			window.draw(playerObj);

			for(const auto & drawable : drawableObj){
				window.draw(drawable);
			}

			//drawing and animating sprites
			for(size_t i=0; i<enemyPtrVec.size();i++){
				enemyPtrVec[i]->animate();
				window.draw(*enemyPtrVec[i]);
				if(enemyPtrVec[i]->toRemove){
					enemyPtrVec.erase(enemyPtrVec.begin()+i);
				}
			}

			window.draw(lifeText);

			//player logic
			playerObj.steer(loadedBrickVec,enemyPtrVec);
			playerObj.updateTexture(txtPlayerWalk);

			if(playerObj.life !=0){
				lifeText.setString("Life: " + std::to_string(int(playerObj.life)) +"\nPoints :"+std::to_string(int(playerObj.points))+"\nTime: "+std::to_string(time));
				lifeText.setPosition(playerObj.getPosition().x-400,playerObj.getPosition().y-370);
			}

			//rip
			if(playerObj.life == 0){
				gamestate.gameCompleted = true;
				gamestate.gameOver = true;
				gamestate.ingame = false;
			}

			//gg
			if(playerObj.hasReachedGoal){
				gamestate.gameCompleted = true;
				gamestate.ingame = false;
			}

		}

		window.display();
	}
	//sukcesem to będzie jak mi pamięć nie wycieknie
	return EXIT_SUCCESS;
}
