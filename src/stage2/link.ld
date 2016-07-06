/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */
/*            Original file taken from Bran's Kernel Development */
/*            tutorials: http://www.osdever.net/bkerndev/index.php. */

OUTPUT_FORMAT("binary")
ENTRY("stage2")
SECTIONS
{
    . =0x8000;
    .text :
    {
        src/stage2/stage2.o(.text)
        *(.text)
    }

    .data :
    {
        *(.data)
        *(.rodata)
    }

    .bss :
    {
        *(.bss)
    }
}
