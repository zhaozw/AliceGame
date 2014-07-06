// Func_Math.cpp

#include "Func_Math.h"
#include "Static_Game.h"		// 設定を参照する

#ifdef DEFDIR_Y_AXIS
inline float rad2x(float rad){
	return -sin(rad);
}

inline float rad2y(float rad){
	return cos(rad);
}

float getRad(float x1, float y1, float x2, float y2){
	// (x1, y1)から見た(x2, y2)の角度(Rad)を返す。
	return atan2(-(x2-x1), y2-y1);
}

float getRad2(float x, float y){
	// (x, y)ベクトルの角度(Rad)を返す。
	return atan2(-x, y);
}

float getGraphAngle(float vx, float vy){
	return getRad2(vx, vy);
}

#endif // DEFDIR_Y_AXIS

#ifdef DEFDIR_X_AXIS
inline float rad2x(float rad){
	return cos(rad);
}

inline float rad2y(float rad){
	return sin(rad);
}

float getRad(float x1, float y1, float x2, float y2){
	// (x1, y1)から見た(x2, y2)の角度(Rad)を返す。
	float x = x2-x1;
	float y = y2-y1;
	return atan2(y, x);
}

float getRad2(float x, float y){
	// (x, y)ベクトルの角度(Rad)を返す。
	return atan2(y, x);
}

float getGraphAngle(float vx, float vy){
	return getRad2(vx, vy);
}

#endif // DEFDIR_X_AXIS


float getLong(float x1, float y1, float x2, float y2){
	// (x1, y1),(x2, y2)の距離を返す
	return (float)sqrt(max(0.0001, (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

float getLong2(float x1, float y1){
	return (float)sqrt(max(0.0001, x1*x1+y1*y1));
}

float Rand(int bias){
	int n;
	if(bias == 0){
		return ((float)(MyGetRand(100)-50))/50.0f;
	}else{
		n = SeamLess(bias*5, 13); // 0～12の値、飛び飛び
		n = ((int)(8.3*n)+MyGetRand(16))%100;
		return ((float)(n-50))/50.0f;
	}
}
float Rand2(){
	return ((float)(MyGetRand(100)))/100.0f;
}

float Rand_Narrow(int bias){
	return (float)tan(0.25*M_PI*Rand(bias));
}

float Rand_Narrow2(int bias){
	float a = Rand(bias);
	return abs(a)*a;
}

float Rand_Wide2(int bias){
	return (float)sin(0.5*M_PI*Rand(bias));
}

int MyGetRand(int maxRand){
#ifdef CHECK_REPLAYLOG
	g_randCount++;
#endif // CHECK_REPLAYLOG
	return GET_RAND(maxRand);
}

float getDir(float dltX, float dlyY){
	return 0;
}

float deg2rad(float d){
	return d*(float)M_PI/180.0f;
}

float rad2deg(float r){
	return r*180.0f/(float)M_PI;
}

void Rotate(float* x, float* y, const float rad){
	float _x = *x;
	float _y = *y;
	*x = _x*cos(rad)-_y*sin(rad);
	*y = _x*sin(rad)+_y*cos(rad);
}

void Rotate(float* x, float* y, const float deg, const int fps){
	Rotate(x, y, (float)(deg*M_PI/fps/180.0f));
}

void Normalize(float* x, float* y){
	float _x = *x;
	float _y = *y;
	*x = _x/getLong2(_x, _y);
	*y = _y/getLong2(_x, _y);
}

int const SeamLess(int const p, int const length){
	if(length <= 0) return 0;
	if(p >= 0){
		return p%length;
	}else{
		return length - ((p*(-1))%length);
	}
	return 0;
}

float GetRotateSpeed(const float deg, const float radius, const int fps){
	return (deg2rad(deg)*radius)/fps;
}

float GetRotateAngleRate(const float speed, const float radius, const int fps){
	return rad2deg((speed/radius))*fps;
}

float GetRotateAngleRate2(const float speed, const float radius, const bool isRadian){
	if(isRadian){
		return speed/radius;
	}else{
		return rad2deg((speed/radius));
	}
}

float Homing(float cnt, float aim, float maxRad){
	float tmpCnd = rad2radPI(cnt-aim);
	if(abs(tmpCnd) < maxRad){
		return aim;
	}else if(tmpCnd > 0){
		return cnt-maxRad;
	}else{
		return cnt+maxRad;
	}
}


float amax(float x, float cmp){
	if(x<0){
		return min(x, -cmp);
	}else{
		return max(x, cmp);
	}
}

float amin(float x, float cmp){
	if(x<0){
		return max(x, -cmp);
	}else{
		return min(x, cmp);
	}
}

// 2つのベクトルのなす角を返す。
// 角度は360.0°の正確さで、
// 角度は-M_PI ~ M_PIの間。
float GetVecRad(float x1, float y1, float x2, float y2){
	if(abs(x1-x2)<0.1 && abs(y1-y2)<0.1) return 0.0f;
	float ac = (x1*x2+y1*y2)/getLong2(x1,y1)/getLong2(x2,y2);
	if(ac>1.0f) ac=1.0f;
	if(ac<-1.0f) ac=-1.0f;
	return rad2radPI(acos(ac));
}

// rad単位で表された角度を-M_PI~M_PIの間に制限する。
float rad2radPI(float rad){
	int deg = (int)(rad2deg(rad)*100);
	// 正の値に変換する
	if(deg<0){
		int plus = deg/36000-1;
		deg -= plus*36000;
	}
	deg=(deg+18000)%36000;
	deg-=18000;
	float deg_raw = (float)deg/100.0f;
	return deg2rad(deg_raw);
}

float way2float(int i, int max){
	return (float)((float)i - ((float)max-1.0)/2.0);
}
