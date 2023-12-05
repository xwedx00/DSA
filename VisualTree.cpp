#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

float window_x = 1000, window_y = 650;

RenderWindow window(VideoMode(window_x, window_y), "AVL Representer");

Font TimesNewRoman;

Vertex Vertex1;
Vertex Vertex2;
VertexArray LinesBetween(Lines, 2);

CircleShape CircleAroundData;
Text ValueInserted;

Text Tree_Name;
const float Tree_Namex = window_x / 2 - 160;
const float Tree_Namey = 50;

const float Root_x = window_x / 2;
const float Root_y = Tree_Namey + 150;

class AVLNode
{
public:
	int Key;

	AVLNode *Left;

	AVLNode *Right;

	AVLNode *Parent;

	float NodeXPosition;
	float NodeYPosition;
	float RadiusofCircle;
	Color Node_Color;
	float OutlineThickness;
	Color OutlineThicknessColor;
	Color Text_Color;

	AVLNode()
	{
		Key = 0;
		Left = Right = Parent = NULL;
		RadiusofCircle = 20;
		Node_Color = Color::Color(179, 240, 197);
		OutlineThickness = 5;
		OutlineThicknessColor = Color::Color(32, 98, 52);
		Text_Color = OutlineThicknessColor;
	}
};

class AVL
{
private:
	AVLNode *AVLRoot;

public:
	bool Insert(int Info)
	{
		AVLNode *NewNode = new AVLNode();
		NewNode->Key = Info;
		bool AlreadyExist = false;
		if (!AVLRoot)
		{
			AVLRoot = NewNode;
			DisplayTree();
			sleep(seconds(3));
			return true;
		}

		else
		{
			AVLNode *CurrentNode = AVLRoot;

			while (true)
			{
				if (NewNode->Key < CurrentNode->Key)
				{
					if (CurrentNode->Left)
					{
						CurrentNode = CurrentNode->Left;
					}
					else
					{
						CurrentNode->Left = NewNode;
						CurrentNode->Left->Parent = CurrentNode;
						DisplayTree();
						sleep(seconds(3));
						AlreadyExist = false;
						break;
					}
				}
				else if (NewNode->Key > CurrentNode->Key)
				{
					if (CurrentNode->Right)
					{
						CurrentNode = CurrentNode->Right;
					}
					else
					{
						CurrentNode->Right = NewNode;
						CurrentNode->Right->Parent = CurrentNode;
						DisplayTree();
						sleep(seconds(3));
						AlreadyExist = false;
						break;
					}
				}

				else
				{
					DisplayTree();
					sleep(seconds(3));
					break;
				}
			}
		}
		DisplayTree();
		sleep(seconds(3));
		if (AlreadyExist)

		{
			return false;
		}
		else

		{
			BalanceIt(AVLRoot);
			return true;
		}
	}

	AVLNode *Search_Node(int InfoProvided)
	{
		AVLNode *CurrentNode = AVLRoot;
		int CurrentKey = InfoProvided % 10;
		while (CurrentNode)
		{
			if (CurrentNode->Key == CurrentKey)
			{
				CurrentNode->OutlineThicknessColor = Color::Red;
				DisplayTree();
				sleep(seconds(3));
				sleep(seconds(3));
				CurrentNode->OutlineThicknessColor = CurrentNode->Text_Color;
				return CurrentNode;
			}
			else if (CurrentNode->Key < CurrentKey)
			{
				CurrentNode->OutlineThicknessColor = Color::Red;
				CurrentNode = CurrentNode->Right;
				CurrentNode->Parent->OutlineThicknessColor = CurrentNode->Text_Color;
			}
			else
			{
				CurrentNode = CurrentNode->Left;
			}
		}
		return NULL;
	}

	int TreeNodes(AVLNode *ProvidedNode)
	{
		int NumberofNodes = 0;
		NodeCounter(ProvidedNode, NumberofNodes);
		return NumberofNodes;
	}

	void NodeCounter(AVLNode *ProvidedNode, int &Count)
	{
		if (ProvidedNode)
		{
			Count++;

			NodeCounter(ProvidedNode->Left, Count);
			NodeCounter(ProvidedNode->Right, Count);
		}
	}
	int TreeHeight(AVLNode *ProvideNode)
	{
		int LeftHeight, RightHeight;
		if (!ProvideNode)
		{

			return -1;
		}
		else
		{
			LeftHeight = TreeHeight(ProvideNode->Left);
			RightHeight = TreeHeight(ProvideNode->Right);
			if (LeftHeight > RightHeight)

			{
				return LeftHeight + 1;
			}
			else
			{
				return RightHeight + 1;
			}
		}
	}

	int BalanceFactor(AVLNode *ProvidedNode)
	{
		if (ProvidedNode == NULL)
		{
			return 0;
		}

		return TreeHeight(ProvidedNode->Left) - TreeHeight(ProvidedNode->Right);
	}

	void RightRotate(AVLNode *&ProvidedNode)
	{
		AVLNode *AuxiliaryNode = ProvidedNode->Left;
		ProvidedNode->Left = AuxiliaryNode->Right;
		AuxiliaryNode->Right = ProvidedNode;
		AuxiliaryNode->Parent = ProvidedNode->Parent;
		ProvidedNode->Parent = AuxiliaryNode;
		if (ProvidedNode->Left != NULL)
			ProvidedNode->Left->Parent = ProvidedNode;
		ProvidedNode = AuxiliaryNode;
	}

	void LeftRotate(AVLNode *&ProvidedNode)
	{
		AVLNode *AuxiliaryNode = ProvidedNode->Right;
		ProvidedNode->Right = AuxiliaryNode->Left;
		AuxiliaryNode->Left = ProvidedNode;
		AuxiliaryNode->Parent = ProvidedNode->Parent;
		ProvidedNode->Parent = AuxiliaryNode;
		if (ProvidedNode->Right != NULL)
			ProvidedNode->Right->Parent = ProvidedNode;
		ProvidedNode = AuxiliaryNode;
	}

	void BalanceIt(AVLNode *&ProvidedNode)
	{
		if (ProvidedNode)
		{
			int B_Factor;
			BalanceIt(ProvidedNode->Left);
			BalanceIt(ProvidedNode->Right);
			B_Factor = BalanceFactor(ProvidedNode);

			if (B_Factor > 1)
			{
				if (BalanceFactor(ProvidedNode->Left) >= 0)
				{
					RightRotate(ProvidedNode);
				}
				else
				{
					sleep(seconds(3));
					LeftRotate(ProvidedNode->Left);
					DisplayTree();
					sleep(seconds(4));
					RightRotate(ProvidedNode);
					DisplayTree();
				}
			}

			if (B_Factor < -1)
			{
				if (BalanceFactor(ProvidedNode->Right) > 0)
				{
					sleep(seconds(3));
					RightRotate(ProvidedNode->Right);
					DisplayTree();
					sleep(seconds(4));
					LeftRotate(ProvidedNode);
					DisplayTree();
				}
				else
				{
					LeftRotate(ProvidedNode);
				}
			}
		}
	}

	AVLNode *GetRoot()
	{
		return AVLRoot;
	}

	void SetRoot(AVLNode *Passed)
	{
		this->AVLRoot = Passed;
	}

	~AVL()
	{
		FreeNodes(AVLRoot);
		AVLRoot = nullptr;
	}

	void FreeNodes(AVLNode *ProvidedNode)
	{
		if (ProvidedNode)
		{

			FreeNodes(ProvidedNode->Left);
			FreeNodes(ProvidedNode->Right);
			delete ProvidedNode;
		}
	}

	void ClassName()
	{
		Tree_Name.setString(" \" AVL \" ");
		Tree_Name.setOutlineThickness(5);
		Tree_Name.setOutlineColor(AVLRoot->OutlineThicknessColor);
		Tree_Name.setFillColor(AVLRoot->Node_Color);
		Tree_Name.setCharacterSize(80);
		Tree_Name.setFont(TimesNewRoman);
		Tree_Name.setLetterSpacing(1.5);
		Tree_Name.setPosition(Tree_Namex, Tree_Namey);
		window.draw(Tree_Name);
	}
	void Set_Root_Position()
	{
		if (AVLRoot != NULL)
		{
			AVLRoot->NodeXPosition = Root_x;
			AVLRoot->NodeYPosition = Root_y;
		}
	}
	void Set_SubTree_X_Axis(AVLNode *ProvidedNode, bool check)
	{
		if (ProvidedNode != NULL)
		{
			Set_SubTree_X_Axis(ProvidedNode->Left, 0);
			if (ProvidedNode != AVLRoot)
			{
				if (check == 0)
				{
					ProvidedNode->NodeXPosition =
						ProvidedNode->Parent->NodeXPosition -
						(TreeNodes(ProvidedNode)) * 30;
				}
				else
				{
					ProvidedNode->NodeXPosition =
						ProvidedNode->Parent->NodeXPosition +
						(TreeNodes(ProvidedNode)) * 30;
				}
			}
			Set_SubTree_X_Axis(ProvidedNode->Right, 1);
		}
	}
	void Set_SubTree_Y_Axis(AVLNode *ProvidedNode, int increment)
	{
		if (ProvidedNode != NULL)
		{
			Set_SubTree_Y_Axis(ProvidedNode->Left, increment + 75);
			if (ProvidedNode != AVLRoot)
			{
				ProvidedNode->NodeYPosition = increment;
			}
			Set_SubTree_Y_Axis(ProvidedNode->Right, increment + 75);
		}
	}
	void Draw_line(AVLNode *Root)
	{
		if (Root != NULL)
		{
			Draw_line(Root->Left);
			if (Root->Left != NULL)
			{
				Vertex1.position = Vector2f(Root->NodeXPosition, Root->NodeYPosition);
				Vertex1.color = Color::Color::Red;
				Vertex2.position = Vector2f(Root->Left->NodeXPosition, Root->Left->NodeYPosition);
				Vertex2.color = Color::Color::Green;
				LinesBetween[0] = Vertex1;
				LinesBetween[1] = Vertex2;
				window.draw(LinesBetween);
			}
			if (Root->Right != NULL)
			{
				Vertex1.position = Vector2f(Root->NodeXPosition, Root->NodeYPosition);
				Vertex1.color = Color::Color::Red;
				Vertex2.position = Vector2f(Root->Right->NodeXPosition, Root->Right->NodeYPosition);
				Vertex2.color = Color::Color::Green;
				LinesBetween[0] = Vertex1;
				LinesBetween[1] = Vertex2;
				window.draw(LinesBetween);
			}
			Draw_line(Root->Right);
		}
	}
	void Draw_CircleANDText(AVLNode *ProvidedNode)
	{
		if (ProvidedNode != NULL)
		{
			Draw_CircleANDText(ProvidedNode->Left);
			CircleAroundData.setRadius(AVLRoot->RadiusofCircle);
			CircleAroundData.setPosition(ProvidedNode->NodeXPosition - 20, ProvidedNode->NodeYPosition - 20);
			CircleAroundData.setFillColor(ProvidedNode->Node_Color);
			CircleAroundData.setOutlineThickness(ProvidedNode->OutlineThickness);
			CircleAroundData.setOutlineColor(ProvidedNode->OutlineThicknessColor);
			window.draw(CircleAroundData);
			ValueInserted.setString(to_string(ProvidedNode->Key));
			ValueInserted.setCharacterSize(20);
			ValueInserted.setPosition(CircleAroundData.getPosition().x + AVLRoot->RadiusofCircle / 2 + 5,
									  CircleAroundData.getPosition().y + AVLRoot->RadiusofCircle / 2 - 3);
			ValueInserted.setFillColor(ProvidedNode->OutlineThicknessColor);
			ValueInserted.setFont(TimesNewRoman);
			window.draw(ValueInserted);
			Draw_CircleANDText(ProvidedNode->Right);
		}
	}
	void Display()
	{
		if (AVLRoot != NULL)
		{
			Set_Root_Position();
			Set_SubTree_X_Axis(AVLRoot, 0);
			Set_SubTree_Y_Axis(AVLRoot, Root_y);
			for (int loop = 0; loop < TreeHeight(AVLRoot) + 2; loop++)
			{
				Draw_line(AVLRoot);
				Draw_CircleANDText(AVLRoot);
			}
		}
	}
	void DisplayTree()
	{
		for (int loop = 0; loop < TreeHeight(AVLRoot) + 1; loop++)
		{
			window.clear(AVLRoot->Node_Color);
			ClassName();
			Display();
			window.display();
		}
	}
};

void MainMenu()
{
	system("color 3f");
	AVL Hashing;
	bool MenuBreak = false;
	int Input;
	int Option;
	do
	{
		cout << "\n\tPlease Select an Option from Following!"
			 << "\n\tPress 1 ===>> Insert"
			 << "\n\tPress 2 ===>> Search"
			 << "\n\tPress 3 ===>> Exit"
			 << "\n\n\tSelect Option = ";
		cin >> Option;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n\n\tSelect Option = ";
			cin >> Option;
		}
		system("cls");
		switch (Option)
		{
		case 1:
			system("color 2f");
			cout << "\n\tPlease Enter the Number to Insert = ";
			cin >> Input;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n\tPlease Enter the Number to Insert = ";
				cin >> Input;
			}
			if (Input != -1)
			{
				if (!Hashing.Insert(Input))
				{
					cout << "\n\tInsertion is not Possible!\n";
				}
			}
			Hashing.DisplayTree();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 2:
			system("color 4f");
			cout << "\n\tPlease Enter the Number to Search = ";
			cin >> Input;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n\tPlease Enter the Number to Search = ";
				cin >> Input;
			}
			if (!Hashing.Search_Node(Input))
			{
				cout << "\n\tData Does not Exist in the Tree\n";
			}
			else
			{
				cout << "\n\tData Exists in the Tree\n";
			}
			Hashing.DisplayTree();
			cout << "\n\n\t";
			system("pause");
			system("cls");
			break;
		case 3:
			MenuBreak = true;
			window.close();
			break;
		default:
			cout << "\n\tPlease Select a Valid Option!\n\tTry Again!\n";
			break;
		}
	} while (!MenuBreak);
}
int main()
{
	TimesNewRoman.loadFromFile("Fonts/Agdasima.ttf");
	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed || evnt.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}
		MainMenu();
	}
	system("pause>0");
	return 0;
}