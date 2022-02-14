#include<iostream>
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
            cout << p.Icon[i][j];
            std::cout << "     |";
        }
        cout << endl;
        PrintVerticalLine(b.Col);
        PrintHorizonLine(b.Col);
    }
}

int main()
{
    Player p;
    Board b;
    print_Board(b, p, 6, 4);
    return 0;
}
