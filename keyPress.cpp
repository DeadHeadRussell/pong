#include "keyPress.h"

keyPress::keyPress(){
    for(int i=0;i<256;i++){
        keys[i] = false;
    }
}

bool keyPress::check(int key){
    if(keys[key]){
        return true;
    }else{
        return false;
    }
}

void keyPress::setTrue(int key){
    keys[key] = true;
}

void keyPress::setFalse(int key){
    keys[key] = false;
}
