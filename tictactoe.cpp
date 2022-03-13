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

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
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

    void Read_database(ifstream &dtb, Player p[], Board b[], int &qty, int &index)
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
              dtb >> row >> col >> p[i].turn;
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
            if(!(strcmp(temp_login, p[i].Login)) && !(strcmp(temp_pass, p[i].Pass)))
            {
                index = temp_index;
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
     void Back_up(Player p[], Board b[], int &qty)
     {
         ofstream dtb("database.txt", ofstream::ate);
         dtb << qty << endl;
         for(int i = 0; i < qty; i++)
         {
             dtb << i << endl;
             Remove_Newline(p[i].Login);
             dtb << p[i].Login << ";" << p[i].Pass << endl;
             dtb << b[i].Row << " " << b[i].Col << " " << p[i].turn << endl;
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
			if(p[index].Icon[i][b[index].Row - 1] == p[index].Icon[i+1][b[index].Row-1 - 1] && p[index].Icon[i][b[index].Row - 1] == p[index].Icon[i+2][b[index].Row- 1 - 2] && p[index].Icon[i][b[index].Row - 1] != ' ') 
				return 1;
	}

    for(int i = 0; i < b[index].Row; i++)
    {
        for(int j = 0; j < b[index].Col; j++)
            if(p[index].Icon[i][j] == ' ')
                return 0;
    }
    return 2;

}

void process(Player p[], Board b[], int row, int col, int &index, int &p_x, int &p_y, int oriX, int oriY, int &i, int &j, int &turn, char &c) // play by new account
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
                case 'r':
                    p[index].turn -= 1;
                    if(p[index].turn == 0)
                    {
                        if(p[index].undo_1 == 0)
                        {
                            p[index].Icon[i][j] = ' ';
                            GoTo(p_x, p_y);
                            cout << p[index].Icon[i][j];
                            p[index].undo_1 ++;
                        } else {
                            cout << p[index].turn << " can not go again \n";
                        }
                    } else if(p[index].turn  == 1)
                    {
                        if(p[index].undo_2 == 0)
                        {
                            p[index].Icon[i][j] = ' ';
                            GoTo(p_x, p_y);
                            cout << p[index].Icon[i][j];
                            p[index].undo_2 ++;
                        } else {
                            cout << p[index].turn << " can not go again \n";
                        }
                    }
                     break;
                default: break;
            }
        }
        
        if(c != 27)
        {
            if(is_emp(p, b, index, i, j))
            {
                system("cls");
                print_Board(b, p, row, col, index);
                if (p[index].turn == 2)
                    p[index].turn -= 2;
                if(p[index].turn == 0)
                {
                    p[index].Icon[i][j] = 'x';
                    p[index].turn++;
                }
                else if(p[index].turn== 1)
                {
                    p[index].Icon[i][j] = 'o';
                    p[index].turn++;
                }
                GoTo(p_x, p_y);
                cout << p[index].Icon[i][j];
            }
        }
}
bool Account(Player p[], Board b[], Menu &menu, int &qty, int &index, int row, int col, ifstream &dtb)
{
    int choice = 1;
    char c = '0';
     SetColor(0,7);
        cout << "\n                                      WELCOME TO TICTACTOE GAME     \n\n";
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign in               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
         cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign up               |\n";
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
        system("cls");
        if(choice == 1)
        {
            SetColor(0,7);
            cout << "\n                                      WELCOME TO TICTACTOE GAME     \n\n";
            SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign in               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign up               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
        } else if(choice == 2)
        {
            cout << "\n                                      WELCOME TO TICTACTOE GAME     \n\n";
             SetColor(0, 7);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign in               |\n";
        cout << "                               |                                    |\n";
        cout << "                               -------------------------------------\n\n";
             SetColor(0, 9);
        cout << "                               -------------------------------------\n";
        cout << "                               |                                    |\n";
        cout << "                               |              Sign up               |\n";
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
        system("cls");
            cout <<"sign up successfully            \n";
            cout << "Enter your row and col for your board: ";
            cin >> row >> col;
            index = qty-1;
            b[index].initialize(row, col);
             p[index].init(b[index]);
             p[index].turn = 0;
             return true;
    }  else if(choice == 2) {

        while(!(menu.sign_in(p, b, qty, index, dtb)))
             {
                 cout << "Your account does not exist \n";
             }
             system("cls");
             if(b[index].Row == 0 && b[index].Col == 0)
                    {
                        cout << "Enter your row and col for your board: ";
                        cin >> b[index].Row >> b[index].Col;
                        p[index].init(b[index]);
                    }
                 system("cls");
             return true;
    }
}

void playGame(Player p[], Board b[], Menu menu, int &row, int &col, int &qty, int &index, int &p_x, int &p_y, int i, int j, int &turn, char c, ifstream &dtb, ofstream &out)
{
    menu.Read_database(dtb, p, b, qty, index);
        if(Account(p,b, menu, qty, index, row, col, dtb))
        {
         int play_again, save_game = 1, choose = 0;      
        do
        {
            system("cls");
            int check = 0;
            i = 0, j = 0, p_x = 5, p_y = 2,  c = '0';  int oriX = p_x, oriY = p_y;
            print_Board(b, p, b[index].Row, b[index].Col, index);
            while(check == 0 && choose == 0)
                {
                    process(p, b, b[index].Row, b[index].Col, index, p_x, p_y, oriX, oriY, i, j, p[index].turn, c);
                    check = is_win(p, b, index, i, j, turn);
                    if(c == 27)
                    {
                        GoTo(1, 5 * b[index].Row);
                        cout << "save the game or continue.Enter 1 to exit and save game, 0 to continue, 2 to exit and not save: ";
                        cin >>choose;
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
                             play_again = 0;
                         }
                    }
                }
                if(check == 1 && c != 27)
                {
                    GoTo(1, p_y + 10);
                    cout << "The winner is player " << p[index].turn << endl;
                   do
                    {
                        cout <<"Do you want to play again? enter 0 for no or 1 for yes: ";
                        cin >>play_again;
                        if(play_again < 0 || play_again >= 2)
                            cout <<"wrong syntax \n";
                    } while(play_again < 0 || play_again >= 2);

                } else if(check == 2 && c != 27)
                {
                    cout << "Draw game \n";
                    do
                    {
                         cout <<"Do you want to play again? enter 0 for no or 1 for yes: ";
                        cin >>play_again;
                        if(play_again < 0 || play_again >= 2)
                            cout <<"wrong syntax \n";
                    } while(play_again < 0 || play_again >= 2);
                }
            if(play_again == 1)
               { p[index].init(b[index]);
                 p[index].turn = 0;
                 p[index].undo_1 = 0;
                 p[index].undo_1 = 0;
               }
        } while(play_again == 1);
        if(play_again == 0 && c != 27)
           {
               do
               {
                    cout << "Do you want to save the game.Enter 0 for no or 1 for yes: ";
                    cin >> save_game;
                    if(save_game < 0  || save_game >= 2)
                        cout << "wrong syntax";
               } while(save_game < 0  || save_game >= 2);
                    if(save_game == 1)
                        menu.Back_up(p, b, qty);
                    else 
                    {
                        p[index].init(b[index]);
                        b[index].Row = 0;
                        b[index].Col = 0;
                        p[index].turn = 0;
                        p[index].undo_1 = 0;
                        p[index].undo_2 = 0;
                         menu.Back_up(p, b, qty);
                    }
           } else if(play_again == 0 && c == 27)
           {
                menu.Back_up(p, b, qty);
           }
        }
}
int main()
{
    Player p[MAX];
    Board b[MAX];
    int qty = 0, index, i, j, p_x, p_y, turn, row, col;
    char c;
    ofstream out;
    ifstream dtb;
    Menu menu;
    SetWindowSize(50, 50);
    playGame(p, b, menu, row, col, qty, index, p_x, p_y, i, j, turn, c, dtb, out);
    GoTo(p_x + 10, p_y + 10);
    return 0;
}
