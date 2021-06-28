#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

template <class ItemType>
struct NodeType
{
	ItemType  info;
	NodeType<ItemType>* next;
};	

template <class ItemType>
class StackType  // Stack (Linked형)
{
public:
	StackType<ItemType>()  // 생성자
	{
		topPtr = NULL;
	}

	~StackType<ItemType>()  // 소멸자
	{
		NodeType<ItemType>* tempPtr;

		while(topPtr != NULL)
		{
			tempPtr = topPtr;
			topPtr = topPtr->next;
			delete tempPtr;
		}
	}

	bool IsFull() const  // 스텍이 꽉 차있는지
	{
		NodeType<ItemType>* location;

		try
		{			
			location = new NodeType<ItemType>;
			delete location;
			return false;
		}
		catch(std::bad_alloc exception)
		{
			return true;
		}
	}

	bool IsEmpty() const  // 스텍이 비었는지
	{
		if(topPtr == NULL)
			return true;
		else
			return false;
	}

	void Push(ItemType newItem)  // 스텍에 원소를 추가
	{
		if( IsFull() )
			cout << "Error: the stack is full." << endl;
		else
		{
			NodeType<ItemType>*  location;
			location = new NodeType<ItemType>;
			location->info = newItem;
			location->next = topPtr;
			topPtr = location;
		}
	}

	void Pop()  // 스텍에 있는 원소를 제거
	{
		if( IsEmpty() )
			cout << "Error: the stack is full." << endl;
		else
		{
			NodeType<ItemType>*  tempPtr;

			tempPtr = topPtr;
			topPtr = topPtr->next;
			delete tempPtr;
		}
	}

	ItemType Top()  // 맨 마지막 원소 반환
	{
		if( IsEmpty() )
			cout << "Error: the stack is full." << endl;
		else
			return topPtr->info;
	}


private:
	NodeType<ItemType>* topPtr;
};


int main(){

	StackType<int> S;  // S: r진수로 변환된 값을 저장하는 스텍
	int n;  // n: 입력받을 10진수를 저장
	int r;  // r: 10진수를 몇 진수로 변환할 것인지 저장
	
	cout << "Input n and r: ";
	cin >> n >> r;  // n과 r을 입력받음

	int out_n = n;  // out_n: 입력받은 10진수를 다시 출력만 하기 위한 변수

	if( !(n > 0 && r > 0) )  // n,r 중 하나라도 양수가 아닐 경우 Error
	{
		cout << "Error: not valid number." << endl;
		return 1;
	}

	if( !( (r <= 9) || (r>=11 && r<=16) ) )  // 잘못된 값이 r에 들어갔을 경우 Error
	{
		cout << "Error: not valid number." << endl;
		return 1;
	}

	while(n != 0)  // 10진수를 r진수로 변환하는 과정
	{
		int rem;  // rem: n을 r로 나눈 나머지를 저장
		rem = n % r;
		S.Push(rem);  // 나머지를 스텍에 하나씩 넣어줌
		n = n/r;
	}

	cout << "Output - " << out_n << "의 " << r << "진수 표현: ";  // 선 출력문

	while( ! S.IsEmpty() )  // r진수로 변환된 값을 하나씩 출력하는 과정
	{
		int x;  // x: 스텍에 저장된 각 원소를 받음
		x = S.Top();  // 맨 마지막 원소를 반환해 저장함

		if(x > 9){  // 원소가 10이상인 경우 대문자 알파벳으로 변환
			char c = x + 55;  // c: 대문자 알파벳을 담은 후 출력
			cout << c;
		}
		else{
			cout << x;
		}

		S.Pop();  // 원소를 하나씩 삭제함
	}

	cout << endl;

	return 0;
}