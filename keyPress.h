class keyPress{
    private:
      bool keys[256];
    public:
      keyPress();
      bool check(int key);
      void setTrue(int key);
      void setFalse(int key);
};
