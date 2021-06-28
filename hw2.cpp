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

	StackType<string> C;  //C: 연산을 위해 숫자를 저장하는 스텍

	while(true)
	{
		string x;  // x: Postfix 수식을 하나씩 읽어서 저장함
		cin >> x;

		if(x == "=") break;

		if(x == "_"){  // 음수 형태로 변환함 (ex: 45 -> -45)
			string val = C.Top();
			C.Pop();
			val += "*";  // ※ 맨 끝에 '*'이 붙으면 음수라는 뜻 (ex: "15*" = -15)
			C.Push(val);
		}
		else if(x == "+" || x == "-" || x == "*" || x == "/" || x == "%"){
			
			string arr1[2];  // arr1[]: 스텍의 값을 받는 변수
			int arr2[2] = { 0 };  // arr2[]: string에서 int로 변환된 값을 담음
			int dight;  // digit: int형 숫자 한자리씩 저장

			bool isMinus;  // isMinus: 스텍 내의 숫자가 음수이면 true

			for(int i=0; i<=1; i++){

				if( C.IsEmpty() ){  // 두 자리 숫자가 추출되지 않을 경우 error
					cout << "Error: Error in Calculation" << endl;
					return 1;
				}

				arr1[i] = C.Top();
				C.Pop();
				
				isMinus = false;
				int p = 0;
				for(int k = arr1[i].length()-1; k>=0; k--){  // string을 int로 변환함 (ex: "543" -> 3 + 40 + 500)
					
					if(arr1[i].at(k) == '*'){  // 숫자가 음수일 경우
						isMinus = true;
						continue;
					}

					dight = arr1[i].at(k) - 48;
					dight *= pow(10,p);
					arr2[i] += dight;

					p++;
				}

				if(isMinus == true) arr2[i] = arr2[i] * -1;  // 음수일 경우
				
			}

			int result;  // result: 연산 결과를 저장하는 int형 변수
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

			string once_result = "";  // once_result: int에서 string으로 변환된 값이 거꾸로 저장됨 (임시 변수)

			if(isMinus == true) once_result += "*";  // 결과가 음수일 경우 '*'을 붙임

			while(result > 0)  // int를 string으로 변환함 (아스키 코드 사용)
			{
				dight = result % 10;
				char ch = dight + 48;
				once_result += ch;

				result /= 10;
			}

			string real_result = "";  // real_result: string으로 변환된 진짜 값. 다시 스텍에 넣을 값.
			for(int j = once_result.length()-1; j>=0; j--)
				real_result += once_result.at(j);  // 역스트링 기능 사용

			C.Push(real_result);  // 연산 결과를 스텍에 넣어줌

		}
		else{  
			C.Push(x);  // 숫자를 스텍에 넣음
		}
	}

	string final_str = C.Top();
	C.Pop();

	if( !C.IsEmpty() ){  // 연산자가 부족해서 최종 결과과 안나왔을 경우
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