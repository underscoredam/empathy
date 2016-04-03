//
// Created by damo on 2/15/16.
//

#include "JSONBrain.h"
#include "../../Utils/file_utils.h"
#include "../../Libs/cJSON/cJSON_utils.h"

#include "../../LifeEvent/CWave/CWave.h"
#include "../../LifeEvent/CWave/CWave_data.h"
#include "../../LifeEvent/FadeInOut/FadeInOut.h"
#include "../../LifeEvent/MathWave/MathWave_Line.h"
#include "../../LifeEvent/MathWave/MathWave_Para_Circle.h"
#include "../../LifeEvent/MathWave/MathWave_Sine.h"
#include "../../LifeEvent/MathWave/MathWave_Sinc.h"


using namespace std;

void empathy::brain::JSONBrain::runLineNumber(std::string lineID, std::string callerID) {
    std::vector<cJSON*> actions=steps[lineID];
    cout<<"running "<<lineID<<endl;

    for(int i=0;i<actions.size();i++){
        std::string action=cJSON_GetObjectItem(actions[i],"type")->valuestring;
        executeJson(action,actions[i]);
    }
}

empathy::brain::JSONBrain::JSONBrain(std::string fileName) :
        Brain(),
        root(nullptr),
        steps()
{
    std::string filePath=getAssetPath(fileName);
    std::string fileContents=file_read(filePath.c_str());
    root = cJSON_Parse(fileContents.c_str());


    std::string title=cJSON_GetObjectItem(root,"title")->valuestring;
    cout<< "\n\n\n -------------------------- "<<endl;
    cout<<"     Playing "<<title<<endl;
    cout<<" --------------------------"<<endl<<endl<<endl;

    cout<< "\n\n\n -------------------------- "<<endl;
    cout<<"  Built with love just for you :)"<<endl;
    cout<<" --------------------------"<<endl<<endl<<endl;

    cJSON * steps=cJSON_GetObjectItem(root,"steps");

    std::vector<std::string> stepKeys=cJSON_get_keys(steps);
    for(int i=0;i<stepKeys.size();i++){
        std::string key=stepKeys[i];

        cJSON* actionList=cJSON_GetObjectItem(steps,key.c_str());

        std::vector<cJSON*> arrayList;
        if(actionList->type==cJSON_Object)arrayList.push_back(actionList);
        else if(actionList->type==cJSON_Array){
            actionList=actionList->child;
            while(actionList){
                arrayList.push_back(actionList);
                actionList=actionList->next;
            }
        }
        this->steps[key]=arrayList;
    }



}

void empathy::brain::JSONBrain::terminate() {
    empathy::brain::Brain::terminate();

    cJSON_Delete(root);
}

void empathy::brain::JSONBrain::executeJson(const std::string action,cJSON *json) {
    if(action=="audio"){

        std::string name=cJSON_GetObjectItem(json, "name")->valuestring;
        bool instrumental=(bool)cJSON_GetObjectItem(json,"instrumental")->valueint;

        if(instrumental){

            std::string instrument=cJSON_GetObjectItem(json,"instrument")->valuestring;

            if(instrument=="keyboard" || instrument=="piano"){
                playKeyboardAudio(name);
            }
        }
    }else if(action=="goto"){
        std::string stepID=cJSON_GetObjectItem(json,"stepID")->valuestring;
        double after=cJSON_GetObjectItem(json,"in")->valuedouble;

        activateTimeoutForNextLine(stepID,after);
    }else if(action=="create"){
        std::string object=cJSON_GetObjectItem(json,"create")->valuestring;

        //create this new object
        empathy::life_event::LifeEvent * event= createEventFromString(object);

        if(event != nullptr){

            //and pass the options to this object.
            std::vector<std::string> keys=cJSON_get_keys(json);

            for(int i=0;i<keys.size();i++){
                std::string key=keys[i];
                cJSON* value=cJSON_GetObjectItem(json,key.c_str());

                event->decodeJson(key,value);

            }

            //finally add this LifeEvent to the gamescreen.
            addLifeEvent(event);
        }
    }
}


empathy::life_event::LifeEvent *empathy::brain::JSONBrain::createEventFromString(const std::string name) {
    if(name=="cwave"){
        return new empathy::life_event::CWave_data();
    }else if(name=="mathwave_line"){
        return new empathy::life_event::MathWave_Line();
    }else if(name=="mathwave_para_circle"){
        return new empathy::life_event::MathWave_Para_Circle();
    }else if(name=="mathwave_sinc"){
        return new empathy::life_event::MathWave_Sinc();
    }else if(name=="mathwave_sine"){
        return new empathy::life_event::MathWave_Sine();
    }


    return nullptr;
}
