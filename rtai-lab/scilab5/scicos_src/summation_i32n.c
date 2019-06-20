/*  Scicos
*
*  Copyright (C) 2015 INRIA - METALAU Project <scicos@inria.fr>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/>.
*
* See the file ./license.txt
*/
/*--------------------------------------------------------------------------*/ 
#include <math.h>
#include <stdio.h>
#include "scicos_block4.h"
#include "MALLOC.h"
#include "dynlib_scicos_blocks.h"
/*--------------------------------------------------------------------------*/ 
SCICOS_BLOCKS_IMPEXP void summation_i32n(scicos_block *block,int flag)
{
	if((flag==1)|(flag==6)) 
	{
		int j = 0,k = 0;
		int nu = 0,mu = 0,nin = 0;
		long *y = NULL;
		int *ipar = NULL;
		double *rpar = NULL;
		long *u = NULL;

		y=Getint32OutPortPtrs(block,1);
		nu=GetInPortRows(block,1);
		mu=GetInPortCols(block,1);
		ipar=GetIparPtrs(block);
		rpar=GetRparPtrs(block);
		nin=GetNin(block);

		if (nin==1)
		{
			y[0]=0;
			u=Getint32InPortPtrs(block,1);
			for (j=0;j<nu*mu;j++) 
			{
				y[0]=y[0]+u[j];
			}
		}
		else 
		{
			for (j=0;j<nu*mu;j++) 
			{
				y[j]=0;
				for (k=0;k<nin;k++) 
				{
					u=Getint32InPortPtrs(block,k+1);
					if(ipar[k]>0)
					{
						y[j]=y[j]+u[j];
					}
					else
					{
						y[j]=y[j]-u[j];}
				}
			}
		}
	}
}
/*--------------------------------------------------------------------------*/ 
