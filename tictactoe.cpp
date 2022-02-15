#include<iostream>
#include<windows.h>
#include<conio.h>
#define MAX 100

using namespace std;

struct Player
{
    char Login[MAX], Pass[MAX];
    char Icon[MAX][MAX];
};

struct Board
{
    int Row = 0, Col = 0;
    void initialize(int row, int col)
    {
        Row = row;
        Col = col;
    }
};

void GoTo(int posX, int posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void PrintHorizonLine(int size)
{

    cout << " ";
    for (int i = 0; i < (11 * size - 1); i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void PrintVerticalLine(int size)
{
    for (int i = 0; i <= size ; i++)
    {
        std::cout << "|";
        std::cout << "          ";
    }
    std::cout << std::endl;
}

void print_Board(Board b, Player p, int row, int col)
{
    b.initialize(row, col);
    PrintHorizonLine(b.Col);
    for(int i = 0; i < b.Row; i++)
    {
        PrintVerticalLine(b.Col);
        cout << "|";
        for(int j = 0; j < b.Col; j ++)
        {
            cout << "    ";
            cout << " "; // tọa độ (5,4) với ô đầu tiên, ô kế đó có tọa độ (16,4)
            std::cout << "     |";
        }
        cout << endl;
        PrintVerticalLine(b.Col);
        PrintHorizonLine(b.Col);
    }
}

void play(Player p, Board b, int row, int col)
{
        char c;
        int p_x = 5, p_y = 2;
        while (c != 13)
        {
            c = _getch();
            switch (c)
            {
                case 'd':p_x += 11; break;
                default: break;
            }
        }
        system("cls");
         print_Board(b, p, 3, 3);
         GoTo(p_x, p_y);
         cout << "x";
}

int main()
{
    Player p;
    Board b;
    print_Board(b, p, 3, 3);
    play(p, b, 3, 3);
    GoTo(15, 15);
    return 0;
}
