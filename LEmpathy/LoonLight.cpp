//
// Created by damo on 1/29/16.
//

#include "LoonLight.h"

#include <iostream>
using namespace std;
void LoonLight::play(std::string id, bool repeat) {
    MoonLight::play(id, repeat);

    try{
        std::string local=references[id];
        std::string file=BASE+local;

        if(local.size()>0)
            engine->play2D(file.c_str());

    }catch (int i){
        return;
    }

}

void LoonLight::init() {
    MoonLight::init();
    initIrr();

    references=std::map<std::string,std::string>();

//    references[EMPATHY_AUDIO_0A]="keyboard/0A.ogg";
//    references[EMPATHY_AUDIO_0B]="keyboard/0A.ogg";
//    references[EMPATHY_AUDIO_0B]="keyboard/0A.ogg";
//    references[EMPATHY_AUDIO_0B]="keyboard/0A.ogg";
//    references[EMPATHY_AUDIO_OB]="keyboard/0A.ogg";
//    references[EMPATHY_AUDIO_OB]="keyboard/0A.ogg";
//    references[EMPATHY_AUDIO_OB]="keyboard/0A.ogg";


}

void LoonLight::terminate() {
    MoonLight::terminate();

    cout<<"terminating loonlinght"<<endl;
    engine->drop(); // delete engine
}

void LoonLight::initIrr() {
    // start the sound engine with default parameters
    engine = createIrrKlangDevice();

    if (!engine)
    {
        printf("Could not startup engine\n");
    }

//    engine->setSoundVolume(0.05f);
}


std::string LoonLight::BASE="/home/damo/Desktop/dance/Empathy/LEmpathy/assets/empathy/audio/";