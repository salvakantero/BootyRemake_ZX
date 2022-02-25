// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// levelnames.h
// Completely custom. But easily customizable. Just read.

#define LEVELNAMES_SIZE 10
#define LEVELNAMES_X 11
#define LEVELNAMES_Y 23
#define LEVELNAMES_C 79

unsigned char *levelnames = "          LA CAMOLLA          HOMBRO IZQEL PECHITOHOMBRO DERBRAZO IZQ.LA BARRIGABRAZO DER.UNA CADERA LA PISHA UNA CADERALA RODILLA          LA RODILLA PIE IZQ.            PIE DER. ";

void print_level_name (void) {
	gen_pt = levelnames + n_pant * LEVELNAMES_SIZE;
	gpit = LEVELNAMES_X; gpjt = LEVELNAMES_SIZE;
	while (gpjt --) sp_PrintAtInv (LEVELNAMES_Y, gpit ++, LEVELNAMES_C, (*gen_pt ++) - 32);
}
