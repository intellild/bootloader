/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */
/*            Original file taken from Bran's Kernel Development */
/*            tutorials: http://www.osdever.net/bkerndev/index.php. */

OUTPUT_FORMAT("binary")
ENTRY(__Start)
SECTIONS
{
    .text 0x100000:
    {
        src/kernel/kernel.o(.text)
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
