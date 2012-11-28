class ball;
class keyPress;

class paddle {
    private:
        float x;
        float y;
        float xHit;
        float ymov;
        float yacc;
        float width;
        float height;
        float time;
        float *ymouse;
        float endy;
        float aiymov;
        double prevy;
        double yspeed;
        bool *keyUp;
        bool *keyDown;
        bool mode;
        ball *ballPadd;
        float by,bx,bdy,bdx,bb,bm;
        keyPress *key;
        
    public:
        void init(float pos, ball *ball1, keyPress *keyed, float *mouse);
        void shutdown();
        void hitTest();
        void move();
        void AIMove();
        void pOneMove();
        void pTwoMove();
        void render();
        void changeMode();
        void reset();
        void calcPos();
};
