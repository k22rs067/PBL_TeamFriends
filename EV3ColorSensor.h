#ifndef EV3_COLOR_SENSOR_H
#define EV3_COLOR_SENSOR_H

#include "ev3api.h"
#include "ColorSensor.h"

class EV3ColorSensor
{
  public:
	explicit EV3ColorSensor(ev3api::ColorSensor &colorSensor);
	virtual ~EV3ColorSensor();

	int getBrightness();			   //輝度値を取得する
	double getColorBrightness();	   //色の輝度値をとる
	void getEncodeHSV();             //RGB値をHSV値に変換
	bool isColor_BLUE();

  private:
	ev3api::ColorSensor &mColorSensor;

	float Hue;
	float Saturation;
	float Brightness;
	int hue;
	int saturation;
	int brightness;
	int min;
	int max;
	double rgb_brightness;

	rgb_raw_t rgb; //rgB値

};

#endif