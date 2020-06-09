void u8g_value_screen2(uint8_t a) {

  if (information)
  {
    u8g.setFont(u8g_font_6x12);
    u8g.setPrintPos(10, 5);
    u8g.print("Torque");
    u8g.setPrintPos(10, 26);
    u8g.print("Airtemp Bat");
    u8g.setPrintPos(80, 5);
    u8g.print("SOC");
    u8g.setPrintPos(80, 26);
    u8g.print("Coolant Temp");
    u8g.setPrintPos(10, 50);
    u8g.print("Acceleration");
    delay(200);
  }
  else
  {
    u8g.setFont(u8g_font_9x18);
    u8g.drawLine(0, 22, 140, 22);
    u8g.drawLine(0, 42, 140, 42);
    u8g.drawLine(70, 0, 70, 42);
    u8g.setPrintPos(20, 5);
    u8g.print(((data[3][4] * 256) + data[3][5]) / 10 , DEC);
    u8g.print("Nm");
    u8g.setPrintPos(20, 26);
    u8g.print((((data[2][4] * 256) + data[2][5]) - 2731 ) / 10 , DEC);
    u8g.write(0xBA);
    u8g.print("C");
    u8g.setPrintPos(20, 50);
    float h = ((data[1][4] * 256) + data[1][5]) ;
    u8g.print(h / 1000 );
    u8g.print("m/s2");
    u8g.setPrintPos(80, 50);
    u8g.print(h / 1000 / 9.81 );
    u8g.print("g");    
    u8g.setPrintPos(80, 26);
    u8g.print((((data[4][4] * 256) + data[4][5]) - 2731) / 10 , DEC);
    u8g.write(0xBA);
    u8g.print("C");
    u8g.setPrintPos(80, 5);
    u8g.print(((data[5][4] * 256) + data[5][5]) / 100 , DEC);
    u8g.print("%");
  }

}
