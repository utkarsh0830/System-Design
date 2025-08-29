import java.util.*;
import java.io.*;

interface IChannel{

    void subscribe(ISubscriber subscriber);
    void unsubscribe(ISubscriber subscriber);
    void notifySubscriber();
}

interface ISubscriber{
    void update();
}

class Channel implements IChannel{
    private String name;
    private List<ISubscriber> subscribers;
    private String latestVideo;

    public Channel(String name) {
        this.name = name;
        this.subscribers = new ArrayList<>();
    }

    @Override
    public void subscribe(ISubscriber subscriber){
        if(!subscribers.contains(subscriber)){
            subscribers.add(subscriber);
        }
    }

    @Override
    public void unsubscribe(ISubscriber subscriber){
        if(subscribers.contains(subscriber)){
            subscribers.remove(subscriber);
        }
    }

    public void notifySubscriber(){
        for(ISubscriber sub : subscribers){
            sub.update();
        }
    }

    public void uploadVideo(String title){
        latestVideo = title;
        System.out.println("\n[" + name + " uploaded \"" + title + "\"]");
        notifySubscriber();
    }

    public String getVideoData(){
        return "\nCheckout our new Video : " + latestVideo + "\n";
    }
}


class Subscriber implements ISubscriber{
    private String name;
    private Channel channel;

    public Subscriber(String name,Channel channel){
        this.name = name;
        this.channel = channel;
    }

    public void update(){
        System.out.println("Hey " + name + "," + channel.getVideoData());
    }
}

public class ObserverDesignPattern{
    public static void main(String[] args){

        Channel channel = new Channel("Utkarsh Agrawal");
        Subscriber sub1 = new Subscriber("Rohit", channel);
        Subscriber sub2 = new Subscriber("Ansh", channel);

        channel.subscribe(sub1);
        channel.subscribe(sub2);

        channel.uploadVideo("Tumhari CHUP");
        channel.unsubscribe(sub1);
        channel.uploadVideo("Saiyaara");
    }
}
