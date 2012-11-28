
/***************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#include "ball.h"
#include "paddle.h"
#include "font.h"
#include "keyPress.h"
#include "resource.h"

#define FRAME_MAINMENU 0
#define FRAME_PLAY     1
#define FRAME_ENDGAME  2
#define FRAME_INST     3

#define SINGLE         4
#define MULTI          5

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

HDC hDC;
//Key press variables
keyPress *keys;
//mouse position variables
float yMouse,xMouse;
//object declaration
ball *ball1 = NULL;
paddle *you;
paddle *him;
font *scoreYou;
font *scoreHim;
font *title;
font *winText;
font *play;
font *inst;
font *quit;
font *instText;
font *mainMenu;
font *players;
font *playersNum;
//score keeping variables
char scoreCharYou [5];
int scoreIntYou;
char scoreCharHim [5];
int scoreIntHim;
//current frame
int frame = FRAME_MAINMENU;
bool win = false;
int selected = 0;
int count = 0;
//multiplayer?
int game = SINGLE;

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PONG));
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Pong";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "Pong", "Pong - The Awesome", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 800, 600,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    //init objects
    keys = new keyPress();
    
    ball1 = new ball; 
    ball1->init(&scoreIntYou, &scoreIntHim);
    
    you = new paddle;
    you->init(-1.2,ball1,keys, &yMouse);
    
    him = new paddle;
    him->init(1.2,ball1,keys, &yMouse);
    
    ball1->initAiPadd(him);
    
    scoreYou = new font;
    scoreYou->init(36);
    
    scoreHim = new font;
    scoreHim->init(36);
    
    scoreIntYou = 0;
    scoreIntHim = 0;
    
    title = new font;
    title->init(48);
    
    winText = new font;
    winText->init(36);
    
    play = new font;
    play->init(36);
    
    inst = new font;
    inst->init(36);
    
    quit = new font;
    quit->init(36);
    
    instText = new font;
    instText->init(24);
    
    players = new font;
    players->init(24);
    
    playersNum = new font;
    playersNum->init(24);
    
    mainMenu = new font;
    mainMenu->init(36);
    mainMenu->select();
    
    time_t seconds;
    time(&seconds);
    srand((unsigned int)seconds);
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            
            if(keys->check(VK_SPACE)){
                you->changeMode();
                keys->setFalse(VK_SPACE);
            }
            
            
            if(keys->check(VK_RETURN)){
                if(frame == FRAME_MAINMENU){
                    if(selected == 0){
                        frame = FRAME_PLAY;
                    }else if(selected == 1){
                        frame = FRAME_INST;
                    }else if(selected == 2){
                        bQuit = TRUE;
                    }
                } else if (frame == FRAME_ENDGAME){
                    frame = FRAME_MAINMENU;
                    scoreIntYou = 0;
                    scoreIntHim = 0;
                    you->reset();
                    him->reset();
                }else if(frame == FRAME_INST){
                    frame = FRAME_MAINMENU;
                }
                keys->setFalse(VK_RETURN);
            }
            
            
            if(frame == FRAME_PLAY){
                //Is game over?
                if(scoreIntYou >= 5){
                    frame = FRAME_ENDGAME;
                    win = true;
                } else if(scoreIntHim >= 5){
                    frame = FRAME_ENDGAME;
                    win = false;
                }
            }
            if(frame == FRAME_PLAY){
                //movement
                ball1->move();
                if(game == SINGLE){
                    you->move();
                    him->AIMove();
                }else{
                    you->pOneMove();
                    him->pTwoMove();
                }
                //ball-paddle hittest
                you->hitTest();
                him->hitTest();
            }
            
            //change scores from int to string
            itoa(scoreIntYou,scoreCharYou,10);
            itoa(scoreIntHim,scoreCharHim,10);
            
            
            ball1->render();
            you->render();
            him->render();
            
            
            if(frame != FRAME_ENDGAME){
                scoreYou->render(-.8,.9,(char*)scoreCharYou);
                scoreHim->render(.7,.9,(char*)scoreCharHim);
            }   
            
             
            if(frame != FRAME_PLAY){
                ball1->drawRect();  
            }
            
            
            if(frame == FRAME_ENDGAME){
                ball1->reset();
                if(win){
                    winText->render(-.31,.35,"YOU WIN!");
                } else {
                    winText->render(-.32,.35,"YOU LOSE!");
                }
                scoreYou->render(-.3,0,(char*)scoreCharYou);
                scoreHim->render(.2,0,(char*)scoreCharHim);
                mainMenu->render(-.32,-.2,"Main Menu");
            }
            
            
            if(frame == FRAME_INST){
                instText->render(-.76,.2,"You can use the up and down arrow keys,");
                instText->render(-.76,.1,"or you can move the mouse up and down,");
                instText->render(-.84,0,"to control your paddle.  Press space to switch.");
                instText->render(-.36,-.1,"(Default is mouse)");
                instText->render(-.89,-.2,"Pressing escape at any time will close the game.");
                mainMenu->render(-.32,-.4,"Main Menu");
            }
            
            if(frame == FRAME_MAINMENU){
                if(keys->check('1')){
                    game = SINGLE;
                }
                if(keys->check('2')){
                    game = MULTI;
                }
                count--;
                if(count<0){
                    count = 0;
                }
                if(count == 0){
                    if(keys->check(VK_DOWN)){
                        selected++;
                        count = 30;
                    }
                    if(keys->check(VK_UP)){
                        selected--;
                        count = 30;
                    }
                }
                if(selected>=3){
                    selected = 0;
                }else if(selected<=-1){
                    selected = 2;
                }
                if(selected == 0){
                    play->select();
                    inst->deselect();
                    quit->deselect();
                } else if(selected == 1){
                    play->deselect();
                    inst->select();
                    quit->deselect();
                } else if(selected == 2){
                    play->deselect();
                    inst->deselect();
                    quit->select();
                }
                play->render(-.15,.2,"Play");
                inst->render(-.36,0,"Instructions");
                quit->render(-.15,-.2,"Quit");
                players->render(-.36,-.6,"Number Players: ");
                if(game == SINGLE){
                    playersNum->render(.3,-.6,"1");
                }else{
                    playersNum->render(.3,-.6,"2");
                }  
                ball1->reset();
            }
            
            
            title->render(-.8,.7,"PONG - The Awesome");
           
           
            SwapBuffers (hDC);
            Sleep (1);
            if(keys->check(VK_ESCAPE)){
                bQuit = true;
            }
        }
    }
    scoreYou->shutdown();
    scoreHim->shutdown();
    title->shutdown();
    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_MOUSEMOVE:
        xMouse = (-((float)LOWORD(lParam))/285)+.975; 
        yMouse = (-((float)HIWORD(lParam))/285)+.975; 
        return 0;
    
    case WM_KEYDOWN:
        if(wParam!=VK_RETURN||wParam!=VK_SPACE){
            keys->setTrue(wParam);
        }
        return 0;
    case WM_KEYUP:
        if(wParam!=VK_RETURN||wParam!=VK_SPACE){
            keys->setFalse(wParam);
        }else{
            keys->setTrue(wParam);
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
    
    //set up projection
    glOrtho((float)-4/3,(float)4/3,-1,1,0,-1);
}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
