# use strict;
use warnings;
our %detector;
our %configuration;
our %parameters;

use Getopt::Long;
use Math::Trig;
use Math::MatrixReal;  
use Math::VectorReal; 

sub makePMTs
{

    my $fluxPMT = 1;

    my $temp_off_V = vector(0.0,0.0,0.0);
    my $tempWindow_off_V = vector(0.0,0.0,0.0);
    my $tempWindow_pos_V = vector(0.0,0.0,0.0);
    my $Pos_obs_V = $Pos_im_Obs_V;
    my $Pos_obs_hfloff = vector(0.0, 0.0, -$PMT_hflngth);
    my $normVec = vector(0.0,0.0,1.0);
    my $RpM = Math::MatrixReal->new_from_rows( [ [1,0,0], [0,1,0], [0,0,1] ] ); 
    my $RpMx = Math::MatrixReal->new_from_rows( [ [1,0,0], [0,1,0], [0,0,1] ] );
    my $RpMy = Math::MatrixReal->new_from_rows( [ [1,0,0], [0,1,0], [0,0,1] ] );
    $RpM = &rotateZ($RpM,-$ang_zrot*$D2R);
    $RpMx = &rotateX($RpMx,-$ang_xrot*$D2R);
    $RpMy = &rotateY($RpMy,-$ang_yrot*$D2R);

    my $RpMxc = &VMconvert($RpMx);
    my $RpMyc = &VMconvert($RpMy);

    $Pos_obs_hfloff = $Pos_obs_hfloff*$RpMyc;
    $Pos_obs_hfloff = $Pos_obs_hfloff*$RpMxc;

    $Pos_obs_V = $Pos_obs_V + $Pos_obs_hfloff;

    my $pmtmat;
    if($fluxPMT){
	$pmtmat = "flux";
    }else{
	$pmtmat = "SOLIDCHER";
    }

 #   my $pmtmat = "SOLIDCHER";
 #   my $pmtmat = "flux";

    for(my $n=1; $n <= $Nsec; $n++)
    {
	$RpM = &rotateZ($RpM,12.0*$D2R);
	my $RpMc = &VMconvert($RpM);

	my $temp_pos_V = $Pos_obs_V;
	my $temp_posW_V = $Pos_obs_V + $Pos_obsWin_V;
	$temp_pos_V = $temp_pos_V*$RpMc;

	my $temp_init_V = $temp_pos_V;
	for(my $j = 0; $j < $pmtN; $j++){
	    for(my $k = 0; $k < $pmtN; $k++){
		if($pmtN%2){
		    $temp_off_V = vector(2.0*($j -($pmtN -1)/2.0)*$pmt_x,  2.0*($k -($pmtN -1)/2.0)*$pmt_x, $PMT_hflngth - 2*$PMTwindow_hfthk- 0.01);
		}else{
		    $temp_off_V = vector((2.0*$j - ($pmtN -1))*$pmt_x,  (2.0*$k - ($pmtN -1))*$pmt_x, $PMT_hflngth - 2*$PMTwindow_hfthk - 0.01);
		}
		$tempWindow_off_V = $temp_off_V + vector(0,0, $PMTwindow_hfthk + 0.01);


		$temp_off_V = $temp_off_V*$RpMxc;
		$temp_off_V = $temp_off_V*$RpMyc;
		$temp_off_V = $temp_off_V*$RpMc;

		$temp_pos_V = $temp_init_V + $temp_off_V;

		my %detector=init_det();
		$detector{"name"} = $namePre."PMT_".$n."_".$j."_".$k;
		$detector{"mother"} = $namePre."Tank";
		$detector{"description"} = "PMT number $n $j $k";
		$detector{"pos"} = sprintf('%.3f',$temp_pos_V->x())."*cm ".sprintf('%.3f',$temp_pos_V->y())."*cm ".sprintf('%.3f',$temp_pos_V->z())."*cm";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg -".$ang_yrot."*deg -".$ang_xrot."*deg";
		$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
		if($n == 1 && $j == 0 && $k == 0){
		    $normVec = $normVec*$RpMc;
		    $normVec = $normVec*$RpMxc;
		    $normVec = $normVec*$RpMyc;
		    print $normVec->x()."  ".$normVec->y()."  ".$normVec->z()."\n";

		    print "To test PMT from 1cm away, shoot gun from ".($temp_pos_V->x() + $normVec->x())."  ".($temp_pos_V->y() + $normVec->y())."  ".($temp_pos_V->z() + $normVec->z())."  at ".(asin($normVec->y())*180.0/3.14159)." degs in phi and ".(acos($normVec->z())*180.0/3.14159)." degs in theta.\n";
		}
		$detector{"color"}      = "ff0000";
		$detector{"type"}       = "Box";
		$detector{"dimensions"} = ($pmt_x - $pmt_shell)."*cm ".($pmt_x -$pmt_shell)."*cm 0.0001*mm";
# 		$detector{"material"}   = "H8500_PMToption"; 
	$detector{"material"}    = "Vacuum";
		$detector{"mfield"}     = "no";
		$detector{"ncopy"}      = 1;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = $pmtmat;
		$detector{"hit_type"}    = $pmtmat;
		if($fluxPMT){
		    $detector{"identifiers"} = "id manual ".$n.$j.$k;
		}else{
		    $detector{"identifiers"} = "sector manual $n pmt manual $j x manual $k";
		}
#		$detector{"identifiers"} = "id manual 1";
		print_det(\%configuration, \%detector);

#window
		$tempWindow_off_V = $tempWindow_off_V*$RpMxc;
		$tempWindow_off_V = $tempWindow_off_V*$RpMc;
		$tempWindow_pos_V = $temp_pos_V -$temp_off_V + $tempWindow_off_V;

		$detector{"name"} = $namePre."PMT_Window_".$n."_".$j."_".$k;
		$detector{"mother"} = $namePre."Tank";
		$detector{"description"} = "PMT number window $n $j $k";
		$detector{"pos"} = sprintf('%.3f',$tempWindow_pos_V->x())."*cm ".sprintf('%.3f',$tempWindow_pos_V->y())."*cm ".sprintf('%.3f',$tempWindow_pos_V->z())."*cm";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg -".$ang_yrot."*deg -".$ang_xrot."*deg";
		$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
		$detector{"color"}      = "ff00ff";
		$detector{"type"}       = "Box";
		$detector{"dimensions"} = ($pmt_x - $pmt_shell)."*cm ".($pmt_x -$pmt_shell)."*cm ".($PMTwindow_hfthk)."*cm";
# 		$detector{"material"}   = "H8500UVwin"; 
	$detector{"material"}    = "Vacuum";
		$detector{"mfield"}     = "no";
		$detector{"ncopy"}      = 1;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = "no";
		$detector{"hit_type"}    = "no";
		$detector{"identifiers"} = "no";
		print_det(\%configuration, \%detector);


#This following part is for a "sleeve" on each PMT.  It is turned off at the moment.

		$detector{"name"} = $namePre."PMTshell1_".$n."_".$j."_".$k;
		$detector{"mother"} = $namePre."Tank";
		$detector{"description"} = "PMT number $n $j $k";
		$detector{"pos"} = sprintf('%.3f',$temp_pos_V->x())."*cm ".sprintf('%.3f',$temp_pos_V->y())."*cm ".sprintf('%.3f',$temp_pos_V->z())."*cm";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
		$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
		$detector{"color"}      = "ff0000";
		$detector{"type"}       = "Box";
		$detector{"dimensions"} = ($pmt_x - $pmt_shell)."*cm ".($pmt_x - $pmt_shell)."*cm ".($PMT_hflngth - $PMTwindow_hfthk)."*cm";
		$detector{"material"}   = "Component";  #for now
		$detector{"mfield"}     = "no";
		$detector{"ncopy"}      = 1;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = "no";
		$detector{"hit_type"}    = "no";
		$detector{"identifiers"} = "no";
#		print_det(\%configuration, \%detector);

		$detector{"name"} = $namePre."PMTshell2_".$n."_".$j."_".$k;
		$detector{"mother"} = $namePre."Tank";
		$detector{"description"} = "PMT number $n $j $k";
		$detector{"pos"} = sprintf('%.3f',$temp_pos_V->x())."*cm ".sprintf('%.3f',$temp_pos_V->y())."*cm ".sprintf('%.3f',$temp_pos_V->z())."*cm";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
		$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
		$detector{"color"}      = "ff0000";
		$detector{"type"}       = "Box";
		$detector{"dimensions"} = $pmt_x."*cm ".$pmt_x."*cm ".($PMT_hflngth - $PMTwindow_hfthk)."*cm";
		$detector{"material"}   = "Component";
		$detector{"mfield"}     = "no";
		$detector{"ncopy"}      = 1;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = "no";
		$detector{"hit_type"}    = "no";
		$detector{"identifiers"} = "no";
#		print_det(\%configuration, \%detector);

		$detector{"name"} = $namePre."PMTshell_".$n."_".$j."_".$k;
		$detector{"mother"} = $namePre."Tank";
		$detector{"description"} = "PMT number $n $j $k";
		$detector{"pos"} = sprintf('%.3f',$temp_pos_V->x())."*cm ".sprintf('%.3f',$temp_pos_V->y())."*cm ".sprintf('%.3f',$temp_pos_V->z())."*cm";
#		$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
		$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
		$detector{"color"}      = "000000";
#		$detector{"dimensions"} = $pmt_x."*cm ".$pmt_x."*cm ".($PMT_hflngth - $PMTwindow_hfthk)."*cm";
		$detector{"type"}   = "Operation:@ ".$namePre."PMTshell2_".$n."_".$j."_".$k." - ".$namePre."PMTshell1_".$n."_".$j."_".$k;  #for now
#		$detector{"material"}   = "Kryptonite";
# 		$detector{"material"}   = "Aluminum";
	$detector{"material"}    = "Vacuum";
		$detector{"mfield"}     = "no";
		$detector{"ncopy"}      = 1;
		$detector{"pMany"}       = 1;
		$detector{"exist"}       = 1;
		$detector{"visible"}     = 1;
		$detector{"style"}       = 1;
		$detector{"sensitivity"} = "no";
		$detector{"hit_type"}    = "no";
		$detector{"identifiers"} = "no";
#		print_det(\%configuration, \%detector);

		#$temp_pos_V = $temp_pos_V - $temp_off_V;
	    }
	}

#this is for the PMT box enclosure.

	$temp_posW_V = $temp_posW_V*$RpMc;

	$detector{"name"} = $namePre."PMTbulk_".$n;
	$detector{"mother"} = $namePre."Tank";
	$detector{"description"} = "PMTbulk number $n";
	$detector{"pos"} = sprintf('%.3f',$temp_posW_V->x())."*cm ".sprintf('%.3f',$temp_posW_V->y())."*cm ".sprintf('%.3f',$temp_posW_V->z())."*cm";
#	$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
	$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
	$detector{"color"}      = "ff0000";
	$detector{"type"}       = "Box";
	$detector{"dimensions"} = $pmtN*$pmt_x."*cm ".$pmtN*$pmt_x."*cm ".$PMT_hflngth."*cm";
	$detector{"material"}   = "Component";
	$detector{"mfield"}     = "no";
	$detector{"ncopy"}      = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "no";
	$detector{"hit_type"}    = "no";
	$detector{"identifiers"} = "PMTbulk_$n";
#	print_det(\%configuration, \%detector);

	$detector{"name"} = $namePre."PMTframe_".$n;
	$detector{"mother"} = $namePre."Tank";
	$detector{"description"} = "PMTframe number $n";
	$detector{"pos"} = sprintf('%.3f',$temp_posW_V->x())."*cm ".sprintf('%.3f',$temp_posW_V->y())."*cm ".sprintf('%.3f',$temp_posW_V->z())."*cm";
#	$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
	$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
	$detector{"color"}      = "ff0000";
	$detector{"type"}       = "Box";
	$detector{"dimensions"} = ($pmtN*$pmt_x + $PMTbox_HL)."*cm ".($pmtN*$pmt_x + $PMTbox_HL)."*cm ".$PMT_hflngth."*cm";
	$detector{"material"}   = "Component"; 
	$detector{"mfield"}     = "no";
	$detector{"ncopy"}      = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "no";
	$detector{"hit_type"}    = "no";
	$detector{"identifiers"} = "PMTFrame_$n";
#	print_det(\%configuration, \%detector);

	$detector{"name"} = $namePre."PMTenclosure_".$n;
	$detector{"mother"} = $namePre."Tank";
	$detector{"description"} = "PMTenc number $n";
	$detector{"pos"} = sprintf('%.3f',$temp_posW_V->x())."*cm ".sprintf('%.3f',$temp_posW_V->y())."*cm ".sprintf('%.3f',$temp_posW_V->z())."*cm";
#	$detector{"rotation"}   = "ordered: zyx ".(-$ang_zrot + $n*12.0)."*deg 0*deg -".$ang_xrot."*deg";
	$detector{"rotation"}   = "ordered: zxy ".(-$ang_zrot + $n*12.0)."*deg -".$ang_xrot."*deg -".$ang_yrot."*deg";
	$detector{"color"}      = "000000";
	$detector{"type"}       = "Operation:@ ".$namePre."PMTframe_$n - ".$namePre."PMTbulk_$n";
	$detector{"material"}   = "Kryptonite"; 
	$detector{"mfield"}     = "no";
	$detector{"ncopy"}      = 1;
	$detector{"pMany"}       = 1;
	$detector{"exist"}       = 1;
	$detector{"visible"}     = 1;
	$detector{"style"}       = 1;
	$detector{"sensitivity"} = "no";
	$detector{"hit_type"}    = "no";
	$detector{"identifiers"} = "PMTenc_$n";
#	print_det(\%configuration, \%detector);


    }
}1;
