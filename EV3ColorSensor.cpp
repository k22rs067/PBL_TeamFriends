#include "EV3ColorSensor.h"

EV3ColorSensor::EV3ColorSensor(ev3api::ColorSensor &colorSensor)
	: mColorSensor(colorSensor)
{
}

EV3ColorSensor::~EV3ColorSensor()
{
}

/*
* 輝度値を取得する
* @return 輝度値
*/
int EV3ColorSensor::getBrightness()
{
	return ev3_color_sensor_get_reflect((sensor_port_t)PORT_2);
}

//RGBライントレースの輝度値
double EV3ColorSensor::getColorBrightness()
{
	mColorSensor.getRawColor(rgb);
	rgb_brightness = (0.299 * rgb.r) + (0.587 * rgb.g) + (0.114 * rgb.b);
	// BluetoothLogger::dataLogger(0, 0, (int16_t)rgb.r, (int16_t)rgb.g, (int16_t)rgb.b, (int16_t)(rgb_brightness * 100));
	float max = rgb.r > rgb.g ? rgb.r : rgb.g;
	max = max > rgb.b ? max : rgb.b;
	float min = rgb.r < rgb.g ? rgb.r : rgb.g;
	min = min < rgb.b ? min :rgb.b;
	Hue = max - min;
	if (Hue > 0.0f) {
		if (max == rgb.r) {
			Hue = (rgb.g - rgb.b) / Hue;
			if (Hue < 0.0f) {
				Hue += 6.0f;
			}
		} else if (max == rgb.g) {
			Hue = 2.0f + (rgb.b - rgb.r) / Hue;
		} else {
			Hue = 4.0f + (rgb.r - rgb.g) / Hue;
		}
	}
	Hue /= 6.0f;
	Saturation = (max - min);
	if (max != 0.0f)
		Saturation /= max;
	    Brightness = max;

    hue = Hue * 100;
	saturation = Saturation * 100;
	brightness = Brightness;

	//syslog(LOG_NOTICE, "%d,%d,%d,%d,%d,%d", (int16_t)hue,  (int16_t)saturation,  (int16_t)rgb_brightness, (int16_t)rgb.r, (int16_t)rgb.g, (int16_t)rgb.b);
	return rgb_brightness;
}

void EV3ColorSensor::getEncodeHSV()
{
	mColorSensor.getRawColor(rgb);
	rgb_brightness = (0.299 * rgb.r) + (0.587 * rgb.g) + (0.114 * rgb.b);
	float max = rgb.r > rgb.g ? rgb.r : rgb.g;
	max = max > rgb.b ? max : rgb.b;
	float min = rgb.r < rgb.g ? rgb.r : rgb.g;
	min = min < rgb.b ? min :rgb.b;
	Hue = max - min;
	if (Hue > 0.0f) {
		if (max == rgb.r) {
			Hue = (rgb.g - rgb.b) / Hue;
			if (Hue < 0.0f) {
				Hue += 6.0f;
			}
		} else if (max == rgb.g) {
			Hue = 2.0f + (rgb.b - rgb.r) / Hue;
		} else {
			Hue = 4.0f + (rgb.r - rgb.g) / Hue;
		}
	}
	Hue /= 6.0f;
	Saturation = (max - min);
	if (max != 0.0f)
		Saturation /= max;
	    Brightness = max;

    hue = Hue * 100;
	saturation = Saturation * 100;
	brightness = Brightness * 100;

	syslog(LOG_NOTICE, "%d,%d,%d,%d,%d,%d", (int16_t)hue,  (int16_t)saturation,  (int16_t)brightness, (int16_t)rgb.r, (int16_t)rgb.g, (int16_t)rgb.b);
}

float EV3ColorSensor::getHue()
{
	return hue;
}

float EV3ColorSensor::getSaturation()
{
	return saturation;
}

float EV3ColorSensor::getBright()
{
	return brightness;
}


bool EV3ColorSensor::isColor_BLUE()
{
	return ((hue >= 50) && (saturation >= 80)) ? true : false;
}

bool EV3ColorSensor::isColor_RED()
{
	return ((hue <= 15) && (saturation >= 50)) ? true : false;
}

bool EV3ColorSensor::isColor_GREEN()
{
	return ((hue >= 30) && (saturation <= 80) && (brightness > 80)) ? true : false;
}

bool EV3ColorSensor::isColor_YELLOW()
{
	return ((hue <= 25) && (brightness > 120)) ? true : false;
}

bool EV3ColorSensor::isColor_WHITE()
{
	return ((brightness >= 180)) ? true : false;
}

bool EV3ColorSensor::isColor_BLACK()
{
	return ((brightness <= 15)) ? true : false;
}

bool EV3ColorSensor::isColor_PRESENT()
{
	return ((Hue >= 90)) ? true : false;
}

bool EV3ColorSensor::isColor_OBSTACLE() 
{
	return (/*(((Hue >= 0)&&(Hue <= 0.07))||((Hue >= 0.8)&&(Hue <= 1)))&&*/(Saturation > 0.3)) ? true : false; //(Hue >= 0.595)&&(Hue <= 0.600)
}

