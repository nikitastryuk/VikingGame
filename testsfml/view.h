#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;
sf::View view;

void setPlayerCoordinateForView(float x, float y, float minX, float minY, float maxY, float maxX) {
	float tempX = x; float tempY = y;
	cout << x << " " << y << endl;
	if (x < minX) tempX = minX;
	if (x > maxX) tempX = maxX;
	if (y < minY) tempY = minY;//верхнюю сторону
	if (y > maxY) tempY = maxY;//нижнюю стороню.для новой карты

	view.setCenter(tempX, tempY); 
}