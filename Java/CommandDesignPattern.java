import java.util.*;
import java.io.*;

interface Command{
    void execute();
    void undo();
}

class Light{
    public void on(){
        System.out.println("Light is ON");
    }

    public void off(){
        System.out.println("Light is OFF");
    }
}

class Fan{
    public void on(){
        System.out.println("Fan is ON");
    }

    public void off(){
        System.out.println("Fan is OFF");
    }
}

class LightCommand implements Command{
    private Light light;

    public LightCommand(Light light){
        this.light = light;
    }

    public void execute(){
        this.light.on();
    }

    public void undo(){
        this.light.off();
    }

}

class FanCommand implements Command{
    private Fan fan;

    public FanCommand(Fan fan){
        this.fan = fan;
    }

    public void execute(){
        this.fan.on();
    }

    public void undo(){
        this.fan.off();
    }
}

class RemoteController{
    
    private static final int cnt = 4;
    private Command buttons[];
    private boolean buttonPressed[];

    public RemoteController(){
        buttons = new Command[cnt];
        buttonPressed = new boolean[cnt];

        for (int i = 0; i < cnt; i++) {
            buttons[i] = null;
            buttonPressed[i] = false; 
        }
    }

    public void setCommand(int idx,Command cmd){
        if(idx >= 0 && idx < cnt ){
            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    public void pressButton(int idx){

        if(idx >= 0 && idx < cnt && buttons[idx] != null){
            if(buttonPressed[idx] == false){
                buttons[idx].execute();
            }else{
                buttons[idx].undo();
            }

            buttonPressed[idx] = !buttonPressed[idx];
        }else {
            System.out.println("No command assigned at button " + idx);
        }
    }
}


public class CommandDesignPattern {
    public static void main(String[] args){

        Light light = new Light();
        Fan fan = new Fan();

        RemoteController remote = new RemoteController();
        remote.setCommand(0, new LightCommand(light));
        remote.setCommand(1, new FanCommand(fan));

        remote.pressButton(0);
        remote.pressButton(0);

        remote.pressButton(1);
        remote.pressButton(1);


    }
}
