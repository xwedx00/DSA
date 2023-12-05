#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Node {
public:
   int key;
   int value;
   Node* next;

   Node(int tempkey, int tempvalue) : key(tempkey), value(tempvalue), next(nullptr) {}
};

class LinkedList {
private:
   Node* head;
   RenderWindow& window;
   Font font;
   Text text;

public:
   LinkedList(RenderWindow& win) : head(nullptr), window(win) {
       if (!font.loadFromFile("Fonts/Agdasima.ttf")) {
           cerr << "Failed to load font." << endl;
       }

       text.setFont(font);
       text.setCharacterSize(24);
       text.setFillColor(Color::White);
   }

   void addNode(int tempkey, int tempvalue) {
       Node* newNode = new Node(tempkey, tempvalue);

       newNode->next = head;
       head = newNode;
   }

   int traverseLastNode() {
       Node* current = head;

       while (current->next != nullptr) {
           current = current->next;
       }
       return (current->value);
   }

   void removeNode(int tempkey) {
       if (head == nullptr) {
           return;
       }

       if (head->key == tempkey) {
           Node* temp = head;
           head = head->next;
           delete temp;
           return;
       }

       Node* current = head;
       Node* previous = nullptr;

       while (current != nullptr && current->key != tempkey) {
           previous = current;
           current = current->next;
       }

       if (current != nullptr) {
           previous->next = current->next;
           delete current;
       }
   }

   int findKey(int tempkey)
   {
       Node* current = head;
       while (current != nullptr)
       {
           if (current->key == tempkey)
               return current->value;
           current = current->next;
       }
       return -1;
   }

   void drawLinkedList() {
       Node* current = head;
       int index = 0;
       const int nodeSize = 100;
       const int nodeSpacing = 20;
       const int startY = 200;

       RectangleShape nodeRect5(Vector2f(650, 75));
       nodeRect5.setFillColor(Color::Transparent);
       nodeRect5.setPosition(167, 50);
       Text text1("Queue Implemntation w/ Linklist Visualization", font, 30);

       text1.setPosition(nodeRect5.getPosition().x + 650 / 2 - text1.getLocalBounds().width / 2, nodeRect5.getPosition().y + 75 / 2 - text1.getLocalBounds().height / 2);
       text1.setFillColor(Color::Yellow);

       window.draw(nodeRect5);
       window.draw(text1);

       RectangleShape nodeRect(Vector2f(nodeSize, nodeSize));
       nodeRect.setFillColor(Color::Magenta);
       nodeRect.setPosition(index * (nodeSize + nodeSpacing) + nodeSpacing, startY);

       text.setString("Head");
       text.setPosition(nodeRect.getPosition().x + nodeSize / 2 - text.getLocalBounds().width / 2, nodeRect.getPosition().y + nodeSize / 2 - text.getLocalBounds().height / 2);

       Text text5;
       text5.setFont(font);
       text5.setString("Value:");
       text5.setPosition(36, 371);
       text5.setFillColor(Color::Cyan);
       text5.setCharacterSize(22);
       window.draw(text5);

       window.draw(nodeRect);
       window.draw(text);

       index = 1;

       while (current != nullptr) {
           RectangleShape nodeRect3(Vector2f(nodeSize, nodeSize));
           nodeRect3.setFillColor(Color::Blue);
           nodeRect3.setPosition(index * (nodeSize + nodeSpacing) + nodeSpacing, startY);

           text.setString(to_string(current->key));
           text.setPosition(nodeRect3.getPosition().x + nodeSize / 2 - text.getLocalBounds().width / 2,
               nodeRect3.getPosition().y + nodeSize / 2 - text.getLocalBounds().height / 2);

           Text text7, text8;
           text7.setString(to_string(current->key));
           text7.setFillColor(Color::White);
           text7.setFont(font);
           text7.setPosition(nodeRect3.getPosition().x + nodeSize / 2 - text7.getLocalBounds().width / 2, nodeRect3.getPosition().y + nodeSize / 2 - text7.getLocalBounds().height / 2);

           window.draw(nodeRect3);
           window.draw(text7);

           RectangleShape nodeRect4(Vector2f(nodeSize, nodeSize));
           nodeRect4.setFillColor(Color::White);
           nodeRect4.setPosition(index * (nodeSize + nodeSpacing) + nodeSpacing, startY + 130);

           text8.setString(to_string(current->value));
           text8.setFillColor(Color::Black);
           text8.setFont(font);
           text8.setPosition(nodeRect4.getPosition().x + nodeSize / 2 - text8.getLocalBounds().width / 2, nodeRect4.getPosition().y + nodeSize / 2 - text8.getLocalBounds().height / 2);

           window.draw(nodeRect4);
           window.draw(text8);

                    current = current->next;
          index++;
      }
  }
};

int main()
{
  const int windowWidth = 1000;
  const int windowHeight = 700;

  int curr_size = 0;

  RenderWindow window(VideoMode(windowWidth, windowHeight), "Queue Implemntation w / Linklist Visualization");
  window.setFramerateLimit(60);

  LinkedList linkedList(window);

  while (window.isOpen())
  {
      Event event;
      while (window.pollEvent(event))
      {
          if (event.type == Event::Closed)
              window.close();
      }

      int key, value;
      cout << "Enter a choice ('q' to quit): 1. Put 2. get" << endl;
      int ch;
      cin >> ch;

      switch (ch)
      {
      case 1:
          cout << "Enter key:" << endl;
          cin >> key;
          cout << "Enter its value:" << endl;
          cin >> value;
          linkedList.addNode(key, value);
          break;
      case 2:
          cout << "Enter key:" << endl;
          cin >> key;
          value = linkedList.findKey(key);
          if (value != -1)
              cout << "Value: " << value << endl;
          else
              cout << "Key not found!" << endl;
          break;
      default:
          cout << "INVALID INPUT!" << endl;
      }

      window.clear();
      linkedList.drawLinkedList();
      window.display();
  }

  return 0;
}
