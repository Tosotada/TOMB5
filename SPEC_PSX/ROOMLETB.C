#include "ROOMLETB.H"

#include "CAMERA.H"
#include "DRAW.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"

void DrawRoomletListAsmBinocular(long underwater, struct room_info* r)//roomletb
{
	S_Warn("[DrawRoomletListAsmBinocular] - Unimplemented!\n");
}

void sub_1BC4D0(struct room_info* r)//roomletb
{

}

void DrawRoomletList()
{
	sub_1BC4D0(&room[camera.pos.room_number]);
}