// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// clevels.h
// Compressed levels loading (use with simplelevels.h)

void prepare_level (void) {
	get_resource (levels [level_ac].map_res, (unsigned int) (map));
	get_resource (levels [level_ac].enems_res, (unsigned int) (baddies));
	get_resource (levels [level_ac].hotspots_res, (unsigned int) (hotspots));
	get_resource (levels [level_ac].behs_res, (unsigned int) (behs));
}
