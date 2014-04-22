//----------------------------------------------------------------------------------------------
// source.cpp (systemc)
//
//	Author: KBE / 2010.09.12
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "CodecSource.h"

void CodecSource::entry()
{ 
	int tmp_val;
	int clk_count;
	bool rightAudio;
	FILE *fp_data;
	fp_left = fopen(INPUT_FILE_LEFT, "r");
	fp_right = fopen(INPUT_FILE_RIGHT, "r");

	AudioSync.write(false);
	AudioIn.write(0);
	rightAudio = true;

	cout << "CodecSource started" << endl;
	while(true)
	{ 
		if (Reset == true)
		{
			clk_count = 0;
		}
		else
		{
			clk_count++;
			if (clk_count == AUDIO_SYNC_CNT)
			{
				if (rightAudio)
					fp_data = fp_right;
				else
					fp_data = fp_left;

				// Read simulation input data from file
				if (fscanf(fp_data, "%d", &tmp_val) == EOF)
				{
					cout << "End of Input Stream: Simulation Stops" << endl;
					sc_stop();
					break;
				};

				// Output audio data
				AudioIn.write(tmp_val);

				if (rightAudio)
				{
					AudioSync.write(true);
					rightAudio = false;
				}
				else
				{
					AudioSync.write(false);
					rightAudio = true;
				}
				clk_count = 0;
			}
		}
		wait();
	}
}
