#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

void u8g_value_screen1(uint8_t a) {

  u8g.drawLine(0, 22, 140, 22);
  u8g.drawLine(0, 42, 140, 42);
  u8g.drawLine(70, 0, 70, 42);
  if (information)
  {
    u8g.setFont(u8g_font_6x12);
    u8g.setPrintPos(10, 5);
    u8g.print("Battemp");
    u8g.setPrintPos(10, 26);
    u8g.print("SOC");
    u8g.setPrintPos(80, 5);
    u8g.print("SOH");
    u8g.setPrintPos(80, 26);
    u8g.print("NV Power");
    u8g.setPrintPos(10, 50);
    u8g.print("Energy Storgage");
    delay(200);
  }
  else
  {
    u8g.setFont(u8g_font_9x18);
    u8g.setPrintPos(20, 5);
    u8g.print((data[3][4]) - 40, DEC);
    u8g.write(0xBA);
    u8g.print("C");
    u8g.setPrintPos(20, 26);
    u8g.print((data[1][4]) / 2, DEC);
    u8g.print("%");
    u8g.setPrintPos(80, 5);
    u8g.print((data[2][4]) , DEC);
    u8g.print("%");
    u8g.setPrintPos(80, 26);
    u8g.print((data[6][7]) * 13, DEC);
    u8g.print("W");
    u8g.setPrintPos(38, 50);
    u8g.print((((data[4][7]) * 256) + (data[5][1])) * 25 , DEC);
    u8g.print("Wh");
  }

}
