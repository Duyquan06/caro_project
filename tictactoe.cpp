#include<iostream>
#include<windows.h>
#include<cstring>
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<time.h>
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
    int turn;
    int undo_1, undo_2;
    void init(Board b)
    {
        for(int i = 0; i < b.Row; i++)
        {
            for(int j = 0; j < b.Col; j++)
                Icon[i][j] = ' ';
        }
        undo_1 = 0; undo_2 = 0;
    }
    int win1 = 0, win2 = 0, draw = 0, human = 0, bot = 0, drawPVE = 0;
    char Icon1, Icon2;
};

void GoTo(int posX, int posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetColor(int background_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void unhide_Pointer()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hOut,&ConCurInf);
}

void Delete (char p[])
{
    int size = strlen(p);
    for(int i = 0; i <= size - 1; i++)
    {
        
        p[i] = p[i+1];
    }
}
void Remove_Newline(char p[])
{
    int size = strlen(p);
    for(int i = 0; i < size; i++)
    {
        if(p[0] == 10)
            Delete(p);
    }
}
struct Menu
{
    bool sign_up(Player p[], int &qty)
    {
        system("cls");
        qty++;
    cout << "                                        Enter your login name         \n\n";
    cout << "                               -------------------------------------\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               -------------------------------------\n\n";
        //cin.ignore();
        //cin.getline(p[qty-1].Login, MAX);
        GoTo(45, 4);
        cin >> p[qty-1].Login;
        //cin.getline(p[qty++].Pass, MAX);
        char c = 1; int i =0;

    cout << "\n\n\n\n                                        Enter your password        \n";
    cout << "                               -------------------------------------\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               -------------------------------------\n\n";
           int j = 45;
            while (c != 13)
        {
            GoTo(j, 12);
            c = _getch();
            if(c != 13)
            {
                cout << "*";
                p[qty-1].Pass[i] = c;
                j++;
            }
            i++;
        }
        p[qty-1].Pass[i] = '\0';
        cout << endl;
        if(qty == 1)
            return true;
        for(int i = 0; i < qty-1;i++)
        {
            if(!strcmp(p[qty-1].Login, p[i].Login))
                {
                    //cout << "Account has existed \n";
                    return false;
                }
        }
        return true;
    }

    void Read_database(ifstream &dtb, Player p[], Board b[], int &qty, int &index, int &bot)
    {
        int temp_check;
        dtb.open("database.txt");
        dtb >> qty;
        for(int i = 0; i < qty;i++)
        {
              dtb >> temp_check;
              dtb.ignore();
              dtb.getline(p[i].Login, MAX, ';');
              dtb.getline(p[i].Pass, MAX);
              int row, col;
              dtb >> row >> col >> p[i].turn >> p[i].Icon1 >> p[i].Icon2 >> bot >> p[i].win1 >> p[i].win2 >> p[i].draw >> p[i].human >> p[i].bot >> p[i].drawPVE;
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

    bool sign_in(Player p[], Board b[], int &qty, int &index, ifstream &dtb)
    {   
        system("cls");
        char temp_login[MAX], temp_pass[MAX];
    cout << "                                        Enter your login name         \n\n";
    cout << "                               -------------------------------------\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               -------------------------------------\n\n";
         GoTo(45, 4);
        //cin.ignore();
        cin >> temp_login;
        //cin.getline(temp_login, MAX);
        //cin.getline(temp_pass, MAX);
    cout << "\n\n\n\n                                        Enter your password        \n";
    cout << "                               -------------------------------------\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               |                                    |\n";
    cout << "                               -------------------------------------\n\n";
    int j = 45;
        char c; int r =0;
        while (c != 13)
    {
        GoTo(j, 12);
        c = _getch();
        if(c != 13)
        {
              cout << "*";
              temp_pass[r] = c;
              r++;
              j++;
        }
    }
        temp_pass[r] = '\0';
        for(int i = 0; i < qty; i++)
        {
            if(!(strcmp(temp_login, p[i].Login)) && !(strcmp(temp_pass, p[i].Pass)))
            {
                index = i;
                return true;
            }
        }
        return false;

    } 
     void Back_up(Player p[], Board b[], int &qty, int bot)
     {
         ofstream dtb("database.txt", ofstream::ate);
         dtb << qty << endl;
         for(int i = 0; i < qty; i++)
         {
             dtb << i << endl;
             Remove_Newline(p[i].Login);
             dtb << p[i].Login << ";" << p[i].Pass << endl;
             dtb << b[i].Row << " " << b[i].Col << " " << p[i].turn << " " << p[i].Icon1 << " "  << p[i].Icon2 <<  " " << bot << "\n";
             dtb << p[i].win1 << " " << p[i].win2 << " " << p[i].draw << "\n";
             dtb << p[i].human << " " << p[i].bot << " " << p[i].drawPVE << "\n";
             for(int j = 0; j < b[i].Row; j++)
             {
                 for(int q = 0; q < b[i].Col; q++)
                    {
                        char temp_Icon;
                        temp_Icon = p[i].Icon[j][q];
                        if(temp_Icon == ' ')
                            temp_Icon = '0';
                        dtb << temp_Icon << " ";   
                    }
                    dtb << endl;
             }
         }
         dtb.close();
     }
};

void print_Board(Board b[], Player p[], int row, int col, int &index, int current_i, int current_j) // paly by new account
{
    b[index].PrintHorizonLine();
    for(int i = 0; i < b[index].Row; i++)
    {
       b[index].PrintVerticalLine();
        cout << "|";
        for(int j = 0; j < b[index].Col; j ++)
        {
            if(i == current_i && j == current_j)
            {
                SetColor(1,7);
                cout << "    ";
                if(p[index].Icon[i][j] == 'x')
                {
                    SetColor(0, 4) ;    // tọa độ (5,4) với ô đầu tiên, ô kế đó có tọa độ (16,4)
                } else if(p[index].Icon[i][j] == 'o')
                {
                    SetColor(0,6);
                }
                 cout << p[index].Icon[i][j];
                 SetColor(1,7);
                std::cout << "     ";
                SetColor(0,7);
                std::cout <<"|";
            } else {
                cout << "    ";
               if(p[index].Icon[i][j] == p[index].Icon1)
                {
                    SetColor(0, 4) ;    // tọa độ (5,4) với ô đầu tiên, ô kế đó có tọa độ (16,4)
                } else if(p[index].Icon[i][j] == p[index].Icon2)
                {
                    SetColor(0,6);
                }
                 cout << p[index].Icon[i][j];
                 SetColor(0,7);
                std::cout << "     ";
                std::cout <<"|";
            }
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

int is_win(Player p[], Board b[], int &index, int i, int j, int &turn)
{
    // check row
	for(int i = 0; i < b[index].Row; ++i)
	{
		for(int j = 0; j < b[index].Col - 2; ++j)
		{
            if(p[index].Icon[i][j] == p[index].Icon[i][j+1] && p[index].Icon[i][j] == p[index].Icon[i][j+2] && p[index].Icon[i][j] != ' ')
                    return 1;
		}	
	}


	// check col
	for(int i = 0; i < b[index].Col; ++i)
	{
		for(int j = 0; j < b[index].Row - 2; ++j)
		{
			if(p[index].Icon[j][i] == p[index].Icon[j+1][i] && p[index].Icon[j][i] == p[index].Icon[j+2][i] && p[index].Icon[j][i] != ' ')
				return 1;
		}
	}

	// Main Diagonal line // need to re-check
    for(int i = 0; i < b[index].Row - 2; i++)
    {
        for(int j = 0; j < b[index].Col - 2; j++)
        {
            if(p[index].Icon[i][j] == p[index].Icon[i+1][j+1] && p[index].Icon[i][j] == p[index].Icon[i+2][j+2] && p[index].Icon[i][j] != ' ')
                return 1;
        }   
    }
	
	
    
	for(int i = 0; i < b[index].Row - 2; ++i)
	{
			for(int j = b[index].Col-1; j >= 0; j--)
                if(p[index].Icon[i][j] == p[index].Icon[i+1][j-1] && p[index].Icon[i][j] == p[index].Icon[i+2][j-2] && p[index].Icon[i][j] != ' ')
                    return 1;
	}

    int count = 0;
    for(int i = 0; i < b[index].Row; i++) //Draw game
    {
        for(int j = 0; j < b[index].Col; j++)
            if(p[index].Icon[i][j] != ' ')
                count++;
    }
    if(count == b[index].Row * b[index].Col)
        return 2;
    return 0;

}

void MoveSuggestion(Player p[], Board b[], int index, int &hintR, int &hintC)
{
    srand((time(0)));
   do
   {
       hintR = rand() % b[index].Row;;
       hintC = rand() % b[index].Col;
   } while (p[index].Icon[hintR][hintC] != ' ');    

}

void process(Player p[], Board b[], int row, int col, int &index, int &p_x, int &p_y, int oriX, int oriY, int &i, int &j, int &turn, char &c, int &latest_x1, int &latest_y1, int &latest_x2, int &latest_y2, int &hintR, int &hintC) // play by new account
{
         c = '0';
         bool check_undo = true;
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
                case 'r':
                    if(p[index].turn == 0 && p[index].undo_1 == 0)
                    {
                        p[index].Icon[latest_x1][latest_y1] = ' ';
                        p[index].undo_1++;
                    } else if(p[index].turn == 1 && p[index].undo_2 == 0)
                    {
                        p[index].Icon[latest_x2][latest_y2] = ' ';
                        p[index].undo_2 ++;
                    } else if(p[index].turn == 0 && p[index].undo_1 != 0) {
                        check_undo = false;
                    } else if(p[index].turn == 1 && p[index].undo_2 != 0) {
                        check_undo = false;
                    }
                     break;
                default: break;
            }
                   system("cls");
                   unhide_Pointer();
                    print_Board(b, p, b[index].Row, b[index].Col, index, i, j);
                        if(check_undo == false)
                        {
                             cout << "\n Player " << p[index].turn + 1 << " can not go again\n";
                             //cout << "\n  this is player " << p[index].turn +1<< " turn \n";
                             check_undo = true;
                        }

                    cout << "\n  this is player " << p[index].turn +1<< " turn \n";
                    cout << "Move suggestion: row " << hintR + 1 << " col " << hintC + 1 << "\n";
        }
        
        if(c != 27)
        {
            if(is_emp(p, b, index, i, j))
            {
                if(p[index].turn == 0)
                {
                    p[index].Icon[i][j] = p[index].Icon1;
                    latest_x1 = i; latest_y1 = j;
                    p[index].turn++;
                }
                else if(p[index].turn== 1)
                {
                    p[index].Icon[i][j] = p[index].Icon2;
                    latest_x2 = i; latest_y2 = j;
                    p[index].turn++;
                }
                if (p[index].turn == 2)
                    p[index].turn -= 2;
                //XoaManHinh();
                system("cls");
                unhide_Pointer();
                print_Board(b, p, row, col, index, i, j);
                cout << "\n  this is player " << p[index].turn +1<< " turn \n";
            }
        }
}
bool Account(Player p[], Board b[], Menu &menu, int &qty, int &index, int row, int col, ifstream &dtb, int &bot)
{
    int choice = 1;
    char c = '0';
     SetColor(0,7);
        cout << "\n                                      WELCOME TO TICTACTOE GAME     \n\n";
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign up               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
         cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign in               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
    while(c != 13)
    {
        c = _getch();
        switch(c)
        {
            case 's':
             if(choice == 1)
                choice++;
            break;

            case 'w':
                if(choice == 2)
                    choice--;
        }
        XoaManHinh();
        if(choice == 1)
        {
            SetColor(0,7);
            cout << "\n                                      WELCOME TO TICTACTOE GAME     \n\n";
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign up               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign in               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
        } else if(choice == 2)
        {
            cout << "\n                                      WELCOME TO TICTACTOE GAME     \n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign up               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign in               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        }
    }
    if(choice == 1)
    {
            while(!(menu.sign_up(p, qty)))
        {
            cout << "Your login name has existed, please try another name \n";
            qty--;
        }
        XoaManHinh();
        b[index].Row == 0;
        b[index].Col == 0;
        index = qty-1;
        bot = 0;
        return true;
    }  else if(choice == 2) {

        while(!(menu.sign_in(p, b, qty, index, dtb)))
             {
                 cout << "Your account does not exist \n";
             }
             XoaManHinh();
             return true;
    }
}


void Animation_3(char f[], char s[], char t[], int &choose)
{
    char c = '0';
    SetColor(0,7);
        cout << "\n                                             Setting     \n\n";
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |       ";
        cout << s;
        cout << "       |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";

        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |     ";
        cout << t;
        cout << "     |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
    while(c != 13)
    {
        c = _getch();
        switch(c)
        {
            case 's':
             if(choose < 2)
                choose++;
            break;

            case 'w':
                if(choose > 0)
                    choose--;
        }
        XoaManHinh();
        if(choose == 0)
        {
            SetColor(0,7);
           cout << "\n                                             Setting     \n\n";
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |       ";
        cout << s;
        cout << "       |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";

        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |     ";
        cout << t;
        cout << "     |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
        } else if(choose == 1)
        {
           cout << "\n                                             Setting     \n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |       ";
        cout << s;
        cout << "       |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |     ";
        cout << t;
        cout << "     |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
        } else if(choose == 2) {
           cout << "\n                                             Setting     \n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |       ";
        cout << s;
        cout << "       |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |     ";
        cout << t;
        cout << "     |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
         SetColor(0, 7);
        }
    }

}


void Animation_2(char f[], char s[], int &choice, Player p[], int index, int check, int bot)
{
    system("cls");
    char c = '0';
    if(bot != 0)
    {
        if(check == 2)
        {
            cout << "\t\t\t\t   Draw game\n";
            if(bot == 1)
                cout << " \t\t  Player 1 wins: " << p[index].win1 << "\t" << "Player 2 wins: " << p[index].win2 << "\t" << "Draw game: " << p[index].draw << "\n";
            else 
                cout << " \t\t  Human wins: " << p[index].human << "\t" << "Bot wins: " << p[index].bot << "\t" << "Draw game: " << p[index].drawPVE << "\n";
        }
        else 
        {
            if(bot == 1)
            {
            cout << "\t\t\t\t   The winner is player " << p[index].turn <<"!!!!!!!\n";
            cout << " \t\t  Player 1 wins: " << p[index].win1 << "\t" << "Player 2 wins: " << p[index].win2 << "\t" << "Draw game: " << p[index].draw << "\n";
            } else {
                if(p[index].turn == 0)
                    cout << "\t\t\t\t   The winner is bot " <<"!!!!!!!\n";
                else 
                    cout << "\t\t\t\t   The winner is human " <<"!!!!!!!\n";
                cout << " \t\t  Human wins: " << p[index].human << "\t\t" << "Bot wins: " << p[index].bot << "\t" << "Draw game: " << p[index].drawPVE << "\n";
            }
        }
    }
     
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |               ";
        cout << s;
        cout << "                 |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
    while(c != 13)
    {
        c = _getch();
        switch(c)
        {
            case 's':
             if(choice == 0)
                choice++;
            break;

            case 'w':
                if(choice == 1)
                    choice--;
            break;
        }
        system("cls");
        if(bot != 0)
        {
            if(check == 2)
            {
                cout << "\t\t\t\t   Draw game\n";
                if(bot == 0)
                    cout << " \t\t  Player 1 wins: " << p[index].win1 << "\t" << "Player 2 wins: " << p[index].win2 << "\t" << "Draw game: " << p[index].draw << "\n";
                else 
                    cout << " \t\t  Human wins: " << p[index].human << "\t" << "Bot wins: " << p[index].bot << "\t" << "Draw game: " << p[index].drawPVE << "\n";
            }
            else 
            {
                if(bot == 1)
                {
                cout << "\t\t\t\t   The winner is player " << p[index].turn <<"!!!!!!!\n";
                cout << " \t\t  Player 1 wins: " << p[index].win1 << "\t" << "Player 2 wins: " << p[index].win2 << "\t" << "Draw game: " << p[index].draw << "\n";
                } else {
                    if(p[index].turn == 2)
                        cout << "\t\t\t\t   The winner is bot " <<"!!!!!!!\n";
                    else 
                        cout << "\t\t\t\t   The winner is human " <<"!!!!!!!\n";
                cout << " \t\t  Human wins: " << p[index].human << "\t" << "Bot wins: " << p[index].bot << "\t" << "Draw game: " << p[index].drawPVE << "\n";
                }
            }
        }
        if(choice == 0)
        {
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |               ";
        cout << s;
        cout << "                 |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
        } else if(choice == 1)
        {
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |             ";
        cout << f;
        cout << "             |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 9);
       cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |               ";
        cout << s;
        cout << "                 |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        }
    }
}

void Bot(Player p[], Board b[], int index)
{
    int col, row;
    srand(time(0));
    while(1)
    {
        col = rand() % b[index].Col;
        row = rand() % b[index].Row;
        if(p[index].Icon[row][col] == ' ')
        {
            p[index].Icon[row][col] = p[index].Icon2;
            break;
        }
    }
    p[index].turn--;
}


void playGame(Player p[], Board b[], Menu menu, int &row, int &col, int &qty, int &index, int &p_x, int &p_y, int i, int j, int &turn, char c, ifstream &dtb, ofstream &out, int bot)
{
    menu.Read_database(dtb, p, b, qty, index, bot);
    XoaManHinh();
        if(Account(p,b, menu, qty, index, row, col, dtb, bot))
        {
         int play_again, save_game = 1, choose = 0;      
        do
        {
            system("cls");
            if(b[index].Row == 0 && b[index].Col == 0)
            {
                 char f[] = "   PVP    ", s[10] = " PVE";
                if(bot == 0)
                {
                    Animation_2(f, s, bot, p, index, 0, 0);
                    bot++;
                }
                while(1)
                {
                    system("cls");
                    cout << "Enter your row and col for your board (col and row MUST GREATER THAN 3): ";
                    cin >> b[index].Row >> b[index].Col;
                    if(b[index].Row >= 3 && b[index].Col >= 3)
                        break;
                }
                cout << "Design icon of player 1: ";
                cin >> p[index].Icon1;
                cout << "Design icon of ";
                if(bot == 1)
                    cout << " player 2: ";
                else 
                    cout << " bot: ";
                cin >> p[index].Icon2;
                p[index].init(b[index]);
            }

            int check = 0, lates_x1 = 0, lates_y1 = 0, lates_x2 = 0, lates_y2 = 0, hintR, hintC;
            i = 0, j = 0, p_x = 5, p_y = 2,  c = '0';  int oriX = p_x, oriY = p_y;
            char f[] = "Continue  ", s[] = "Exit and save the game", t[] = "Exit and not save the game";

            system("cls");
            print_Board(b, p, b[index].Row, b[index].Col, index, 0, 0);
             cout << "\n  this is player " << p[index].turn + 1<< " turn \n";

            if(check == 0)
            {
             MoveSuggestion(p, b, index, hintR, hintC);
             cout << "Move suggestion: row " << hintR + 1 << " col " << hintC + 1 << "\n";
            }
             check = is_win(p, b, index, i, j, turn);
            while(check == 0 && choose == 0)
                {
                    process(p, b, b[index].Row, b[index].Col, index, p_x, p_y, oriX, oriY, i, j, p[index].turn, c, lates_x1, lates_y1, lates_x2, lates_y2, hintR, hintC);
        
                    check = is_win(p, b, index, i, j, turn);
                    if(check == 0)
                    {
                        MoveSuggestion(p, b, index, hintR, hintC);
                         cout << "Move suggestion: row " << hintR + 1 << " col " << hintC + 1 << "\n";
                    }

                    if(bot == 2 && c != 27 && check == 0)
                    {
                        Bot(p, b, index);
                       system("cls");
                        print_Board(b, p, b[index].Row, b[index].Col, index, i, j);
                        
                        check = is_win(p, b, index, i, j, turn);
                        if(check == 0)
                        {
                            MoveSuggestion(p, b, index, hintR, hintC);
                            cout << "Move suggestion: row " << hintR + 1 << " col " << hintC + 1 << "\n";
                        }
                    }
                    if(c == 27)
                    {
                        system("cls");
                        Animation_3(f, s, t, choose);
                        if(choose == 0)
                            {
                                system("cls");
                                c = '0';
                                print_Board(b, p, b[index].Row, b[index].Col, index, i, j);
                                cout << "\n  this is player " << p[index].turn +1<< " turn \n";
                                cout << "Move suggestion: row " << hintR + 1 << " col " << hintC + 1 << "\n";
                               
                            }
                        if(choose == 1)
                         {
                            play_again = 0;
                         } else if(choose == 2)
                         {
                             p[index].init(b[index]);
                            b[index].Row = 0;
                            b[index].Col = 0;
                            p[index].turn = 0;
                            p[index].undo_1 = 0;
                            p[index].undo_2 = 0;
                            bot = 0;
                             play_again = 0;
                         }
                    }
                }
                if(check == 1)
                {
                   if(bot == 1)
                   {
                    if(p[index].turn == 0)
                        {
                            p[index].turn+=2;
                            p[index].win2 += 1;
                        } else {
                            p[index].win1 += 1;
                        }
                   } else {
                       if(p[index].turn == 0)
                        {
                            p[index].bot += 1;
                        } else {
                            p[index].human += 1;
                        }
                   }
                }
                if(check == 2)
                {
                    if(bot == 1)
                        p[index].draw += 1;
                    else 
                        p[index].drawPVE += 1;
                }
                if(c != 27)
                {
                    strcpy(f, "Play Again");
                    strcpy(s, "Exit");
                    choose = 0;
                  Animation_2(f, s, choose, p, index, check, bot);
                   if(choose == 0)
                        play_again = 1;
                    else 
                    {
                        play_again = 0;
                        if(choose == 1)
                            save_game = 1;
                    }
                }
            if(play_again == 1)
               { 
                 p[index].init(b[index]);
                 p[index].turn = 0;
                 p[index].undo_1 = 0;
                 p[index].undo_2 = 0;
                 b[index].Row = 0;
                 b[index].Col = 0;
                 bot = 0;
               }
        } while(play_again == 1);
        if(play_again == 0 && c != 27)
           {
                p[index].init(b[index]);
                b[index].Row = 0;
                b[index].Col = 0;
                p[index].turn = 0;
                p[index].undo_1 = 0;
                p[index].undo_2 = 0;
                bot = 0;
                menu.Back_up(p, b, qty, bot);
           } else if(play_again == 0 && c == 27 && save_game == 1)
                menu.Back_up(p, b, qty, bot);
        }
}
int main()
{
    Player p[MAX];
    Board b[MAX];
    int qty = 0, index, i, j, p_x, p_y, turn, row, col, bot;
    char c;
    ofstream out;
    ifstream dtb;
    Menu menu;
    SetWindowSize(50, 50);
    playGame(p, b, menu, row, col, qty, index, p_x, p_y, i, j, turn, c, dtb, out, bot);
    system("cls");
    GoTo(p_x + 10, p_y + 10);
    return 0;
}
