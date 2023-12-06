#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
using namespace sf;

class Box {
public:
	RectangleShape body;
	int value;
	int type;
	int xLocation;
	int yLocation;
	bool visited;
	Box* prev;

	Box(int x, int y) {
		this->body.setSize(Vector2f(10.f, 10.f));
		this->body.setPosition(Vector2f(x, y));
		this->body.setOutlineColor(Color::Black);
		this->body.setOutlineThickness(1.f);

		this->value = NULL;
		this->type = 0;
		this->xLocation = NULL;
		this->yLocation = NULL;
		this->visited = false;
		this->prev = NULL;

	}
};

void BFS(vector<vector<Box*> > b, RenderWindow& window, int startX, int startY) {

	vector<Box*> visited;
	vector<Box*> queue;

	int yPos = startY;
	int xPos = startX;
	visited.push_back(b.at(yPos).at(xPos));
	visited.at(0)->xLocation = xPos;
	visited.at(0)->yLocation = yPos;
	visited.at(0)->visited = true;

	while (visited.at(visited.size() - 1)->type != 3) {

		xPos = visited.at(visited.size() - 1)->xLocation;
		yPos = visited.at(visited.size() - 1)->yLocation;

		if (yPos - 1 >= 0 && b.at(yPos - 1).at(xPos)->visited == false && (b.at(yPos - 1).at(xPos)->type == 0 || b.at(yPos - 1).at(xPos)->type == 3)) {
			queue.push_back(b.at(yPos - 1).at(xPos));
			b.at(yPos - 1).at(xPos)->xLocation = xPos;
			b.at(yPos - 1).at(xPos)->yLocation = yPos - 1;
			b.at(yPos - 1).at(xPos)->prev = b.at(yPos).at(xPos);
			queue.at(queue.size() - 1)->body.setFillColor(Color::Magenta);
			queue.at(queue.size() - 1)->visited = true;
		}

		if (yPos + 1 <= 71 && b.at(yPos + 1).at(xPos)->visited == false && (b.at(yPos + 1).at(xPos)->type == 0 || b.at(yPos + 1).at(xPos)->type == 3)) {
			queue.push_back(b.at(yPos + 1).at(xPos));
			b.at(yPos + 1).at(xPos)->xLocation = xPos;
			b.at(yPos + 1).at(xPos)->yLocation = yPos + 1;
			b.at(yPos + 1).at(xPos)->prev = b.at(yPos).at(xPos);
			queue.at(queue.size() - 1)->body.setFillColor(Color::Magenta);
			queue.at(queue.size() - 1)->visited = true;
		}

		if (xPos - 1 >= 0 && b.at(yPos).at(xPos - 1)->visited == false && (b.at(yPos).at(xPos - 1)->type == 0 || b.at(yPos).at(xPos - 1)->type == 3)) {
			queue.push_back(b.at(yPos).at(xPos - 1));
			b.at(yPos).at(xPos - 1)->xLocation = xPos - 1;
			b.at(yPos).at(xPos - 1)->yLocation = yPos;
			b.at(yPos).at(xPos - 1)->prev = b.at(yPos).at(xPos);
			queue.at(queue.size() - 1)->body.setFillColor(Color::Magenta);
			queue.at(queue.size() - 1)->visited = true;
		}

		if (xPos + 1 <= 127 && b.at(yPos).at(xPos + 1)->visited == false && (b.at(yPos).at(xPos + 1)->type == 0 || b.at(yPos).at(xPos + 1)->type == 3)) {
			queue.push_back(b.at(yPos).at(xPos + 1));
			b.at(yPos).at(xPos + 1)->xLocation = xPos + 1;
			b.at(yPos).at(xPos + 1)->yLocation = yPos;
			b.at(yPos).at(xPos + 1)->prev = b.at(yPos).at(xPos);
			queue.at(queue.size() - 1)->body.setFillColor(Color::Magenta);
			queue.at(queue.size() - 1)->visited = true;
		}

		if (queue.size() >= 0) {
			visited.push_back(queue.at(0));

			queue.erase(queue.begin());
		}

		visited.at(visited.size() - 1)->body.setFillColor(Color::Blue);

		window.clear(Color::White);
		for (int i = 0; i < 72; i++) {
			for (int j = 0; j < 128; j++) {
				window.draw(b.at(i).at(j)->body);
			}
		}
		window.display();

	}

	Box* temp = visited.at(visited.size() - 1);
	while (temp->prev != NULL) {
		temp->body.setFillColor(Color::Yellow);
		temp = temp->prev;
	}

}

int main(int argc, char* argv[]) {

	RenderWindow window(VideoMode(1280, 720), "Path Finding");

	int count = 0;
	int startX;
	int startY;

	int endX;
	int endY;

	vector<vector<Box*> > boxes;
	for (int i = 0; i < 72; i++) {
		vector<Box*> temp;
		boxes.push_back(temp);
	}

	for (int i = 0; i < 72; i++) {
		for (int j = 0; j < 128; j++) {
			Box* b = new Box(j * 10, i * 10);
			boxes.at(i).push_back(b);
		}
	}

	while (window.isOpen()) {
		Event event;
		Vector2i mousePosition;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				mousePosition = Mouse::getPosition(window);

				int x = NULL, y = NULL;
				x = mousePosition.x / 10;
				y = mousePosition.y / 10;
				boxes[y][x]->body.setFillColor(Color::Black);
				boxes[y][x]->type = 1;

			}

			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (count == 0) {
					cout << "pathfind" << endl;

					BFS(boxes, window, startX, startY);
					count++;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				mousePosition = Mouse::getPosition(window);
				int x = NULL, y = NULL;
				startX = mousePosition.x / 10;
				startY = mousePosition.y / 10;
				boxes[startY][startX]->body.setFillColor(Color::Green);
				boxes[startY][startX]->type = 2;
			}

			if (Keyboard::isKeyPressed(Keyboard::E)) {
				mousePosition = Mouse::getPosition(window);
				int x = NULL, y = NULL;
				endX = mousePosition.x / 10;
				endY = mousePosition.y / 10;
				boxes[endY][endX]->body.setFillColor(Color::Red);
				boxes[endY][endX]->type = 3;
			}

		}

		window.clear(Color::White);
		for (int i = 0; i < 72; i++) {
			for (int j = 0; j < 128; j++) {
				window.draw(boxes.at(i).at(j)->body);
			}
		}
		window.display();

	}
}