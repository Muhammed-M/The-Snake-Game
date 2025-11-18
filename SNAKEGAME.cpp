#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>
#include <cctype>
#include <windows.h>
#include <random>

using namespace std;


//------------------------------------------------------- THE SNAKE GAME PROJECT ------------------------------------------------------- //

//----------------------- Game Objects Structure ----------------------- //


class Game 
{
    private :
        int width ;
        int height ;
        int Speed ;

    public :

        Game(int w , int h ) 
        {
            width = w ;
            height = h ;
            Speed = 50 ;
        }

        int GetWidth() {return width ;}
        int GetHeight() {return height ;}
        int GetSpeed() {return Speed ;}

        void IncSpeed() 
        {   
            if(Speed < 95)
            {Speed += 5 ;}
        }
        void DecSpeed() 
        {
            if(Speed > 5 )
            {Speed -= 5 ;}
        }

};

class SnakeHead 
{
    private :
        int x ;
        int y ;
        char Snake_GUI , Snake_UPGUI , Snake_DWGUI , Snake_RGUI , Snake_LGUI ; 

    public :

        SnakeHead(int xr , int yr ) 
        {
            x = xr ;
            y = yr ;
            Snake_GUI = 'Z' ;
        }

        void SetX(int xn)  { x = xn ; }
        void SetY(int yn)  { y = yn ; }

        void IncX()  { x ++ ; }
        void DecX()  { x -- ; }

        void IncY()  { y ++ ; }
        void DecY()  { y -- ; }

        int GetX() {return x ;}
        int GetY() {return y ;}

        char GetGUI() {return Snake_GUI ;}
};

class Fruit 
{
    private :
        int x ;
        int y ;
        char Fruit_GUI ; 
        static int score ;

    public :

        Fruit(int xr , int yr ) 
        {
            x = xr ;
            y = yr ;
            Fruit_GUI = '@' ;   
        }

        int GetX() {return x ;}
        int GetY() {return y ;}
        char GetGUI() {return Fruit_GUI ;}
        static int GetScore() {return score ;} 

        ~ Fruit()
        {
            score ++ ;
        }

};


//----------------------- Game Functions Declaration ----------------------- //


void StartMessage(int W , int H) ;
void ControlMessege(int W , int H , int& direction ) ;
void EndMessage(int W , int H , int GO)  ;
void FramePrint(int W , int H , Game* G1) ;

Fruit RandomFruitGenerator(int W , int H)  ;
void FruitReBirth(Game* G1 , Fruit* F1 , int* x , int* y , int BD ) ;
SnakeHead RandomSnakeGenerator(int W , int H) ;

void NewFunction(int bodycount, int *SnakeHistory_X, int *SnakeHistory_Y, SnakeHead &SH1, Game &G1, int &GameOver, int &direction, int& lastD , int Body_GUI, int &retFlag , char BodyGUI);

void GetValidInput(int& direction) ;
void gotoxy(int x, int y) ;
void ClearKeyboardBuffer() ;
void HideCursor() ;
void SetColor(int color) ;

int Fruit::score = 0 ;
 

//----------------------- Game Main Logic ----------------------- //


int main()
{

    HideCursor() ;


    Game G1( 115 , 25 ) ;

    int GameSize = G1.GetWidth() * G1.GetHeight() ;

    int *SnakeHistory_X = new int[ GameSize ] ;
    int *SnakeHistory_Y = new int[ GameSize ] ;
    int bodycount = 0 ;
    int Body_GUI = 42 ;
    int direction = 0 ;

    SetColor(7) ;
    StartMessage( G1.GetWidth(), G1.GetHeight() ) ;
    FramePrint( G1.GetWidth() , G1.GetHeight() , &G1 ) ;
    ControlMessege(G1.GetWidth(), G1.GetHeight() , direction ) ;

    SnakeHead SH1 = RandomSnakeGenerator( G1.GetWidth() , G1.GetHeight() ) ;
    gotoxy( SH1.GetX() , SH1.GetY() ) ;
    SetColor(10) ;
    cout << SH1.GetGUI() ;
    SetColor(7) ;

    SnakeHistory_X[0] = SH1.GetX() ;
    SnakeHistory_Y[0] = SH1.GetY() ;

    Fruit F1 = RandomFruitGenerator( G1.GetWidth() , G1.GetHeight() ) ; 
    gotoxy( F1.GetX() , F1.GetY() ) ;
    SetColor(4) ;
    cout << F1.GetGUI() ;
    SetColor(7) ;
    






    int lastD = 0 ;
    int GameOver = 0 ;
    ClearKeyboardBuffer() ;
    GetValidInput(direction) ;
        while (direction != 27)
        {
            if ( (direction == 72 && lastD != 80 ) || ( direction == 80 && lastD == 72 ) ) // UP
            {
                lastD = 72 ;
                while( ! _kbhit() )
                {
                    if ( SH1.GetX() == F1.GetX() && SH1.GetY() == F1.GetY() ) 
                    {
                        FruitReBirth( &G1 , &F1 , SnakeHistory_X , SnakeHistory_Y , bodycount ) ;
                        bodycount ++ ;
                        continue ;                         
                    }

                    Sleep(G1.GetSpeed()) ;

                    int retFlag;
                    char BodyGUI = 'A' ;
                    NewFunction(bodycount, SnakeHistory_X, SnakeHistory_Y, SH1, G1, GameOver, direction, lastD , Body_GUI, retFlag , BodyGUI);
                    if (retFlag == 2) {break;}
                }
                if(GameOver != 999){GetValidInput(direction) ;}
            } 
            if ( ( direction == 80 && lastD != 72 ) || ( direction == 72 && lastD == 80 ) ) // DOWN
            {
                lastD = 80 ;
                while( ! _kbhit() )
                {
                    if ( SH1.GetX() == F1.GetX() && SH1.GetY() == F1.GetY() ) 
                    {
                        FruitReBirth( &G1 , &F1 , SnakeHistory_X , SnakeHistory_Y , bodycount ) ;
                        bodycount ++ ;
                        continue ;                         
                    }

                    Sleep(G1.GetSpeed()) ;

                    int retFlag;
                    char BodyGUI = 'V' ;
                    NewFunction(bodycount, SnakeHistory_X, SnakeHistory_Y, SH1, G1, GameOver, direction, lastD , Body_GUI, retFlag , BodyGUI);
                    if (retFlag == 2) {break;}
                }
                if(GameOver != 999){GetValidInput(direction) ;}
            }
            if ( ( direction == 77 && lastD != 75 ) || ( direction == 75 && lastD == 77 ) ) // RIGHT
            {
                lastD = 77 ;
                while( ! _kbhit() )
                {
                    if ( SH1.GetX() == F1.GetX() && SH1.GetY() == F1.GetY() ) 
                    {
                        FruitReBirth( &G1 , &F1 , SnakeHistory_X , SnakeHistory_Y , bodycount ) ;
                        bodycount ++ ;
                        continue ;                         
                    }

                    Sleep(G1.GetSpeed()) ;

                    int retFlag;
                    char BodyGUI = '>' ;
                    NewFunction(bodycount, SnakeHistory_X, SnakeHistory_Y, SH1, G1, GameOver, direction, lastD , Body_GUI, retFlag , BodyGUI);
                    if (retFlag == 2) {break;}
                }
                if(GameOver != 999){GetValidInput(direction) ;}
            }
            if ( ( direction == 75 && lastD != 77 ) || ( direction == 77 && lastD == 75 ) ) // LEFT
            {
                lastD = 75 ;
                while( ! _kbhit() )
                {
                    if ( SH1.GetX() == F1.GetX() && SH1.GetY() == F1.GetY() ) 
                    {
                        FruitReBirth( &G1 , &F1 , SnakeHistory_X , SnakeHistory_Y , bodycount ) ;
                        bodycount ++ ;
                        continue ;                         
                    }

                    Sleep(G1.GetSpeed()) ;

                    int retFlag;
                    char BodyGUI = '<' ;
                    NewFunction(bodycount, SnakeHistory_X, SnakeHistory_Y, SH1, G1, GameOver, direction, lastD , Body_GUI, retFlag , BodyGUI);
                    if (retFlag == 2) {break;}
                }
                if(GameOver != 999){GetValidInput(direction) ;}
            }
            if ( direction == 45 ) // Slower
            {
                G1.IncSpeed() ;
                gotoxy(G1.GetWidth()-20,0) ;
                SetColor(15) ;
                cout << " Speed : " << 100 - G1.GetSpeed() << " ";
                SetColor(7) ;
                GetValidInput(direction) ;

            }
            if ( direction == 43 ) // Faster
            {
                G1.DecSpeed() ;
                gotoxy(G1.GetWidth()-20,0) ;
                SetColor(15) ;
                cout << " Speed : " << 100 - G1.GetSpeed() << " ";
                SetColor(7) ;
                GetValidInput(direction) ;
            }   
        }
    
    


    delete[] SnakeHistory_X ;
    delete[] SnakeHistory_Y ;

    ClearKeyboardBuffer() ;
    EndMessage( G1.GetWidth(), G1.GetHeight() , GameOver ) ;

    return 0;
}



//----------------------- Game Functions ----------------------- //


void StartMessage(int W , int H) 
{
    
    gotoxy((W/2)-16 , 5 ) ;
    cout << "THE SNAKE GAME (Console Edition)" ;
    gotoxy((W/2)-16 , H/2 + 2 ) ;
    SetColor(15) ;
    cout << "==>  Press Any Key To Start  <==" ;
    SetColor(14) ;
    gotoxy((W/2)-24 , H-1 ) ;
    cout << "Copyright @ 2025 Muhammed M. All Rights Reserved" ;
    gotoxy((W/2)-7 , H ) ;
    cout << "Buy me a Coffee"; 
    gotoxy((W/2)-19 , H+1) ;
    cout << "Instapay : " ;
    SetColor(15) ;
    cout << "mohamedqnb9935@instapay.com" ;
    SetColor(7) ;
    getch() ;
    system("cls") ;
}

void ControlMessege(int W , int H, int& direction )
{
    SetColor(8) ;
    gotoxy((W/2)-13 , H/2 - 3 ) ;
    cout << "<.. Gameplay Controls ..>" ;
    gotoxy((W/2)-22 , H/2 -1 ) ;
    cout << "Move with Arrows ( UP , DOWN , RIGHT , LEFT )" ;
    gotoxy((W/2)-11 , H/2 + 1 ) ;
    cout << "+ , - to Control Speed" ;
    gotoxy((W/2)-8 , H/2 + 3 ) ;
    cout << "ESC to Exit Game" ;
    getch() ;
    SetColor(0) ;
    gotoxy((W/2)-13 , H/2 - 3 ) ;
    cout << "<.. Gameplay Controls ..>" ;
    gotoxy((W/2)-22 , H/2 -1 ) ;
    cout << "Move with Arrows ( UP , DOWN , RIGHT , LEFT )" ;
    gotoxy((W/2)-11 , H/2 + 1 ) ;
    cout << "+ , - to Control Speed" ;
    gotoxy((W/2)-8 , H/2 + 3 ) ;
    cout << "ESC to Exit Game" ;
    SetColor(7) ;
}

void EndMessage(int W , int H , int GO) 
{
    if(GO == 999) 
    {
        gotoxy((W/2)-9 , H/2 - 2 ) ;
        SetColor(6) ;
        cout << "!! GAME OVER !!" ;
        
    }
    gotoxy((W/2)-9 , H/2 ) ;
    SetColor(7) ;

    if(Fruit::GetScore() < 10)
    {
        cout << "Your Score = 00" << Fruit::GetScore() ;
    }
    else if(Fruit::GetScore() < 100)
    {
        cout << "Your Score = 0" << Fruit::GetScore() ;
    }
    else {cout << "Your Score = " << Fruit::GetScore() ;}

    gotoxy((W/2)-15 , H/2 + 2 ) ;
    SetColor(15) ;
    cout << "==> Press Any Key To Exit <==" ;
    SetColor(7) ;
    getch() ;
}

void FramePrint(int W , int H , Game* G1)
{
    int x = 0 ;
    int y = 0 ;

    char RightSide = ']' ;
    char LeftSide = '[' ;
    char Top = '=' ;
    char Bottom = '=' ;
    int Delay = 0 ;


    system("cls") ;
    
    for ( x = 0 ; x < W+1 ; x++ ) 
    {
        gotoxy(x , y) ;
        cout << Top ;
        Sleep(Delay) ;
    }
    for ( y = 0 ; y <= H ; y++ ) 
    {
        gotoxy(x , y) ;
        cout << RightSide ;
        Sleep(Delay) ;

    }
    gotoxy(x , y) ;
    cout << RightSide ;
    x-- ;
    for (  ; x > 0 ; x-- ) 
    {
        
        gotoxy(x , y) ;
        cout << Bottom ;
        Sleep(Delay) ;

    }
    for (  ; y >= 0 ; y-- ) 
    {
        gotoxy(x , y) ;
        cout << LeftSide ;
        Sleep(Delay) ;
    }

    gotoxy(10,0) ;
    SetColor(15) ;
    cout << " Score : " << Fruit::GetScore() << " " ; 
    SetColor(7) ;

    gotoxy(W-20,0) ;
    SetColor(15) ;
    cout << " Speed : " << 100 - G1->GetSpeed() << " " ; 
    SetColor(7) ;
}

Fruit RandomFruitGenerator(int W , int H) 
{

    int xr , yr ;

    static random_device rd ;
    static mt19937 gen(rd());

    uniform_int_distribution <> distrX( 1, W );
    uniform_int_distribution <> distrY( 1, H );

    xr = distrX(gen);
    yr = distrY(gen);

    return Fruit( xr , yr ) ;

}

void FruitReBirth(Game* G1 , Fruit* F1 , int* x , int* y , int BD )
{
    

    *F1 = RandomFruitGenerator( G1->GetWidth() , G1->GetHeight() ) ; 
    for(int i = 0 ; i <= BD ; i ++)
    {
        if( F1->GetX() == x[i] && F1->GetY() == y[i] )
        {*F1 = RandomFruitGenerator( G1->GetWidth() , G1->GetHeight() ) ; i = -1 ; }
        
    }
    gotoxy( F1->GetX() , F1->GetY() ) ;
    SetColor(4) ;
    cout << F1->GetGUI() ;
    gotoxy(10,0) ;
    SetColor(15) ;
    cout << " Score : " << Fruit::GetScore() << " " ; 
    SetColor(7) ;

    
}

SnakeHead RandomSnakeGenerator(int W , int H) 
{

    int xr , yr ;

    static random_device rd ;
    static mt19937 gen(rd());

    uniform_int_distribution <> distrX( 1, W );
    uniform_int_distribution <> distrY( 1, H );

    xr = distrX(gen);
    yr = distrY(gen);

    SnakeHead SnTMP(xr , yr ) ;

    return SnTMP ;

}

void NewFunction(int bodycount, int *SnakeHistory_X, int *SnakeHistory_Y, SnakeHead &SH1, Game &G1, int &GameOver, int &direction, int& lastD , int Body_GUI, int &retFlag , char BodyGUI)
{
    retFlag = 1;
    if (bodycount > 0)
    {
        gotoxy(SnakeHistory_X[bodycount], SnakeHistory_Y[bodycount]);
        cout << " ";
    }
    else
    {
        gotoxy(SH1.GetX(), SH1.GetY());
        cout << " ";
    }

    for (int i = bodycount; i >= 1; i--)
    {
        SnakeHistory_X[i] = SnakeHistory_X[i - 1];
        SnakeHistory_Y[i] = SnakeHistory_Y[i - 1];
    }

    if ( BodyGUI == 'A' ) // UP
    {
        if (SH1.GetY() == 1)
        { SH1.SetY(G1.GetHeight()); }
        else
        { SH1.DecY(); }
    }
    if ( BodyGUI == 'V' ) // DOWN
    {
        if ( SH1.GetY() == G1.GetHeight() ) 
        { SH1.SetY(1) ; }
        else 
        { SH1.IncY() ; }
    }
    if ( BodyGUI == '>' ) // RIGHT
    {
        if ( SH1.GetX() == G1.GetWidth()  ) 
        { SH1.SetX(1) ; }
        else 
        { SH1.IncX() ; }
    }
    if ( BodyGUI == '<' ) // LEFT
    {
        if ( SH1.GetX() == 1  ) 
        { SH1.SetX(G1.GetWidth()) ; }
        else 
        { SH1.DecX() ; }
    }


    SnakeHistory_X[0] = SH1.GetX();
    SnakeHistory_Y[0] = SH1.GetY();

    for (int i = 1; i <= bodycount; i++)
    {
        if (SH1.GetX() == SnakeHistory_X[i] && SH1.GetY() == SnakeHistory_Y[i])
        {
            GameOver = 999;
            break;
        }
    }
    if (GameOver == 999)
    {
        direction = 27;
        {
            retFlag = 2;
            return;
        };
    }

    gotoxy(SH1.GetX(), SH1.GetY());
    SetColor(10);
    cout << BodyGUI; 



    if (bodycount > 0)
    {
        gotoxy(SnakeHistory_X[1], SnakeHistory_Y[1]);
        SetColor(10);
        cout << (char)Body_GUI;
        SetColor(7);
    }
}

void GetValidInput(int& direction)
{
    direction = getch() ;
    while (direction != 43 &&direction != 45 && 
            direction != 27 && direction != 0 &&direction != 224 )
        {
            direction = getch() ;
        }
    if (direction == 0 || direction == 224 ) 
    {
        direction = getch() ;
        while (direction != 72 &&direction != 80 &&direction != 75 && 
                direction != 77)
            {
                direction = getch() ;
            }
    }
}

void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ClearKeyboardBuffer() 
{
    while ( _kbhit() ) 
        { getch() ; }
}

void HideCursor() 
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}








