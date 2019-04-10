////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	newton_filter.h
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
#include "ap_int.h"
#include "ap_fixed.h"

#define K 5 //filter tap

#define INTERP
//#define DECIM

typedef ap_fixed<32,8> data_t;

const data_t R = 0.651041667; //resample rate [0.5-1.0] for interpolation, [1.0-2.0] for decimation

const data_t reciproc[K] = {1.0, 1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0, 1.0 / 5.0};

void newton_interp(const data_t R, data_t in, data_t *out, data_t *out_interp, bool *strobe); //[0.5-1.0]
void newton_decim(const data_t R, data_t in, data_t *out, bool *strobe); //[1.0-2.0]

