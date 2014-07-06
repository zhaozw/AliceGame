// Player_Sample.h

#ifndef PLAYER_SAMPLE_H
#define PLAYER_SAMPLE_H

class Player_Sample{
	float x;
	float y;
public:
	Player_Sample();
	bool Update();
	void Draw();

	float GetX(){ return x; };
	float GetY(){ return y; };
};

#endif // PLAYER_SAMPLE_H