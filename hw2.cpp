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
	StackType<ItemType>()
	{
		topPtr = NULL;
	}

	~StackType<ItemType>()
	{
		NodeType<ItemType>* tempPtr;

		while(topPtr != NULL)
		{
			tempPtr = topPtr;
			topPtr = topPtr->next;
			delete tempPtr;
		}
	}

	bool IsFull() const
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

	bool IsEmpty() const
	{
		if(topPtr == NULL)
			return true;
		else
			return false;
	}

	void Push(ItemType newItem)
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

	void Pop()
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

	ItemType Top()
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

	//while(true){

	StackType<string> C;  //C: ������ ���� ���ڸ� �����ϴ� ����

	while(true)
	{
		string x;  // x: Postfix ������ �ϳ��� �о ������
		cin >> x;

		if(x == "=") break;

		if(x == "_"){  // ���� ���·� ��ȯ�� (ex: 45 -> -45)
			string val = C.Top();
			C.Pop();
			val += "*";  // �� �� ���� '*'�� ������ ������� �� (ex: "15*" = -15)
			C.Push(val);
		}
		else if(x == "+" || x == "-" || x == "*" || x == "/" || x == "%"){
			
			string arr1[2];  // arr1[]: ������ ���� �޴� ����
			int arr2[2] = { 0 };  // arr2[]: string���� int�� ��ȯ�� ���� ����
			int dight;  // digit: int�� ���� ���ڸ��� ����

			bool isMinus;  // isMinus: ���� ���� ���ڰ� �����̸� true

			for(int i=0; i<=1; i++){

				if( C.IsEmpty() ){  // �� �ڸ� ���ڰ� ������� ���� ��� error
					cout << "Error: Error in Calculation" << endl;
					return 1;
				}

				arr1[i] = C.Top();
				C.Pop();
				
				isMinus = false;
				int p = 0;
				for(int k = arr1[i].length()-1; k>=0; k--){  // string�� int�� ��ȯ�� (ex: "543" -> 3 + 40 + 500)
					
					if(arr1[i].at(k) == '*'){  // ���ڰ� ������ ���
						isMinus = true;
						continue;
					}

					dight = arr1[i].at(k) - 48;
					dight *= pow(10,p);
					arr2[i] += dight;

					p++;
				}

				if(isMinus == true) arr2[i] = arr2[i] * -1;  // ������ ���
				
			}

			int result;  // result: ���� ����� �����ϴ� int�� ����
			if(x == "+") result = arr2[1] + arr2[0];
			else if(x == "-") result = arr2[1] - arr2[0];
			else if(x == "*") result = arr2[1] * arr2[0];
			else if(x == "/") result = arr2[1] / arr2[0];
			else if(x == "%") result = arr2[1] % arr2[0];

			isMinus = false;
			if(result < 0){
				result = result * -1;
				isMinus = true;
			}

			string once_result = "";  // once_result: int���� string���� ��ȯ�� ���� �Ųٷ� ����� (�ӽ� ����)

			if(isMinus == true) once_result += "*";  // ����� ������ ��� '*'�� ����

			while(result > 0)  // int�� string���� ��ȯ�� (�ƽ�Ű �ڵ� ���)
			{
				dight = result % 10;
				char ch = dight + 48;
				once_result += ch;

				result /= 10;
			}

			string real_result = "";  // real_result: string���� ��ȯ�� ��¥ ��. �ٽ� ���ؿ� ���� ��.
			for(int j = once_result.length()-1; j>=0; j--)
				real_result += once_result.at(j);  // ����Ʈ�� ��� ���

			C.Push(real_result);  // ���� ����� ���ؿ� �־���

		}
		else{  
			C.Push(x);  // ���ڸ� ���ؿ� ����
		}
	}

	string final_str = C.Top();
	C.Pop();

	if( !C.IsEmpty() ){  // �����ڰ� �����ؼ� ���� ����� �ȳ����� ���
		cout << "Error: Error in Calculation" << endl;
		return 1;
	}

	int len = final_str.length()-1;

	if(final_str.at(len) == '*')
		cout << "The Result: " << "-" << final_str.substr(0,len) << endl;
	else
		cout << "The Result: " << final_str << endl;

	//}

	return 0;
}