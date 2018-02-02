#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include "level.h"
#include <vector>
#include <list>

////////////////////////////////////Общий класс родитель//////////////////////////
class Entity {
protected:
	std::vector<Object> _obj;//вектор объектов карты
	float _dx, _dy, _x, _y, _speed, _moveTimer, _currentFrame;;
	int _width, _height, _health, _coinsFound;
	bool _life, _onGround, _lookSide;
	Texture _texture;
	Sprite _sprite;
	String name; //свое действие в update в зависимости от имени;
public:
	virtual void update(float time) = 0;
	Entity(Image &image, float X, float Y, int W, int H, String Name) {
		_x = X;
		_y = Y;
		_width = W;
		_height = H;
		name = Name;
		_moveTimer = 0;
		_lookSide = false;
		_coinsFound = 0;
		_currentFrame = 0;
		_speed = 0;
		_health = 100;
		_dx = 0;
		_dy = 0;
		_life = true;
		_onGround = false;
		_texture.loadFromImage(image);
		_sprite.setTexture(_texture);
		_sprite.setOrigin(_width / 2, _height / 2);
	}
	void SetDx(float value) {
		_dx = value;
	}
	void SetDy(float value) {
		_dy = value;
	}
	void SetY(float value) {
		_y = value;
	}
	void SetX(float value) {
		_x = value;
	}
	void SetOnGround(bool value) {
		_onGround = value;
	}
	void SetHealth(int value) {
		_health = value;
	}
	void SetCoinsFound(int value) {
		_coinsFound = value;
	}
	float GetHeight() const {
		return _height;
	}
	float GetWidth() const {
		return _width;
	}
	int GetCoinsFound() const
	{
		return _coinsFound;
	}
	float GetX() const {
		return _x;
	}
	float GetY() const {
		return _y;
	}
	bool GetLife() const {
		return _life;
	}
	Sprite GetSprite() const
	{
		return _sprite;
	}
	String GetName() const
	{
		return name;
	}
	float GetDx() const {
		return _dx;
	}
	float GetDy() const {
		return _dy;
	}
	bool IsOnGround() const {
		return _onGround;
	}
	bool GetLookSide() const {
		return _lookSide;
	}
	FloatRect GetRect() { //ф-ция получения прямоугольника. его коорд,размеры (шир,высот);
		return FloatRect(_x, _y, _width, _height);
	}

};
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
	enum state { left, right, fight, down, jump, stay } _state;//добавляем тип перечисления - состояние объекта

	Player(Image &image, Level &lvl, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		_obj = lvl.GetAllObjects();
		_state = stay;
		if (name == "viking") {
			_sprite.setTextureRect(IntRect(0, 0, _width, _height));
		}
	}

	void control() {
		if (Keyboard::isKeyPressed) {//если нажата клавиша
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				_state = left;
				_speed = 0.15;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				_state = right;
				_speed = 0.15;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (_onGround)) {//если нажата клавиша вверх и мы на земле, то можем прыгать
				_state = jump;
				_dy = -0.7;
				_onGround = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				_state = down;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				_state = fight;
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = 0; i < _obj.size(); i++)//проходимся по объектам
			if (GetRect().intersects(_obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (_obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) {
						_y = _obj[i].rect.top - _height;
						_dy = 0;
						_onGround = true;
					}
					if (Dy < 0) {
						_y = _obj[i].rect.top + _obj[i].rect.height;
						_dy = 0;
					}
					if (Dx > 0) {
						_x = _obj[i].rect.left - _width;
					}
					if (Dx < 0) {
						_x = _obj[i].rect.left + _obj[i].rect.width;
					}
				}
			}
	}

	void update(float time)
	{
		control();//функция управления персонажем
		switch (_state)//различные действия в зависимости от состояния
		{
		case right: {
			_dx = _speed;
			_lookSide = false;
			_currentFrame += 0.006*time;
			if (_currentFrame > 10) {
				_currentFrame -= 10;
			}
			_sprite.setTextureRect(IntRect(80 * int(_currentFrame), 200, _width, _height));
			_sprite.move(0.1*time, 0);
			break;
		}
		case left: {
			_dx = -_speed;
			_lookSide = true;
			_currentFrame += 0.006*time;
			if (_currentFrame > 10) {
				_currentFrame -= 10;
			}
			_sprite.setTextureRect(IntRect(80 * int(_currentFrame + 1), 200, -_width, _height));
			_sprite.move(-0.1*time, 0);
			break;
		}																																																								//case jump: _currentFrame += 0.003*time;  if (_currentFrame > 5) _currentFrame -= 5; _sprite.setTextureRect(IntRect(80 * int(_currentFrame), 100, _width, _height)); break;//будет состояние поднятия наверх (например по лестнице)
		case down: {
			_currentFrame += 0.003*time;
			if (_currentFrame > 5) {
				_currentFrame -= 5;
			}
			if (!_lookSide) {
				_dx = 0.4;
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame), 400, _width, _height));
			}
			if (_lookSide) {
				_dx = -0.4;
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame + 1), 400, -_width, _height));
			}
			break;
		}
		case stay: {
			_currentFrame += 0.004*time;
			if (_currentFrame > 10) {
				_currentFrame -= 10;
			}
			if (!_lookSide) {
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame), 0, _width, _height));
			}
			if (_lookSide) {
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame + 1), 0, -_width, _height));
			}
			break;
		}
		case fight: {
			_currentFrame += 0.01*time;
			if (_currentFrame > 8) {
				_currentFrame -= 8;
			}
			if (!_lookSide) {
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame), 300, _width, _height));
			}
			if (_lookSide) {
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame + 1), 300, -_width, _height));
			}
			break;//и здесь тоже		
		}
		}
		_state = stay;

		_x += _dx*time;
		checkCollisionWithMap(_dx, 0);//обрабатываем столкновение по Х
		_y += _dy*time;
		checkCollisionWithMap(0, _dy);//обрабатываем столкновение по Y
		_sprite.setPosition(_x + _width / 2, _y + _height / 2); //задаем позицию спрайта в место его центра
		if (_health <= 0) {
			_life = false;
		}
		if (!_onGround) {
			_currentFrame += 0.003*time;
			if (_currentFrame > 5) {
				_currentFrame -= 5;
			}
			if (_lookSide == false) {
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame), 100, _width, _height));
			}
			else {
				_sprite.setTextureRect(IntRect(80 * int(_currentFrame + 1), 100, -_width, _height));
			}
		}
		_dy = _dy + 0.0015*time;//постоянно притягиваемся к земле;
		_dx = 0;
	}
};

	class Platform : public Entity {//класс движущейся платформы
	public:

		Platform(Image &image, float X, float Y, int W, int H, String Name, Level &lvl) :Entity(image, X, Y, W, H, Name) {
			_sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
			_dx = 0.08;//изначальное ускорение по Х
		}

		void update(float time)
		{
		}

		void update(float time, int distance)//функция обновления платформы.
		{

			_y += _dx * time;//реализация движения по горизонтали
			_moveTimer += time;//наращиваем таймер
			if (_moveTimer > distance) {
				_dx *= -1; 
				_moveTimer = 0; 
			}//если прошло примерно 2 сек, то меняется направление движения платформы,а таймер обнуляется
			_sprite.setPosition(_x + _width / 2, _y + _height / 2);//задаем позицию спрайту
		}
		void update(float time, int distance, bool value)//функция обновления платформы.
		{
			_x += _dx * time;//реализация движения по вертикали
			_moveTimer += time;//наращиваем таймер
			if (_moveTimer > distance) {
				_dx *= -1; 
				_moveTimer = 0; 
			}//если прошло примерно 2 сек, то меняется направление движения платформы,а таймер обнуляется
			_sprite.setPosition(_x + _width / 2, _y + _height / 2);//задаем позицию спрайту
		}
	};

	class Enemy :public Entity {
	public:
		Enemy(Image &image, Level &lvl, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
			_obj = lvl.GetAllObjects();
			_sprite.setTextureRect(IntRect(0, 0, _width, _height));
		}

		void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
		{
			for (int i = 0; i < _obj.size(); i++)//проходимся по объектам
				if (GetRect().intersects(_obj[i].rect))//проверяем пересечение игрока с объектом
				{
					if (_obj[i].name == "solid")//если встретили препятствие
					{
						if (Dy > 0) { 
							_y = _obj[i].rect.top - _height; 
							_dy = 0;
							_onGround = true; 
						}
						if (Dy < 0) { 
							_y = _obj[i].rect.top + _obj[i].rect.height; 
							_dy = 0; 
						}
					}
				}
		}

		void update(float time)
		{
			_y += _dy*time;
			checkCollisionWithMap(0, _dy);//обрабатываем столкновение по Y
			_sprite.setPosition(_x + _width / 2, _y + _height / 2); //задаем позицию спрайта в место его центра
			if (_health <= 0) {
				_life = false;
			}
			if (_life) { 
				_currentFrame += 0.004*time; 
				if (_currentFrame > 5) {
					_currentFrame -= 5;
				}
					_sprite.setTextureRect(IntRect(100 * int(_currentFrame), 0, _width, _height)); }
			if (!_life) {
				_currentFrame += 0.004*time;
				_sprite.setTextureRect(IntRect(100 * int(_currentFrame), 100, _width, _height));
				if (_currentFrame > 9) {
					_sprite.setTextureRect(IntRect(800, 100, _width, _height));
				}
			}
			_dy = _dy + 0.0015*time;//постоянно притягиваемся к земле;
			_dx = 0;
		}
	};


	class Coin : public Entity {//класс монеты
	public:

		Coin(Image &image, float X, float Y, int W, int H, String Name, Level &lvl) :Entity(image, X, Y, W, H, Name) {
			_sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
		}

		void update(float time)
		{
			_sprite.setPosition(_x + _width / 2, _y + _height / 2);//задаем позицию спрайту
			_currentFrame += 0.009*time;
			if (_currentFrame > 10) {
				_currentFrame -= 10;
			}
			_sprite.setTextureRect(IntRect(50 * int(_currentFrame), 0, _width, _height));
			if (_health <= 0) { 
				_life = false; 
			}
		}
	};

	class CoinsBar : public Entity {//класс панели монеток
	public:

		CoinsBar(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
			_sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
		}
		void update(float time)
		{
		}
		void update(float time, int coinsFound, int x, int y)
		{

			_sprite.setPosition(view.getCenter().x - 270, view.getCenter().y - 270);//задаем позицию спрайту
			if (coinsFound == 0) {
				_sprite.setTextureRect(IntRect(0, 0, _width, _height));
			}
			if (coinsFound == 1) {
				_sprite.setTextureRect(IntRect(0, 60, _width, _height)); 
			}
			if (coinsFound == 2) { 
				_sprite.setTextureRect(IntRect(0, 120, _width, _height)); 
			}
			if (coinsFound == 3) {
				_sprite.setTextureRect(IntRect(0, 180, _width, _height)); 
			}
			if (coinsFound == 4) { 
				_sprite.setTextureRect(IntRect(0, 240, _width, _height)); 
			}
			if (coinsFound == 5) { 
				_sprite.setTextureRect(IntRect(0, 300, _width, _height));
			}
		}

	};

	class LevelFinish : public Entity {
	public:

		LevelFinish(Image &image, float X, float Y, int W, int H, String Name, Level &lvl) :Entity(image, X, Y, W, H, Name) {
			_sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
		}
		void update(float time)
		{
		}
	};

	class Abyss : public Entity {//класс движущейся платформы
	public:

		Abyss(Image &image, float X, float Y, int W, int H, String Name, Level &lvl) :Entity(image, X, Y, W, H, Name) {
			_sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
		}
		void update(float time)
		{
		}
	};

