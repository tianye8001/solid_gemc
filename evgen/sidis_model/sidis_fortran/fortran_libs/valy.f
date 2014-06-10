
*VALY
      SUBROUTINE VALY(X,F)
      IMPLICIT REAL (A-H,O-Z)
C     REAL*8 FUNCTION F(X)
      COMMON/QFSPAR/E,TH,W,Z,A,EPS,EPSD,PF,SPENCE
      ALPH=1./137.03604
      EMASS=.511
      PI=ACOS(-1.)
      THR=TH*PI/180.
      SIG1=SIGQFS(E,TH,X,Z,A,EPS,PF)
      SIG1=SIG1+SIGDEL(E,TH,X,A,EPSD,PF)
      SIG1=SIG1+SIGX(E,TH,X,A)
      SIG1=SIG1+SIGR1(E,TH,X,A,PF)
      SIG1=SIG1+SIGR2(E,TH,X,A,PF)
      SIG1=SIG1+SIG2N(E,TH,X,Z,A,PF)
      SIG2=SIGQFS(E-W+X,TH,X,Z,A,EPS,PF)
      SIG2=SIG2+SIGDEL(E-W+X,TH,X,A,EPSD,PF)
      SIG2=SIG2+SIGX(E-W+X,TH,X,A)
      SIG2=SIG2+SIGR1(E-W+X,TH,X,A,PF)
      SIG2=SIG2+SIGR2(E-W+X,TH,X,A,PF)
      SIG2=SIG2+SIG2N(E-W+X,TH,X,Z,A,PF)
      QMS1=4.*E*(E-X)*SIN(THR/2.)**2
      QMS2=4.*(E-W+X)*(E-W)*SIN(THR/2.)**2
      QMSBAR=SQRT(QMS1*QMS2)
      F1=(LOG(QMS1/EMASS**2)-1.)/2./(E-X)**2
      F1=F1*SIG1
      F1=F1*ALPH*((E-X)**2+(E-W)**2)/(W-X)/PI
      F2=SIG2*(LOG(QMS2/EMASS**2)-1.)/2./E**2
      F2=F2*ALPH*(E**2+(E-W+X)**2)/(W-X)/PI
      D1=(2.*ALPH/PI)*(LOG(QMSBAR/EMASS**2)-1.)
      D2=13.*(LOG(QMSBAR/EMASS**2)-1.)/12.-17./36.
      D2=(2.*ALPH/PI)*(D2-0.5*(PI**2/6.-SPENCE))
      EBAR=SQRT((E-X)*(E-W))
      F=(F1+F2)*(1.+D2)*((W-X)/EBAR)**D1
      RETURN
      END
