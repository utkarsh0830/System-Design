import java.util.*;
import java.io.*;

interface WalkableRobot{
	void walk();
}

class NormalWalk implements WalkableRobot{

	public void walk(){
		System.out.println("Robot can walk.");
	}
}

class NoWalk implements WalkableRobot{
	public void walk(){
		System.out.println("Robot can't walk.");
	}
}

interface TalkableRobot{
	void talk();
}

class NormalTalk implements TalkableRobot{
	public void talk(){
		System.out.println("Robot can talk.");
	}
}

class NoTalk implements TalkableRobot{
	public void talk(){
		System.out.println("Robot can't talk.");
	}
}

interface FlyableRobot{
	void fly();
}

class NormalFly implements FlyableRobot{
	public void fly(){
		System.out.println("Robot can fly.");
	}
}

class NoFly implements FlyableRobot{
	public void fly(){
		System.out.println("Robot can't fly.");
	}
}

abstract class Robot{
	TalkableRobot talkableRobot;
	WalkableRobot walkableRobot;
	FlyableRobot flyableRobot;

	Robot(TalkableRobot t,WalkableRobot w,FlyableRobot f){
		this.talkableRobot = t;
		this.walkableRobot = w;
		this.flyableRobot = f;
	}

	public void walk(){
		walkableRobot.walk();
	}

	public void fly(){
		flyableRobot.fly();
	}

	public void talk(){
		talkableRobot.talk();
	}

	public abstract void projection();
}

class CompanionRobot extends Robot{

	public CompanionRobot(TalkableRobot t,WalkableRobot w,FlyableRobot f){
		super(t,w,f);
	}

	public void projection(){
		System.out.println("Robot is friendly.");
	}


}
	
class WorkerRobot extends Robot{
	public WorkerRobot(TalkableRobot t,WalkableRobot w,FlyableRobot f){
		super(t,w,f);
	}

	public void projection(){
		System.out.println("Robot is Worker.");
	}
}

class Main {
    public static void main(String[] args) {
        System.out.print("Robot1:-\n");

        Robot robot1 = new WorkerRobot(new NormalTalk(),new NormalWalk(), new NoFly());
        Robot robot2 = new CompanionRobot(new NormalTalk(),new NoWalk(),new NormalFly());

        robot1.walk();
        robot1.talk();
        robot1.fly();
        robot1.projection();
        System.out.print("\n");
        System.out.print("Robot2:-\n");

        robot2.walk();
        robot2.talk();
        robot2.fly();
        robot2.projection();

    }
}