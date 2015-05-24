using PCM16 = short int;
using U32 = unsigned int;
using U16 = unsigned short int;

/*
	Work under the assumption that the WAV file we read from is in the 
	canonical form (that is, it contains only a format and a data subchunk, in that order) 
	and that the audio data is stored without any compression. Under these conditions, 
	we know where all of the data is stored, and can simply index into the file to read 
	it. That is certainly not the case for every WAV file, which would require a more 
	complex loading sequence.
*/
class MySound 
{
	public:
		MySound(const char* path);
		~MySound();
		U32 samplingRate;
		U16 numChannels;
		U16 bitsPerSample;
		PCM16* data;
		U32 count;
};


	

