#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class INotification{
public:
	virtual string getContent() const = 0;
	virtual ~INotification(){}
};

class SimpleNotification : public INotification{
private:
	string text;
public:
	SimpleNotification(const string &msg){
		text = msg;
	}

	string getContent() const{
		return text;
	}
};

class INotificationDecorator : public INotification{
protected:
	INotification *notification;

public:

	INotificationDecorator(INotification *n){
		notification = n;
	}

	virtual ~INotificationDecorator() {
        delete notification;
    }

};

class TimeStampDecorator : public INotificationDecorator{
public:
	TimeStampDecorator(INotification *n) : INotificationDecorator(n){}

	string getContent() const{
		return "[2025-04-13 14:22:00] " + notification->getContent();
	}
};

class SignatureDecorator : public INotificationDecorator{
private:
	string signature;
public:

	SignatureDecorator(INotification *n,const string &sig) : INotificationDecorator(n){
		signature = sig;
	}

	string getContent() const override {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};

class IObserver{
public:
	virtual void update() = 0;
	virtual ~IObserver(){}
};

class IObservable{
public:
	virtual void addObserver(IObserver *obs) = 0;
	virtual void removeObserver(IObserver *obs) = 0;
	virtual void notifyObservers() = 0;
	virtual ~IObservable(){}
};

class NotificationObservable : public IObservable{
private:
	vector<IObserver*> observers;
	INotification *currentNotification;

public:

	void addObserver(IObserver *obs){
		observers.push_back(obs);
	}

	void removeObserver(IObserver *obs){
		observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
	}

	void notifyObservers(){
		for(IObserver *obs : observers){
			obs->update();
		}
	}

	void setNotification(INotification* notification){
		if (currentNotification != nullptr) {
            delete currentNotification;
        }
		currentNotification = notification;
		notifyObservers();
	}

	INotification *getNotification(){
		return currentNotification;
	}

	string getNotificationContent(){
		return currentNotification->getContent();
	}
	~NotificationObservable() {
        if (currentNotification != NULL) {
            delete currentNotification;
        }
    }

};

class Logger : public IObserver{
protected:
	NotificationObservable *notificationObservable;

public:

	Logger(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

	void update(){
		cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
	}

};

class INotificationStrategy{
public:
	virtual void sendNotification(string content) = 0;
	virtual ~INotificationStrategy(){}
};


class EmailStrategy : public INotificationStrategy{
private:
	string emailId;
public:
	EmailStrategy(const string &emailId){
		this->emailId = emailId;
	}

	void sendNotification(string content){
		cout << "Sending email Notification to: " << emailId << "\n" << content;
	}
};

class SMSStrategy : public INotificationStrategy {
private:
    string mobileNumber;
public:

    SMSStrategy(string mobileNumber) {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override {
        
        cout << "Sending SMS Notification to: " << mobileNumber << "\n" << content;
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        
        cout << "Sending Popup Notification: \n" << content;
    }
};

class NotificationEngine : public IObserver{
private:
	NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;
public:

	NotificationEngine(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(INotificationStrategy* ns) {
        this->notificationStrategies.push_back(ns);
    }

    void update() {
        string notificationContent = notificationObservable->getNotificationContent();
        for(const auto notificationStrategy : notificationStrategies) {
            notificationStrategy->sendNotification(notificationContent);
        }
    }

};

class NotificationService {
private:
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<INotification*> notifications;

    NotificationService() {
       
        observable = new NotificationObservable();
    }

public:
    static NotificationService* getInstance() {
        if(instance == nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }

   
    NotificationObservable* getObservable() {
        return observable;
    }

    
    void sendNotification(INotification* notification) {
        notifications.push_back(notification);
        observable->setNotification(notification);
    }

    ~NotificationService() {
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;


int main(){

	NotificationService* notificationService = NotificationService::getInstance();

	NotificationObservable* notificationObservable = notificationService->getObservable();
	
	Logger* logger = new Logger(notificationObservable);

	NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

	notificationEngine->addNotificationStrategy(new EmailStrategy("rohit@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9794299299"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimeStampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");
    

    notificationService->sendNotification(notification);


    delete logger;
    delete notificationEngine;

	return 0;
}