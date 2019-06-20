c     Scicos
c     
c     Copyright (C) 2015 INRIA - METALAU Project <scicos@inria.fr>
c     
c     This program is free software; you can redistribute it and/or modify
c     it under the terms of the GNU General Public License as published by
c     the Free Software Foundation; either version 2 of the License, or
c     (at your option) any later version.
c     
c     This program is distributed in the hope that it will be useful,
c     but WITHOUT ANY WARRANTY; without even the implied warranty of
c     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
c     GNU General Public License for more details.
c     
c     You should have received a copy of the GNU General Public License
c     along with this program; if not, see <http://www.gnu.org/licenses/>.
c     
c     See the file ./license.txt
c     

      subroutine forblk(flag,nevprt,t,xd,x,nx,z,nz,tvec,ntvec,
     &     rpar,nrpar,ipar,nipar,u,nu,y,ny)
c     Copyright INRIA

c     Scicos block simulator
c     For block
c
      double precision t,xd(*),x(*),z(*),tvec(*),rpar(*),u(*),y(*)
      integer flag,nevprt,nx,nz,ntvec,nrpar,ipar(*)
      integer nipar,nu,ny

c
      double precision atol,rtol,ttol,deltat
      common /costol/ atol,rtol,ttol,deltat
c
c     
      if(flag.eq.3) then
         if(nevprt.eq.1) then
            z(2)=u(1)
            z(1)=1.d0
c     
            if(u(1).ge.1) then
               tvec(1)=t-1.d0
               tvec(2)=t+ttol/2.0d0
            else
               tvec(1)=t-1.d0
               tvec(2)=t-1.d0
            endif

         else
            z(1)=z(1)+1.d0
c     
            if(z(1).ge.z(2)) then
               tvec(1)=t+ttol/2.0d0
               tvec(2)=t-1.d0
            else
               tvec(1)=t-1.d0
               tvec(2)=t+ttol/2.0d0
            endif
         endif
      endif

      if(flag.eq.1.or.flag.eq.3) then
         y(1)=z(1)
      endif
      
      end
