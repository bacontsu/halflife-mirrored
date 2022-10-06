// by Bacontsu, based on Color Correction tutorial from https://hlfx.ru

class CFlipScreen
{
public:
	void InitScreen(void);
	void DrawColorCor(void);

	unsigned int tex;
};

extern CFlipScreen gFlipScene;