////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	newton_tb.h
//
// Project:	Fraction delay filter for interpolation and decimation
//
// Purpose:	This program is used for resampling signal. The method is based on 
// newton interpolation formula. 
//
// R = input sample rate / output sample rate
// R in range of [0.5 1.0] is interpolation, R in range of [1.0 2.0] is decimation
//
//	IF you use decimation, set function "newton_decim" as "Top Function" in "Project Settings".
//	IF you use interpolation, set function "newton_interp" as "Top Function" in "Project Settings".
//
// Creator:	liuming
//		lewming@gmail.com
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018-2019, liuming
//
// This program is free software (firmware): you can redistribute it and/or
// modify it under the terms of  the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  (It's in the $(ROOT)/doc directory.  Run make with no
// target there if the PDF file isn't present.)  If not, see
// <http://www.gnu.org/licenses/> for a copy.
//
// License:	GPL, v3, as defined and found on www.gnu.org,
//		http://www.gnu.org/licenses/gpl.html
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include "newton_filter.h"


int main ()
{
	std::ifstream fin("DataIn.txt", std::ios::in);
    std::ofstream fout("DataOut.txt", std::ios::trunc);

    
	if (!fin.is_open()){ //make sure file is valid
		std::cout << "Error Opening DataIn.txt File!" << std::endl;
	}
    
    data_t input = 0.0;    
    data_t output;
    data_t output_interp;
    bool strobe;
    
	std::cout << "Resampling input signal..." << std::endl;
    
    while (fin >> input)
    {
#ifdef INTERP
        newton_interp(R, input, &output, &output_interp, &strobe);
        fout << output << std::endl;
        if(strobe)
            fout << output_interp << std::endl;
#endif
#ifdef DECIM
        newton_decim(R, input, &output, &strobe);
        if(strobe)
            fout << output << std::endl;
#endif
    }
    std::cout << "Resampling input signal...done" << std::endl;
    
    fin.close();
    fout.close();
    
    return 0;
}