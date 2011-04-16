// Notes
#define EIGH 315
#define QUAR 631	// quarternote in miliseconds in 95 bpm
#define HALF 1262
#define WHOL 2524
// Tones
#define F5 698
#define E5 659
#define C4 261
#define A4 440
#define D4 586//293
#define G5 784
#define A5 880
#define C5 1046

// Melodies

//----- Queen - We Are The Champions -----

//----------------------------------------

void melody()
{

	int numofnotes = 22;
	int tones[22] =
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
	int notes[22] =
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

	int i = 0;
	int temptone;
	int tempnote;
	for(i = 0; i < numofnotes; i++ )
	{
		temptone = tones[i];
		tempnote = notes[i];

		if(temptone == 0)
		{
			Wait(tempnote);
		}	
		else
		{
			PlayToneEx(temptone, tempnote, 4, false);
			Wait(tempnote);
		}
	}
	
}



