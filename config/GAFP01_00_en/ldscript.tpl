MEMORY
{
    text : origin = $ORIGIN
}

SECTIONS
{
    GROUP:
    {
        $SECTIONS
        .stack ALIGN(0x20):{}
    } > text

    _stack_end = ($LAST_SECTION_SYMBOL + SIZEOF($LAST_SECTION_NAME)+ 0x7) & ~0x7;
    _stack_addr = (_stack_end + 0x1000 + 0x7) & ~0x7;
    _db_stack_addr = (_stack_addr + 0x2000);
    _db_stack_end = _stack_addr;
    __ArenaLo = (_db_stack_addr + 0x1F) & ~0x1F;
    __ArenaHi = 0x81700000;
}

FORCEACTIVE
{
    $FORCEACTIVE
}
