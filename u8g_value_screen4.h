void u8g_value_screen4(uint8_t a) {

  if (information)
  {
    u8g.setFont(u8g_font_6x12);
    u8g.setPrintPos(10, 5);
    u8g.print("L1 Current");
    u8g.setPrintPos(10, 26);
    u8g.print("L2 Current");
    u8g.setPrintPos(80, 5);
    u8g.print("L1 Power");
    u8g.setPrintPos(80, 26);
    u8g.print("L2 Power");
    u8g.setPrintPos(10, 50);
    u8g.print("Efficiency");
    u8g.setPrintPos(80, 50);
    u8g.print("Power Total");
    delay(200);
  }
  else
  {
    u8g.setFont(u8g_font_9x18);
    u8g.drawLine(0, 22, 140, 22);
    u8g.drawLine(0, 42, 140, 42);
    u8g.drawLine(70, 0, 70, 64);
    u8g.setPrintPos(10, 5);
    float h = ((data[1][4])  ) ;
    u8g.print(h / 10 );
    u8g.print("A");
    u8g.setPrintPos(10, 26);
    h = ((data[1][5])  ) ;
    u8g.print(h / 10 );
    u8g.print("A");
    u8g.setPrintPos(80, 5);
    u8g.print((data[1][4] * 230 / 10 ) , DEC);
    u8g.print("W");
    u8g.setPrintPos(80, 26);
    u8g.print((data[1][5] * 230 / 10 ) , DEC);
    u8g.print("W");
    u8g.setPrintPos(20, 50);
    u8g.print((data[2][4] / 2)  , DEC);
    u8g.print("%");
    u8g.setPrintPos(80, 50);
    u8g.print((data[3][5] * 100)  , DEC);
    u8g.print("W");
  }

}
