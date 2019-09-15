#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h> 
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define MAXSIZE 24
using namespace std;
int map[MAXSIZE][MAXSIZE]={0};//地图 
int over=0;


void initmap()
{
	int i,j;
	for(i=0;i<MAXSIZE;i++)
	for(j=0;j<MAXSIZE;j++)
	if(i==0||j==0||i==MAXSIZE-1||j==MAXSIZE-1)map[i][j]=1;
}

void gotoxy(int x,int y)//光标位置 
{
    COORD pos;
	pos.X=2*x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
 } 
 
 
void printmap()
{
	int i,j;
	for(i=0;i<MAXSIZE;i++)
	{for(j=0;j<MAXSIZE;j++)
	{
		if(map[i][j]==0)
		cout<<"  ";
		else if(map[i][j]==1)
		cout<<"■";
	}cout<<endl;
	}
	
}
 
struct food{
    void newfood();
    int food_x;
    int food_y;
};

void food::newfood(){
	while(1)
	{food_x=rand()%(MAXSIZE-1)+1;
	food_y=rand()%(MAXSIZE-1)+1;
	if(map[food_x][food_y]==0)break;
	}
	map[food_x][food_y]=2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),06);
	gotoxy(food_x,food_y);cout<<"★"; 
	
}
struct snake{
	snake();
	int direction;//方向 
	int L;//长度
	int hand_x[(MAXSIZE-2)*(MAXSIZE-2)];
	int hand_y[(MAXSIZE-2)*(MAXSIZE-2)];
};

snake::snake() {direction=rand()%4+1;L=1;
hand_x[0]=6;hand_y[0]=6;map[hand_x[0]][hand_y[0]]=3;
gotoxy(hand_x[0],hand_y[0]);cout<<"●";
} 

void printsnake(snake &S)
{int i=S.L ;
while(i>1)
{
	S.hand_x[i-1]=S.hand_x[i-2];S.hand_y[i-1]=S.hand_y[i-2];
	i--;
}
}


void playgame(char ch,snake&S){
	switch(ch)
	{case 's':
		if(S.direction!=3)S.direction=1;break;
		case 'a':
			if(S.direction!=4)S.direction=2;break;
			case 'w':
				if(S.direction!=1)S.direction=3;break;
				case 'd': 
					if(S.direction!=2)S.direction=4;break;
	}
}

void exe(snake& S,food& F){
	int i;
	switch(S.direction)
	{case 1://上 
		if(map[S.hand_x[0]][S.hand_y[0]+1]==0)
		{
		    gotoxy(S.hand_x[S.L-1],S.hand_y[S.L-1]);cout<<"  ";
			map[S.hand_x[S.L-1]][S.hand_y[S.L-1]]=0;printsnake(S);
		    S.hand_y[0]+=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";
		}
		else if(map[S.hand_x[0]][S.hand_y[0]+1]==2)
		{
			S.L++;printsnake(S);
		    S.hand_y[0]+=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";F.newfood() ;
		}
	    else if(map[S.hand_x[0]][S.hand_y[0]+1]==1||map[S.hand_x[0]][S.hand_y[0]+1]==3)
		{
			over=1;
		}break;
		case 2://左 
			if(map[S.hand_x[0]-1][S.hand_y[0]]==0)
		{
		    gotoxy(S.hand_x[S.L-1],S.hand_y[S.L-1]);cout<<"  ";
			map[S.hand_x[S.L-1]][S.hand_y[S.L-1]]=0;printsnake(S);
		    S.hand_x[0]-=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";
		}
		else if(map[S.hand_x[0]-1][S.hand_y[0]]==2)
		{
			S.L++;printsnake(S);
		    S.hand_x[0]-=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";F.newfood() ;
		}
	    else if(map[S.hand_x[0]-1][S.hand_y[0]]==1||map[S.hand_x[0]-1][S.hand_y[0]]==3)
		{
			over=1;
		}break;
			case 3://下 
				if(map[S.hand_x[0]][S.hand_y[0]-1]==0)
		{
		    gotoxy(S.hand_x[S.L-1],S.hand_y[S.L-1]);cout<<"  ";
			map[S.hand_x[S.L-1]][S.hand_y[S.L-1]]=0;printsnake(S);
		    S.hand_y[0]-=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";
		}
		else if(map[S.hand_x[0]][S.hand_y[0]-1]==2)
		{
			S.L++;printsnake(S);
		    S.hand_y[0]-=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";F.newfood() ;
		}
	    else if(map[S.hand_x[0]][S.hand_y[0]-1]==1||map[S.hand_x[0]][S.hand_y[0]-1]==3)
		{
			over=1;
		}break;
				case 4://右 
					if(map[S.hand_x[0]+1][S.hand_y[0]]==0)
		{
		    gotoxy(S.hand_x[S.L-1],S.hand_y[S.L-1]);cout<<"  ";
			map[S.hand_x[S.L-1]][S.hand_y[S.L-1]]=0;printsnake(S);
		    S.hand_x[0]+=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";
		}
		else if(map[S.hand_x[0]+1][S.hand_y[0]]==2)
		{
			S.L++;printsnake(S);
		    S.hand_x[0]+=1;map[S.hand_x[0]][S.hand_y[0]]=3;
		    gotoxy(S.hand_x[0],S.hand_y[0]);cout<<"●";F.newfood() ;
		}
	    else if(map[S.hand_x[0]+1][S.hand_y[0]]==1||map[S.hand_x[0]+1][S.hand_y[0]]==3)
		{
			over=1;
		}break;
	}
}

int main()
{
	int x;
	cout<<"注：小写英文键盘输入"<<endl<<"选择速度："<<" 1~7"<<endl;
	cin>>x; 
	//PlaySound(TEXT("C:\\Christophe Lebled - Alpha.wav"),NULL,SND_FILENAME|SND_ASYNC);
	system("CLS");
	srand(time(NULL)) ;
	char ch;
	initmap();
	printmap();
	food F;
	snake S;
	F.newfood() ;
	
	while(over==0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),07);
		Sleep(1000-x*100);
		if(kbhit())
		playgame(ch=getch(),S);
		exe(S,F);
	}
	system("CLS");
	cout<<"game over";
	system("pause");
}
