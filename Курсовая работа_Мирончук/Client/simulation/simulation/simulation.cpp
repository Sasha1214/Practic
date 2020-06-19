#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

const double pixelsPerKm = 7.865514798730e-4;
const double kmPerPixels = 1 / pixelsPerKm;
double kmToPixels(double km) {
	return km * pixelsPerKm;
}
sf::Vector2<long double> kmToPixels(sf::Vector2<long double> v) {
	return v * (long double)pixelsPerKm;
}
sf::Vector2f kmToPixelsF(sf::Vector2<long double> v) {
	sf::Vector2f vf((float)v.x * (float)pixelsPerKm, (float)v.y * (float)pixelsPerKm);
	return vf;
}
double pixelsToKm(double px) {
	return px * kmPerPixels;
}

sf::Vector2<long double> calculateOrbitVelocity(long double x, long double y);

class CosmicBody {
private:
	// m
	sf::Vector2<long double> pos;
	// m/s
	sf::Vector2<long double> vel;// скорость  (velocity)
	// m/s^2
	sf::Vector2<long double> acc;// ускорение (acceleration)
	
	sf::Color col;

	// m
	long double radius;
	// kg
	long double mass;

	std::string name;
public:
	CosmicBody(long double x, long double y, long double radius, long double mass, std::string name, sf::Vector2<long double> vel = sf::Vector2<long double>(0, 0), sf::Color c = sf::Color::White)
		: pos(sf::Vector2<long double>(x, y)), radius(radius), mass(mass), name(name), vel(vel), col(c)
	{
		/*if (vel.x != 0 && vel.y != 0)
			vel = calculateOrbitVelocity(x, y);*/
	}

	// Выставить свои параметры переданной по ссылке фигуре
	void applyShape(sf::CircleShape& shape) {
		shape.setPosition(kmToPixelsF(pos));
		shape.setRadius(kmToPixels(radius));
		shape.setFillColor(col);

		// Делаем координату круга его центром
		shape.setOrigin(kmToPixels(radius), kmToPixels(radius));
	}

	sf::Vector2<long double> getPosPixels() {
		return kmToPixels(pos);
	}

	sf::Vector2f getPosPixelsF() {
		return kmToPixelsF(pos);
	}

	// Добавить силу к ускорению
	void applyForce(sf::Vector2<long double> force) {
		// F = ma;
		// a = F/m;
		force.x /= mass;
		force.y /= mass;
		acc += force;
	}

	// Посчитать перемещение на этом кадре, сбросить ускорение
	void update(int amountPerSecond) {
		long double a = static_cast<long double>(amountPerSecond);
		vel += (acc / (a*a));
		pos += (vel / a);

		// if (mass == 1) std::cout << vel.y << '\n';

		acc *= 0.L;
	}
	
	/* Геттеры, сеттеры */
	sf::Vector2<long double> getPos() {
		return pos;
	}
	void setPos(sf::Vector2<long double> p) {
		pos = p;
	}
	void setVel(sf::Vector2<long double> v) {
		vel = v;
	}
	sf::Vector2<long double> getVel() {
		return vel;
	}

	long double getRadius() {
		return radius;
	}

	long double getMass() {
		return mass;
	}

	std::string getName() {
		return name;
	}

	void setName(std::string n) {
		name = n;
	}
	sf::Color getColor() {
		return col;
	}
};

std::vector<CosmicBody> bodies;

std::string bodyToStr(CosmicBody& b) {
	std::stringstream buf;
	buf << b.getPos().x << '\n';
	buf << b.getPos().y << '\n';
	buf << b.getRadius() << '\n';
	buf << b.getMass() << '\n';
	buf << b.getName() << '\n';
	buf << b.getVel().x << '\n';
	buf << b.getVel().y << '\n';
	buf << (int)b.getColor().r << '\n';
	buf << (int)b.getColor().g << '\n';
	buf << (int)b.getColor().b << '\n';
	return buf.str();
}

CosmicBody readBody(std::ifstream& fin) {
	long double x, y;
	fin >> x >> y;
	std::cout << "x, y: " << x << " " << y << '\n';
	long double rad;
	fin >> rad;
	std::cout << "rad: " << rad << '\n';
	long double mass;
	fin >> mass;
	std::cout << "mass: " << mass << '\n';
	std::string name;
	fin.ignore();
	std::getline(fin, name);
	std::cout << "name: " << name << '\n';
	long double vx, vy;
	fin >> vx >> vy;
	std::cout << "vx, vy: " << vx << " " << vy << '\n';
	short r, g, b;
	fin >> r >> g >> b;
	std::cout << "r, g, b: " << r << " " << g << " " << b << '\n';

	return CosmicBody(x, y, rad, mass, name, sf::Vector2<long double>(vx, vy), sf::Color(r, g, b));
}

void saveBodies(std::string filename) {
	std::ofstream fout(filename);

	fout << bodies.size() << '\n';
	for (int i = 0; i < bodies.size(); i++) {
		fout << bodyToStr(bodies[i]);
;	}
	fout.close();
}

std::vector<CosmicBody> readBodies(std::string filename) {
	std::vector<CosmicBody> bs;
	std::ifstream fin(filename);
	if (fin) {
		int size;
		fin >> size;
		std::cout << "Читаю информацию о " << size << " телах\n";
		for (int i = 0; i < size; i++) {
			std::cout << "Тело " << i + 1 << ":\n";
			bs.push_back(readBody(fin));
		}
		std::cout << "Итого: " << bs.size() << '\n';
	}
	else {
		std::cout << "Не могу открыть файл " << filename << '\n';
	}

	return bs;
}

/* Глобальные переменные и константы */
int mouseX, mouseY;
float zoomFactor = 1;
const int width = 1280, height = 720;
const long double G = 6.67e-11L;

/* Вспомогательные функции */

// Выставить конкретный zoom
void zoomView(sf::View& view, float zF) {
	view.setSize(width * zF, height * zF);
	zoomFactor = zF;
}

// Добавить к текущему
void zoomViewScale(sf::View& view, float zF) {
	zoomFactor *= zF;
	zoomView(view, zoomFactor);
}

long double vectorLength(long double x, long double y) {
	return sqrt(x*x + y*y);
}

/*long double vectorLength(sf::Vector2<long double> v) {
	return vectorLength(v.x, v.y);
}*/

long double distance(long double x1, long double y1, long double x2, long double y2) {
	long double vectorX = x2 - x1;
	long double vectorY = y2 - y1;

	return vectorLength(vectorX, vectorY);
}

// Первая космическая; h = R0 + h над поверхностью 
long double orbitalVelocity(long double mass, long double h) {
	return sqrt(G*mass/h);
}

// Выставить вектору нужную длину
void setMagnitude(sf::Vector2<long double>& vector, long double mag) {
	long double length = vectorLength(vector.x, vector.y);
	vector /= length;
	// Выставляем нужную длину
	vector *= mag;
}

// "Точность" симуляции -- чем больше, тем точнее
const int precision = 100;

CosmicBody* star = nullptr;
sf::Vector2<long double> calculateOrbitVelocity(long double planetX, long double planetY) {
	if (star == nullptr) {
		std::cout << "Звезда не определена\n";
		return sf::Vector2<long double>(0, 0);
	}

	std::cout << "Передали: " << planetX << " " << planetY << '\n';
	// long double starX = star->getPos().x; long double starY = star->getPos().y;
	long double starX = 0; long double starY = 0;
	std::cout << "Звезда: " << starX << " " << starY << '\n';
	long double velScalar = orbitalVelocity(1.9891e30, distance(starX, starY, planetX, planetY));
	std::cout << "Вычислил скаляр: " << velScalar << " " << distance(starX, starY, planetX, planetY) << '\n';
	// bx = -ay/ax;
	long double yComponent = 1;
	long double xComponent = 1;
	//if (starX - planetX != 0)
		xComponent = -1.0L * (starY - planetY) * yComponent / (starX - planetX);
	/*else
		yComponent = -1.0L * (starX - planetX) * xComponent / (starY - planetY);*/

	std::cout << "Компоненты: " << xComponent << " " << yComponent << '\n';
	sf::Vector2<long double> vel(xComponent, yComponent);
	setMagnitude(vel, velScalar);
	
	std::cout << "Чекаю вектор: " << vel.x << " " << vel.y << '\n';

	vel.x /= 10L;
	vel.y /= 10L;
	return vel;
}

/* Собственно симуляция */
bool isProgramStopped = false;

float timeScale = 1;
int amountPerSecond = precision; //* timeScale;
auto simulationDelay = (1s / static_cast<double>(amountPerSecond));
void changeTimeScale(float scale) {
	if (scale > 4096) scale = 4096;
	else if (scale < 1) scale = 1;
	std::cout << "Выставляю скорость " << scale << "x;\n";
	timeScale = scale;
	amountPerSecond = precision * scale;
	simulationDelay = (1s / static_cast<double>(amountPerSecond));
}

bool isPaused = false, doBlink = false, isActuallyPaused = false;
void pauseSimulation() { std::cout << "На паузе\n"; isPaused = true; }
void playSimulation() { std::cout << "Проигрываю симуляцию\n"; isPaused = false; }
void toggleSimulation() {
	if (isPaused) playSimulation();
	else pauseSimulation();
}
void stopSimulation() {
	isProgramStopped = true;
	while (!isActuallyPaused);
	isProgramStopped = false;
}

void simulationLoop() {
	std::cout << "Starting sim\n";
	while (!isProgramStopped) {
		// Если поставили на паузу, ждём в while, пока нас не снимут с паузы
		while (isPaused && !doBlink) {
			isActuallyPaused = true;
		}
		isActuallyPaused = false;
		if (doBlink) doBlink = false;

		for (int iterations = 0; iterations < 1000; iterations++) {
			for (int i = 0; i < bodies.size(); i++) {
				// CosmicBody& b1 = bodies[i];

				// Просчитать силы
				for (int j = 0; j < bodies.size(); j++) {
					// printf("stuck in here 2 lol\n");

					if (i == j) continue; // Не считать самого себя
					// Мы считаем для b1 на этой итерации*/
					// printf("oof\n");
					// CosmicBody& b2 = bodies[j];
					sf::Vector2<long double> b1Pos = bodies[i].getPos(), b2Pos = bodies[j].getPos();
					long double dist = distance(b1Pos.x, b1Pos.y, b2Pos.x, b2Pos.y);
					//std::cout << "Тела " << i << " и " << j << ": " << dist << '\n';
					long double forceMag = ((G * bodies[i].getMass() * bodies[j].getMass()) / dist) / dist;
					//std::cout << forceMag << '\n';

					// Получаем вектор, соединяющий два тела
					sf::Vector2<long double> force(b2Pos.x - b1Pos.x, b2Pos.y - b1Pos.y);
					//std::cout << force.x << " " << force.y << '\n';
					setMagnitude(force, forceMag);
					//std::cout << force.x << " " << force.y << '\n';

					bodies[i].applyForce(force);
				}
				// Закончили расчёт сил, обновляем скорость и позицию
				bodies[i].update(precision);
			}
		}


		std::this_thread::sleep_for(simulationDelay);
	}
	isActuallyPaused = true;
	std::cout << "Stopping sim\n";
}

sf::Vector2f textPoses[30];

sf::Font font;
const long double coef = 50;
int main()
{
	setlocale(LC_ALL, "Russian");

	if (!font.loadFromFile("Lobster-Regular.ttf")) {
		std::cout << "Не смог загрузить Lobster-Regular.ttf\n";
		return 1;
	}

	/* Настройки окна */
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), "Planet Simulation", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	/* Настройки view */
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(width, height)); // Центр, размер

	/* Описание внешнего вида космических тел */
	sf::CircleShape circleBody(0, 30);
	circleBody.setFillColor(sf::Color::White);
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(24);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(5);

	// Устанавливаем timeScale
	changeTimeScale(1);
	zoomView(view, 3000.f);

	// pauseSimulation();


	// Звезда
	int sunCount = 0;
	CosmicBody Sun(0, 0, 6.9551e8, 1.9891e30, "Sun");
	bodies.push_back(Sun);
	star = &bodies[0];
	// Планеты
	// std::cout << "Расстояние должно быть: " << 6.9551e5L + 149'597'870L;

	bodies.push_back(CosmicBody(57'909'227'000.0L / coef, 0, 2439.7e3, 3.33022e23, "Mercury", calculateOrbitVelocity(57'909'227'000.0L / coef, 0), sf::Color(150, 75, 0)));
	bodies.push_back(CosmicBody(108'208'930'000.0L / coef, 0, 6'051'800, 4.87e24, "Venus", calculateOrbitVelocity(108'208'930'000.0L / coef, 0), sf::Color(36, 179, 167)));
	int earthCount = 0;
	CosmicBody Earth(149'597'870'000.0L / coef, 0, 6'356'863, 5.97e24, "Earth", calculateOrbitVelocity(149'597'870'000.0L / coef, 0), sf::Color(0, 121, 219));
	bodies.push_back(Earth);
	//bodies.push_back(CosmicBody(148'597'870'000.0L / coef, 0, 6'356'863, 5.97e24, "Earthh", calculateOrbitVelocity(149'597'870'000.0L / coef, 0), sf::Color(0, 121, 219)));
	bodies.push_back(CosmicBody(2.2794382e11L / coef, 0, 3'389'500, 6.4171e23, "Mars", calculateOrbitVelocity(2.2794382e11L / coef, 0), sf::Color(153, 46, 0)));

	for (int i = 0; i < bodies.size(); i++) {
		std::cout << i << ") " << bodies[i].getName() << " " << bodies[i].getPos().x << " " << bodies[i].getPos().y << '\n'; 
	}

	std::thread simulationThread(simulationLoop);
	simulationThread.detach();
	 
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch(event.type)                                                           
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					std::cout << "Escape was pressed\n";
					break;
					
				case sf::Keyboard::Left:
					if (event.key.shift)
						view.move(-width/6.0 * zoomFactor, 0);
					else
						view.move(-width/12.0 * zoomFactor, 0);
					break;

				case sf::Keyboard::Right:
					if (event.key.shift)
						view.move(width/6.0 * zoomFactor, 0);
					else
						view.move(width/12.0 * zoomFactor, 0);
					break;

				case sf::Keyboard::Up:
					if (event.key.shift)
						view.move(0, height/6.0 * zoomFactor);
					else
						view.move(0, height/12.0 * zoomFactor);
					break;

				case sf::Keyboard::Down:
					if (event.key.shift)
						view.move(0, -height/6.0 * zoomFactor);
					else
						view.move(0, -height/12.0 * zoomFactor);
					break;

				case sf::Keyboard::Add:
					zoomViewScale(view, 9.f/10);
					std::cout << "Current zoom: " << zoomFactor << '\n';
					/*text.setCharacterSize(24 * zoomFactor);
					text.setOutlineThickness(5 * zoomFactor);*/

					break;

				case sf::Keyboard::Subtract:
					zoomViewScale(view, 10.f/9);
					std::cout << "Current zoom: " << zoomFactor << '\n';
					/*text.setCharacterSize(24 * zoomFactor);
					text.setOutlineThickness(5 * zoomFactor);*/

					break;

				case sf::Keyboard::LBracket:
					if (event.key.shift) changeTimeScale(timeScale - 1);
					else changeTimeScale(timeScale / 2);
					break;

				case sf::Keyboard::RBracket:
					if (event.key.shift) changeTimeScale(timeScale + 1);
					else changeTimeScale(timeScale * 2);
					break;

				case sf::Keyboard::Space:
					toggleSimulation();
					break;

				case sf::Keyboard::R:
					changeTimeScale(1.f);
					break;

				case sf::Keyboard::B:
					doBlink = true;
					break;

				case sf::Keyboard::S: {
					// Ctrl + S
					if (event.key.control) {
						std::cout << "Сохраняю...\n";
						saveBodies("sim.save");
						break;
					}
					else {
						std::cout << "Adding extra Sun\n";
						pauseSimulation();
						while (!isActuallyPaused);

						window.setView(view);
						// Получить текущую позицию мыши в окне
						sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
						//std::cout << "Window coords: x: " << pixelPos.x << " y: " << pixelPos.y << "\n";

						// Конвертировать в "мировые" координаты
						sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
						std::cout << "World coords: x: " << pixelsToKm(worldPos.x) << " y: " << pixelsToKm(worldPos.y) << "\n";

						Sun.setPos(sf::Vector2<long double>(pixelsToKm(worldPos.x), pixelsToKm(worldPos.y)));
						Sun.setName("Sun Copy #" + std::to_string(++sunCount));
						bodies.push_back(Sun);

						playSimulation();
						break;
					}
				}

				case sf::Keyboard::E: {
					std::cout << "Adding extra Earth\n";
					pauseSimulation();
					while (!isActuallyPaused);

					window.setView(view);
					// Получить текущую позицию мыши в окне
					sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
					//std::cout << "Window coords: x: " << pixelPos.x << " y: " << pixelPos.y << "\n";

					// Конвертировать в "мировые" координаты
					sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
					std::cout << "Ставлю копию Земли на x: " << pixelsToKm(worldPos.x) << " y: " << pixelsToKm(worldPos.y) << "\n";

					Earth.setPos(sf::Vector2<long double>(pixelsToKm(worldPos.x), pixelsToKm(worldPos.y)));
					Earth.setVel(calculateOrbitVelocity(pixelsToKm(worldPos.x), pixelsToKm(worldPos.y)));
					Earth.setName("Earth Copy #" + std::to_string(++earthCount));
					bodies.push_back(Earth);

					playSimulation();
					break;
				}

				case sf::Keyboard::O:
					// Ctrl + O
					if (event.key.control) {
						pauseSimulation();
						while (!isActuallyPaused);

						std::cout << "Открываю...\n";
						bodies = readBodies("sim.save");

						playSimulation();
					}
					break;

				case sf::Keyboard::U:
					// Ctrl + U
					if (event.key.control) {
						std::cout << "Выгружаю файл сохранения на сервер...\n";
						sf::TcpSocket socket;
						if (socket.connect("localhost", 9000) != sf::Socket::Done) {
							std::cout << "Не могу подключиться к серверу :(\n";
						}
						else {
							std::cout << "Введите название симуляции (cancel для выхода): ";
							std::string filename;
							std::getline(std::cin, filename);
							if (filename == "cancel") break;

							sf::Packet packet;
							packet << "upload" << filename;
							std::stringstream buf;
							std::ifstream fin("sim.save");
							if (!fin) {
								std::cout << "Ошибка при открытии файла\n";
								break;
							}
							buf << fin.rdbuf();
							std::string file = buf.str();

							packet << file;

							socket.send(packet);
							std::cout << "Готово!\n";
						}
					}
					break;

				case sf::Keyboard::D:
					// Ctrl + D
					if (event.key.control) {
						std::cout << "Загружаю файл сохранения с сервера...\n";
						sf::TcpSocket socket;
						if (socket.connect("localhost", 9000) != sf::Socket::Done) {
							std::cout << "Не могу подключиться к серверу :(\n";
						}
						else {
							std::cout << "Введите название симуляции (cancel для выхода): ";
							std::string filename;
							std::getline(std::cin, filename);
							if (filename == "cancel") break;

							sf::Packet packet;
							packet << "download" << filename;
							socket.send(packet);
							std::cout << "Отправляю запрос...\n";
							packet.clear();
							socket.receive(packet);

							std::string resp;
							packet >> resp;
							if (resp == "notExists") {
								std::cout << "Такого файла не существует\n";
							}
							else {
								std::ofstream fout("sim.save");
								std::string file;
								packet >> file;
								fout << file;
								fout.close();
								std::cout << "Успешно! Ctrl + O, чтобы загрузить\n";
							}
						}
					}
					break;
				}


				break;

				
			case sf::Event::MouseMoved:
				mouseX = event.mouseMove.x;
				mouseY = event.mouseMove.y;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "\nMouse pressed" << '\n';
					// Получить текущую позицию мыши в окне
					sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
					//std::cout << "Window coords: x: " << pixelPos.x << " y: " << pixelPos.y << "\n";

					// Конвертировать в "мировые" координаты
					// sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
					//std::cout << "World coords: x: " << worldPos.x << " y: " << worldPos.y << "\n";

					// Понять, на какое тело мы нажали
					for (int i = 0; i < bodies.size(); i++) {
						// std::cout << "Дистанция до " << i << " " << distance(worldPos.x, worldPos.y, bodies[i].getPos().x, bodies[i].getPos().y) << '\n';
						if (distance(pixelPos.x, pixelPos.y, textPoses[i].x, textPoses[i].y) < 50) {
							// Мы нажали по телу
							std::cout << "Объект: " << bodies[i].getName() << '\n';
							std::cout << "Расстояние до Солнца: " << distance(bodies[i].getPos().x, bodies[i].getPos().y, 0, 0) << '\n';
							std::cout << "Радиус (м): " << bodies[i].getRadius() << '\n';
							auto vel = bodies[i].getVel();
							std::cout << "Скорость по иксу: " << vel.x << ";\nСкорость по игреку: " << vel.y << '\n';
						}
					}
				}
				break;

			}
		}

		window.setView(view);
		window.clear(sf::Color::Black);

		for (int i = 0; i < bodies.size(); i++)  {
			// std::cout << "x: " << bodies[i].getPos().x << " y: " << bodies[i].getPos().y << '\n';
			// Нарисовать на экране
			window.setView(view);
			bodies[i].applyShape(circleBody);
			window.draw(circleBody);

			window.setView(window.getDefaultView());
			text.setString(bodies[i].getName());

			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

			textPoses[i] = sf::Vector2f(window.mapCoordsToPixel(bodies[i].getPosPixelsF(), view));
			text.setPosition(textPoses[i]);
			window.draw(text);
		}

		window.display();
	}

	isProgramStopped = true;
	playSimulation();
	simulationThread.join();
	return 0;
}