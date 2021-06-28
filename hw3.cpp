#include<iostream>
#include<string>

using namespace std;

const int MAX = 100;

struct Point
{
  int row; // 행
  int col;  // 열
  int distance; // 시작점으로부터 거리
};
	
template<class ItemType>
class QueType  // Queue
{
public:
	QueType( ) 
	{
		maxQueSize = 501;
		front = 0;  rear = 0;
		items = new ItemType[maxQueSize];               // dynamically allocates
	}

	QueType( int max )	// PARAMETERIZED CONSTRUCTOR
	{
		maxQueSize = max + 1;
 		front = 0;
		rear = 0;
		items = new ItemType[maxQueSize];               // dynamically allocates
	}

	~QueType( ) 		// DESTRUCTOR
	{
		delete [ ] items;          // deallocates array
	}
    
	bool IsEmpty() const
	{
		return ( rear == front );
	}

	bool IsFull() const
	{							
		return ( (rear + 1) % maxQueSize == front );    // WRAP AROUND
	}

	void Enqueue( ItemType item )
	{
		if( IsFull() )
		{
		   cout << "Error: Queue is full \n"; // 예외처리
	      return;
	  }
	    items[rear] = item;
	    rear = (rear + 1) % maxQueSize; // WRAP AROUND
	}

	void Dequeue( ItemType&  item )
	{		
	     if( IsEmpty() )
	    {
		   cout << "Error: Queue is empty \n"; // 예외처리
	        return;
	    }
	    item = items[front];
	   front = (front + 1) % maxQueSize;    // <-> back = (back + 1) % maxQueSize
	}

private:
	int front;
	int rear;
	int maxQueSize;  		
	ItemType* items;	   // DYNAMIC ARRAY IMPLEMENTATION
};


////////////////////////////////////////////////////////////////////////////////

int main(){

	QueType<struct Point> Q;

	bool map[MAX][MAX];  // 미로
	int visited[MAX][MAX]; // 시작점으로부터 도달(방문)했는지를 나타냄  

	int row_Size, col_Size;
	Point currentPoint;  // 현재 점
	Point nextPoint;
	int i, j;

	cout << "지도의 행, 열 입력: ";
	cin >> row_Size >> col_Size;  // 행의 개수와 열의 개수 입력
	cout << endl;

	// 미로는 2차원 배열 map에 저장됨: 1은 막혀있음을, 0은 막혀있지 않음을 나타냄
	// 미로의 오른쪽 경계는 열의 값이 col_Size-1, 왼쪽 경계는 열의 값이 0임
	// 미로의 위쪽 경계는 행의 값이 0임, 아래쪽 경계는 행의 값이 row_Col-1임
	cout << "지도 입력" << endl;
	for (i = 0; i < row_Size; i++)
		for (j = 0; j < col_Size; j++)
			cin >> map[i][j];     // 미로의 각 점의 정보 (0: 막혀있지 않음/1:막혀있음) 입력

	cout << endl;

	for (i = 0; i < row_Size; i++)
		for (j = 0; j < col_Size; j++)
			visited[i][j] = 0;   // 미로의 모든 점은 도달(방문)하지 않은 것으로 초기화

	int start_row, start_col;

	cout << "시작 지점 입력: ";
	cin >> start_row >> start_col;  // 시작 점 (행, 열) 입력
	cout << endl;

	if(map[start_row][start_col] == 1){
		cout << "Error: Start point is blocked" << endl;
		return 1;
	}

	currentPoint.row = start_row;   // 현재 점을 시작점으로 초기화
	currentPoint.col = start_col;
	currentPoint.distance = 0;

	// 시작점에서 가까운 순서대로 도달하는 점을 찾는다.
	// 이를 위하여 시작점으로부터 도달한 점들을 큐로 관리한다. 
	// 먼저 도달한 점에 대하여 상하좌우로 인접한 점들을 본다.  

	// 도달했다는 표시를 시작점에 함
	visited[start_row][start_col] = 1; // 시작점 도착 표시는 0이 아닌 값으로 저장
	Q.Enqueue(currentPoint);  // 현재 도달한 점(시작점)을 큐에 넣는다.

	Point Last[100];  // Last[]: 가장 마지막 지점들을 저장
	int numbers = 1;  // numbers: 

	int x = 0;
	while(!Q.IsEmpty()) 
	{ // 현재 도달한 점들 중 시작점으로부터 가장 거리가 짧은 점을 얻음
		Q.Dequeue(currentPoint); 

		bool isLast = true;  // isLast: 가장 마지막 지점일 경우 true;

		// 현재 점에서 상우하좌 4 방향으로 도달가능한 점을 봄
		 // 현재 점의 위쪽을 봄
		if(currentPoint.row > 0) // 현재 점이 위쪽 경계에 있지 않으면
		{
		  // 위쪽 점이 도달되지 않았고 막혀있지 않으면
		 if (visited[currentPoint.row - 1][currentPoint.col] == 0 &&
		    map[currentPoint.row - 1][currentPoint.col] == 0) 
		 {
			   // 다음 도달 점(현재 점 위에 있는 점)의 위치를 계산함

			 isLast = false;
			 numbers++;

		    nextPoint.row = currentPoint.row-1;
		    nextPoint.col = currentPoint.col;
		     nextPoint.distance = currentPoint.distance+1; // 다음 도달 점의 거리를 1 증가
		     // 도달하였다는 것을 표시를 함
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		// 현재 점의 오른쪽을 봄 
		 if(currentPoint.col < col_Size-1) // 현재 점이 오른쪽 경계에 있지 않으면
		 {
		   // 오른쪽 점이 도달되지 않았고 막혀있지 않으면
		   if (visited[currentPoint.row][currentPoint.col+1] == 0 &&
		      map[currentPoint.row][currentPoint.col+1] == 0) 
		   {
			   isLast = false;
			   numbers++;

		     nextPoint.row = currentPoint.row;
		      nextPoint.col = currentPoint.col+1;
		     nextPoint.distance = currentPoint.distance+1; // 다음 도달 점의 거리를 1 증가
		     // 도달하였다는 것을 표시를 함
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		 // 현재 점의 아래쪽을 봄   
		 if(currentPoint.row < row_Size-1) // 현재 점이 아래쪽 경계에 있지 않으면
		 {
		   // 아래쪽 점이 도달되지 않았고 막혀있지 않으면
		   if (visited[currentPoint.row+1][currentPoint.col] == 0 &&
		      map[currentPoint.row+1][currentPoint.col] == 0) 
		   {
			   isLast = false;
			   numbers++;

		     nextPoint.row = currentPoint.row+1;
		      nextPoint.col = currentPoint.col;
		     nextPoint.distance = currentPoint.distance+1; // 다음 도달 점의 거리를 1 증가
		     // 도달하였다는 것을 표시를 함
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		// 현재 점의 왼쪽을 봄   
		 if(currentPoint.col > 0) // 현재 점이 왼쪽 경계에 있지 않으면
		 {
		   // 왼쪽 점이 도달되지 않았고 막혀있지 않으면
		   if (visited[currentPoint.row][currentPoint.col-1] == 0 &&
		      map[currentPoint.row][currentPoint.col-1] == 0) 
		   {
			   isLast = false;
			   numbers++;

		     nextPoint.row = currentPoint.row;
		      nextPoint.col = currentPoint.col-1;
		     nextPoint.distance = currentPoint.distance+1; // 다음 도달 점의 거리를 1 증가
		     // 도달하였다는 것을 표시를 함
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		 // 가장 마지막 지점(더이상 진행 불가)일 경우
		 if(isLast == true){
			Last[x] = currentPoint;
			x++;
		 }

	}

	x--;
	int end_x = x;  // end_x: 가장 마지막 지점의 갯수를 저장
	Point max_equels[100];  // max_equels[100]: 거리의 최대값과 값이 같은 점들을 저장

	int maxvalue = 0;  // maxvalue: 시작점으로부터의 거리의 최대값
	while( x >= 0 ){  // 최대값을 구함
		if(maxvalue < Last[x].distance){  
			maxvalue = Last[x].distance;
			max_equels[0] = Last[x];  // 구한 최대값은 max_equels[0]에 저장함
		}
		x--;
	}

	int y = 0;
	bool isMultiple = false;  // isMultiple: 최대값이랑 값이 같은 점이 여러 개 있으면 true;

	for(int i=1; i<=end_x; i++){
		if(maxvalue == Last[i].distance){
			isMultiple = true;
			max_equels[y] = Last[i];  // 거리의 최대값하고 값이 같은 점들을 저장함
			y++;
		}
	}

	y--;

	cout << "시작 위치에서 갈 수 있는 모든 위치 갯수: " << numbers << endl;

	cout << "가장 멀리 떨어져 있는 점까지의 거리: " << maxvalue << endl;

	cout << "가장 멀리 떨어져 있는 점들: " << "(" << max_equels[0].row << "," << max_equels[0].col << ")";
	
	if(isMultiple == true){  // 최대값하고 값이 같은 점이 있을 경우 그것까지 모두 출력
		for(int i=1; i<=y; i++)
			cout << ", " << "(" << max_equels[i].row << "," << max_equels[i].col << ")";
	}

	cout << endl;

	return 0;
}