#pragma once
#include "DebugDataSave.h"
/*#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>*/

//std::vector <int> data_from_last_sec;

//double seconds_since_last_data_save = time(NULL);

void DebugDataSave(double* last_save, std::vector <int>* data)
{
	if (double(time(NULL)) - *last_save > 1)
	{
		int temp;

		std::ofstream save_file("savedCoords.txt");
		save_file << "SAVE!!!!!!!!\n";
		temp = data->size();
		for (int i = 0; i < temp; i++)
		{
			/*if (&data[i] == 0)
			{
				save_file << data->at(i) << " ";
				/*for (int j = 1; temp > i + j; j++)
				{
					if (data->at(i + j) == -1)
					{
						save_file << -1 << "/n";
						i += j;
						break;
					}
					save_file << data->at(i + j) << " ";
				}
			}
			else
			{
				save_file << data->at(i) << " ";
				for (int j = 1; temp > i + j; j++)
				{
					if (j == 4)
					{
						save_file << data->at(i + j) << "\n";
						i += j;
						break;
					}
					save_file << data->at(i + j) << " ";
				}
			}*/
			save_file << data->at(i) << " ";
			for (int j = 1; temp > i + j; j++)
			{
				if (j == 5)
				{
					save_file << data->at(i + j) << "   ";
					i += j;
					break;
				}
				save_file << data->at(i + j) << " ";
			}
		}
		*last_save = double(time(NULL));
		save_file.close();
		data->clear();
	}
}