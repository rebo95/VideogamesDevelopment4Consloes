#include <queue>



class Drops {
private :
	static const int NUM_DROPS = 10;
	static const int DROP_TIMER = 5;
	static const int MIN_INIT_HEIGHT = -500;
	static const int MAX_INIT_HEIGHT = 500;

	uint32_t* picture_;
	int* heightBuffer1_;
	int* heightBuffer2_;
	bool* changes_;

public:
	Drops();
	~Drops();

	void update(int frames);

private:
	void simulate(int* sorce, int* result, int frames);
};
