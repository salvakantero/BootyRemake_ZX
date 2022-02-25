// librarian.h
// Generated by The Librarian
// Copyleft 2012 The Mojon Twins
 
typedef struct {
   unsigned char ramPage;
   unsigned int ramOffset;
} RESOURCE;
 
RESOURCE resources [] = {
   {3, 49152},   // 0: title.bin
   {3, 51121},   // 1: marco.bin
   {3, 51121},   // 2: ending.bin
   {3, 53782},   // 3: title2.bin
   {3, 56765},   // 4: title3.bin
   {3, 59352}    // 5: title4.bin
};
 
void get_resource (unsigned char res, unsigned int dest) {
   unpack_RAMn (resources [res].ramPage, resources [res].ramOffset, dest);
}
 
// Defines
#define TITLE_BIN           	0
#define MARCO_BIN           	1
#define ENDING_BIN          	2
#define TITLE2_BIN          	3
#define TITLE3_BIN          	4
#define TITLE4_BIN          	5