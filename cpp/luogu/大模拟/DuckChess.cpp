#include<bits/stdc++.h>

using namespace std;

int ques,Start_x,Start_y,End_x,End_y,Flag=0,PlayerID=0;

const int Fx1[4]={1,1,-1,-1},Fy1[4]={1,-1,1,-1},Fx2[6]={0,1,2,1,0,3},Fy2[6]={1,1,2,2,0,2};
int ChessPlace[10][9]={{1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0,1},{1,0,1,0,1,0,1,0,1},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{2,0,2,0,2,0,2,0,2},{2,0,0,0,0,0,0,0,2},{0,0,0,0,0,0,0,0,0},{2,2,2,2,2,2,2,2,2}};
int ChessBoard[10][9]={{5,4,3,2,1,2,3,4,5},{0,0,0,0,0,0,0,0,0},{6,0,0,0,0,0,0,0,6},{7,0,7,0,7,0,7,0,7},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{7,0,7,0,7,0,7,0,7},{6,0,0,0,0,0,0,0,6},{0,0,0,0,0,0,0,0,0},{5,4,3,2,1,2,3,4,5}};

bool CheckPoint(int x,int y){return x>=0&&x<=9&&y>=0&&y<=8;}

void PrintChessType(int Type){
	PlayerID?printf("blue "):printf("red ");if(Type==1) printf("captain;");else if(Type==2) printf("guard;");else if(Type==3) printf("elephant;");
	else if(Type==4) printf("horse;");else if(Type==5) printf("car;");else if(Type==6) printf("duck;");else if(Type==7) printf("soldier;");
}

bool MoveChess(int Now,int Start_x,int Start_y,int End_x,int End_y){
	int Min=min(Fx2[Now],Fy2[Now])-(Fx2[Now]==Fy2[Now]);

	for(int To_x,To_y,Tag,i=0;i<4;i++){
		To_x=Start_x+Fx2[Now]*Fx1[i],To_y=Start_y+Fy2[Now]*Fy1[i],Tag=0;
		if(!CheckPoint(To_x,To_y)) continue;

		if(To_x==End_x&&To_y==End_y){for(int j=1;j<=Min&&!Tag;j++) if(ChessBoard[To_x-j*Fx1[i]][To_y-j*Fy1[i]]) Tag=1;if(!Tag) return true;}
	}
	for(int To_x,To_y,Tag,i=0;i<4;i++){
		To_x=Start_x+Fy2[Now]*Fx1[i],To_y=Start_y+Fx2[Now]*Fy1[i],Tag=0;
		if(!CheckPoint(To_x,To_y)) continue;

		if(To_x==End_x&&To_y==End_y){for(int j=1;j<=Min&&!Tag;j++) if(ChessBoard[To_x-j*Fx1[i]][To_y-j*Fy1[i]]) Tag=1;if(!Tag) return true;}
	}

	return false;
}
bool CheckIllegal(int Start_x,int Start_y,int End_x,int End_y){
	if(Flag||!CheckPoint(Start_x,Start_y)||!CheckPoint(End_x,End_y)) return true;
	if(ChessBoard[Start_x][Start_y]==5){
		int Min_x=min(Start_x,End_x),Max_x=max(Start_x,End_x),Min_y=min(Start_y,End_y),Max_y=max(Start_y,End_y);
		if(Start_x!=End_x&&Start_y!=End_y) return true;
		if(Start_x==End_x){for(int i=Min_y+1;i<Max_y;i++) if(ChessBoard[Start_x][i]) return true;}
		else for(int i=Min_x+1;i<Max_x;i++) if(ChessBoard[i][Start_y]) return true;
		return false;
	}else if(ChessBoard[Start_x][Start_y]==7) return!(MoveChess(0,Start_x,Start_y,End_x,End_y)||MoveChess(1,Start_x,Start_y,End_x,End_y));
	else return (!MoveChess(ChessBoard[Start_x][Start_y]-1,Start_x,Start_y,End_x,End_y));
}

bool GameOver(){
	int Captains=0;
	for(int i=0;i<10;i++) for(int j=0;j<9;j++) if(ChessBoard[i][j]==1) Captains++;
	return Captains<2;
}
bool PutOnTheSpot(int Now){
	int Now_x=0,Now_y=0;
	for(int i=0;!Now_x&&i<10;i++) for(int j=0;!Now_x&&j<9;j++) if(ChessBoard[i][j]==1&&ChessPlace[i][j]==Now) Now_x=i,Now_y=j;
	for(int i=0;i<10;i++) for(int j=0;j<9;j++) if(ChessBoard[i][j]&&ChessPlace[i][j]!=Now) if(!CheckIllegal(i,j,Now_x,Now_y)) return true;
	return false;
}

int main(){
	scanf("%d",&ques);
	for(int Case=0;Case<ques;Case++){
		scanf("%d %d %d %d",&Start_x,&Start_y,&End_x,&End_y);
		if(CheckIllegal(Start_x,Start_y,End_x,End_y)||((PlayerID+1)!=ChessPlace[Start_x][Start_y])||((PlayerID+1)==ChessPlace[End_x][End_y])){printf("Invalid command\n");continue;}
		
		PrintChessType(ChessBoard[Start_x][Start_y]),PlayerID^=1;
		if(ChessPlace[End_x][End_y]) PrintChessType(ChessBoard[End_x][End_y]);
		else printf("NA;");

		ChessPlace[End_x][End_y]=ChessPlace[Start_x][Start_y],ChessBoard[End_x][End_y]=ChessBoard[Start_x][Start_y],ChessPlace[Start_x][Start_y]=ChessBoard[Start_x][Start_y]=0;
		if(GameOver()) Flag=1;
		
		PutOnTheSpot(1)||PutOnTheSpot(2)?printf("yes;"):printf("no;");
		Flag?printf("yes\n"):printf("no\n");
	}

	return 0;
}