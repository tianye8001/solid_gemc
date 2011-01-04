#!/usr/bin/perl

# We need this to get the paths and libraries going
# on our install for python.  python-config doesn't
# always seem to exist on the RHEL5 machines with 
# python2.4 (at least on the one's I tested) so this
# gets the proper flags in the case python-config
# is missing

# This isn't horribly robust, but it should work
# in most cases. Multiple installs of python can 
# probably make this freak out (or point to a 
# version you don't want to use)

# Seamus
# sriordan@physics.umass.edu
# January 4, 2011


sub errorout 
{
    print "Python doesn't look to be installed...\n";
    print "Make sure it is installed (we need Python.h\n";
    print "and libpythonx.x.so)\n";
    print "Otherwise, find an expert!";
    exit 1;
}

# See if python-config exists

$arg = shift(@ARGV);

$res = `python-config 2>&1`;

if( !$res ){
#    print "python-config doesn't exist, guessing\n";

# Get python version
    $version = `python -V 2>&1`;
    if( $version =~ /^Python (\d+\.\d+).*/ ){
	$version = $1;
	$Mver = $1;

	# find inc dir
	$Pyh = `locate python$Mver/Python.h`;
	if( $Pyh =~ /(.*python$Mver)\/Python\.h/){
	    $incdir = $1;
	} else {
	    print("Can't locate python$Mver/Python.h\n");
	    errorout();
	}

	# find lib dir
	$Pyh = `locate libpython$Mver.so`;
	if( $Pyh =~ /(.*)\/libpython$Mver\.so/){
	    $libdir = $1;
	} else {
	    print("Can't locate libpython$Mver.so\n");
	    errorout();
	}

	if( $arg eq "--libs" ){
	    print "-lpthread -ldl -lutil -lm -lpython$Mver\n";
	}

	if( $arg eq "--includes" ){
	    print "-I$incdir\n";
	}
    } else {
	print("Can't run python executable to get version\n");
	errorout();
    }
    
} else {
    system("python-config $arg");
}
