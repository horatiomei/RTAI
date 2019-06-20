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
#include "scicos_block4.h"
#include "MALLOC.h"
#include "dynlib_scicos_blocks.h"
/*--------------------------------------------------------------------------*/ 
SCICOS_BLOCKS_IMPEXP void exttriuz(scicos_block *block,int flag)
{
  double *ur = NULL;
  double *ui = NULL;
  double *yr = NULL;
  double *yi = NULL;
  int nu = 0,mu = 0,i = 0,j = 0,ij = 0;

  mu=GetInPortRows(block,1);
  nu=GetInPortCols(block,1);
  ur=GetRealInPortPtrs(block,1);
  ui=GetImagInPortPtrs(block,1);
  yr=GetRealOutPortPtrs(block,1);
  yi=GetImagOutPortPtrs(block,1);
  for(i=0;i<mu*nu;i++) 
	{*(yr+i)=*(ur+i);
	 *(yi+i)=*(ui+i);}
  for (j=0;j<nu;j++)
	{for (i=j+1;i<mu;i++)
		{ij=i+j*mu;
		 *(yr+ij)=0;
		 *(yi+ij)=0;}}
}
/*--------------------------------------------------------------------------*/ 
