#include "usage.h"

void AddOpts( gemc_opts &opts ){
	 opts.args["USE_PHYSICSL"].help += "            * noint: No physics interactions\n";
}
