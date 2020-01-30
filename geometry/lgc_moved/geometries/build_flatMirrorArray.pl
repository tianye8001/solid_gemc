sub make_mirror1
{
	
	my $GeoOpt = 0;  #0 for cone, 1 for trapezoid
	
	
	
    my $V0_tg_V = vector(0.,0.,$ztarg_cent1);

    $R = 0.;  #zero out buildSPmirror globals
    $PosV = vector(0.,0.,0.);
    
    my $mirrRotPoint = vector(0.0, (-$V0_tg_V->z() + $zMirrRotPoint1)*tan($cr_ang1*$D2R), $zMirrRotPoint1);

    my $Z_front = $frontPlaneZ - $V0_tg_V->z();
    my $Z_end = $backPlaneZ - $V0_tg_V->z();
    
    my $R_front_in = $Z_front*tan($Angle_in1*$D2R);
    my $R_front_out = $Z_front*tan($Angle_out1*$D2R);
    my $R_end_in = $Z_end*tan($Angle_in1*$D2R);
    my $R_end_out = $Z_end*tan($Angle_out1*$D2R);

    &buildSPmirror($V0_tg_V, $Pos_im_Obs_V, $cr_ang1, $Z_M1);
    print "MIRROR 1:\n";
    print "sphere center $PosV\n";
    print "sphere R: $R\n";

    my $PosV_temp = $PosV;
    my $PosV_cone = vector(0.,0.,250.5);
	my $PosV_coneIni = vector(0.,0.,250.5);
    my $PosV_delta = vector(0., 0., 0.);
	my $PosV_deltaF = vector(0., 0., 0.);
    my $PosV_deltaC = vector(0., 0., 0.);
    
    if($mirrAng1 != 0.0){
	print "Mirror 1 ang = ".$mirrAng1."\n";
	$PosV_delta = mirrorRot($cr_ang1, $PosV_temp, $mirrAng1, $ztarg_cent1, $zMirrRotPoint1);
	$PosV_temp = $PosV_temp + $PosV_delta;
	$PosV_deltaC = mirrorRot($cr_ang1, $PosV_cone, $mirrAng1, $ztarg_cent1, $zMirrRotPoint1);
	print $PosV_deltaC;
	$PosV_cone = $PosV_cone + $PosV_deltaC;
	print $PosV_cone;
	print "Mirror Z-rot point: ". $zMirrRotPoint1."\n";
    }
    my $PosV_temp_CM = $PosV_temp;
    my $RotPointV = vector(0, $PosV->y() - sqrt($R*$R - ($zMirrRotPoint1 - $PosV->z())*($zMirrRotPoint1 - $PosV->z())), $zMirrRotPoint1);

    &calcIntPoints($R, $PosV_temp, $PosV_cone, 0.5*($Z_end - $Z_front), $R_front_in, $R_front_out, $R_end_in, $R_end_out, -$mirrAng1);

	my $rotAng = $initRot;
	#my $rotAng = 0.0;
	$PosV_temp = &rotateZv($PosV_temp, $initRot*$D2R);
	$PosV_cone = &rotateZv($PosV_cone, $initRot*$D2R);
	$PosV_temp_CM = &rotateZv($PosV_temp_CM, $initRot*$D2R);
	
	
	my $nMirVert = 4;
	my $nMirHor = 3;
	
	
	
    for(my $n=1; $n<=$Nsec; $n++)
    {
	$rotAng += 12.0;
	
	$PosV_cone = &rotateZv($PosV_cone,12.0*$D2R);
	$PosV_temp = &rotateZv($PosV_temp, 12.0*$D2R);
	$PosV_temp_CM = &rotateZv($PosV_temp_CM,12.0*$D2R);
	
	#we need to verify the with the other mirrors:
	
     $detector{"name"}        = $namePre."Mirror1s_$n";
     $detector{"mother"}      = $namePre."Tank" ;
     $detector{"description"} = "Mirror1 Sphere number $n";
     $detector{"pos"}        = sprintf('%.3f',$PosV_temp->x())."*cm ".sprintf('%.3f',$PosV_temp->y())."*cm ".sprintf('%.3f',$PosV_temp->z())."*cm";
     $detector{"rotation"}   = "0*deg 0*deg 0*deg";
     $detector{"color"}      = "66bbff";
     $detector{"type"}       = "Sphere";
     $detector{"dimensions"} = sprintf('%.3f',$R)."*cm ". sprintf('%.3f',$R + 0.1*$T_M1)."*cm 0.0 360.0*deg 0.0 90.0*deg";
     $detector{"material"}   = "Component";
     $detector{"mfield"}     = "no";
     $detector{"ncopy"}      = 1;
     $detector{"pMany"}       = 1;
     $detector{"exist"}       = 1;
     $detector{"visible"}     = 1;
     $detector{"style"}       = 1;
     $detector{"sensitivity"} = "no";
     $detector{"hit_type"}    = "no";
     $detector{"identifiers"} = "Mirror1 sphere $n";
     
     print_det(\%configuration, \%detector);

    # $PosV_cone = &rotateZv($PosV_cone,12.0*$D2R);

     $detector{"name"}        = $namePre."Mirror1c_$n";
     $detector{"mother"}      = $namePre."Tank" ;
     $detector{"description"} = "Mirror1 cone $n";
     $detector{"pos"}        = sprintf('%.3f',$PosV_cone->x())."*cm ".sprintf('%.3f',$PosV_cone->y())."*cm ".sprintf('%.3f',$PosV_cone->z())."*cm";
     #$detector{"rotation"}   = "ordered: zyx ".(12.0*$n)."*deg 0*deg ".(-$mirrAng1)."*deg"; 
     $detector{"rotation"}   = "ordered: zyx ".$rotAng."*deg 0*deg ".(-$mirrAng1)."*deg";    
     $detector{"color"}      = "66bbff";
     $detector{"type"}       = "Cons";
     $detector{"dimensions"} = sprintf('%.3f',$R_front_in)."*cm ". sprintf('%.3f',$R_front_out)."*cm ".sprintf('%.3f',$R_end_in)."*cm ".sprintf('%.3f',$R_end_out)."*cm ".sprintf('%.3f',0.5*($Z_end - $Z_front))."*cm "." 84*deg 12*deg";
     $detector{"material"}   = "Component";
     $detector{"mfield"}     = "no";
     $detector{"ncopy"}      = 1;
     $detector{"pMany"}       = 1;
     $detector{"exist"}       = 1;
     $detector{"visible"}     = 1;
     $detector{"style"}       = 1;
     $detector{"sensitivity"} = "no";
     $detector{"hit_type"}    = "no";
     $detector{"identifiers"} = "Mirror1 cone $n";
     
     print_det(\%configuration, \%detector);

     #$PosV_temp_CM = &rotateZv($PosV_temp_CM,12.0*$D2R);     
     
     $detector{"name"}        = $namePre."Mirror1_".&sec($n);
     $detector{"mother"}      = $namePre."Tank" ;
     $detector{"description"} = "Mirror1 segment ".&sec($n);
     $detector{"pos"}        = sprintf('%.3f',$PosV_temp_CM->x())."*cm ".sprintf('%.3f',$PosV_temp_CM->y())."*cm ".sprintf('%.3f',$PosV_temp_CM->z())."*cm";
     $detector{"rotation"}   = "0*deg 0*deg 0*deg";
     $detector{"color"}      = "661111";
     $detector{"type"}       = "Operation:@ ".$namePre."Mirror1s_$n * ".$namePre."Mirror1c_$n";
     $detector{"material"}   = "SL_RCFP";
     $detector{"mfield"}     = "no";
     $detector{"ncopy"}      = 1;
     $detector{"pMany"}       = 1;
     $detector{"exist"}       = 1;
     $detector{"visible"}     = 1;
     $detector{"style"}       = 1;
     $detector{"sensitivity"} = "mirror: LGC_Mirror";
     $detector{"hit_type"}    = "mirror";
     $detector{"identifiers"} = "no";
    # print_det(\%configuration, \%detector);
     
 
	
	
	
	
	
	
	for(my $nv = 0; $nv < $nMirVert; $nv++){
		
		my $ylen = $R_end_out - $R_end_in;
		my $ystep = $ylen/$nMirVert;
		my $yvert = $R_end_in + 0.5*$ystep + $nv*$ystep;
		
		my $newRendIn = $yvert - 0.5*$ystep;
		my $newRendOut = $yvert + 0.5*$ystep;
		
		my $newRfrontIn = $R_front_in + $nv*($R_front_out - $R_front_in)/$nMirVert;
		my $newRfrontOut = $R_front_in + ($nv + 1)*($R_front_out - $R_front_in)/$nMirVert;
		
		
		
		for(my $nh = 0; $nh < $nMirHor; $nh++){
			
			my $ystepFac = 12.0*$D2R/$nMirHor;
			my $xvert = $yvert*(-12.0*$D2R/2.0 + ($nh + 0.5)*$ystepFac);
			
			my $zvert = sqrt(($R + 0.1*$T_M1/2.0)*($R + 0.1*$T_M1/2.0) - ($xvert - $PosV->x())*($xvert -  $PosV->x()) - ($yvert - $PosV->y())*($yvert -  $PosV->y())) + $PosV->z();
			#my $zvert = sqrt($R*$R - ($xvert)*($xvert) - ($yvert)*($yvert));
			my $PosV_flatSeg = vector($xvert, $yvert, $zvert);
			my $normVec = vector($PosV->x() - $xvert, $PosV->y() - $yvert, $PosV->z() - $zvert);
			my $norm = sqrt($normVec->x()*$normVec->x() + $normVec->y()*$normVec->y() + $normVec->z()*$normVec->z());
			
			my $coneRotini = 84.0 + $nh*$ystepFac/$D2R;
			my $coneRotfin = $ystepFac/$D2R;
			
			#$PosV_flatSeg = &rotateZv($PosV_flatSeg, $initRot*$D2R + $n*12.0*$D2R);
			#$normVec = &rotateZv($normVec, $initRot*$D2R + $n*12.0*$D2R);
			my $rotFlatz = 90 - acos($normVec->z()/$norm)/$D2R;
			my $rotFlatx = (90 - acos($normVec->x()/$norm)/$D2R)*1.0;
			my $rotFlaty = (90 - acos($normVec->y()/$norm)/$D2R)*1.05;
			
			my $PosV_flatSegFin = vector($PosV_flatSeg->x(), $PosV_flatSeg->y(), $PosV_flatSeg->z());
			#$PosV_flatSegFin -= $PosV;
			
			if($mirrAng1){
				$PosV_deltaF = mirrorRot($cr_ang1, $PosV_flatSeg, $mirrAng1, $ztarg_cent1, $zMirrRotPoint1);
				$PosV_flatSeg  += $PosV_delta + $PosV_deltaF;
				#$PosV_flatSeg = &rotateXv($PosV_flatSeg, -$mirrAng1*$D2R);
				#$PosV_flatSeg  += $PosV_delta;
			}
			
			
		
			
			
			
			#for trapezodial sections:
			
			my $TrapIniRot = $coneRotfin*$D2R;
			
			#print "ROT:   ".$coneRotfin."  ".$coneRotini."\n";
			
			my $pDz = 0.5*($Z_end - $Z_front);
			my $pDy1 = ($newRfrontOut - $newRfrontIn)*0.5;
			my $pDy2 = ($newRendOut - $newRendIn)*0.5;
			my $pTheta =  atan((($newRendOut - $newRendIn) - ($newRfrontOut - $newRfrontIn))/($Z_end - $Z_front))/$D2R;
			my $pPhi = 0.0;
			my $pDx1 = $newRfrontIn*sin($TrapIniRot*0.5);
			my $pDx2 = $newRfrontOut*sin($TrapIniRot*0.5);
			my $pDx3 = $newRendIn*sin($TrapIniRot*0.5);
			my $pDx4 = $newRendOut*sin($TrapIniRot*0.5);
			my $pAlp1 = 0.0;
			my $pAlp2 = 0.0;
			
			my $TrapR = (($newRendOut + $newRendIn)*0.5 + ($newRfrontOut + $newRfrontIn)*0.5)*0.5;
			
			my $TrapZ = $PosV_coneIni->z();
			my $TrapX = $PosV_coneIni->x() + $TrapR*cos($coneRotini*$D2R + $TrapIniRot*0.5);
			my $TrapY = $PosV_coneIni->y() + $TrapR*sin($coneRotini*$D2R + $TrapIniRot*0.5);
			
			print "POS:  ".$TrapX."  ".$TrapY."  ".$TrapZ."\n";
			
			my $TrapVec = vector($TrapX, $TrapY, $TrapZ);
			my $TrapVecIni = vector($TrapX, $TrapY, $TrapZ);
			my $TrapZrot = 90.0 - ($coneRotini*$D2R + $TrapIniRot*0.5)/$D2R;
			
			
			$TrapVec = &rotateZv($TrapVec, ($initRot + $n*12.0)*$D2R);
			
			
		
			
			
			#print $PosV_flatSeg;
			#print $PosV_coneIni."----------\n";
			
			#print $PosV_flatSeg;
			#
			#$PosV_flatSeg -= $PosV_cone;
			
			#my $PosVsz = vector(0.0, 0.0, $PosV_temp->z());
			#$PosV_flatSeg -= $PosVsz;
			
			
			
			print $n." | ".$nv." | ".$nh."\n";
			print $n." | ".$nv." | ".$nh."\n";
			
			
			
			$detector{"name"}        = $namePre."Mirror1c_".$n."_".$nv."_".$nh;
			$detector{"mother"}      = $namePre."Tank" ;
			$detector{"description"} = "Mirror1 cone $n $nv $nh";
			#print sprintf('%.3f',$PosV_cone->x())."*cm ".sprintf('%.3f',$PosV_cone->y())."*cm ".sprintf('%.3f',$PosV_cone->z())."*cm\n";
			#$detector{"rotation"}   = "ordered: zyx ".(12.0*$n)."*deg 0*deg ".(-$mirrAng1)."*deg";	
			#$detector{"rotation"}   = "ordered: zyx ".$rotAng."*deg 0*deg ".(-$mirrAng1)."*deg";
			
			if($n%2){
				if(($nv + $nh)%2){
					$detector{"color"}      = "66bbff";
				}else{
					$detector{"color"}      = "60b0f0";
				}
			}else{
				if(($nv + $nh)%2){
					$detector{"color"}      = "86bbff";
				}else{
					$detector{"color"}      = "80b0f0";
				}
			}
			#print sprintf('%.3f',$newRfrontIn)."*cm ". sprintf('%.3f',$newRfrontOut)."*cm ".sprintf('%.3f',$newRendIn)."*cm ".sprintf('%.3f',$newRendOut)."*cm ".sprintf('%.3f',0.5*($Z_end - $Z_front))."*cm ".sprintf('%.3f',$coneRotini)."*deg ".sprintf('%.3f',$coneRotfin)."*deg\n";
			$detector{"material"}   = "Component";
#			$detector{"material"}   = "SL_RCFP";
			$detector{"mfield"}     = "no";
			$detector{"ncopy"}      = 1;
			$detector{"pMany"}       = 1;
			$detector{"exist"}       = 1;
			$detector{"visible"}     = 1;
			$detector{"style"}       = 1;
			$detector{"sensitivity"} = "no";
			$detector{"hit_type"}    = "no";
			$detector{"identifiers"} = "Mirror1 cone $n $nv $nh";
			
			
			
			##############Switch for cone or trapezoid:
			
			if($GeoOpt == 0){
				############## FOR CONE #################
				$detector{"type"}       = "Cons";
				$detector{"pos"}        = sprintf('%.3f',$PosV_coneIni->x())."*cm ".sprintf('%.3f',$PosV_coneIni->y())."*cm ".sprintf('%.3f',$PosV_coneIni->z())."*cm";
				$detector{"rotation"}   = "ordered: zyx 0.*deg 0*deg ".(-$mirrAng1)."*deg";
				$detector{"dimensions"} = sprintf('%.3f',$newRfrontIn)."*cm ". sprintf('%.3f',$newRfrontOut)."*cm ".sprintf('%.3f',$newRendIn)."*cm ".sprintf('%.3f',$newRendOut)."*cm ".sprintf('%.3f',0.5*($Z_end - $Z_front))."*cm ".sprintf('%.3f',$coneRotini)."*deg ".sprintf('%.3f',$coneRotfin)."*deg";
				$PosV_flatSeg -= $PosV_coneIni;
			}else{
				############## FOR TRAP #################
				$detector{"type"}       = "G4Trap";
				$detector{"pos"}        = sprintf('%.3f',$TrapVecIni->x())."*cm ".sprintf('%.3f',$TrapVecIni->y())."*cm ".sprintf('%.3f',$TrapVecIni->z())."*cm";
				$detector{"rotation"}   = sprintf('ordered: zyx %.3f',$TrapZrot)."*deg 0*deg ".sprintf('%.3f',-$mirrAng1)."*deg";
				#$detector{"rotation"}   = sprintf('ordered: zyx %.3f',0.0)."*deg 0*deg ".sprintf('%.3f',-$mirrAng1)."*deg";
				$detector{"dimensions"} = sprintf('%.3f',$pDz)."*cm ".sprintf('%.3f',$pTheta)."*deg ".sprintf('%.3f',$pPhi)."*deg ".sprintf('%.3f',$pDy1)."*cm ".sprintf('%.3f',$pDx1)."*cm ".sprintf('%.3f',$pDx2)."*cm ".sprintf('%.3f',$pAlp1)."*deg ".sprintf('%.3f',$pDy2)."*cm ".sprintf('%.3f',$pDx3)."*cm ".sprintf('%.3f',$pDx4)."*cm ".sprintf('%.3f',$pAlp2)."*deg";
				print "TRAP DIMENSIONS: ".sprintf('%.3f',$pDz)."*cm ".sprintf('%.3f',$pTheta)."*deg ".sprintf('%.3f',$pPhi)."*deg ".sprintf('%.3f',$pDy1)."*cm ".sprintf('%.3f',$pDx1)."*cm ".sprintf('%.3f',$pDx2)."*cm ".sprintf('%.3f',$pAlp1)."*deg ".sprintf('%.3f',$pDy2)."*cm ".sprintf('%.3f',$pDx3)."*cm ".sprintf('%.3f',$pDx4)."*cm ".sprintf('%.3f',$pAlp2)."*deg\n";
				$PosV_flatSeg -= $TrapVecIni;
			}
			
			
			print_det(\%configuration, \%detector);
			
			
			
			
			
		
			
			$PosV_flatSeg = &rotateYv($PosV_flatSeg,-$rotFlatx*$D2R);
			$PosV_flatSeg = &rotateXv($PosV_flatSeg,($rotFlaty + $mirrAng1)*$D2R);
			
			
			$detector{"name"}        = $namePre."Mirror1f_".$n."_".$nv."_".$nh;
			$detector{"mother"}      = $namePre."Tank" ;
			$detector{"description"} = "Mirror1 flat number $n $nv $nh";
			$detector{"pos"}        = sprintf('%.3f',$PosV_flatSeg->x())."*cm ".sprintf('%.3f',$PosV_flatSeg->y())."*cm ".sprintf('%.3f',$PosV_flatSeg->z())."*cm";
	#		$detector{"pos"}        = sprintf('%.3f',$PosV_flatSegFin->x())."*cm ".sprintf('%.3f',$PosV_flatSegFin->y())."*cm ".sprintf('%.3f',$PosV_flatSegFin->z())."*cm";
			#$detector{"pos"}        = "0*cm 0*cm 0*cm";
	#		print sprintf('%.3f',$PosV_flatSeg->x())."*cm ".sprintf('%.3f',$PosV_flatSeg->y())."*cm ".sprintf('%.3f',$PosV_flatSeg->z())."*cm\n";
			#$detector{"rotation"}   = "ordered: zyx ".sprintf('%.3f',$rotFlatz)."*deg ".sprintf('%.3f',$rotFlaty)."*deg ".sprintf('%.3f',$rotFlatx)."*deg";
			$detector{"rotation"}   = "ordered: zyx ".sprintf('%.3f',0.0)."*deg ".sprintf('%.3f',-$rotFlatx)."*deg ".sprintf('%.3f',-$rotFlaty - $mirrAng1)."*deg";
		#	print "ordered: zyx ".sprintf('%.3f',$rotFlatz)."*deg ".sprintf('%.3f',-$rotFlaty)."*deg ".sprintf('%.3f',$rotFlatx/2.0)."*deg\n";
		#	print "ordered: zyx ".sprintf('%.3f',0.0)."*deg ".sprintf('%.3f',$rotFlaty)."*deg ".sprintf('%.3f',-$rotFlatx)."*deg\n";
			#print "ordered: zyx ".sprintf('%.3f',0.0)."*deg ".sprintf('%.3f',0)."*deg ".sprintf('%.3f',-$rotFlatx)."*deg\n";
			$detector{"color"}      = "66bbff";
			$detector{"type"}       = "Box";
			$detector{"dimensions"} = ($ylen)."*cm ".($ylen)."*cm ".(0.05*$T_M1)."*cm";
			$detector{"material"}   = "Component";
#			$detector{"material"}   = "SL_RCFP";
			$detector{"mfield"}     = "no";
			$detector{"ncopy"}      = 1;
			$detector{"pMany"}       = 1;
			$detector{"exist"}       = 1;
			$detector{"visible"}     = 1;
			$detector{"style"}       = 1;
			$detector{"sensitivity"} = "no";
			$detector{"hit_type"}    = "no";
			$detector{"identifiers"} = "Mirror1 flat $n $nv $nh";
			
			print_det(\%configuration, \%detector);
			
			#$PosV_flatSeg += $PosV_coneIni;
			#$PosV_flatSeg = &rotateXv($PosV_flatSeg,-$rotFlaty*$D2R);
			
			
			
			$detector{"name"}        = $namePre."Mirror1_".&sec($n)."_".$nv."_".$nh;
			#$detector{"name"}        = $namePre."Mirror1_".&sec($n);
			$detector{"mother"}      = $namePre."Tank" ;
			$detector{"description"} = "Mirror1 segment ".&sec($n)."_".$nv."_".$nh;
#			$detector{"pos"}        = sprintf('%.3f',$PosV_temp_CM->x())."*cm ".sprintf('%.3f',$PosV_temp_CM->y())."*cm ".sprintf('%.3f',$PosV_temp_CM->z())."*cm";
#			$detector{"pos"}        = sprintf('%.3f',$PosV_flatSegFin->x())."*cm ".sprintf('%.3f',$PosV_flatSegFin->y())."*cm ".sprintf('%.3f',$PosV_flatSegFin->z())."*cm";



		if($GeoOpt == 0){
			$detector{"pos"}        = sprintf('%.3f',$PosV_cone->x())."*cm ".sprintf('%.3f',$PosV_cone->y())."*cm ".sprintf('%.3f',$PosV_cone->z())."*cm";
		}else{
			$detector{"pos"}        = sprintf('%.3f',$TrapVec->x())."*cm ".sprintf('%.3f',$TrapVec->y())."*cm ".sprintf('%.3f',$TrapVec->z())."*cm";
		}



#			print sprintf('%.3f',$PosV_temp_CM->x())."*cm ".sprintf('%.3f',$PosV_temp_CM->y())."*cm ".sprintf('%.3f',$PosV_temp_CM->z())."*cm\n";
			#$detector{"rotation"}     = "0*deg ".sprintf('%.3f',-$rotFlatx)."*deg 0*deg";
			$detector{"rotation"}   = "ordered: zyx ".$rotAng."*deg 0*deg 0*deg";
			#$detector{"rotation"}     = "0*deg 0*deg 0*deg";
#			$detector{"rotation"} = "ordered: zyx ".sprintf('%.3f',0.0)."*deg ".sprintf('%.3f',$rotFlatx)."*deg ".sprintf('%.3f',-$rotFlaty)."*deg";
			if($n%2){
				if(($nv + $nh)%2){
					$detector{"color"}      = "66bbff";
				}else{
					$detector{"color"}      = "60b0f0";
				}
			}else{
				if(($nv + $nh)%2){
					$detector{"color"}      = "86bbff";
				}else{
					$detector{"color"}      = "80b0f0";
				}
			}

#			$detector{"color"}      = "661111";
			$detector{"type"}       = "Operation:~ ".$namePre."Mirror1c_".$n."_".$nv."_".$nh." * ".$namePre."Mirror1f_".$n."_".$nv."_".$nh;
#			$detector{"type"}       = "Operation: ".$namePre."Mirror1f_".$n."_".$nv."_".$nh." * ".$namePre."Mirror1c_".$n."_".$nv."_".$nh;
			#print "Operation:@~ ".$namePre."Mirror1c_".$n."_".$nv."_".$nh." * ".$namePre."Mirror1f_".$n."_".$nv."_".$nh."\n";
			$detector{"material"}   = "SL_RCFP";
			$detector{"mfield"}     = "no";
			$detector{"ncopy"}      = 1;
			$detector{"pMany"}       = 1;
			$detector{"exist"}       = 1;
			$detector{"visible"}     = 1;
			$detector{"style"}       = 1;
			$detector{"sensitivity"} = "mirror: LGC_Mirror";
			$detector{"hit_type"}    = "mirror";
			$detector{"identifiers"} = "no";
			print_det(\%configuration, \%detector);
			
		
		}
	}
	
    }
}1;

