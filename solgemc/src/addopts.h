#include "usage.h"

void AddOpts( gemc_opts &opts ){
	 opts.args["USE_PHYSICSL"].help += "            * noint: No physics interactions\n";
	 // Set default GUI to 2 (no QT, but OGLIX)
	 opts.args["USE_QT"].arg = 2;
}
