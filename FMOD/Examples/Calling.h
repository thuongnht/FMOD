#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
Every time we multiply/divide a frequency by two we get a new frequency
that sounds one octave higher/lower
*/
float ChangeOctave(float frequency, float variation) {
	static float octave_ratio = 2.0f;
	return frequency * pow(octave_ratio, variation);
}

/*
Every time we multiply/divide a frequency by two and a half we get new
a frequency that sounds one semitone higher/lower
*/
float ChangeSemitone(float frequency, float variation) {
	static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
	return frequency * pow(semitone_ratio, variation);
}

//get a random number
float RandomBetween(float min, float max) {
	if (min == max) return min;
	float n = (float)rand() / (float)RAND_MAX;
	return min + n * (max - min);
}