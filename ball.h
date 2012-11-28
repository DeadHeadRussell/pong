class paddle;

class ball {
    private:
        float x;
        float y;
        float xmov;
        float ymov;
        float width;
        float randNum;
        int *scoreHim;
        int *scoreYou;
        int movement;
        paddle *aiPadd;
    
    public:
        void init(int *you, int *him);
        void shutdown();
        void move();
        void hit(double yspeed);
        void yhit();
        void render();
        float getx();
        float getxmov();
        float gety();
        float getymov();
        float getWidth();
        void reset();
        void drawRect();
        int getHimScore();
        int getYouScore();
        void initAiPadd(paddle *ai);
        float randomMov();
};
