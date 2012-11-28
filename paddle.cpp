#include <windows.h>
#include <gl/gl.h>
#include "paddle.h"
#include "ball.h"
#include "keyPress.h"

void paddle::init(float pos, ball *ball1, keyPress *keyed, float *mouse){
    x = pos;
    y = 0;
    ymov = 0;
    yacc = .0005;
    aiymov = .03;
    width = .1;
    height = .35;
    if(x>0){
        xHit = x*((x-width)/x);
    } else if (x<0){
        xHit = x*((x+width)/x);
    }
    mode = false;
    ballPadd = ball1;
    ymouse = mouse;
    key = keyed;
}

void paddle::shutdown(){
}

void paddle::changeMode(){
     mode = !mode;
}

void paddle::hitTest(){
    time = (xHit-(ballPadd->getx()))/(ballPadd->getxmov());
    if(time<1&&time>=0){
        if((ballPadd->gety()-ballPadd->getWidth()/2)<(y+height/2) && 
           (ballPadd->gety()+ballPadd->getWidth()/2)>(y-height/2)){
              ballPadd->hit(yspeed);
        }
    }
    time = -1;
    if((ballPadd->getx()-ballPadd->getWidth()/2)<(x+width/2) && (ballPadd->getx()+ballPadd->getWidth()/2)>(x-width/2)){
        if(ballPadd->gety()-ballPadd->getWidth()/2 > y+height/2)
            time = ((y+height/2)-(ballPadd->gety()-ballPadd->getWidth()/2))/(ballPadd->getymov()+ymov);
        else if(ballPadd->gety()-ballPadd->getWidth()/2 < y-height/2)
            time = ((y-height/2)-(ballPadd->gety()+ballPadd->getWidth()/2))/(ballPadd->getymov()+ymov);
        if(time<2&&time>=0)
            ballPadd->yhit();
    }
    /*if((ballPadd->getx()-ballPadd->getWidth()/2)<(x+width/2) &&
       (ballPadd->getx()+ballPadd->getWidth()/2)>(x-width/2)){
        if(ballPadd->gety()-ballPadd->getwidth()/2>y+height/2){
            if(ballPadd->getymov() < 0){
                xint = ((y+height)-(ballPadd->gety()))/(ballPadd->getymov());
                if(time<1&&time>=0){
                    ballPadd->yhit();
                }
            }
        }else if(ballPadd->gety()+ballPadd->getwidth()/2<y-height/2){
            if(ballPadd->getymov() > 0){
                xint = (ballPadd->getxmov()*(y-height-ballPadd->gety()))/
                       (ballPadd->getymov())+ballPadd->getx();
                time = xint
                if(time<1&&time>=0){
                    ballPadd->yhit();
                }
            }
        }
    }*/
}

void paddle::move(){
    prevy = y;
    if(mode){
        /*if(key->check(VK_UP)){
            if(y<.825){
                y += ymov;
            }
        }
        if(key->check(VK_DOWN)){
            if(y>-.825){
                y -= ymov;
            }
        }*/
        if(key->check(VK_SHIFT)){
            if(key->check(VK_UP)){
                if(y<.825){
                    ymov += yacc*5;
                }
            }
            if(key->check(VK_DOWN)){
                if(y>-.825){
                    ymov -= yacc*5;
                }
            }
        }else{
            if(key->check(VK_UP)){
                if(y<.825){
                    ymov += yacc;
                }
            }
            if(key->check(VK_DOWN)){
                if(y>-.825){
                    ymov -= yacc;
                }
            }
        }
        if(y + (height/2) > 1){
            ymov *= -1;
            y = 1 - height/2;
        }else if(y - (height/2) < -1){
            ymov *= -1;
            y = -1 + height/2;
        }
        if(ymov > .05){
            ymov = .05;
        }
        ymov *= .99;
        y += ymov;
    } else {
        y = *ymouse;
        if(y>.825){
            y = .825;
        } else if (y<-.825){
            y = -.825;
        }
    }
    yspeed = y-prevy;
}
void paddle::pOneMove(){
    prevy = y;
    if(key->check('S')){
        if(key->check(VK_SHIFT)){
            if(y<.825){
                ymov += yacc*5;
            }
        }
        if(key->check(VK_CONTROL)){
            if(y>-.825){
                ymov -= yacc*5;
            }
        }
    }else{
        if(key->check(VK_SHIFT)){
            if(y<.825){
                ymov += yacc;
            }
        }
        if(key->check(VK_CONTROL)){
            if(y>-.825){
                ymov -= yacc;
            }
        }
    }
    if(y + (height/2) > 1){
        ymov *= -1;
        y = 1 - height/2;
    }else if(y - (height/2) < -1){
        ymov *= -1;
        y = -1 + height/2;
    }
    if(ymov > .05){
        ymov = .05;
    }
    ymov *= .99;
    y += ymov;
    yspeed = y-prevy;
}
void paddle::pTwoMove(){
    prevy = y;
    if(key->check('P')){
        if(key->check(VK_UP)){
            if(y<.825){
                ymov += yacc*5;
            }
        }
        if(key->check(VK_DOWN)){
            if(y>-.825){
                ymov -= yacc*5;
            }
        }
    }else{
        if(key->check(VK_UP)){
            if(y<.825){
                ymov += yacc;
            }
        }
        if(key->check(VK_DOWN)){
            if(y>-.825){
                ymov -= yacc;
            }
        }
    }
    if(y + (height/2) > 1){
        ymov *= -1;
        y = 1 - height/2;
    }else if(y - (height/2) < -1){
        ymov *= -1;
        y = -1 + height/2;
    }
    if(ymov > .05){
        ymov = .05;
    }
    ymov *= .99;
    y += ymov;
    yspeed = y-prevy;
}

void paddle::reset(){
     y = 0;
     ymov = 0;
     yacc = 0.0005;
}

void paddle::AIMove(){ 
    prevy = y;
    if(y>endy+.06){
        y-=aiymov;
    }else if(y<endy-.06){
        y+=aiymov;
    }
    if(y>.825){
        y = .825;
    } else if (y<-.825){
        y = -.825;
    }
    yspeed = y-prevy;
}

void paddle::calcPos(){
    by = ballPadd->gety();
    bx = ballPadd->getx();
    bdy = ballPadd->getymov();
    bdx = ballPadd->getxmov();
    bm = bdy/bdx;
    bb = by-bm*bx;
    endy = bm+bb;
    endy += 2*ballPadd->randomMov();
}

void paddle::render(){
    glPushMatrix ();
    glTranslatef(x,y,0.0);
    glBegin (GL_TRIANGLE_STRIP);
    glColor3f (0.0f, 1.0f, 0.0f);
    glVertex3f (-width/2, -height/2, 0);
    glVertex3f (-width/2, height/2, 0);
    glVertex3f (width/2, -height/2, 0);
    glVertex3f (width/2, height/2, 0);
    glEnd ();
    glPopMatrix ();
}
