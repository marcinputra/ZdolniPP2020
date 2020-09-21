#pragma once
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
/// <summary>
/// saves coords to file saveCoords.txt every second
/// requires adding elements to vector data_from_last_sec
///  every time something is drawn
/// </summary>
std::vector <int> data_from_last_sec;
/*
contains coordinates data from last minute as ints, in pattern
[tool: 0 - free painting x1 y1 x2 y2 colour(black, red, green, blue) 1 - rectangle x1 y1 x2 y2 colour(black, red, green, blue) 2 - line x1 y1 x2 y2 colour(black, red, green, blue)
*/
double seconds_since_last_data_save = time(NULL);

void DebugDataSave(double* last_save, std::vector <int> *data)
{
	if (double(time(NULL)) - *last_save > 1)
	{
		int temp;
		
		std::ofstream save_file("savedCoords.txt");
		save_file << "SAVE!!!!!!!!\n";
		temp = data->size();
		for (int i = 0; i <temp; i++)
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
		seconds_since_last_data_save = double(time(NULL));
		save_file.close();
		data->clear();
	}
}
