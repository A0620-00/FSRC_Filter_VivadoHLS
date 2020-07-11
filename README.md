# Fractional_Sample_Rate_Conversion_Filter_VivadoHLS

Project:	Fractional Sample Rate Conversion Filter for interpolation and decimation

Purpose:	This program is used for resampling signal. The method is based on 
newton interpolation formula. 

R = input sample rate / output sample rate

R in range of [0.5 1.0] is interpolation, R in range of [1.0 2.0] is decimation

IF you use decimation, set function "newton_decim" as "Top Function" in "Project Settings".

IF you use interpolation, set function "newton_interp" as "Top Function" in "Project Settings".
