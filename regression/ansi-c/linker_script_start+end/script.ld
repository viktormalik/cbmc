MEMORY {
  RAM : ORIGIN = 0x0, LENGTH = 25M
}

SECTIONS
{
  /* GCC insists on having these */
  .note.gnu.build-id : { } > RAM
  .text : { } > RAM

  .src_section : {
    src_start = .;
    *(.text*)
    src_end = .;
  } > RAM

  .dst_section : {
    dst_start = .;
    *(.text*)
    dst_end = .;
  } > RAM
}
