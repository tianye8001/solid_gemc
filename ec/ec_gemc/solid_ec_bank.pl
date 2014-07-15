use strict;
use warnings;

our %configuration;

# Variable Type is two chars.
# The first char:
#  R for raw integrated variables
#  D for dgt integrated variables
#  S for raw step by step variables
#  M for digitized multi-hit variables
#  V for voltage(time) variables
#
# The second char:
# i for integers
# d for doubles

sub define_solidec_bank
{
	# uploading the hit definition
	my $bankId = 300;
	my $bankname = "solidec";
	
	insert_bank_variable(\%configuration, $bankname, "bankid", $bankId, "Di", "$bankname bank ID");
	insert_bank_variable(\%configuration, $bankname, "id",           1, "Di", "id number");
	insert_bank_variable(\%configuration, $bankname, "hitn",        99, "Di", "hit number");
}

1;










