
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"
#define NES_MIRRORING 0
/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x19,			// screen color

  0x11,0x30,0x27,0x0,	// background palette 0
  0x1c,0x20,0x2c,0x0,	// background palette 1
  0x00,0x10,0x20,0x0,	// background palette 2
  0x06,0x16,0x26,0x0,   // background palette 3

  0x16,0x35,0x24,0x0,	// sprite palette 0
  0x00,0x37,0x25,0x0,	// sprite palette 1
  0x0d,0x2d,0x3a,0x0,	// sprite palette 2
  0x0d,0x27,0x2a	// sprite palette 3
};

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  
  // set palette colors
  pal_all(PALETTE);
}

void put_str(unsigned int adr, const char *str) {
  vram_adr(adr);        // set PPU read/write address
  vram_write(str, strlen(str)); // write bytes to PPU
}

void scroll_demo() {
  int x = 0;   // x scroll position
  int y = 0;   // y scroll position
  
  int dy = 1; // x scroll direction
  // infinite loop
  while (1) {
    // wait for next frame
    ppu_wait_frame();
    // update y variable
    y += dy;
    // change direction when hitting either edge of scroll area
    if (y >= 160) dy = -1;
    if (y == 0) dy = 1;
    // set scroll register
    scroll(x, y);
  }
}

void draw_pitch() {
    int i,y;
  y = 2;
  setup_graphics();
   vram_adr(NTADR_A(2,2));
   vram_put(0x87);
  // top line
  for(i = 3;i<= 28;++i) {
    vram_adr(NTADR_A(i,y));
    vram_put(0x83);
    
  }
  
  // left line A
  for(i = 3;i<= 29;++i) {
    vram_adr(NTADR_A(2,i));
    vram_put(0x85);
    ++y;
  }
  
  y = 3;
  vram_adr(NTADR_A(28,2));
  vram_put(0x8B);
  // right line A
  for(i = 3;i<= 29;++i) {
    vram_adr(NTADR_A(28,y));
    vram_put(0x8A);
    ++y;
  }
  
  
  // bottom line
  for(i = 2, y = 10;i<= 28;++i) {
    vram_adr(NTADR_C(i,y));
    vram_put(0x83);
    
  }
  
  // left line B
  for(i = 0;i<= 9;++i) {
    vram_adr(NTADR_C(2,i));
    vram_put(0x85);
    ++y;
  }
  
  // right line B
  for(i = 0;i<= 9;++i) {
    vram_adr(NTADR_C(28,i));
    vram_put(0x8A);
    ++y;
  }
  
  vram_adr(NTADR_A(2,21));
  vram_put(0x8C);
  //middle line
  for(i = 3;i<= 27;++i) {
    vram_adr(NTADR_A(i,21));
    vram_put(0x80);
    ++y;
  }
  
  vram_adr(NTADR_A(28,21));
  vram_put(0x8F);
}

void main(void)
{
  
  draw_pitch();
  // enable rendering
  ppu_on_all();
  scroll_demo();
  // infinite loop
  while(1) {
  }
}
