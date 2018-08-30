package materials;
require Exporter;

use lib ("$ENV{GEMC}/io");
use utils;
use 5.010;

@ISA = qw(Exporter);
@EXPORT = qw(init_mat print_mat);


# Initialize hash maps
sub init_mat
{
	my %mat = ();
	
	# The default value for identifier is "id"
	$mat{"description"} = "id";
	
	# The optical properties are defaulted to none
	# User can define a optical property with arrays of:
	#
	# - photon wavelength (mandatory)
	# - At least one of the following quantities arrays
	$mat{"photonEnergy"}       = "none";
	$mat{"indexOfRefraction"}  = "none";
	$mat{"absorptionLength"}   = "none";
	$mat{"reflectivity"}       = "none";
	$mat{"efficiency"}         = "none";
	
	# scintillation specific
	$mat{"fastcomponent"}      = "none";
	$mat{"slowcomponent"}      = "none";
	$mat{"scintillationyield"} = "-1";
	$mat{"resolutionscale"}    = "-1";
	$mat{"fasttimeconstant"}   = "-1";
	$mat{"slowtimeconstant"}   = "-1";
	$mat{"yieldratio"}         = "-1";
	$mat{"rayleigh"}           = "none";
	
	return %mat;
}


# Print material to TEXT file or upload it onto the DB
sub print_mat
{
	my %configuration = %{+shift};
	my %mats          = %{+shift};
	
	my $table   = $configuration{"detector_name"}."__materials";
	my $varia   = $configuration{"variation"};
	
	# converting the hash maps in local variables
	# (this is necessary to parse the MYSQL command)
	my $lname               = trim($mats{"name"});
	my $ldesc               = trim($mats{"description"});
	my $ldensity            = trim($mats{"density"});
	my $lncomponents        = trim($mats{"ncomponents"});
	my $lcomponents         = trim($mats{"components"});
	my $lphotonEnergy       = trim($mats{"photonEnergy"});
	my $lindexOfRefraction  = trim($mats{"indexOfRefraction"});
	my $labsorptionLength   = trim($mats{"absorptionLength"});
	my $lreflectivity       = trim($mats{"reflectivity"});
	my $lefficiency         = trim($mats{"efficiency"});
	
	# scintillation specific
	my $lfastcomponent      = trim($mats{"fastcomponent"});
	my $lslowcomponent      = trim($mats{"slowcomponent"});
	my $lscintillationyield = trim($mats{"scintillationyield"});
	my $lresolutionscale    = trim($mats{"resolutionscale"});
	my $lfasttimeconstant   = trim($mats{"fasttimeconstant"});
	my $lslowtimeconstant   = trim($mats{"slowtimeconstant"});
	my $lyieldratio         = trim($mats{"yieldratio"});
	my $lrayleigh           = trim($mats{"rayleigh"});

	# after 5.10 once can use "state" to use a static variable`
	state $counter = 0;
	state $this_variation = "";
	
	# TEXT Factory
	if($configuration{"factory"} eq "TEXT")
	{
		my $file = $configuration{"detector_name"}."__materials_".$varia.".txt";
		
		if($counter == 0 || $this_variation ne  $varia)
		{
			`rm -f $file`;
			print "Overwriting if existing: ",  $file, "\n";
			$counter = 1;
			$this_variation = $varia;
		}
		
		open(INFO, ">>$file");
		printf INFO ("%20s  |",  $lname);
		printf INFO ("%30s  |",  $ldesc);
		printf INFO ("%10s  |",  $ldensity);
		printf INFO ("%10s  |",  $lncomponents);
		printf INFO ("%50s  |",  $lcomponents);
		
		if($lphotonEnergy eq "none")
		{
			printf INFO ("%5s  |",  $lphotonEnergy);
			printf INFO ("%5s  |",  $lindexOfRefraction);
			printf INFO ("%5s  |",  $labsorptionLength);
			printf INFO ("%5s  |",  $lreflectivity);
			printf INFO ("%5s  |",  $lefficiency);
			# scintillation
			printf INFO ("%5s  |",  $lfastcomponent);
			printf INFO ("%5s  |",  $lslowcomponent);
			printf INFO ("%5s  |",  $lscintillationyield);
			printf INFO ("%5s  |",  $lresolutionscale);
			printf INFO ("%5s  |",  $lfasttimeconstant);
			printf INFO ("%5s  |",  $lslowtimeconstant);
			printf INFO ("%5s  |", $lyieldratio);
			printf INFO ("%5s  \n", $lrayleigh);

		}
		else
		{
			printf INFO ("%s  |", $lphotonEnergy);
			
			# index of refraction
			if($lindexOfRefraction eq "none"){	printf INFO ("%5s |", $lindexOfRefraction);}
			else                             {	printf INFO ("%s  |", $lindexOfRefraction);}
			# absorption length
			if($labsorptionLength eq "none") {	printf INFO ("%5s |", $labsorptionLength);}
			else                             {  printf INFO ("%s  |", $labsorptionLength);}
			# reflectivity
			if($lreflectivity eq "none")     {  printf INFO ("%5s |", $lreflectivity);}
			else                             {	printf INFO ("%s  |", $lreflectivity);}
			# efficiency
			if($lefficiency eq "none")       {	printf INFO ("%5s |", $lefficiency);}
			else                             {	printf INFO ("%s  |", $lefficiency);}

			# scintillation
			
			# fast component (as function of wavelength)
			if($lfastcomponent eq "none")      {	printf INFO ("%5s |", $lfastcomponent);}
			else                               {	printf INFO ("%s  |", $lfastcomponent);}
			# slow component (as function of wavelength)
			if($lslowcomponent eq "none")      {	printf INFO ("%5s |", $lslowcomponent);}
			else                               {	printf INFO ("%s  |", $lslowcomponent);}
			# scintillation yield (constant)
			if($lscintillationyield eq "none") {	printf INFO ("%5s |", $lscintillationyield);}
			else                               {	printf INFO ("%s  |", $lscintillationyield);}
			# resolution scale (constant)
			if($lresolutionscale eq "none")    {	printf INFO ("%5s |", $lresolutionscale);}
			else                               {	printf INFO ("%s  |", $lresolutionscale);}
			# fast time (constant)
			if($lfasttimeconstant eq "none")   {	printf INFO ("%5s |", $lfasttimeconstant);}
			else                               {	printf INFO ("%s  |", $lfasttimeconstant);}
			# slow time (constant)
			if($lslowtimeconstant eq "none")   {	printf INFO ("%5s |", $lslowtimeconstant);}
			else                               {	printf INFO ("%s  |", $lslowtimeconstant);}
			# ratio of yield to total yield for slow component (constant)
			if($lyieldratio eq "none")         {	printf INFO ("%5s |", $lyieldratio);}
			else                               {	printf INFO ("%s  |", $lyieldratio);}
			# rayleigh scattering
			if($lrayleigh eq "none")           {	printf INFO ("%5s\n", $lrayleigh);}
			else                               {	printf INFO ("%s \n", $lrayleigh);}

		
		}
		
		close(INFO);
	}
	
	# MYSQL Factory
	my $err;
	if($configuration{"factory"} eq "MYSQL")
	{
		my $dbh = open_db(%configuration);
		
		$dbh->do("insert into $table( \
			          name,     description,     density,    ncomponents,    components,    photonEnergy,    indexOfRefraction,    absorptionLength,    reflectivity,   efficiency,   fastcomponent,   slowcomponent,   scintillationyield,   resolutionscale,   fasttimeconstant,   slowtimeconstant,   yieldratio,  rayleigh,   variation) \
			values(      ?,               ?,           ?,              ?,             ?,               ?,                    ?,                   ?,               ?,            ?,               ?,               ?,                    ?,                 ?,                  ?,                  ?,            ?,         ?,           ?)   ON DUPLICATE KEY UPDATE \
			        name=?,   description=?,   density=?,  ncomponents=?,  components=?,  photonEnergy=?,  indexOfRefraction=?,  absorptionLength=?,  reflectivity=?, efficiency=?, fastcomponent=?, slowcomponent=?, scintillationyield=?, resolutionscale=?, fasttimeconstant=?, slowtimeconstant=?, yieldratio=?,rayleigh=?, variation=?, \
			        time=CURRENT_TIMESTAMP",  undef,
			        $lname,          $ldesc,   $ldensity,  $lncomponents,  $lcomponents,  $lphotonEnergy,  $lindexOfRefraction,  $labsorptionLength,  $lreflectivity, $lefficiency, $lfastcomponent, $lslowcomponent, $lscintillationyield, $lresolutionscale, $lfasttimeconstant, $lslowtimeconstant, $lyieldratio, $lrayleigh, $varia,
			        $lname,          $ldesc,   $ldensity,  $lncomponents,  $lcomponents,  $lphotonEnergy,  $lindexOfRefraction,  $labsorptionLength,  $lreflectivity, $lefficiency, $lfastcomponent, $lslowcomponent, $lscintillationyield, $lresolutionscale, $lfasttimeconstant, $lslowtimeconstant, $lyieldratio, $lrayleigh, $varia)
			
			or die "SQL Error: $DBI::errstr\n";
		
		$dbh->disconnect();
	}
	
	if($configuration{"verbosity"} > 0)
	{
		print "  + Material $lname uploaded successfully for variation \"$varia\" \n";
	}
}


1;





