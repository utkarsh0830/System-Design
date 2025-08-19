#include<iostream>
using namespace std;


class WalkableRobot{
public:
	virtual void walk() = 0;
	virtual ~WalkableRobot(){}
};

class NormalWalk : public WalkableRobot{

public:
	void walk() override {
		cout<<"Robot can walk\n";
	}
};

class NoWalk : public WalkableRobot{
public:
	void walk() override{
		cout<<"Robot can't walk\n";
	}
};

class FlyableRobot{
public:
	virtual void fly() = 0;
	virtual ~FlyableRobot(){}
};

class NormalFly : public FlyableRobot{
public:
	void fly() override{
		cout<<"Robot can fly\n";
	}
};

class NoFly : public FlyableRobot{
	void fly() override{
		cout<<"Robot can't fly\n";
	}
};



class TalkableRobot{
public:
	virtual void talk() = 0;
	virtual ~TalkableRobot(){}
};

class NormalTalk : public TalkableRobot{
public:
	void talk() override{
		cout<<"Robot can talk\n";
	}
};

class NoTalk : public TalkableRobot{
public:
	void talk() override{
		cout<<"Robot can't talk\n"; 
	}
};

//Base class

class Robot{
public:

	TalkableRobot *talkableRobot;
	WalkableRobot *walkableRobot;
	FlyableRobot  *flyableRobot;

	Robot(TalkableRobot *t,WalkableRobot *w, FlyableRobot *f){
		this->talkableRobot = t;
		this->walkableRobot = w;
		this->flyableRobot = f;
	}

	void walk(){
		walkableRobot->walk();
	}

	void talk(){
		talkableRobot->talk();
	}

	void fly(){
		flyableRobot->fly();
	}

	virtual void projection() = 0;

};

class CompanionRobot : public Robot{
public:

	CompanionRobot(TalkableRobot *t,WalkableRobot *w, FlyableRobot *f) : Robot(t,w,f){}

	void projection(){
		cout<<"Robot is friendly with the owner\n";
	}

};

class WorkerRobot : public Robot{
public:

	WorkerRobot(TalkableRobot *t,WalkableRobot *w, FlyableRobot *f) : Robot(t,w,f){}

	void projection(){
		cout<<"Robot is a worker\n";
	}
};

int main(){

	Robot *robot1 = new CompanionRobot(new NormalTalk(),new NormalWalk(),new NormalFly());
	Robot *robot2 = new WorkerRobot(new NoTalk(),new NoWalk(),new NoFly());
    cout<<"Robot1 Features: -\n\n";
	robot1->walk();
	robot1->fly();
	robot1->talk();

	robot1->projection();
    cout<<"\nRobot2 Features: -\n\n";
    robot2->walk();
	robot2->fly();
	robot2->talk();
	robot2->projection();


	return 0;
}