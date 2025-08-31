#include<iostream>
#include <vector>

using namespace std;


class Character{
public:
	virtual string getAbilities() = 0;
	virtual ~Character(){}
};

class Mario : public Character{
public:

	string getAbilities(){
		return "Mario";
	}
};

class CharacterDecorator : public Character{
protected:
	Character *character;

public:
	CharacterDecorator(Character *c){
		this->character = c;
	}

	string getAbilities(){
		return character->getAbilities();
	}

};

class HeightUp : public CharacterDecorator{
public:

	HeightUp(Character *c) : CharacterDecorator(c){}

	string getAbilities(){
		return character->getAbilities() + " with height up";
	}
};

class GunPowerUp : public CharacterDecorator{
public:

	GunPowerUp(Character *c) : CharacterDecorator(c){}

	string getAbilities(){
		return character->getAbilities() + " with Gun Shoot";
	}
};

class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() {
        return character->getAbilities() + " with Star Power (Limited Time)";
    }
    
    ~StarPowerUp() {
        cout << "Destroying StarPowerUp Decorator" << endl;
    }
};


int main(){

	Character *mario = new Mario();
	cout << "Basic Character: " << mario->getAbilities() << endl;

	mario = new HeightUp(mario);
	cout << "After HeightUp: " << mario->getAbilities() << endl;

	mario = new GunPowerUp(mario);
	cout << "After GunPowerUp: " << mario->getAbilities() << endl;

	mario = new StarPowerUp(mario);
	cout << "After StarPowerUp: " << mario->getAbilities() << endl;

	delete mario;

	return 0;
}