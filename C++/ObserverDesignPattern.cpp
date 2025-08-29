#include <iostream>
#include <vector>

using namespace std;


class ISubscriber{

public:
	virtual void update() = 0;
	virtual ~ISubscriber(){}
};

class IChannel{

public:
	virtual void subscribe(ISubscriber *subscriber) = 0;
	virtual void unsubscribe(ISubscriber *subscriber) = 0;
	virtual void notifySubscriber() = 0;

	virtual ~IChannel(){}
};

class Channel : public IChannel{
private:

	vector<ISubscriber*> subscribers;
	string latestVideo;
	string name;

public:
	Channel(const string &name){
		this->name = name;
	}

	void subscribe(ISubscriber *subscriber){
		if(find(subscribers.begin(),subscribers.end(),subscriber) == subscribers.end()){
			subscribers.push_back(subscriber);
		}
	}

	void unsubscribe(ISubscriber *subscriber){
		auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
	}

	void notifySubscriber(){
		for(ISubscriber *sub : subscribers){
			sub->update();
		}
	}

	void uploadVideo(const string &title){
		latestVideo = title;
		cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
		notifySubscriber();
	}

	string getVideoData(){
		return "\nCheckout our new Video : " + latestVideo + "\n";
	}
};

class Subscriber : public ISubscriber{
private:

	string name;
	Channel *channel;

public:

	Subscriber(const string &name,Channel *channel){
		this->name = name;
		this->channel = channel;
	}

	void update(){
		cout << "Hey " << name << "," << this->channel->getVideoData();
	}

};

int main(){

	Channel *channel = new Channel("Rohit Agrawal");

	Subscriber *sub1 = new Subscriber("Aman",channel);
	Subscriber *sub2 = new Subscriber("Tanmay",channel);

	channel->subscribe(sub1);
	channel->subscribe(sub2);

	channel->uploadVideo("LNMIIT Review");

	channel->unsubscribe(sub2);

	channel->uploadVideo("Dark Web");
 
	return 0;
}