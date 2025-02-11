#include "sprites.hpp"

namespace level2_nmspc{
	
	class dialog_bar{
		
		Text name;
		Text speech;
		
		bool isClick; // ��� ������������� ������� ���
		bool isPrinting; // ���������� �� � ������ ������ �����
		
		RectangleShape shape; // ����� ������
		RectangleShape name_shape; // ����� ���� � ������ ���������
		
		int max_lenght; // ������������ ���������� ���� � ������
		
		double alpha; // ������� ������������ ������
		double x, y; // ���������� ������
		double speed; // �������� ��������
		double delta_time_text_animation; // ����� ��� ������ ����� �����		
		
		string script_text; // ������ ��������
		string current_speech; // ������� ���� ���������
		string name_character; // ��� ���������
		string current_speech_animated; // ������������� ����� ������� ����
		
		SoundBuffer buffer; // ���� ������ ������
		Sound text_appearence;
		
		void parsing(string str); // ������ ��������
		void text_animation(string str); // �������� ������ ��������
		
	public:
		
		fstream script; // ����� ��������
		
		bool isActive; // ������� �� � ������ ������ ������
		
		void update(); // ����������
		void render(); // ���������
		
		int script_act;
		
		
		dialog_bar(){
			shape.setSize(Vector2f(WIDTH - 2 * (thick_size), HEIGHT * 0.2));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, 0));
			shape.setFillColor(Color(255, 255, 255, 255));
			shape.setOutlineColor(Color(0, 0, 0, 255));
			shape.setOutlineThickness(thick_size);
			shape.setPosition(WIDTH / 2, HEIGHT + thick_size);
			
			name_shape.setSize(Vector2f(WIDTH / 6, WIDTH / 25));
			name_shape.setOrigin(Vector2f(name_shape.getSize().x / 2, name_shape.getSize().y / 2));
			name_shape.setFillColor(Color(200, 200, 200, 255));
			name_shape.setOutlineThickness(thick_size);
			name_shape.setOutlineColor(Color(0, 0, 0, 255));
			name_shape.setPosition(WIDTH / 9, HEIGHT + thick_size + name_shape.getSize().y / 2);
			
			name_character = "������";
			name.setFont(main_font);
			name.setFillColor(Color(0, 0, 0, 255));
			name.setCharacterSize((HEIGHT + WIDTH) / 2 * 0.016f);
			name.setPosition(name_shape.getPosition().x - name.getCharacterSize() * 0.8f * name_character.length() / 2, name_shape.getPosition().y - name.getCharacterSize() / 2);
			name.setString(name_character);
			
			speech.setFont(main_font);
			speech.setFillColor(Color(0, 0, 0, 255));
			speech.setCharacterSize((HEIGHT + WIDTH) / 2 * 0.025f);
			speech.setPosition(WIDTH / 8, HEIGHT + shape.getSize().y / 3);
			
			x = WIDTH / 2;
			y = HEIGHT - (WIDTH - shape.getSize().x) / 2;
			
			max_lenght = WIDTH * 0.82f / ((HEIGHT + WIDTH) / 2 * 0.025f);
			script_act = 0;
			
			speed = WIDTH / 4.f;
			delta_time_text_animation = 0.05f;
			
			isClick = false;
			isActive = false;
			isPrinting = false;
			
			buffer.loadFromFile("Sounds/text.ogg");
			text_appearence.setBuffer(buffer);
			text_appearence.setVolume(5.f);
			
			script.open("Scripts/Script2.dat");
			if(!script) cout<<"Error!!! File not open."<<'\n';
			else cout<<"File opened succsessfully."<<'\n';
		}	
	};
	
	// ����������
	void dialog_bar::update(){
		
		if (isActive){
			// �������� ��������� ������
			if (name_shape.getPosition().y > HEIGHT){
				name_shape.move(0, -speed / 4 * deltaTime);
				name.move(0, -speed / 4 * deltaTime);
			}
			if (view.getCenter().y < HEIGHT / 2 + shape.getSize().y + 2 * thick_size){
				view.move(0, speed * deltaTime);
				if (view.getCenter().y > HEIGHT / 2 + shape.getSize().y + 2 * thick_size){
					view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2 + shape.getSize().y + 2 * thick_size + 0.001f));
				}
			}
			
			if(Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1)){
				if (!isClick){
					if (!isPrinting){
						name_character = current_speech = current_speech_animated = "";
						delta_time_text_animation = 0.05f;
						getline(script, script_text);
						parsing(script_text);
						name.setString(name_character);
						name.setPosition(name_shape.getPosition().x - name.getCharacterSize() * 0.8f * name_character.length() / 2, name_shape.getPosition().y - name.getCharacterSize() / 2);
						isPrinting = true;
					}
					else{
						delta_time_text_animation = 0.02f;
					}
				}
				isClick = true;
			}
			else{
				isClick = false;
			}
			
			if (isPrinting){
				text_animation(current_speech);
				speech.setString(current_speech_animated);
			}
				
			
		}
		else {
			// �������� ������������ ���������� ������
			if (view.getCenter().y > HEIGHT / 2){
				view.move(0, - speed * deltaTime);
				if (view.getCenter().y < HEIGHT / 2){
					view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
					
				}
			}
			if (name_shape.getPosition().y < HEIGHT + name_shape.getSize().y / 2 + thick_size){
				name_shape.move(0, speed / 4 * deltaTime);
				name.move(0, speed / 4 * deltaTime);
			}
		}
	}
	
	// ������ ��������
	void dialog_bar::parsing(string str){
		bool name = false;
		bool action = false;
		string action_str = "";
		for(int i = 0; i < str.length(); i++){
			if (str[i] == '<') {
				name = true;
				continue;
			} 
			else if (str[i] == '>') {
				name = false;
				continue;
			}
			else if (str[i] == '@'){
				continue;
			}
			else if (str[i] == '['){
				action = true;
				continue;
			}
			else if (str[i] == ']'){
				script_act = stoi(action_str);
				action_str = "";
				action = false;
				continue;
			}
			
			if (name) name_character += str[i];
			else if (action){
				action_str += str[i];
			}
			else current_speech += str[i];
		}
	}
	
	// �������� ������ ������
	void dialog_bar::text_animation(string str){
		static int index = 0;
		static int line_index = 0;
		static Clock text_animation_timer;
		double text_animation_time = (double)text_animation_timer.getElapsedTime().asMilliseconds() / 1000;
		
		if(current_speech_animated.length() >= str.length()){
			index = line_index = 0;
			isPrinting = false;
		}
		
		if (text_animation_time > delta_time_text_animation){
			if (delta_time_text_animation > 0.04f) text_appearence.play();
			current_speech_animated += str[index];
			index++;
			line_index++;
			text_animation_timer.restart();
		}
		
		if (line_index > max_lenght && str[index] == ' '){
			current_speech_animated += '\n';
			line_index = 0;
		}
	}
	
	// ���������
	void dialog_bar::render(){
		window.draw(shape);
		window.draw(name_shape);
		window.draw(name);
		window.draw(speech);
	}
	
}
