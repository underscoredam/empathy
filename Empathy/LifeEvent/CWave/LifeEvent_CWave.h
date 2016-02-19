//
// Created by damo on 2/5/16.
//

#ifndef EMPATHY_LIFEEVENT_CWAVE_H
#define EMPATHY_LIFEEVENT_CWAVE_H


#include <math.h>
#include "../LifeEvent_Collection.h"
#include "../../Utils/Color.h"
#include "../../PureMath/Wave.h"

#define EMPATHY_LIFE_EVENT_CWAVE_CREATE_NEW_WAVE 0
#define EMPATHY_LIFE_EVENT_CWAVE_PERIOD_COMPLETE "EMPATHY_LIFE_EVENT_CWAVE_PERIOD_COMPLETE"

class LifeEvent_CWave : public LifeEvent_Collection,public Color , public Wave{

public:
    LifeEvent_CWave();
    virtual void passTime(GLfloat delTime) override;

protected:
    virtual void onInit() override;

private:
    bool shouldCreateNewWave;

public:
    virtual void decodeJson(std::string key, cJSON *value) override;

public:
    virtual void onReceiveEvent(Event &event) override;
};


#endif //EMPATHY_LIFEEVENT_CWAVE_H
