/*
Design you own font:
https://github.com/moononournation/Font-Stuff/tree/master/FontDesignHtml

fontsetvalue:
000047404620528045C09B2254CA4400544006C0E500254800C0210800401B2056C005409F428FC06548ADE06DC08760557E45F8028002C003A2529403A28740AF6A7E8AAFC05462AEC0AD62AD20746EA92A054096E0ABA2A842EB2AE9AA76C8AF0076CAAF824DE08560A06AD2E0B9AADBA2C3609F620562C182046A46000842060011C2A9C0114A116A53427C007900A94081408940B9400540398A294011C07A88728A01C83940F04052C030C8599A49D842DA23A20540D9086188
*/
#include <avr/pgmspace.h>

#define FONT_WIDTH  3
#define FONT_HEIGHT 5

static const uint8_t font_data[] PROGMEM = {
0x00, 0x00, 0x47, 0x40, 0x46, 0x20, 0x52, 0x80,
0x45, 0xC0, 0x9B, 0x22, 0x54, 0xCA, 0x44, 0x00,
0x54, 0x40, 0x06, 0xC0, 0xE5, 0x00, 0x25, 0x48,
0x00, 0xC0, 0x21, 0x08, 0x00, 0x40, 0x1B, 0x20,
0x56, 0xC0, 0x05, 0x40, 0x9F, 0x42, 0x8F, 0xC0,
0x65, 0x48, 0xAD, 0xE0, 0x6D, 0xC0, 0x87, 0x60,
0x55, 0x7E, 0x45, 0xF8, 0x02, 0x80, 0x02, 0xC0,
0x03, 0xA2, 0x52, 0x94, 0x03, 0xA2, 0x87, 0x40,
0xAF, 0x6A, 0x7E, 0x8A, 0xAF, 0xC0, 0x54, 0x62,
0xAE, 0xC0, 0xAD, 0x62, 0xAD, 0x20, 0x74, 0x6E,
0xA9, 0x2A, 0x05, 0x40, 0x96, 0xE0, 0xAB, 0xA2,
0xA8, 0x42, 0xEB, 0x2A, 0xE9, 0xAA, 0x76, 0xC8,
0xAF, 0x00, 0x76, 0xCA, 0xAF, 0x82, 0x4D, 0xE0,
0x85, 0x60, 0xA0, 0x6A, 0xD2, 0xE0, 0xB9, 0xAA,
0xDB, 0xA2, 0xC3, 0x60, 0x9F, 0x62, 0x05, 0x62,
0xC1, 0x82, 0x04, 0x6A, 0x46, 0x00, 0x08, 0x42,
0x06, 0x00, 0x11, 0xC2, 0xA9, 0xC0, 0x11, 0x4A,
0x11, 0x6A, 0x53, 0x42, 0x7C, 0x00, 0x79, 0x00,
0xA9, 0x40, 0x81, 0x40, 0x89, 0x40, 0xB9, 0x40,
0x05, 0x40, 0x39, 0x8A, 0x29, 0x40, 0x11, 0xC0,
0x7A, 0x88, 0x72, 0x8A, 0x01, 0xC8, 0x39, 0x40,
0xF0, 0x40, 0x52, 0xC0, 0x30, 0xC8, 0x59, 0x9A,
0x49, 0xD8, 0x42, 0xDA, 0x23, 0xA2, 0x05, 0x40,
0xD9, 0x08, 0x61, 0x88
};