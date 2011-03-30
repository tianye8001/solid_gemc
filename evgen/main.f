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

      integer i,j

      real theta,mom,theta_deg,mom_mev

      Lumi = 1000000.0 ! 10^39  luminosity /cm^2/s (* nb) 10^-9*10^-28*10^4
      ebeam = 4.4 ! GeV
      
      mom_min = 3.5 ! GeV
      mom_max = 4.5 ! GeV
      
      theta_min_deg = 15.0 ! deg
      theta_max_deg = 20.0 ! deg
      
      ebeam_mev = ebeam * 1000.0
      mom_min_mev = mon_min * 1000.0
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
            theta = theta_min + (theta_max-theta_min)*i/100.0-
     c           (theta_max-theta_min)*i/200.0
            theta_deg = theta *180.0/3.1415926
            mom = mom_min + (mom_max-mom_min)*j/100.0 -
     c           (mom_max-mom_min)*j/200.0
            mom_mev = mom*1000.0
            
      ! calculate electron rate using whitlow
            call whitlow(0,ebeam_mev,mom_mev,0.,mom_mev,theta_deg,0.
     c           ,theta_deg,dxs_ele1,success)
            
            if (success.ne.0) then
               dxs_ele1 = 0.
            endif
            
            xs_ele1 = xs_ele1 + dxs_ele1*sin(theta)
            
       ! calculate electron rate using qfs                          
            call qfsrad(ebeam,mom,theta,0,dxs_ele2
     c     ,success)
            if (success.ne.0) then
               dxs_ele2 = 0.
            endif
            
            
            xs_ele2 = xs_ele2 + dxs_ele2*sin(theta)
       
!     calculate proton rate using wiser
            call wiser(5,0,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_p,success)
            if (success.ne.0) then
               dxs_p = 0.
            endif
            xs_p = xs_p + dxs_p*sin(theta)
            
       
!     calculate pip rate using wiser
            call wiser(1,0,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_pip,success)
            if (success.ne.0) then
               dxs_pip = 0.
            endif
            xs_pip = xs_pip + dxs_pip*sin(theta)

       
!     calculate pim rate using wiser
            call wiser(2,0,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_pim,success)
            if (success.ne.0) then
               dxs_pim = 0.
            endif
            xs_pim = xs_pim + dxs_pim*sin(theta)
            
       
!     calculate kp rate using wiser
            call wiser(3,0,ebeam_mev,mom_mev,0.1,mom_mev,
     c           theta_deg,0.1 
     c           ,theta_deg,dxs_kp,success)
            if (success.ne.0) then
               dxs_kp = 0.
            endif
            xs_kp = xs_kp + dxs_kp*sin(theta)

       
!     calculate km rate using wiser
            call wiser(4,0,ebeam_mev,mom_mev,0.1,mom_mev,
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
      
      print*,xs_ele2,",",xs_pip,",",xs_pim,",",xs_p,",",xs_kp,",",xs_km

      end
