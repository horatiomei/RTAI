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
#include <stdio.h>
#include "machine.h" /* C2F */
#include "MALLOC.h"
#include "scicos.h"
#include "core_math.h"
#include "scicos_block4.h"
#include "scicos_malloc.h"
#include "scicos_free.h"
#include "dynlib_scicos_blocks.h"
/*--------------------------------------------------------------------------*/ 
extern int C2F(dgesvd)();
extern int C2F(dlaset)();
extern int C2F(dlacpy)();
extern int C2F(dmmul)();
/*--------------------------------------------------------------------------*/ 
typedef struct
{         
	double *l0;
	double *LA;
	double *LSV;
	double *LVT;
	double *dwork;
} mat_sdv_struct ;
/*--------------------------------------------------------------------------*/ 
SCICOS_BLOCKS_IMPEXP void mat_svd(scicos_block *block,int flag)
{
 double *u = NULL;
 double *y1 = NULL,*y2 = NULL,*y3 = NULL;
 int nu = 0, mu = 0;
 int info = 0;
 int i = 0,j = 0,ij = 0,ji = 0,ii = 0,lwork = 0;
 mat_sdv_struct *ptr = NULL;

 mu=GetInPortRows(block,1);
 nu=GetInPortCols(block,1);
 u=GetRealInPortPtrs(block,1);
 y1=GetRealOutPortPtrs(block,1);
 y2=GetRealOutPortPtrs(block,2);
 y3=GetRealOutPortPtrs(block,3);
 /* for lapack 3.1 (2006)*/
 lwork=Max(3*Min(mu,nu)+Max(mu,nu),5*Min(mu,nu));
 lwork=Max(1,lwork); 
             /*init : initialization*/
if (flag==4)
   {if((*(block->work)=(mat_sdv_struct*) scicos_malloc(sizeof(mat_sdv_struct)))==NULL)
	{set_block_error(-16);
	 return;}
    ptr=*(block->work);
    if((ptr->l0=(double*) scicos_malloc(sizeof(double)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr);
	 return;}
    if((ptr->LA=(double*) scicos_malloc(sizeof(double)*(mu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LSV=(double*) scicos_malloc(sizeof(double)*(Min(mu,nu))))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LVT=(double*) scicos_malloc(sizeof(double)*(nu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->dwork=(double*) scicos_malloc(sizeof(double)*lwork))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LVT);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
   }

       /* Terminaison */
else if (flag==5)
   {ptr=*(block->work);
    if((ptr->dwork)!=NULL) {
    	scicos_free(ptr->l0);
    	scicos_free(ptr->LA);
    	scicos_free(ptr->LSV);
    	scicos_free(ptr->LVT);
    	scicos_free(ptr->dwork);
    	scicos_free(ptr);
    	return;}
   }

else
   {
    ptr=*(block->work);
    C2F(dlacpy)("F",&mu,&nu,u,&mu,ptr->LA,&mu);
    C2F(dgesvd)("A","A",&mu,&nu,ptr->LA,&mu,ptr->LSV,y1,&mu,ptr->LVT,&nu,ptr->dwork,&lwork,&info);
     if (info !=0)
       {if (flag!=6)
   	{set_block_error(-7);
        return;}}
    
    *(ptr->l0)=0;
     C2F(dlaset)("F",&mu,&nu,ptr->l0,ptr->l0,y2,&mu);
    for (i=0;i<Min(mu,nu);i++)
	{ii=i+i*mu;
	 *(y2+ii)=*(ptr->LSV+i);}
    for (j=0;j<nu;j++)
	{for (i=j;i<nu;i++)
		{ij=i+j*nu;
	 	 ji=j+i*nu;
		 *(y3+ij)=*(ptr->LVT+ji);
		 *(y3+ji)=*(ptr->LVT+ij);}
	}
   }
}
/*--------------------------------------------------------------------------*/ 
