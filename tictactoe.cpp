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

struct Menu
{
    void sign_up(Player p[], int &qty)
    {
        qty++;
        cin.ignore();
        cin.getline(p[qty-1].Login, MAX);
        //cin.getline(p[qty++].Pass, MAX);
        char c; int i =0;
        while (c != 13)
    {
        c = _getch();
        if(c != 13)
        {
              cout << "*";
              p[qty-1].Pass[i] = c;
        }
        i++;
    }
        p[qty-1].Pass[i] = '\0';
        cout << endl;

    }

    void Read_database(ifstream &dtb, Player p[], Board b[], int &qty, int &index)
    {
        int temp_check;
        dtb.open("database.txt");
        dtb >> qty;
        for(int i = 0; i < qty;i++)
        {
            dtb >> temp_check;
              dtb.getline(p[i].Login, MAX, ';');
              dtb.getline(p[i].Pass, MAX);
              int row, col;
              dtb >> row >> col >> index;
              b[i].initialize(row, col);
              for(int j = 0; j < b[i].Row; j++)
              {
                  for(int q = 0; q <  b[i].Col; q++)
                  {
                       char temp_Icon;
                        dtb >> temp_Icon;
                        if(temp_Icon == '0')
                            temp_Icon = ' ';
                        p[i].Icon[j][q] = temp_Icon;
                  }

              }

        }
        dtb.close();
    }
    bool sign_in(Player p[], Board b[], int &qty, int &index, ifstream &dtb, int &turn)
    {   
        char temp_login[MAX], temp_pass[MAX];
        cin.ignore();
        cin.getline(temp_login, MAX);
        //cin.getline(temp_pass, MAX);
        char c; int r =0;
        while (c != 13)
    {
        c = _getch();
        if(c != 13)
        {
              cout << "*";
              temp_pass[r] = c;
              r++;
        }
    }
        temp_pass[r] = '\0';
        cout << endl << temp_pass;
        cout << endl;
        dtb.open("database.txt");
        dtb >> qty;
        for(int i = 0; i < qty; i++)
        {
            char check_login[MAX] = {' '}, check_pass[MAX] = {' '};
            int temp_index;
            dtb >> temp_index;
            dtb.ignore();
            dtb.getline(check_login, MAX, ';');
            dtb.getline(check_pass, MAX);
            int temp_row, temp_col, temp_turn;
            if(!(strcmp(temp_login, check_login)) && !(strcmp(temp_pass, check_pass)))
            {
                index = temp_index;
                dtb >> temp_row >> temp_col >> turn;
                dtb.close();
                return true;
            }
                dtb >> temp_row >> temp_col >> temp_turn;
                for(int j = 0; j < b[temp_index].Row; j++)
                {
                    for(int q = 0; q < b[temp_index].Col; q++)
                    {
                        char temp_Icon;
                        dtb >> temp_Icon;
                    }
                }
        }
        dtb.close();
        return false;

    }
    void Back_up(Player p[], Board b[], int &qty, ofstream &dtb, int &turn)
    {
        dtb.open("database.txt");
        dtb << qty << endl;
        for(int i = 0; i < qty; i++)
        {
            dtb << i << endl;
            dtb << p[i].Login << ";" << p[i].Pass << endl;
            dtb << b[i].Row << " "<< b[i].Col << " "<< turn << endl;
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

void print_Board(Board b[], Player p[], int row, int col, int &index) // paly by new account
{
    b[index].PrintHorizonLine();
    for(int i = 0; i < b[index].Row; i++)
    {
       b[index].PrintVerticalLine();
        cout << "|";
        for(int j = 0; j < b[index].Col; j ++)
        {
            cout << "    ";
            cout << p[index].Icon[i][j]; // tọa độ (5,4) với ô đầu tiên, ô kế đó có tọa độ (16,4)
            std::cout << "     |";
        }
        cout << endl;
        b[index].PrintVerticalLine();
        b[index].PrintHorizonLine();
    }
}

bool is_emp(Player p[], Board b[], int &index, int i, int j)
{
   
        if(p[index].Icon[i][j] != ' ')
             return false;
    return true;
}

bool is_win(Player p[], int &index, int i, int j, int &turn)
{
    return false;
}

void process(Player p[], Board b[], int row, int col, int &index, int &p_x, int &p_y, int oriX, int oriY, int &i, int &j, int &turn, char c) // play by new account
{

         c = '0';
        while (c != 13 && c != 27)
        {
            c = _getch();
            switch (c)
            {
                case 'w':
                    if(p_y > oriY)
                    {  
                        p_y -= 4; 
                        i--;
                    }
                    break;
                case 'a':
                    if(p_x > oriX)
                    {  
                        p_x -= 11; 
                        j--;
                    }
                    break;
                case 'd':
                    if(p_x < (col-1)*11)
                    {  
                        p_x += 11; 
                        j++;
                    }
                     break;
                case 's':
                    if(p_y < (row-1)*4)
                    {  
                        p_y += 4; 
                        i++;
                    }
                     break;
                default: break;
            }
        }
        
        if(is_emp(p, b, index, i, j))
        {
            system("cls");
            print_Board(b, p, row, col, index);
            if (turn == 2)
                turn -= 2;
            if(turn == 0)
            {
                p[index].Icon[i][j] = 'x';
                turn ++;
            }
            else if(turn == 1)
            {
                 p[index].Icon[i][j] = 'o';
                 turn++;
            }
            GoTo(p_x, p_y);
            cout << p[index].Icon[i][j];
        }
}

void game_play(Player p[], Board b[], int &row, int &col, int &qty, int &index, int &p_x, int &p_y, int i, int j, int &turn, char c, ifstream &dtb, ofstream &out)
{
    Menu menu;
    menu.Read_database(dtb, p, b, qty, index);
    int choice;
     Start:
    cin >> choice;
 
    if(choice == 1)
    {
            menu.sign_up(p, qty);
            cin >> row >> col;
            int oriX, oriY;
             i = 0, j = 0, p_x = 5, p_y = 2, turn = 0, c = '0', index = qty -1, oriX = p_x, oriY = p_y;
            b[qty-1].initialize(row, col);
            p[qty-1].init(b[qty-1]);
            print_Board(b, p, row, col, index);
            while(!(is_win(p, index, i, j, turn)) || c != 27)
            {
                process(p, b, row, col, index, p_x, p_y, oriX, oriY, i, j, turn, c);
            }
            cout << "the winner is player " << turn << endl;
      
    } else if(choice == 2) {
            int oriX, oriY;
            i = 0, j = 0, p_x = 5, p_y = 2, c = '0', oriX = p_x, oriY = p_y;;
            if(menu.sign_in(p, b, qty, index, dtb, turn))
            {
                print_Board(b, p, row, col, index);
                while(!(is_win(p, index, i, j, turn)) || c != 27)
                {
                    process(p, b, b[index].Row, b[index].Col, index, p_x, p_y, oriX, oriY, i, j, turn, c);
                }
                cout << "The winner is player " << turn << endl;
            
            } else {
                cout << "Account not exit";
                goto Start;
            }
    }   
     menu.Back_up(p, b, qty, out, turn);
}

int main()
{
    Player p[MAX];
    Board b[MAX];
    int qty = 0, index, i, j, p_x, p_y, turn, row, col;
    char c;
    //print_Board(b, p, 3, 3);
    //play(p, b, 3, 3);
    ofstream out;
    ifstream dtb;
    Menu menu;
    game_play(p, b, row, col, qty, index, p_x, p_y, i, j, turn, c, dtb, out);
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
