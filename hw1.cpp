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
class StackType  // Stack (Linked��)
{
public:
	StackType<ItemType>()  // ������
	{
		topPtr = NULL;
	}

	~StackType<ItemType>()  // �Ҹ���
	{
		NodeType<ItemType>* tempPtr;

		while(topPtr != NULL)
		{
			tempPtr = topPtr;
			topPtr = topPtr->next;
			delete tempPtr;
		}
	}

	bool IsFull() const  // ������ �� ���ִ���
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

	bool IsEmpty() const  // ������ �������
	{
		if(topPtr == NULL)
			return true;
		else
			return false;
	}

	void Push(ItemType newItem)  // ���ؿ� ���Ҹ� �߰�
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

	void Pop()  // ���ؿ� �ִ� ���Ҹ� ����
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

	ItemType Top()  // �� ������ ���� ��ȯ
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

	StackType<int> S;  // S: r������ ��ȯ�� ���� �����ϴ� ����
	int n;  // n: �Է¹��� 10������ ����
	int r;  // r: 10������ �� ������ ��ȯ�� ������ ����
	
	cout << "Input n and r: ";
	cin >> n >> r;  // n�� r�� �Է¹���

	int out_n = n;  // out_n: �Է¹��� 10������ �ٽ� ��¸� �ϱ� ���� ����

	if( !(n > 0 && r > 0) )  // n,r �� �ϳ��� ����� �ƴ� ��� Error
	{
		cout << "Error: not valid number." << endl;
		return 1;
	}

	if( !( (r <= 9) || (r>=11 && r<=16) ) )  // �߸��� ���� r�� ���� ��� Error
	{
		cout << "Error: not valid number." << endl;
		return 1;
	}

	while(n != 0)  // 10������ r������ ��ȯ�ϴ� ����
	{
		int rem;  // rem: n�� r�� ���� �������� ����
		rem = n % r;
		S.Push(rem);  // �������� ���ؿ� �ϳ��� �־���
		n = n/r;
	}

	cout << "Output - " << out_n << "�� " << r << "���� ǥ��: ";  // �� ��¹�

	while( ! S.IsEmpty() )  // r������ ��ȯ�� ���� �ϳ��� ����ϴ� ����
	{
		int x;  // x: ���ؿ� ����� �� ���Ҹ� ����
		x = S.Top();  // �� ������ ���Ҹ� ��ȯ�� ������

		if(x > 9){  // ���Ұ� 10�̻��� ��� �빮�� ���ĺ����� ��ȯ
			char c = x + 55;  // c: �빮�� ���ĺ��� ���� �� ���
			cout << c;
		}
		else{
			cout << x;
		}

		S.Pop();  // ���Ҹ� �ϳ��� ������
	}

	cout << endl;

	return 0;
}