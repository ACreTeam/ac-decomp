/*
 * --INFO--
 * Address:	80010E00
 * Size:	00000C
 */
static void OSf32tos8(register f32* in, volatile register s8* out)
{
    *out = __OSf32tos8(*in);
}

