#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cassert>
#include <cmath>

using namespace std;
using namespace sf;

// ���������� ���������� ������� ������.
//int WIDTH = VideoMode::getDesktopMode().width;
//int HEIGHT = VideoMode::getDesktopMode().height;
int WIDTH = 683;
int HEIGHT = 384;

double deltaTime = 0; // ���������� ���������� �������.
double anim_speed = 15.f; // �������� ������������ ��������
double thick_size = (WIDTH + HEIGHT)/ 300; // ������ �������

bool start_game = false; // ������ �� ����
bool to_settings = false; // ������� � ����������

Vector2i mouse_position; // ������� ����
Font main_font; // �������� ����� ����
Color main_color = Color(255, 255, 255, 255); // ������� ���� ����.

// �������� ����
RenderWindow window(VideoMode(WIDTH, HEIGHT), "I became an excelent student when I visited another world");

View view(FloatRect(0.f, 0.f, WIDTH, HEIGHT));



// ~~~~~~~~~~~~~~�����������_�������~~~~~~~~~~~~~~~

// ��������������� � ���������� ������� � ������� ����
void background_init(Texture &txt, RectangleShape &background){
	background.setSize(Vector2f(WIDTH, HEIGHT));
    background.setTexture(&txt);
    background.setOrigin(Vector2f(background.getSize().x / 2, background.getSize().y / 2));
    background.setPosition(WIDTH / 2, HEIGHT / 2);
}

// ������� �������� �������� ����� � ������
string to_string(double num){
	ostringstream result;
	result << num;
	return result.str();
}
 // ������� ������ � ����� �����
int stoi(string str)
{
	int result = 0;
	for (int i = 0; i < str.length(); i++){
		assert((str[i] >= '0') && (str[i] <= '9'));
		result += str[i] - '0';
		result *= 10;
	}
	result /= 10;
	return result;
}

