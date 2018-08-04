//
//  BackboneProgram.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "BackboneProgram.h"
#include "Arduino.h"



BackboneProgram::BackboneProgram(int defaultState){
    OS_STATE = defaultState;
}

void BackboneProgram::initProgram(){
    pushToState(OS_STATE);
}

void BackboneProgram::run(int delta){
    currentScreen->run(delta);
    checkForStateChange();
}

void BackboneProgram::addScreen(BackboneScreen *bs){
    screens.push_back(bs);
}

void BackboneProgram::checkForStateChange(){
    if (currentScreen->pollForStateChange() != -2){
        int change = currentScreen->pollForStateChange();
        if (change == -1){
            popState(0);
        }
        else if (change >= 0){
            pushToState(change);
        }
    }
}

void BackboneProgram::pushToState(int state){
    stack.push_back(currentScreen);
    
    currentScreen = screens[state];
    currentScreen->init();
    currentScreen->draw();
}

void BackboneProgram::popState(int rip){
    currentScreen = stack.back();
    currentScreen->init();
    currentScreen->draw();
    stack.pop_back();
}

void BackboneProgram::sendMailOut(char *mail, int32_t size){
    if (bufferSize == 0){
        buffer = mail;
        bufferSize = size;
    }
    else{
        freeVar(mail, size);
    }
}

int32_t BackboneProgram::pollForMail(){
    return bufferSize;
}

char* BackboneProgram::getMail(){
    bufferSize = 0;
    return buffer;
}



