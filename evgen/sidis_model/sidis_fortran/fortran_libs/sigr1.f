
*SIGR1
      REAL FUNCTION SIGR1(E,TH,W,A,PF)
      IMPLICIT REAL (A-H,O-Z)
      PI=ACOS(-1.)
      PM=939.
      PIMASS=140.
      THR=TH*PI/180.
      PFR=230.
      RM=1500.
      EPSR=0.
      AR0=1000.
      AR1=1000.
      GAMQFR=120.
      GAMSPRD=140.
      GAMR=110.
      GAMPI=5.
      QFRP=1.20D-7
      QMSQFR=4.*730.*(730.-115.)*SIN(37.1*PI/180./2.)**2
      QVSQFR=QMSQFR+115.**2
      QMSRR=4.*10000.*(10000.-1240.)*SIN(6.*PI/180./2.)**2
      QVSRR=QMSRR+1240.**2
      SIGREF=FD(QMSRR,AR0)**2*QVSRR
      SIGREF=SIGREF*(QMSRR/2./QVSRR+TAN(6.*PI/180./2.)**2)
      SIGREF=SIGREF*SIGMOT(10000.0,6.*PI/180.)
      NA=INT(A)
      IF(NA.EQ.1)THEN
      QFR=QFRP
      GSPRDA=0.
      AR=AR0
      ELSEIF(NA.LT.4)THEN
      QFR=QFRP
      GSPRDA=(A-1.)*GAMSPRD/3.
      AR=AR0+(A-1.)*(AR1-AR0)/3.
      ELSE
      AR=AR1
      GSPRDA=GAMSPRD
      QFR=QFRP
      ENDIF
      QMS=4.*E*(E-W)*SIN(THR/2.)**2
      QVS=QMS+W**2
      IF(NA.GT.1)THEN
      GAMQ=GAMQFR*PF*SQRT(QVS)/PFR/SQRT(QVSQFR)
      ELSE
      GAMQ=0.
      ENDIF
      CMTOT2=PM**2+2.*PM*W-QMS
      WTHRESH=4.*E**2*SIN(THR/2.)**2+PIMASS**2+2.*PIMASS*PM
      WTHRESH=WTHRESH/2./PM
      THRESHD=1.+PF/PM+PF**2/2./PM**2+2.*E*SIN(THR/2.)**2/PM
      WTHRESH=WTHRESH/THRESHD
      IF(W.GT.WTHRESH)THEN
      THRESH=1.-EXP(-(W-WTHRESH)/GAMPI)
      ELSE
      THRESH=0.
      ENDIF
      EPR=E-(RM-PM)*(RM+PM)/2./PM
      EPR=EPR/(1.+2.*E*SIN(THR/2.)**2/PM)
      EPR=EPR-EPSR
      WR=E-EPR
      GAM=SQRT(GAMR**2+GAMQ**2+GSPRDA**2)
      SIGR=QFR*(GAMR/GAM)/SIGREF
      SIGR=SIGR*CMTOT2*GAM**2
      SIGR=SIGR/((CMTOT2-(RM+EPSR)**2)**2+CMTOT2*GAM**2)
      SIGR=SIGR*QVS*FD(QMS,AR)**2
      SIGR=SIGR*(QMS/2./QVS+TAN(THR/2.)**2)
      SIGR=SIGR*SIGMOT(E,THR)
      SIGR1=A*THRESH*SIGR
      RETURN
      END
