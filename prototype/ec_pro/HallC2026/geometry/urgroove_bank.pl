use strict;
use warnings;

use bank;
our %configuration;

my $bankID   = 2300;
my $bankname = "urgroove";

sub define_bank
{
    insert_bank_variable(\%configuration, $bankname, "bankid",    $bankID, "Di", "$bankname bank ID");

    insert_bank_variable(\%configuration, $bankname, "sector",    1, "Di", "module/sector number");
    insert_bank_variable(\%configuration, $bankname, "layer",     2, "Di", "readout layer or view");
    insert_bank_variable(\%configuration, $bankname, "component", 3, "Di", "strip number");

    insert_bank_variable(\%configuration, $bankname, "ADC_order", 4, "Di", "always 0");
    insert_bank_variable(\%configuration, $bankname, "ADC_ADC",   5, "Di", "ADC");
    insert_bank_variable(\%configuration, $bankname, "ADC_time",  6, "Dd", "time");
    insert_bank_variable(\%configuration, $bankname, "ADC_ped",   7, "Di", "pedestal");

    insert_bank_variable(\%configuration, $bankname, "hitn",     99, "Di", "hit number");
}

1;
