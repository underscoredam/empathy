//
// Created by damo on 2/5/16.
//

#ifndef EMPATHY_LIFEEVENT_CWAVE_DATA_H
#define EMPATHY_LIFEEVENT_CWAVE_DATA_H

#define EMPATHY_CWAVE_MAX_RADIUS 2.25

#include <math.h>
#include "../life_event.hpp"
#include "../../Utils/Color.h"
#include "../../PureMath/Wave.h"
#include <vector>
class LifeEvent_CWave_data : public LifeEvent , public Color, public Wave{

public:
    //constructors
    LifeEvent_CWave_data();

private:

    GLuint VAO;
    GLuint VBO;

    std::vector<GLfloat> vertices;
public:
    virtual void onInit() override;

protected:
    virtual void onRun(GLfloat delTime) override;

public:
    virtual void onDestroy() override;

    virtual void draw() override;
};


#endif //EMPATHY_LIFEEVENT_CWAVE_DATA_H
