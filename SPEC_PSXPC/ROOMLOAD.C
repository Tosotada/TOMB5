#include "ROOMLOAD.H"

#include "CD.H"
#include "DRAW.H"
#include "FILE.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "SETUP.H"

#include <stdio.h>
#include <string.h>

long AnimFilePos;
long AnimFileLen;
short* floor_data;
unsigned long* SetupPtr;
unsigned short ClutStartY;
struct SVECTOR* RoomBBoxes;
short* mesh_base;
struct PSXSPRITESTRUCT* GLOBAL_default_sprites_ptr;
struct PSXTEXTI* AnimatingWaterfalls[6];
int AnimatingWaterfallsV[6];
unsigned long envmap_data[6];
unsigned long* RelocPtr[128];

void ReloadAnims(int name, long len)//600E4(<), 60D20(<)
{
#if DISC_VERSION
	cdCurrentSector = AnimFilePos;
	DEL_CDFS_Read((char*) frames, len);
#else
	FILE* file;
	char buf[80];

	strcpy(buf, &gfFilenameWad[gfFilenameOffset[name]]);
	strcat(buf, ".PSX");
	file = fopen(buf, "rb");

	fseek(file, AnimFilePos, SEEK_SET);
	FILE_Read((char*) frames, 1, len, file);

	fclose(file);
#endif

	return;
}

void S_LoadLevelFile(int Name)//60188(<), 60D54(<) (F)
{
	char buf[80];
	unsigned long* mod;
	int len;
	FILE* file;

#if DISC_VERSION
	//TITLE is the base file entry index for levels, simply as a result, we must add gameflow level id to this.
	DEL_CDFS_OpenFile(Name + TITLE);
#endif

	//DrawSync(0);

	init_game_malloc();

	LOAD_Start(Name + TITLE);
	
	SetupPtr = &db.poly_buffer[0][1026];

#if DISC_VERSION
	DEL_CDFS_Read((char*) &db.poly_buffer[1024], gwHeader.entries[NONE].fileSize);//jal 5E414
	RelocateLevel();
#else
	len = FILE_Length("DATA\\SETUP.MOD");
	file = fopen("DATA\\SETUP.MOD", "rb");

	//FILE_Read(&db.poly_buffer[1024], 1, len, file);

	fclose(file);
#endif

#if 0
	RelocateModule((unsigned long)SetupPtr, (unsigned long*)&temp[(*(unsigned long*)&temp[0]) + 8] );
#endif

#if !DISC_VERSION
	strcpy(buf, &gfFilenameWad[gfFilenameOffset[Name]]);
	strcat(buf, ".PSX");

	len = FILE_Length(buf);

	file = fopen(buf, "rb");

	RelocateLevel(file);
#endif

	 //jalr SetupPtr[5](len);, retail a0 = s1? len?

	LOAD_Stop();
	
	return;
}