#pragma once
#include "DebugDataSave.h"
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
//std::vector <int> data_from_last_sec;
/*
contains coordinates data from last minute as ints, in pattern
[tool: 0 - free painting x1 y1 x2 y2 colour(black, red, green, blue) 1 - rectangle x1 y1 x2 y2 colour(black, red, green, blue) 2 - line x1 y1 x2 y2 colour(black, red, green, blue)
*/
//double seconds_since_last_data_save = time(NULL);
using namespace std;
void DebugDataSave(double* last_save, vector <int>* data);