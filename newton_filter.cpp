////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	newton_filter.cpp
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
#include "newton_filter.h"


void newton_interp(const data_t R, data_t in, data_t *out, data_t *out_interp, bool *strobe)
{
    static data_t d = 0.0;
    static data_t dk[K] = {0.0};
    static data_t dx[K + 1] = {0.0};
    static data_t dx_z[K + 1] = {0.0};
    static data_t mx[K] = {0.0};
    static data_t yk[K + 1] = {0.0};
    
    short i;
    newton_interp_label0:for(i = 0; i < K + 1; i++)
    {
#pragma HLS UNROLL
        dx_z[i] = dx[i];
    }
    
    dx[0] = in;
    newton_interp_label1:for(i = 0; i < K; i++)
    {
#pragma HLS UNROLL
        dx[i + 1] = dx[i] - dx_z[i];
    }
    d += (data_t)1.0;

    yk[K] = dx[K];
    newton_interp_label2:for(i = K - 1; i >= 0; i--)
    {
#pragma HLS UNROLL
        //dk[i] = (-d + i) / (i + 1);
        dk[i] = (-d + i) * reciproc[i];
        mx[i] = dk[i] * yk[i + 1];
        yk[i] = mx[i] + dx[i];
    }
    
    *out = yk[0];
    *strobe = false;
    d -= R;
    
    if(d > 0)
    {
        newton_interp_label3:for(i = K - 1; i >= 0; i--)
        {
#pragma HLS UNROLL
            //dk[i] = (-d + i) / (i + 1);
            dk[i] = (-d + i) * reciproc[i];
            mx[i] = dk[i] * yk[i + 1];
            yk[i] = mx[i] + dx[i];
        }
        
        *out_interp = yk[0];
        *strobe = true;
        d -= R;
    }
}

void newton_decim(const data_t R, data_t in, data_t *out, bool *strobe)
{
    static data_t d = 0.0;
    static data_t dk[K] = {0.0};
    static data_t dx[K + 1] = {0.0};
    static data_t dx_z[K + 1] = {0.0};
    static data_t mx[K] = {0.0};
    static data_t yk[K + 1] = {0.0};
    
    short i;
    newton_decim_label0:for(i = 0; i < K + 1; i++)
    {
#pragma HLS UNROLL
        dx_z[i] = dx[i];
    }
    
    dx[0] = in;
    newton_decim_label1:for(i = 0; i < K; i++)
    {
#pragma HLS UNROLL
        dx[i + 1] = dx[i] - dx_z[i];
    }
    d += (data_t)1.0;

    yk[K] = dx[K];
    *strobe = false;
    
    if(d > 0)
    {
        newton_decim_label2:for(i = K - 1; i >= 0; i--)
        {
#pragma HLS UNROLL
            //dk[i] = (-d + i) / (i + 1);
            dk[i] = (-d + i) * reciproc[i];
            mx[i] = dk[i] * yk[i + 1];
            yk[i] = mx[i] + dx[i];
        }
        
        *out = yk[0];
        *strobe = true;
        d -= R;
    }
}

/* 
void newton_interp(const data_t R, data_t in, data_t *out, data_t *out_interp, bool *strobe)
{
    static data_t d = 0.0;
    static data_t dk[K] = {0.0};
    static data_t dx[K + 1] = {0.0};
    static data_t dx_z[K + 1] = {0.0};
    static data_t mx[K] = {0.0};
    static data_t yk[K + 1] = {0.0};

    
    dx_z[0] = dx[0];
    dx_z[1] = dx[1];
    dx_z[2] = dx[2];
    dx_z[3] = dx[3];
    dx_z[4] = dx[4];
    dx_z[5] = dx[5];

    dx[0] = in;
    dx[1] = dx[0] - dx_z[0];
    dx[2] = dx[1] - dx_z[1];
    dx[3] = dx[2] - dx_z[2];
    dx[4] = dx[3] - dx_z[3];
    dx[5] = dx[4] - dx_z[4];

    d += (data_t)1.0;
    

    yk[5] = dx[5];
    
    dk[4] = (-d + 4) / 5;
    mx[4] = dk[4] * yk[5];
    yk[4] = mx[4] + dx[4];
    
    dk[3] = (-d + 3) / 4;
    mx[3] = dk[3] * yk[4];
    yk[3] = mx[3] + dx[3];
    
    dk[2] = (-d + 2) / 3;
    mx[2] = dk[2] * yk[3];
    yk[2] = mx[2] + dx[2];
    
    dk[1] = (-d + 1) / 2;
    mx[1] = dk[1] * yk[2];
    yk[1] = mx[1] + dx[1];
    
    dk[0] = -d;
    mx[0] = dk[0] * yk[1];
    yk[0] = mx[0] + dx[0];

    *out = yk[0];
    *strobe = false;
    d -= R;
    
    if(d > 0)
    {
        dk[4] = (-d + 4) / 5;
        mx[4] = dk[4] * yk[5];
        yk[4] = mx[4] + dx[4];
        
        dk[3] = (-d + 3) / 4;
        mx[3] = dk[3] * yk[4];
        yk[3] = mx[3] + dx[3];
        
        dk[2] = (-d + 2) / 3;
        mx[2] = dk[2] * yk[3];
        yk[2] = mx[2] + dx[2];
        
        dk[1] = (-d + 1) / 2;
        mx[1] = dk[1] * yk[2];
        yk[1] = mx[1] + dx[1];
        
        dk[0] = -d;
        mx[0] = dk[0] * yk[1];
        yk[0] = mx[0] + dx[0];
        
        *out_interp = yk[0];
        *strobe = true;
        d -= R;
    }
}
*/
