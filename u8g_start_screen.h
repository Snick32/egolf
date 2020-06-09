void u8g_start_screen(uint8_t a) {

  u8g.drawStr(2, 5, "E-Golf");
  if (failure_code == failurecode::CAN_FAIL)
  {
    u8g.drawStr(2, 26, "Init: Fail");
  }
  else
  {
    failure_code = failurecode::NO_COMMUNICATION;
  }
  u8g.setPrintPos(2, 47);
  u8g.print("EV Scanner");

  delay(2000);
  draw_state = 1;
}
