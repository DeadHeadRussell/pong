class font
{
private:
	unsigned int m_fontListBase;
    bool selected;
    
	unsigned int CreateBitmapFont(char *fontName, int fontSize);
	void RenderFont(float xPos, float yPos, unsigned int base, char *str);
	void ReleaseFont(unsigned int base);

public:
	font();
	virtual ~font();

	void init(int size);
	void shutdown();
    void select();
    void deselect();
	void render(float xpos, float ypos, char* string);
};
