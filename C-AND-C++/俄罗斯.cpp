#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
using namespace std;
#define N 26
#define M 22

int map[N][M];
int cubex[4],cubey[4]; 
char control;
int condition,typed,nexttyped; 
int timer=500;
int point=0;

void gotoxy(int x,int y){   
   COORD c;   
   c.X = 2*x ;   
   c.Y = y ;   
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);   
 }     

void initmaps(){
	
	int i,j; 
	for(i=0;i<N;i++)
	for(j=0;j<M;j++)
	{if(i==0||i==N-1){map[i][j]=1;gotoxy(j,i);cout<<"—";	}
	else if(j==0||j==M-1){map[i][j]=1;gotoxy(j,i);cout<<" |";	}
	else {map[i][j]=0;gotoxy(j,i);cout<<"  ";	} 
	}
	gotoxy(M+3,4);cout<<"point:"<<point;
	gotoxy(M+3,7);cout<<"下一个：";
	nexttyped=rand()%5+1;;
}

void newcube(){
	void down();
	int i,j;
	typed= nexttyped;
	nexttyped=rand()%5+1;
	condition=3;timer=500;
	
	switch(nexttyped)
	{
		case 1:cubex[0]=M+4;cubey[0]=9;
				cubex[1]=M+5;cubey[1]=9;
				cubex[2]=M+4;cubey[2]=10;
				cubex[3]=M+5;cubey[3]=10;break;
		case 2:
			cubex[0]=M+4;cubey[0]=9;
				cubex[1]=M+4;cubey[1]=10;
				cubex[2]=M+4;cubey[2]=11;
				cubex[3]=M+4;cubey[3]=12;break;
		case 3:
			cubex[0]=M+4;cubey[0]=9;
				cubex[1]=M+4;cubey[1]=10;
				cubex[2]=M+3;cubey[2]=10;
				cubex[3]=M+5;cubey[3]=10;break;
		case 4:
			cubex[0]=M+4;cubey[0]=9;
				cubex[1]=M+5;cubey[1]=9;
				cubex[2]=M+3;cubey[2]=9;
				cubex[3]=M+3;cubey[3]=10;break;
		case 5:
			cubex[0]=M+4;cubey[0]=9;
				cubex[1]=M+5;cubey[1]=9;
				cubex[2]=M+3;cubey[2]=9;
				cubex[3]=M+5;cubey[3]=10;break;
		default:
			cubex[0]=M+4;cubey[0]=9;
				cubex[1]=M+5;cubey[1]=9;
				cubex[2]=M+4;cubey[2]=10;
				cubex[3]=M+5;cubey[3]=10;break;
	}
	for(i=9;i<13;i++)
	for(j=M+3;j<M+6;j++)
	{gotoxy(j,i);cout<<"  ";
	}
	for(i=0;i<4;i++)
	{gotoxy(cubex[i],cubey[i]);cout<<"■";	}
	
	switch(typed)
	{
		case 1:cubex[0]=M/2;cubey[0]=1;
				cubex[1]=M/2+1;cubey[1]=1;
				cubex[2]=M/2;cubey[2]=2;
				cubex[3]=M/2+1;cubey[3]=2;break;
		case 2:
			cubex[0]=M/2;cubey[0]=1;
				cubex[1]=M/2;cubey[1]=2;
				cubex[2]=M/2;cubey[2]=3;
				cubex[3]=M/2;cubey[3]=4;break;
		case 3:
			cubex[0]=M/2;cubey[0]=1;
				cubex[1]=M/2;cubey[1]=2;
				cubex[2]=M/2-1;cubey[2]=2;
				cubex[3]=M/2+1;cubey[3]=2;break;
		case 4:
			cubex[0]=M/2;cubey[0]=1;
				cubex[1]=M/2+1;cubey[1]=1;
				cubex[2]=M/2-1;cubey[2]=1;
				cubex[3]=M/2-1;cubey[3]=2;break;
		case 5:
			cubex[0]=M/2;cubey[0]=1;
				cubex[1]=M/2+1;cubey[1]=1;
				cubex[2]=M/2-1;cubey[2]=1;
				cubex[3]=M/2+1;cubey[3]=2;break;
		default:
			cubex[0]=M/2;cubey[0]=1;
				cubex[1]=M/2+1;cubey[1]=1;
				cubex[2]=M/2;cubey[2]=2;
				cubex[3]=M/2+1;cubey[3]=2;break;
	}
	for(i=0;i<4;i++)
	{gotoxy(cubex[i],cubey[i]);cout<<"■";map[cubey[i]][cubex[i]]=2;	}

} 

void avoidcube(){
	int i ,j,k,l;
	for(i=1;i<N-1;i++)
	for(j=1;j<M-1;j++)
	{
	if(map[i][j]==0)break;
	if(j==M-2)
	{
	for(l=1;l<M-1;l++)
	{map[i][l]=0;gotoxy(l,i);cout<<"  ";
	}
	
	for(l=i-1;l>=1;l--)
	for(k=1;k<M-1;k++)
	{
	if(map[l][k]==1)
	{	map[l][k]=0;gotoxy(k,l);cout<<"  ";
		map[l+1][k]=1;gotoxy(k,l+1);cout<<"■";
	}
	}
	point++;gotoxy(M+3,4);cout<<"point:"<<point;
	break;
	}
		
	}
}

int wall(){
	int min;
	for(int i=0;i<4;i++)
	{
	if(cubex[i]<=2)min=cubex[i];
	else if(cubex[i]==M-2)min=-1;
	if(cubey[i]==1)min=0;
	if(cubey[i]+1==N-1)min=4;
	}
	return min;
}

void change()//状态condition;墙wall； 
{
	int flag=wall();
	int i;//temp=condition;
	if(flag==0||flag==4)return;
	condition=(condition+1)%4;
	
	switch(typed)
	{
		//case 1:condition=temp;return;
		case 2:
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";	}
			if(condition==0||condition==2){
			cubex[0]++;cubey[0]++;
			cubex[2]--;cubey[2]--;
			cubex[3]-=2;cubey[3]-=2;
			}
			else if(condition==1||condition==3){
			cubex[0]--;cubey[0]--;
			cubex[2]++;cubey[2]++;
			cubex[3]+=2;cubey[3]+=2;	
			}
			if(flag==1)for(i=0;i<4;i++)cubex[i]+=2;
			else if(flag==2)for(i=0;i<4;i++)cubex[i]+=1;
			else if(flag==-1)for(i=0;i<4;i++)cubex[i]-=1;
			
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";}
			break;
		case 3:
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";	}
			cubex[2]=cubex[0];cubey[2]=cubey[0];
			cubex[0]=cubex[3];cubey[0]=cubey[3];
			if(condition==0){cubex[3]--;cubey[3]++;		}
			else if(condition==1){cubex[3]--;cubey[3]--;if(flag==1)for(i=0;i<4;i++)cubex[i]+=1;		}
			else if(condition==2){cubex[3]++;cubey[3]--;		}
			else if(condition==3){cubex[3]++;cubey[3]++;if(flag==-1)for(i=0;i<4;i++)cubex[i]-=1;		}
			
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";}
			break;
		case 4:
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";	}
			if(condition==0){
			cubex[1]--;cubey[1]++;
			cubex[2]++;cubey[2]--;
			cubey[3]-=2;
					}
			else if(condition==1){
			cubex[1]--;cubey[1]--;
			cubex[2]++;cubey[2]++;
			cubex[3]+=2;
			if(flag==-1)for(i=0;i<4;i++)cubex[i]-=1;
					}
			else if(condition==2){
			cubex[1]++;cubey[1]--;
			cubex[2]--;cubey[2]++;
			cubey[3]+=2;
				}
			else if(condition==3){
			cubex[1]++;cubey[1]++;
			cubex[2]--;cubey[2]--;
			cubex[3]-=2;
			if(flag==1)for(i=0;i<4;i++)cubex[i]+=1;
				}
			
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";}
			break;
		case 5:
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";	}
			if(condition==0){
			cubex[1]--;cubey[1]++;
			cubex[2]++;cubey[2]--;
			cubex[3]-=2;
					}
			else if(condition==1){
			cubex[1]--;cubey[1]--;
			cubex[2]++;cubey[2]++;
			cubey[3]-=2;
			if(flag==-1)for(i=0;i<4;i++)cubex[i]-=1;
					}
			else if(condition==2){
			cubex[1]++;cubey[1]--;
			cubex[2]--;cubey[2]++;
			cubex[3]+=2;
				}
			else if(condition==3){
			cubex[1]++;cubey[1]++;
			cubex[2]--;cubey[2]--;
			cubey[3]+=2;
			if(flag==1)for(i=0;i<4;i++)cubex[i]+=1;
				}
			
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";}
			break;
	}
	
}

void click(char s)
{
	int i,flag=1;
	for(i=0;i<4;i++)
	{
	if(map[cubey[i]][cubex[i]-1]==1)flag=0;
	else if(map[cubey[i]][cubex[i]+1]==1)flag=2;
	}
	switch(s)
	{
		case 'a':if(flag!=0){
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";cubex[i]--;	}
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";		}
		}break;
		case 'd':if(flag!=2){
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";cubex[i]++;	}
			for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";		}
		}break;
		case 'w':
			change();break;
		case 's':
			timer=2;return;
		default:
			return;
		
	}
	Sleep(150);
	if(kbhit())
	click(control=getch());
} 


void down(){
	Sleep(timer);
	if(kbhit())
	click(control=getch());
	int i,flag=0;
	for(i=0;i<4;i++)
	{if(map[cubey[i]+1][cubex[i]]==1){flag=1;	}
	}
	if(flag==1)
	{for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=1;}
	if(map[1][M/2]==1){gotoxy(0,N);cout<<"game over"<<endl<<"分数："<<point<<endl;return;}
	avoidcube();newcube();down();
	}
	else 
	{for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=0;gotoxy(cubex[i],cubey[i]);cout<<"  ";cubey[i]++;	}
	for(i=0;i<4;i++){map[cubey[i]][cubex[i]]=2;gotoxy(cubex[i],cubey[i]);cout<<"■";		}
    }
    down();
}


int main(){
	//settextcolor(RGB(0,150,0));
	char s;
	srand(time(NULL));initmaps();
	newcube(); 
	down();
	system("pause");
	return 0;
}
