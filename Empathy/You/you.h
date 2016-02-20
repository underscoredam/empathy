/*
 * All the life events happen, and You are the one who makes them happen!
 * You handle all the events in life! 
 */

#ifndef EMPATHY_YOU
#define EMPATHY_YOU

 
#include "../LifeEvent/LifeEvent.h"
#include "../global.h"
#include "../Brain/Brain.h"

#include <vector>
class Brain;
class You: public Subscriber{
public:
	std::vector<empathy::life_event::LifeEvent*> lifeEvents;

	You();

	void init();

	void blit();

	void addEvent(empathy::life_event::LifeEvent *);
	void removeEvent(empathy::life_event::LifeEvent *);
	void clearEvents();

	long curTime;
	float lastTime,deltaTime;
	int calcFPS(GLfloat curTime);
	void passTime(GLfloat);
	void setTime(GLfloat);

    virtual void onReceiveEvent(Event &) override;

	std::vector<Brain *> brains;

    void addBrain(Brain * );

	void terminate();
public:
    static You * getInstance(){return instance;}
private:
    static You * instance;
};

#endif