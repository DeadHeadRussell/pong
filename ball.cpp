#include <gl/gl.h>
#include <cstdlib>
#include "ball.h"
#include "paddle.h"

void ball::init(int *you,int *him){
    x = -width/4;
    y = 0;
    xmov = randomMov();
    ymov = randomMov();
    width = .1;
    scoreHim = him;
    scoreYou = you;
    movement = 50;
}

void ball::initAiPadd(paddle *ai){
     aiPadd = ai;
}

float ball::randomMov(){
    float rndNum;
    rndNum = 0;
    while((rndNum > -.005 && rndNum < .005)){
        rndNum = ((float)(rand()%(4+1))-2)/100;
    }
    randNum = rndNum;
    return randNum;
}

void ball::shutdown(){
}

void ball::move(){
    xmov *= 1.001;
    ymov *= 1.001;
    if(x > (2/1.5)){
        x = -width/4;
        y = 0;
        ymov = randomMov();
        xmov = randomMov();
        (*scoreYou)++;
        movement = 50;
    } else if (x <-(2/1.5)){
        x = -width/4;
        y = 0;
        ymov = randomMov();
        xmov = randomMov();
        (*scoreHim)++;
        movement = 50;
    }
    if(y > .95||y < -.95){
        ymov *= -1;
        aiPadd->calcPos();
    }
    if(movement > 0){
        movement--;
    }
    if(movement == 0){
        aiPadd->calcPos();
    }    
    if(movement == 0 || movement == -1){
        movement = -1;
        x += xmov;
        y += ymov;
    }
}

float ball::getx(){
    return x;
}

float ball::getxmov(){
    return xmov;
}

float ball::gety(){
    return y;
}

float ball::getymov(){
    return ymov;
}

float ball::getWidth() {
    return width;
}

void ball::hit(double yspeed){
    xmov *= -1.0001;
    ymov += yspeed/2;
    aiPadd->calcPos();
}
void ball::yhit(){
    ymov *= -1.0001;
}

void ball::reset(){
     x = -width/4;
     y = 0;
     movement = 50;
}

int ball::getHimScore(){
     return *scoreHim;
}

int ball::getYouScore(){
     return *scoreYou;
}

void ball::render(){
    glPushMatrix ();
    glTranslatef(x,y,0.0);
    glBegin (GL_TRIANGLE_STRIP);
    glColor3f (1.0f, 0.0f, 0.0f);
    glVertex3f (-width/2, -width/2, 0);
    glVertex3f (-width/2, width/2, 0);
    glVertex3f (width/2, -width/2, 0);
    glVertex3f (width/2, width/2, 0);
    glEnd ();
    glPopMatrix ();
}

void ball::drawRect(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin (GL_TRIANGLE_STRIP);
    glColor4f (0.0f, 0.0f, 0.0f, 0.4f);
    glVertex3f (-(2/1.5), -1, 0);
    glVertex3f (-(2/1.5), 1, 0);
    glVertex3f ((2/1.5), -1, 0);
    glVertex3f ((2/1.5), 1, 0);
    glEnd ();
    glDisable(GL_BLEND);
}
