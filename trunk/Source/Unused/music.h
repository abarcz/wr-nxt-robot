#define EIGH QUAR/2
#define QUAR 631	// quarternote in miliseconds in 95 bpm
#define HALF 2*QUAR
#define WHOL 4*QUAR
// Tones
#define F5 698
#define E5 659
#define C4 261
#define A4 440
#define D4 293
#define G5 784
#define A5 880
#define C5 523

// Melodies
int champions_num = 22;
int champions_tones[22] =
							{
								F5,
								E5,
								F5,
								E5,
								C4,
								0,
								A4,
								D4,
								A4,
								0,
								0,
								0,
								0,
								C4,
								F5,
								G5,
								A5,
								C5,
								A5,
								D4,
								F5,
								D4
							};
int champions_durations[22] =
							{
								HALF,
								EIGH,
								EIGH,
								QUAR,
								QUAR,
								EIGH,
								EIGH,
								QUAR,
								QUAR,
								EIGH,
								EIGH,
								EIGH,
								HALF,
								EIGH,
								HALF,
								EIGH,
								EIGH,
								QUAR,
								QUAR,
								EIGH,
								EIGH,
								WHOL
							};

void melody(int tones[], int durations[], int numofnotes)
{
	int i = 0;
	for(i = 0; i < numofnotes; i++ )
	{
		PlayToneEx(tones[i], durations[i], 4, false);
	}
}

task main(){}


