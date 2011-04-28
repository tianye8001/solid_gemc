      PROGRAM main
      real ebeam,ebeam_mev
      real dxs_pip,dxs_pim,dxs_kp,dxs_km,dxs_ele1,dxs_ele2,dxs_p
      real xs_pip,xs_pim,xs_kp,xs_km,xs_ele1,xs_ele2,xs_p
      real rate_pip,rate_pim,rate_kp,rate_km,rate_ele1,rate_ele2,rate_p
      real Lumi
      
      real theta_min,theta_max
      real mom_min,mom_max

      real theta_min_deg,theta_max_deg
      real mom_min_mev,mom_max_mev

      real x_min,xmax
      real q2_min,q2_max

      real cos_theta_min_deg,cos_theta_max_deg

      real par1,par2,par3,par4

      integer target

      integer option

      integer i,j

      real theta,mom,theta_deg,mom_mev

  !DEFINE BUFFER HOLDS THE COMMAND LINE ARGUMENT
      CHARACTER *100 BUFFER  

  !GET THE PARAMETERS FROM THE COMMAND LINE ARGUMENT
      CALL GETARG(1,BUFFER)
      READ(BUFFER,*) target
      CALL GETARG(2,BUFFER)
      READ(BUFFER,*) Lumi      
      CALL GETARG(3,BUFFER)
      READ(BUFFER,*) ebeam
      CALL GETARG(4,BUFFER)
      READ(BUFFER,*) option
      CALL GETARG(5,BUFFER)
      READ(BUFFER,*) par1
      CALL GETARG(6,BUFFER)
      READ(BUFFER,*) par2
      CALL GETARG(7,BUFFER)
      READ(BUFFER,*) par3
      CALL GETARG(8,BUFFER)
      READ(BUFFER,*) par4

      if (option.eq.1) then
	print*,"use mom and theta as variables"
	mom_min=par1
	mom_max=par2
	theta_min_deg=par3
	theta_max_deg=par4
      else if (option.eq.2) then
	print*,"use x and Q2 as variables"
	x_min=par1
	x_max=par2
	q2_min=par3
	q2_max=par4
	mom_min=ebeam-(q2_max/x_min)/2./0.939
	mom_max=ebeam-(q2_min/x_max)/2./0.939
	if (mom_min.le.0) then 
	  print*,"mom_min ",mom_min
	  mom_min=0
	endif
	if (mom_max.ge.ebeam) then
	  print*,ebeam,"mom_max ",mom_max
	  mom_max=ebeam
	endif
	cos_theta_min_deg=1.-1./(2.*ebeam*(ebeam/q2_min-
     >     1./2./0.939/x_max))
	cos_theta_max_deg=1.-1./(2.*ebeam*(ebeam/q2_max-
     >     1./2./0.939/x_min))
	if (cos_theta_min_deg.ge.1.) then
	  print*,"cos_theta_min_deg ",cos_theta_min_deg
	  theta_min_deg=0.
	else 
	  theta_min_deg=acos(cos_theta_min_deg)/3.1415926*180.
	endif
	if (cos_theta_max_deg.le.-1.) then
	  print*,"cos_theta_max_deg ",cos_theta_max_deg
	  theta_max_deg=180.
	else 
	 theta_max_deg=acos(cos_theta_max_deg)/3.1415926*180.
	endif
      else 
	  print*,"wrong option"
      endif

      print*,"mom_min ",mom_min,"mom_max,",mom_max,"theta_min_deg,",theta_min_deg,"theta_max_deg,",theta_max_deg

!       Lumi = 1000000.0 ! 10^39  luminosity /cm^2/s (* nb) 10^-9*10^-28*10^4
!       ebeam = 4.4 ! GeV
!       
!       mom_min = 3.5 ! GeV
!       mom_max = 4.5 ! GeV
!       
!       theta_min_deg = 15.0 ! deg
!       theta_max_deg = 20.0 ! deg
      
      ebeam_mev = ebeam * 1000.0
      mom_min_mev = mom_min * 1000.0
      mom_max_mev = mom_max * 1000.0

      theta_min = theta_min_deg/180.0*3.1415926
      theta_max = theta_max_deg/180.0*3.1415926
      
       xs_pip=0.0
       xs_pim=0.0
       xs_kp=0.0
       xs_km=0.0
       xs_ele1=0.0
       xs_ele2=0.0
       xs_p=0.0

      ! assume 2-pi coverage in azimuthal angle
      do i=1,100
         do j=1,100
            theta = theta_min + (theta_max-theta_min)/100.0*(i+0.5)
            theta_deg = theta *180.0/3.1415926
            mom = mom_min + (mom_max-mom_min)*j/100.0*(j+0.5)
            mom_mev = mom*1000.0
            
! whitlow code somehow doesn't stepsize none 0

      ! calculate electron rate using whitlow
            call whitlow(target,ebeam_mev,mom_mev,0.,mom_mev,theta_deg
     c           ,0.,theta_deg,dxs_ele1,success)
            
            if (success.ne.0) then
               dxs_ele1 = 0.
            endif
            
            xs_ele1 = xs_ele1 + dxs_ele1*sin(theta)
            
       ! calculate electron rate using qfs                          
            call qfsrad(ebeam,mom,theta,target,dxs_ele2
     c     ,success)
            if (success.ne.0) then
               dxs_ele2 = 0.
            endif            
            
            xs_ele2 = xs_ele2 + dxs_ele2*sin(theta)

!    wiser code somehow doesn't take step as 0 if min=max,but it will ignore any other value, 0.1 here is a placeholder
       
!     calculate proton rate using wiser
            call wiser(5,target,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_p,success)
            if (success.ne.0) then
               dxs_p = 0.
            endif
            xs_p = xs_p + dxs_p*sin(theta)
            
       
!     calculate pip rate using wiser
            call wiser(1,target,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_pip,success)
            if (success.ne.0) then
               dxs_pip = 0.
            endif
            xs_pip = xs_pip + dxs_pip*sin(theta)

       
!     calculate pim rate using wiser
            call wiser(2,target,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_pim,success)
            if (success.ne.0) then
               dxs_pim = 0.
            endif
            xs_pim = xs_pim + dxs_pim*sin(theta)
            
       
!     calculate kp rate using wiser
            call wiser(3,target,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_kp,success)
            if (success.ne.0) then
               dxs_kp = 0.
            endif
            xs_kp = xs_kp + dxs_kp*sin(theta)

       
!     calculate km rate using wiser
            call wiser(4,target,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_km,success)
            if (success.ne.0) then
               dxs_km = 0.
            endif
            xs_km = xs_km + dxs_km*sin(theta)
         enddo
      enddo

     

      xs_ele1 = xs_ele1/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.
      xs_ele2 = xs_ele2/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.
      xs_p = xs_p/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.
      xs_pip = xs_pip/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.
      xs_pim = xs_pim/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.
      xs_kp = xs_kp/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.
      xs_km = xs_km/100./100.*(theta_max-theta_min)
     c     *2*3.1415926*(mom_max-mom_min)*Lumi/1000000.


      print*,"Electron from whitlow   :",xs_ele1,"MHz"
      print*,"Electron from qfs       :",xs_ele2,"MHz"
      print*,"Positive Pion from wiser:",xs_pip,"MHz"
      print*,"Negative Pion from wiser:",xs_pim,"MHz"
      print*,"Proton from wiser       :",xs_p,"MHz"
      print*,"Positive Kaon from wiser:",xs_kp,"MHz"
      print*,"Negative Kaon from wiser:",xs_km,"MHz"

      print*,xs_ele1," ",xs_ele2

      open(unit=11,file='ele1.dat',status='unknown')
      open(unit=12,file='ele2.dat',status='unknown')

      write(11,*) xs_ele1*1000000.  ! write out in unit Hz
      write(12,*) xs_ele2*1000000.  ! write out in unit Hz
         
      end
