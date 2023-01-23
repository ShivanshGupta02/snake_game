#include <iostream>
#include <conio.h>   
#include <windows.h>
#include <time.h>
#include <vector>
using namespace std;

#define MAXSNAKESIZE 100   // maximum size of snake
#define MAXFRAMEX 50       // maximum size of boundary in x-dirextion
#define MAXFRAMEY 30       //maximum size of boundary in y-dirextion

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;  //  co-ordinate system



void gotoxy(int x, int y){  // this function helps us to set cursor position 
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
 void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible cursor, bool visible = 1 - visible cursor
{
	if(size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
} 

class Point{  // class for point 
	private:
		int x;  // value of x co-ordinate
		int y;   // value of y co-ordinate
	public:    // access specifier 
	
		Point(){     // default constructor
			x = y = 10;
		} 
		Point(int x, int y){   // parametrized constructor
			this -> x = x;
			this -> y = y;
		}
		void SetPoint(int x, int y){    // function for setting point 
			this -> x = x;
			this -> y = y;
		}
		int GetX(){  // returns co-ordinate of x-axis
			return x;
		}
		int GetY(){ // returns co-ordinate of y-axis
			return y;
		}
		void MoveUp(){  // decreases the y co-ordinate by one 
			y--;
			if( y < 0 )
				y = MAXFRAMEY;
		}
		void MoveDown(){  // increases the y co-ordinate by one 
			y++;
			if( y > MAXFRAMEY )
				y = 0;
		}
		void MoveLeft(){  // decreases the x co-ordinate by one 
			x--;
			if( x < 0 )
				x = MAXFRAMEX;
		}
		void MoveRight(){  // increases the x co-ordinate by one 
			x++;
			if( x > MAXFRAMEX )
				x = 0;
		}
		void Draw(char ch='O'){  // draws the point which is represented by 'O' on console
			gotoxy(x,y);
			cout<<ch;
		}
		
		void Erase(){  // to erase the point by printing space simply
			gotoxy(x,y);
			cout<<" ";
		}
		void CopyPos(Point &p){  // for copying position
			p.x= x;
			p.y = y;
		}
		int IsEqual(Point *p){  // to compare two points and returns 1 if they match
			if( p->x == x && p->y ==y )
				return 1;
			return 0;
		}
		
};


class Snake{  
 
	vector<Point>body;  // here body of the snake is implemented using vector
	int size;  // size of the snake
	char dir;   //  direction
	Point Fruit;  // represents food point
	int blink;   // bliking status of fruit (value is either 0 or 1) 
 public:
	int state;   // Alive status of snake ( value is either 0 or 1)
	int started;   // starting status of game( value is either 0 or 1)
	public:  
	 
	 
	 Snake(){         // default constructor
	 	size=1; state=0;started=0;
	 	body.push_back({20,20});
	 	Fruit.SetPoint(rand()%MAXFRAMEX,rand()%MAXFRAMEY);  
	 }
	 
	 void Addcell(int x,int y){     // for adding new cell in snake body
	 	body.insert(body.end(),{x,y});
	 	size++;
	 }
	 
	 void TurnUp(){   // used to update private data member 'dir' with w if dir is 's' already it will not be updated by w
	 	if(dir!='s')dir='w';
	 }
	 
	 void TurnDown(){  //used to update private data member 'dir' with s if dir is 'w' already it will not be updated by s
	 	if(dir!='w')dir='s';
	 }
	 
	 void TurnLeft(){  // used to update private data member 'dir' with a if dir is 'd' already it will not be updated by a
	 	if(dir!='d')dir='a';
	 }
	 
	 void TurnRight(){  //used to update private data member 'dir' with a if dir is 'd' already it will not be updated by a
	 	if(dir!='a')dir='d';
	 }
	 
	 int SelfCollision(){  // To check collision of head with vector body of the snake
	 	for(int i=3;i<size;i++){
	 		if(body[0].IsEqual(&body[i])){
	 		    return 1;
			 }
		 }
		 return 0;
	 }
	  
	 void Move(){     // this function mainly clears the console screen and loactes the snake's body cells at new positions
	 	system("cls");
	
	 	if(state==0){
	 		  
			   	cout<< "Game Over";
			   	cout<<"\n\n";
			   	cout<< "Press any key to start the game again";
			   	getch();  // used to hold console screen
			   	state=1;
			   	size=1;
			   		
		 }

	 	for(int i=size-1;i>0;i--){  //  used to update snake body cells with new co-ordinates
	 		body[i-1].CopyPos(body[i]);
		 }
		 
		 switch(dir){
            case 'w':
                body[0].MoveUp();
                break;
            case 's':
                body[0].MoveDown();
                break;
            case 'a':
                body[0].MoveLeft();
                break;
            case 'd':
                body[0].MoveRight();
                break;
            
        }
           
		 
		 if(Fruit.GetX()==body[0].GetX() && Fruit.GetY()==body[0].GetY()){
		 	Addcell(0,0);
		 	Fruit.SetPoint(rand()%MAXFRAMEX,rand()%MAXFRAMEY);
		 }  
		 
		  if(SelfCollision())  
		          state=0;
		 
		 if(!blink){
		 	Fruit.Draw('@');  
		 }
		      
		     
	     blink=!blink;   
        
       for(int i=0;i<size;i++){
       	if(i==0){
       		SetConsoleTextAttribute(console,242);
			   if(dir=='d')
       		       body[0].Draw('>');
       		   else if(dir=='a')
       		       body[0].Draw('<');
       		   else if(dir=='w')
       		       body[0].Draw('^'); 
			   else
			   	body[0].Draw('*');  
			       
		   }
		else{
			SetConsoleTextAttribute(console,121);   // to set new colours for text
			body[i].Draw();
		}   
       	
	   }
	   
	   SetConsoleTextAttribute(console,252);
	   
	   Sleep(80); // used to hold screen for 80 milli seconds
	   
	   
        
	 }	 
	 
};

void WelcomeScreen(){
	SetConsoleTextAttribute(console,121);
//	SetConsoleCursorPosition(console, {20,0});
cout<<"    WELCOME TO C++ SNAKE GAME     "<<endl;
	

cout<<"        /                         "<<endl;
cout<<"       /O                         "<<endl;
cout<<"      /                           "<<endl;
cout<<"     ||~~~~~~~~~~~~~~~~~~~~~~~    "<<endl;
cout<<"      \\                           "<<endl;
cout<<"       \\O                         "<<endl;
cout<<"        \\                         "<<endl;

cout<<"\n\n\n Press any key to start game";
getch();
	}


int main(){
	//random no generation
	setcursor(0,0);
	srand( (unsigned)time(NULL));  // used to generate the sequence of pseudo random integer values
	
	// Testing snake 
	Snake snake;
	WelcomeScreen(); 
	
	snake.state=1;
	snake.started=1;
	char op = 'l';
	do{
		if(kbhit()){
			op = getch();
		}
		switch(op){
			case 'w':
			case 'W':
				snake.TurnUp();
				break;
			
			case 's':
			case 'S':
				snake.TurnDown();
				break;
			
			case 'a':
			case 'A':
				snake.TurnLeft();
				break;
			
			case 'd':
			case 'D':
				snake.TurnRight();
				break;
			
		}
		snake.Move();
	      
	}while(op != 'e');
	
	return 0;
}

