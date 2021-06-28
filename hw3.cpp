#include<iostream>
#include<string>

using namespace std;

const int MAX = 100;

struct Point
{
  int row; // ��
  int col;  // ��
  int distance; // ���������κ��� �Ÿ�
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
		   cout << "Error: Queue is full \n"; // ����ó��
	      return;
	  }
	    items[rear] = item;
	    rear = (rear + 1) % maxQueSize; // WRAP AROUND
	}

	void Dequeue( ItemType&  item )
	{		
	     if( IsEmpty() )
	    {
		   cout << "Error: Queue is empty \n"; // ����ó��
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

	bool map[MAX][MAX];  // �̷�
	int visited[MAX][MAX]; // ���������κ��� ����(�湮)�ߴ����� ��Ÿ��  

	int row_Size, col_Size;
	Point currentPoint;  // ���� ��
	Point nextPoint;
	int i, j;

	cout << "������ ��, �� �Է�: ";
	cin >> row_Size >> col_Size;  // ���� ������ ���� ���� �Է�
	cout << endl;

	// �̷δ� 2���� �迭 map�� �����: 1�� ����������, 0�� �������� ������ ��Ÿ��
	// �̷��� ������ ���� ���� ���� col_Size-1, ���� ���� ���� ���� 0��
	// �̷��� ���� ���� ���� ���� 0��, �Ʒ��� ���� ���� ���� row_Col-1��
	cout << "���� �Է�" << endl;
	for (i = 0; i < row_Size; i++)
		for (j = 0; j < col_Size; j++)
			cin >> map[i][j];     // �̷��� �� ���� ���� (0: �������� ����/1:��������) �Է�

	cout << endl;

	for (i = 0; i < row_Size; i++)
		for (j = 0; j < col_Size; j++)
			visited[i][j] = 0;   // �̷��� ��� ���� ����(�湮)���� ���� ������ �ʱ�ȭ

	int start_row, start_col;

	cout << "���� ���� �Է�: ";
	cin >> start_row >> start_col;  // ���� �� (��, ��) �Է�
	cout << endl;

	if(map[start_row][start_col] == 1){
		cout << "Error: Start point is blocked" << endl;
		return 1;
	}

	currentPoint.row = start_row;   // ���� ���� ���������� �ʱ�ȭ
	currentPoint.col = start_col;
	currentPoint.distance = 0;

	// ���������� ����� ������� �����ϴ� ���� ã�´�.
	// �̸� ���Ͽ� ���������κ��� ������ ������ ť�� �����Ѵ�. 
	// ���� ������ ���� ���Ͽ� �����¿�� ������ ������ ����.  

	// �����ߴٴ� ǥ�ø� �������� ��
	visited[start_row][start_col] = 1; // ������ ���� ǥ�ô� 0�� �ƴ� ������ ����
	Q.Enqueue(currentPoint);  // ���� ������ ��(������)�� ť�� �ִ´�.

	Point Last[100];  // Last[]: ���� ������ �������� ����
	int numbers = 1;  // numbers: 

	int x = 0;
	while(!Q.IsEmpty()) 
	{ // ���� ������ ���� �� ���������κ��� ���� �Ÿ��� ª�� ���� ����
		Q.Dequeue(currentPoint); 

		bool isLast = true;  // isLast: ���� ������ ������ ��� true;

		// ���� ������ ������� 4 �������� ���ް����� ���� ��
		 // ���� ���� ������ ��
		if(currentPoint.row > 0) // ���� ���� ���� ��迡 ���� ������
		{
		  // ���� ���� ���޵��� �ʾҰ� �������� ������
		 if (visited[currentPoint.row - 1][currentPoint.col] == 0 &&
		    map[currentPoint.row - 1][currentPoint.col] == 0) 
		 {
			   // ���� ���� ��(���� �� ���� �ִ� ��)�� ��ġ�� �����

			 isLast = false;
			 numbers++;

		    nextPoint.row = currentPoint.row-1;
		    nextPoint.col = currentPoint.col;
		     nextPoint.distance = currentPoint.distance+1; // ���� ���� ���� �Ÿ��� 1 ����
		     // �����Ͽ��ٴ� ���� ǥ�ø� ��
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		// ���� ���� �������� �� 
		 if(currentPoint.col < col_Size-1) // ���� ���� ������ ��迡 ���� ������
		 {
		   // ������ ���� ���޵��� �ʾҰ� �������� ������
		   if (visited[currentPoint.row][currentPoint.col+1] == 0 &&
		      map[currentPoint.row][currentPoint.col+1] == 0) 
		   {
			   isLast = false;
			   numbers++;

		     nextPoint.row = currentPoint.row;
		      nextPoint.col = currentPoint.col+1;
		     nextPoint.distance = currentPoint.distance+1; // ���� ���� ���� �Ÿ��� 1 ����
		     // �����Ͽ��ٴ� ���� ǥ�ø� ��
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		 // ���� ���� �Ʒ����� ��   
		 if(currentPoint.row < row_Size-1) // ���� ���� �Ʒ��� ��迡 ���� ������
		 {
		   // �Ʒ��� ���� ���޵��� �ʾҰ� �������� ������
		   if (visited[currentPoint.row+1][currentPoint.col] == 0 &&
		      map[currentPoint.row+1][currentPoint.col] == 0) 
		   {
			   isLast = false;
			   numbers++;

		     nextPoint.row = currentPoint.row+1;
		      nextPoint.col = currentPoint.col;
		     nextPoint.distance = currentPoint.distance+1; // ���� ���� ���� �Ÿ��� 1 ����
		     // �����Ͽ��ٴ� ���� ǥ�ø� ��
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		// ���� ���� ������ ��   
		 if(currentPoint.col > 0) // ���� ���� ���� ��迡 ���� ������
		 {
		   // ���� ���� ���޵��� �ʾҰ� �������� ������
		   if (visited[currentPoint.row][currentPoint.col-1] == 0 &&
		      map[currentPoint.row][currentPoint.col-1] == 0) 
		   {
			   isLast = false;
			   numbers++;

		     nextPoint.row = currentPoint.row;
		      nextPoint.col = currentPoint.col-1;
		     nextPoint.distance = currentPoint.distance+1; // ���� ���� ���� �Ÿ��� 1 ����
		     // �����Ͽ��ٴ� ���� ǥ�ø� ��
		    visited[nextPoint.row][nextPoint.col] = 1; 
		    Q.Enqueue(nextPoint); 
		  }
		 }

		 // ���� ������ ����(���̻� ���� �Ұ�)�� ���
		 if(isLast == true){
			Last[x] = currentPoint;
			x++;
		 }

	}

	x--;
	int end_x = x;  // end_x: ���� ������ ������ ������ ����
	Point max_equels[100];  // max_equels[100]: �Ÿ��� �ִ밪�� ���� ���� ������ ����

	int maxvalue = 0;  // maxvalue: ���������κ����� �Ÿ��� �ִ밪
	while( x >= 0 ){  // �ִ밪�� ����
		if(maxvalue < Last[x].distance){  
			maxvalue = Last[x].distance;
			max_equels[0] = Last[x];  // ���� �ִ밪�� max_equels[0]�� ������
		}
		x--;
	}

	int y = 0;
	bool isMultiple = false;  // isMultiple: �ִ밪�̶� ���� ���� ���� ���� �� ������ true;

	for(int i=1; i<=end_x; i++){
		if(maxvalue == Last[i].distance){
			isMultiple = true;
			max_equels[y] = Last[i];  // �Ÿ��� �ִ밪�ϰ� ���� ���� ������ ������
			y++;
		}
	}

	y--;

	cout << "���� ��ġ���� �� �� �ִ� ��� ��ġ ����: " << numbers << endl;

	cout << "���� �ָ� ������ �ִ� �������� �Ÿ�: " << maxvalue << endl;

	cout << "���� �ָ� ������ �ִ� ����: " << "(" << max_equels[0].row << "," << max_equels[0].col << ")";
	
	if(isMultiple == true){  // �ִ밪�ϰ� ���� ���� ���� ���� ��� �װͱ��� ��� ���
		for(int i=1; i<=y; i++)
			cout << ", " << "(" << max_equels[i].row << "," << max_equels[i].col << ")";
	}

	cout << endl;

	return 0;
}