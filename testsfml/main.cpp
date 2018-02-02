#include "Objects.h"


void changeLevel(Level &lvl, int numberLevel, Image &movePlatformImage, int &platformWidth, int &platformHeight, int &platformUpDownDistance, int &platformLeftRightDistance, float &minX, float &minY, float &maxY, float &maxX);
void startGame(RenderWindow &window, int &numberLevel, int &lvlOpen);
void menu(int &lvlOpen);

void main()
{
	int lvlOpen = 1;
	menu(lvlOpen);//вызов меню
}

void menu(int &lvlOpen) {
	int numberLevel = 1; //старт;
	bool isMenu = 1;
	int menuNum = 0;

	RenderWindow window(VideoMode(800, 600), "SFML", sf::Style::Titlebar); //создаем объект окна "SFML";
	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuBackground, menuExit;

	menuTexture1.loadFromFile("images/1.jpg");
	menuTexture2.loadFromFile("images/2.jpg");
	menuTexture3.loadFromFile("images/3.jpg");
	menuTexture4.loadFromFile("images/4.jpg");
	menuBackground.loadFromFile("images/10.png");
	menuExit.loadFromFile("images/exit.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu4(menuTexture4), menu3(menuTexture3), menuBg(menuBackground), exit(menuExit);

	menu1.setPosition(180, 184);
	menu2.setPosition(270, 184);
	menu3.setPosition(360, 184);
	menu4.setPosition(460, 184);
	menuBg.setPosition(0, 0);
	exit.setPosition(639, 116);

	while (isMenu)
	{
		menuNum = 0;

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		exit.setColor(Color::White);

		if (IntRect(180, 184, 92, 100).contains(Mouse::getPosition(window))) {
			menu1.setColor(Color::Yellow);
			menuNum = 1;
		}
		if (IntRect(270, 184, 92, 100).contains(Mouse::getPosition(window))) {
			if (lvlOpen<2) {
				menu2.setColor(Color::Blue);
			}
			else {
				menu2.setColor(Color::Yellow);
			}
			menuNum = 2;
		}
		if (IntRect(360, 184, 92, 100).contains(Mouse::getPosition(window))) {
			if (lvlOpen<3) {
				menu3.setColor(Color::Blue);
			}
			else {
				menu3.setColor(Color::Yellow);
			}
			menuNum = 3;
		}
		if (IntRect(450, 184, 92, 100).contains(Mouse::getPosition(window))) {
			if (lvlOpen<4) {
				menu4.setColor(Color::Blue);
			}
			else {
				menu4.setColor(Color::Yellow);
			}
			menuNum = 4;
		}
		if (IntRect(639, 116, 50, 50).contains(Mouse::getPosition(window))) {
			exit.setColor(Color::Yellow);
			menuNum = 5;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				numberLevel = 1;
			}
			if (menuNum == 2) {
				if (lvlOpen >= 2) {
					numberLevel = 2;
				}
				else {
					window.close();
					menu(lvlOpen);
				}
			}
			if (menuNum == 3) {
				if (lvlOpen >= 3) {
					numberLevel = 3;
				}
				else {
					window.close();
					menu(lvlOpen);
				}
			}
			if (menuNum == 4) {
				if (lvlOpen >= 4) {
					numberLevel = 4;
				}
				else {
					window.close();
					menu(lvlOpen);
				}
			}
			if (menuNum == 5) {
				std::exit(0);
			}
			isMenu = false;
			startGame(window, numberLevel, lvlOpen);

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.draw(exit);
		window.display();

	}
}

void changeLevel(Level &lvl, int numberLevel, Image &movePlatformImage, int &platformWidth, int &platformHeight, int &platformUpDownDistance, int &platformLeftRightDistance, float &minX, float &minY, float &maxY, float &maxX) {
	switch (numberLevel) {
	case 1: {
		lvl.LoadFromFile("level 1.tmx");
		movePlatformImage.loadFromFile("images/platformwinter.png");
		platformWidth = 230;
		platformHeight = 55;
		platformUpDownDistance = 2500;
		platformLeftRightDistance = 5500;
		minX = 400;
		minY = 300;
		maxY = 660;
		maxX = 1390;
		break;
	}
	case 2: {
		lvl.LoadFromFile("level 2.tmx");
		movePlatformImage.loadFromFile("images/platformdesert.png");
		platformWidth = 177;
		platformHeight = 64;
		platformUpDownDistance = 4500;
		platformLeftRightDistance = 4000;
		minX = 400;
		minY = 300;
		maxY = 750;
		maxX = 880;
		break;
	}
	case 3: {
		lvl.LoadFromFile("level 3.tmx");
		movePlatformImage.loadFromFile("images/platformcemetry.png");
		platformWidth = 180;
		platformHeight = 65;
		platformUpDownDistance = 9200;
		platformLeftRightDistance = 4200;
		minX = 400;
		minY = 300;
		maxY = 820;
		maxX = 1580;
		break;
	}
	case 4: {
		lvl.LoadFromFile("level 4.tmx");
		movePlatformImage.loadFromFile("images/platformforest.png");
		platformWidth = 180;
		platformHeight = 65;
		platformUpDownDistance = 7000;
		platformLeftRightDistance = 3300;
		minX = 400;
		minY = 300;
		maxY = 1380;
		maxX = 1260;
		break;
	}
	}
}

void startGame(RenderWindow &window, int &numberLevel, int &lvlOpen) {
	view.reset(FloatRect(0, 0, 800, 600));

	int platformWidth, platformHeight, platformUpDownDistance, platformLeftRightDistance;
	float minX, minY, maxY, maxX;

	Level lvl;

	Image movePlatformImage; //создаем объект Image;
	Image heroImage;
	Image coinImage;
	Image coinBarImage;
	Image levelFinish;
	Image enemyImage;
	Image abyssImage;

	enemyImage.loadFromFile("images/enemy.png");
	coinImage.loadFromFile("images/coins.png"); //загружаем в Image изображение;
	heroImage.loadFromFile("images/viking.png");
	/*levelFinish.loadFromFile("images/Sign_2.png");*/
	coinBarImage.loadFromFile("images/coinsbar.png");

	changeLevel(lvl, numberLevel, movePlatformImage, platformWidth, platformHeight, platformUpDownDistance, platformLeftRightDistance, minX, minY, maxY, maxX); //инициализируем необходимые переменные для текущего уровня/переходим на новый;

	Object enemy = lvl.GetObject("enemy");
	Object platform1 = lvl.GetObject("MovingPlatform");
	Object platform2 = lvl.GetObject("MovingPlatform1");
	Object player = lvl.GetObject("player");
	Object finish = lvl.GetObject("finish");
	Object abyssObject = lvl.GetObject("abyss");

	Enemy e(enemyImage, lvl, enemy.rect.left, enemy.rect.top, 100, 100, "enemy");
	Player p(heroImage, lvl, player.rect.left, player.rect.top, 80, 100, "viking");
	LevelFinish levelEnd(levelFinish, finish.rect.left, finish.rect.top, 50, 50, "finish", lvl);
	CoinsBar bar(coinBarImage, view.getCenter().x - 270, view.getCenter().y - 270, 250, 50, "coinsbar");
	Abyss abyss(abyssImage, abyssObject.rect.left, abyssObject.rect.top, 5000, 5000, "abyss", lvl);

	Platform platformUpDown(movePlatformImage, platform1.rect.left, platform1.rect.top, platformWidth, platformHeight, "MovingPlatform", lvl);
	Platform platformLeftRight(movePlatformImage, platform2.rect.left, platform2.rect.top, platformWidth, platformHeight, "MovingPlatform1", lvl);

	list<Entity*> coinsList; //создаём список для монет;
	list<Entity*>::iterator it; //итератор для перемещения по списку;
	vector<Object> coinsVector = lvl.GetObjects("coin"); //создаем вектор из монет с карты;

	for (int i = 0; i < coinsVector.size(); i++) {
		coinsList.push_back(new Coin(coinImage, coinsVector[i].rect.left, coinsVector[i].rect.top, 50, 50, "coin", lvl)); //помещаем монеты в список;
	}

	Clock clock;  //создаем переменную времени;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //определяем прошедшее время в микросекундах;
		clock.restart();  //перезагружает время
		time = time / 700; //скорость игры

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		platformUpDown.update(time, platformUpDownDistance);
		platformLeftRight.update(time, platformLeftRightDistance, 0);

		/*for (Entity* a: coinsList) {
		a->update(time);
		}*/

		for (it = coinsList.begin(); it != coinsList.end();)
		{
			(*it)->update(time); //вызываем ф-цию update для всех объектов
			if ((*it)->GetLife() == false) {
				it = coinsList.erase(it);
				p.SetCoinsFound(p.GetCoinsFound() + 1);
			} // если этот объект мертв, то удаляем его
			else {
				it++;
			} //идем итератором к след объекту
		}

		for (it = coinsList.begin(); it != coinsList.end(); it++)//проходимся по эл-там списка
		{
			if ((*it)->GetRect().intersects(p.GetRect())) //если прямоугольник спрайта объекта пересекается с игроком
			{
				if ((*it)->GetName() == "coin") {
					(*it)->SetHealth(0);
				}
			}
		}

		if ((platformUpDown.GetName() == "MovingPlatform") && (platformUpDown.GetRect().intersects(p.GetRect())))//если игрок столкнулся с объектом
		{
			if ((p.GetDy() > 0) || (p.IsOnGround() == false)) {//при этом игрок находится в состоянии Jump, т.е падает вниз
				if (p.GetY() + p.GetHeight() < platformUpDown.GetY() + platformUpDown.GetHeight())
				{
					p.SetDy(0); p.SetOnGround(true); p.SetY(platformUpDown.GetY() - p.GetHeight());
				}
			}
			if (p.GetY() + p.GetHeight() > platformUpDown.GetY() + platformUpDown.GetHeight())
			{
				p.SetDy(0.5);
			}
		}

		if ((platformLeftRight.GetName() == "MovingPlatform1") && (platformLeftRight.GetRect().intersects(p.GetRect())))
		{
			if ((p.GetDy() > 0) || (p.IsOnGround() == false))
				if (p.GetY() + p.GetHeight() < platformLeftRight.GetY() + platformLeftRight.GetHeight())
				{
					p.SetY(platformLeftRight.GetY() - p.GetHeight() + 3); p.SetX(p.GetX() + platformLeftRight.GetDx()*time); p.SetDy(0); p.SetOnGround(true);
				}
			if (p.GetY() + p.GetHeight() > platformLeftRight.GetY() + platformLeftRight.GetHeight())
			{
				p.SetDy(0.5);
			}
		}


		if ((e.GetName() == "enemy") && (e.GetRect().intersects(p.GetRect())) && e.GetLife()) {
			if (!p.GetLookSide()) {
				p.SetX(e.GetRect().left - p.GetWidth() + 15);
			}
		}

		if ((abyss.GetName() == "abyss") && (abyss.GetRect().intersects(p.GetRect()))) {
			window.close();
			menu(lvlOpen);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space) && (e.GetName() == "enemy") && (e.GetRect().intersects(p.GetRect())))
		{
			e.SetHealth(0);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space) && (levelEnd.GetName() == "finish") && (levelEnd.GetRect().intersects(p.GetRect())) && p.GetCoinsFound() == 5) {
			window.close();
			lvlOpen++;
			menu(lvlOpen);
		}
		p.update(time);
		e.update(time);
		bar.update(time, p.GetCoinsFound(), p.GetX(), p.GetY());
		setPlayerCoordinateForView(p.GetX(), p.GetY(), minX, minY, maxY, maxX); //слежение камеры за персонажем

		window.setView(view);
		/*	window.clear();*/
		lvl.Draw(window);
		window.draw(bar.GetSprite());
		window.draw(e.GetSprite());
		window.draw(platformUpDown.GetSprite());
		window.draw(platformLeftRight.GetSprite());
		for (it = coinsList.begin(); it != coinsList.end(); it++) {
			window.draw((*it)->GetSprite());
		}

		window.draw(p.GetSprite());
		window.display();
	}
}
