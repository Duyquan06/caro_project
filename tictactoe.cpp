#include<iostream>
#include<windows.h>
#include<cstring>
#include<fstream>
#include<conio.h>
#define MAX 100

using namespace std;


struct Board
{
    int Row = 0, Col = 0;
    void initialize(int row, int col)
    {
        Row = row;
        Col = col;
    }
    void PrintHorizonLine()
        {

            cout << " ";
            for (int i = 0; i < (11 * Col - 1); i++)
            {
                std::cout << "-";
            }
            std::cout << std::endl;
        }

    void PrintVerticalLine()
        {
            for (int i = 0; i <= Col ; i++)
            {
                std::cout << "|";
                std::cout << "          ";
            }
            std::cout << std::endl;
        }

};

struct Player
{
    char Login[MAX], Pass[MAX];
    char Icon[MAX][MAX];
    void init(Board b)
    {
        for(int i = 0; i < b.Row; i++)
        {
            for(int j = 0; j < b.Col; j++)
                Icon[i][j] = ' ';
        }
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

struct menu
{
    void sign_in(Player p[], int &qty)
    {
        cin.getline(p[qty].Login, MAX);
        cin.getline(p[qty++].Pass, MAX);
    }

    bool sign_up(Player p[], Board b[], int &qty, int &index, ifstream &dtb)
    {   
        char temp_login[MAX], temp_pass[MAX], check_login[MAX], check_pass[MAX];
        cin.getline(temp_login, MAX);
        cin.getline(temp_pass, MAX);
        dtb.open("database.txt");
        dtb >> qty;
        for(int i = 0; i < qty; i++)
        {
            dtb >> index;
            dtb.ignore();
            dtb.getline(check_login, MAX, ';');
            dtb.getline(check_pass, MAX);
            if(!(strcmp(temp_login, check_login)) && !(strcmp(temp_pass, check_pass)))
            {
                int row, col;
                dtb >> row >> col;
                b[index].initialize(row, col);
                for(int j = 0; j < b[index].Row; j++)
                {
                    for(int q = 0; q < b[index].Col; q++)
                    {
                        char temp_Icon;
                        dtb >> temp_Icon;
                        if(temp_Icon == '0')
                            temp_Icon = ' ';
                        p[index].Icon[i][j] = temp_Icon;
                    }
                }
                dtb.close();
                return true;
            } else {
                dtb.close();
                return false;
            }
        }

    }
    void Back_up(Player p[], Board b[], int &qty, ofstream &dtb)
    {
        dtb.open("database.txt");
        dtb << qty << endl;
        for(int i = 0; i < qty; i++)
        {
            dtb << i << endl;
            dtb << p[i].Login << ";" << p[i].Pass << endl;
            dtb << b[i].Row << " " << b[i].Col << endl;
            for(int j = 0; j < b[i].Row; j++)
            {
                for(int q = 0; q < b[i].Col; q++)
                {
                    if(p[i].Icon[j][q] == ' ')
                        p[i].Icon[j][q] = '0';
                    dtb << p[i].Icon[j][q] << " ";
                }
                dtb << endl;
            }
        }
        dtb << endl;
        dtb.close();
    }
};

void print_Board(Board b, Player p, int row, int col)
{
    b.initialize(row, col);
    p.init(b);
    b.PrintHorizonLine();
    for(int i = 0; i < b.Row; i++)
    {
       b.PrintVerticalLine();
        cout << "|";
        for(int j = 0; j < b.Col; j ++)
        {
            cout << "    ";
            cout << p.Icon[i][j]; // tọa độ (5,4) với ô đầu tiên, ô kế đó có tọa độ (16,4)
            std::cout << "     |";
        }
        cout << endl;
        b.PrintVerticalLine();
        b.PrintHorizonLine();
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
                case 'w':p_y -= 4;  break;
                case 'a':p_x -= 11; break;
                case 'd':p_x += 11; break;
                case 's':p_y += 4;break;
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
    Player p[MAX];
    Board b[MAX];
    int qty = 0, index;
    //print_Board(b, p, 3, 3);
    //play(p, b, 3, 3);
    ofstream dtb;
    ifstream d;
    menu m;
    //m.sign_in(p, qty);
   // b[0].initialize(3,3);
   // for(int i = 0; i < 3; i++)
    //{
        //for(int j = 0; j < 3; j++)
            //cin >> p[0].Icon[i][j];
    //}
    //m.Back_up(p,b, qty, dtb);
    //cout << m.sign_up(p,b,qty,index, d);
    GoTo(15, 15);
    return 0;
}
