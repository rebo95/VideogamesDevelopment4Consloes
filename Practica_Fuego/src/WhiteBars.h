
class WhiteBars {
private :

	static const int BAR_HEIHGT = 10;
	static const int BAR_WIDHT = 100;
	static const int BAR_INTER_SPACE = 20;
	int num_bars_horizontal;
	int num_bars_vertical;

	int offset_ = 0;
	static const int barsVel = 1;

public:
	WhiteBars();
	~WhiteBars();

	void render();
	void render(int deltaTime);

	void update();

private:
	//dibujado de la barra partiendo de una posición X, Y
	void drawBar(int x, int y);
	void drawBar(int x, int y, int delta);
};