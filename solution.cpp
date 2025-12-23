#include <iostream>
#include <string>

//struct Item { //아이템의 구조 원형 class의 public과 거의 동일하게 동작하는 *단순한 구조
//	std::string name_;
//	int price_;
//};

class Item {
public:
	Item(const std::string& name, int price) {//아이템이 받을 값 변수 세팅
		name_ = name;
		price_ = price;
	}
	Item() : name_(""), price_(0) {} //new T[] 를 위해서 기본 생성자가 반드시 필요하다.(포인터의 특징)

	const std::string& GetName() const {
		return name_;
	}

	int GetPrice() const { //
		return price_;
	}

	void Clear() { //아이템 정보 삭제
		name_ = "Null";
		price_ = 0;
	}

	void PrintInfo() const { //아이템 정보 출력
		std::cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << std::endl;
	}

private:
	std::string name_;
	int price_;
};

template<typename T>
class Inventory {
public:
	Inventory(int capacity = 10) : pItems_(nullptr), size_(0), capacity_(capacity)
	{
		/*if (capacity_ <= 0) {
			std::cout << "capacity는 0이하가 될 수 없습니다.";
			capacity_ = 1;
			pItems_ = new T[capacity_];
		}else {
			capacity_ = capacity;
			pItems_ = new T[capacity_];
		}*/ //else가 오지 않으면 다음 구문이 
		if (capacity_ <= 0) { //조건미달일 시 1로 강제 조정
			std::cout << "capacity는 0이하가 될 수 없습니다.";
			capacity_ = 1;
		}
		pItems_ = new T[capacity_];
	}
	~Inventory() { //소멸자. 사용한 포인터를 지우고 비우기(단순한 버전)
		delete[] pItems_;
		pItems_ = nullptr;
	}

	void AddItem(const T& item) {
		if (size_ < capacity_) {
			//Item[size_]; //사이즈 인덱스에 아이템 추가 잘못된 내용
			//T = item//T 내에 아이템 추가
				//size_ += 1;
			pItems_[size_] = item; //배열에 정상적으로 아이템 복사
			size_++; //간략화 한 +1
		}else { //추가하지 않고 추가할 수 없음을 안내
			std::cout << "인벤토리가 꽉 찼습니다!" << std::endl;
		}
	}

	void RemoveLastItem() {
		if (size_ == 0) {
			std::cout << "인벤토리가 비어있습니다." << std::endl;
		}
		else {
			//size_ -= 1;
			pItems_[size_ - 1].Clear();
			size_--;
		}
	}

	int GetSize() const { //아이템 개수 확인
		return size_;
	}

	int GetCapacity() const { //가방 크기 확인
		return capacity_;
	}

	/*void PrintInfo() const { //아이템 정보 출력 이건 아이템 클래스에서 사용
		std::cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << std::endl;
	}*/

	void PrintAllItems() const {
		for (int i = 0; i < size_; i++) {
			//std::cout << i << " : " << Inventory[i].name_ << ", " << Inventory[i].value_ << std::endl;
			std::cout << i << " : "; //i번째 : 
			pItems_[i].PrintInfo();	//i번째 아이템 정보 출력
		}
	}
private:
	T* pItems_;					//사용할 아이템 포인터
	int capacity_;				//최대 용량
	int size_;					//인벤토리에 저장된 아이템의 실제 개수
};



int main() {
	/*Inventory<10> a;
	a.AddItem("sword");*/ //뼈대를 안보고 조정해본것
	//Inventory<Item>(s);로 설정하면 capacity(최대 용량) = s 로 설정 가능하다. [기본 생성자 사용]
	Inventory<Item>* itemInventory = new Inventory<Item>();
	for (int i = 0; i < 11; ++i) {
		itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
	}

	itemInventory->PrintAllItems();

	delete itemInventory;

	return 0;
}