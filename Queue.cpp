#include <SFML/Graphics.hpp>
#include <iostream>

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
   sf::RenderWindow& window;
   sf::Font font;
   sf::Text text;

public:
   LinkedList(sf::RenderWindow& win) : head(nullptr), window(win) {
       if (!font.loadFromFile("Fonts/Agdasima.ttf")) {
           std::cerr << "Failed to load font." << std::endl;
       }

       text.setFont(font);
       text.setCharacterSize(24);
       text.setFillColor(sf::Color::White);
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

       sf::RectangleShape nodeRect5(sf::Vector2f(650, 75));
       nodeRect5.setFillColor(sf::Color::Transparent);
       nodeRect5.setPosition(167, 50);
       sf::Text text1("Queue Implemntation w/ Linklist Visualization", font, 30);

       text1.setPosition(nodeRect5.getPosition().x + 650 / 2 - text1.getLocalBounds().width / 2, nodeRect5.getPosition().y + 75 / 2 - text1.getLocalBounds().height / 2);
       text1.setFillColor(sf::Color::Yellow);

       window.draw(nodeRect5);
       window.draw(text1);

       sf::RectangleShape nodeRect(sf::Vector2f(nodeSize, nodeSize));
       nodeRect.setFillColor(sf::Color::Magenta);
       nodeRect.setPosition(index * (nodeSize + nodeSpacing) + nodeSpacing, startY);

       text.setString("Head");
       text.setPosition(nodeRect.getPosition().x + nodeSize / 2 - text.getLocalBounds().width / 2, nodeRect.getPosition().y + nodeSize / 2 - text.getLocalBounds().height / 2);

       sf::Text text5;
       text5.setFont(font);
       text5.setString("Value:");
       text5.setPosition(36, 371);
       text5.setFillColor(sf::Color::Cyan);
       text5.setCharacterSize(22);
       window.draw(text5);

       window.draw(nodeRect);
       window.draw(text);

       index = 1;

       while (current != nullptr) {
           sf::RectangleShape nodeRect3(sf::Vector2f(nodeSize, nodeSize));
           nodeRect3.setFillColor(sf::Color::Blue);
           nodeRect3.setPosition(index * (nodeSize + nodeSpacing) + nodeSpacing, startY);

           text.setString(std::to_string(current->key));
           text.setPosition(nodeRect3.getPosition().x + nodeSize / 2 - text.getLocalBounds().width / 2,
               nodeRect3.getPosition().y + nodeSize / 2 - text.getLocalBounds().height / 2);

           sf::Text text7, text8;
           text7.setString(std::to_string(current->key));
           text7.setFillColor(sf::Color::White);
           text7.setFont(font);
           text7.setPosition(nodeRect3.getPosition().x + nodeSize / 2 - text7.getLocalBounds().width / 2, nodeRect3.getPosition().y + nodeSize / 2 - text7.getLocalBounds().height / 2);

           window.draw(nodeRect3);
           window.draw(text7);

           sf::RectangleShape nodeRect4(sf::Vector2f(nodeSize, nodeSize));
           nodeRect4.setFillColor(sf::Color::White);
           nodeRect4.setPosition(index * (nodeSize + nodeSpacing) + nodeSpacing, startY + 130);

           text8.setString(std::to_string(current->value));
           text8.setFillColor(sf::Color::Black);
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

  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Queue Implemntation w / Linklist Visualization");
  window.setFramerateLimit(60);

  LinkedList linkedList(window);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      int key, value;
      std::cout << "Enter a choice ('q' to quit): 1. Put 2. get" << std::endl;
      int ch;
      std::cin >> ch;

      switch (ch)
      {
      case 1:
          std::cout << "Enter key:" << std::endl;
          std::cin >> key;
          std::cout << "Enter its value:" << std::endl;
          std::cin >> value;
          linkedList.addNode(key, value);
          break;
      case 2:
          std::cout << "Enter key:" << std::endl;
          std::cin >> key;
          value = linkedList.findKey(key);
          if (value != -1)
              std::cout << "Value: " << value << std::endl;
          else
              std::cout << "Key not found!" << std::endl;
          break;
      default:
          std::cout << "INVALID INPUT!" << std::endl;
      }

      window.clear();
      linkedList.drawLinkedList();
      window.display();
  }

  return 0;
}
