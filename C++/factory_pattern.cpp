#include<iostream>
using namespace std;
	

//Interface Product-1
class Burger{
public:
	virtual void prepare() = 0;
	virtual ~Burger(){};
};

class BasicBurger : public Burger{
public:	
	void prepare() override{
		cout<<"Basic Burger made with potato and vegies.\n";
	}
};

class CheeseBurger : public Burger{
public:
	void prepare() override{
		cout<<"Cheese Burger filled with cheese and vegies.\n";
	}
};

class PremiumBurger : public Burger{
public:
	void prepare() override{
		cout<<"Premium Burger contains paneer, cheese, and vegies\n";
	}
};

//Interface Product-2
class GarlicBread{
public:
	virtual void prepare() = 0;
	virtual ~GarlicBread(){};
};

class BasicGarlicBread : public GarlicBread{
public:
	void prepare(){
		cout<<"Basic GarlicBread Sticks.\n";
	}
};

class CheeseGarlicBread : public GarlicBread{
public:
	void prepare(){
		cout<<"Cheese GarlicBread filled with cheese and corn.\n";
	}
};

class PremiumGarlicBread : public GarlicBread{
public:
	void prepare(){
		cout<<"Premium GarlicBread filled with paneer, cheese and corn.\n";
	}
};

class Factory{
public:
	virtual Burger* createBurger(const string &type) = 0;
	virtual GarlicBread* createGarlicBread(const string &type) = 0;
	virtual ~Factory() {};
};

class BurgerKing : public Factory{
public:

	Burger* createBurger(const string &type){
		//make all types of burger
		if(type == "basic") return new BasicBurger();
		else if(type == "cheese") return new CheeseBurger();
		else if(type == "premium") return new PremiumBurger();
		else{
			cout<<"Item Unavailable.\n";
			return nullptr;
		}
		return nullptr;
	}

	GarlicBread* createGarlicBread(const string &type){
		//make only basic and cheese garlic bread

		if(type == "basic") return new BasicGarlicBread();
		else if(type == "cheese") return new CheeseGarlicBread();
		else{
			cout<<"We don't make premium GarlicBread.\n";
			return nullptr;
		}
		return nullptr;
	}
};	

class Rominus : public Factory{
public:
	Burger* createBurger(const string &type){
		//make only cheese burger

		if(type == "cheese"){
			return new CheeseBurger();
		}else{
			cout<<"Item Unavailable.\n";
			return nullptr;
		}

	}

	GarlicBread* createGarlicBread(const string &type){

		if(type == "basic") return new BasicGarlicBread();
		else if(type == "cheese") return new CheeseGarlicBread();
		else if(type == "premium") return new PremiumGarlicBread();
		else{
			cout<<"Item Unavailable.\n";
			return nullptr;
		}
	}	
};

int main(){

	Factory *burgerKing = new BurgerKing();
    Factory *rominus = new Rominus();

    cout<<"Burger King\n\n";
    Burger* cheeseBurger = burgerKing->createBurger("cheese");
    Burger* premiumBurger = burgerKing->createBurger("premium");

    if(cheeseBurger) cheeseBurger->prepare();
    if(premiumBurger) premiumBurger->prepare();

    GarlicBread* cheeseGarlicBread = burgerKing->createGarlicBread("cheese");
    if(cheeseGarlicBread) cheeseGarlicBread->prepare();

    cout<<"\nRominus\n\n";
    Burger* rominusPremiumBurger = rominus->createBurger("premium");
    Burger* rominusBasicBurger = rominus->createBurger("basic");
    GarlicBread *premiumGarlicBread = rominus->createGarlicBread("premium");

    if(rominusPremiumBurger) rominusPremiumBurger->prepare();
    if(rominusBasicBurger) rominusBasicBurger->prepare();
    if(premiumGarlicBread) premiumGarlicBread->prepare();

    // cleanup
    delete cheeseBurger;
    delete premiumBurger;
    delete cheeseGarlicBread;
    delete rominusPremiumBurger;
    delete rominusBasicBurger;
    delete premiumGarlicBread;
    delete burgerKing;
    delete rominus;



	return 0;
}