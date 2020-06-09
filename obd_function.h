
byte failure_code, i;
uint8_t data[8][9];
int comm_counter;

void obd_init(uint8_t device, uint16_t can_id, uint8_t init_200) {
  delay(500);
  if (init_200)
  {
    CAN.beginPacket(0x200, 7);
    CAN.write(device); // device adress
    CAN.write(0xC0);
    CAN.write(0x00);
    CAN.write(0x10);
    CAN.write(0x00);
    CAN.write(0x03);
    CAN.write(0x01);
    CAN.endPacket();
    delay(50);
  }

  CAN.beginPacket(can_id, 8);
  CAN.write(0x02);
  CAN.write(0x10);
  CAN.write(0x03);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.endPacket();
}

void obd_read_id(uint16_t id, uint8_t arrayID) {
  int packetSize  = 0;
  int timeover = 100;
  delay(20);
  while (packetSize == 0)
  {
    packetSize = CAN.parsePacket();
    delay(1);
    timeover--;
    if (timeover == 0)
      break;
  }
  if ((CAN.packetId() == v_gateway_can_id_filter ) || (CAN.packetId() == v_engine_can_id_filter) || (CAN.packetId() == v_engine_II_can_id_filter) || (CAN.packetId() == v_batcharger_can_id_filter) )
  {
    i = 0;
    while (CAN.available()) {
      data[arrayID][i] = CAN.read();
      i++;
    }
    if (data[arrayID][3] == id)
    {
      failure_code = failurecode::OK_COMMUNICATION;
    }
    else
    {
      // failure_code = failurecode::WRONG_RESPONSE_COMMUNICATION;
    }
  }
  else
  {
    failure_code = failurecode::NO_COMMUNICATION;
  }

}


void ack_more_data(uint16_t can_id_sender) { // werden mehr als 7 Byte gesendet, muss der Scanner dies bestätigen
  CAN.beginPacket(can_id_sender, 8);
  CAN.write(0x30);
  CAN.write(0x00);
  CAN.write(0x01);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.endPacket();
}

void obd_get_id(uint16_t id, uint8_t arrayID, uint16_t can_id_sender) {
  delay(15);
  CAN.flush();
  i = 0;
  while (CAN.available()) {
    data[0][i] = CAN.read();
    i++;
  }

  CAN.beginPacket(can_id_sender, 8);
  CAN.write(0x03); // device adress
  CAN.write(0x22);
  CAN.write(id >> 8);
  CAN.write(id);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.write(0x55);
  CAN.endPacket();
  CAN.flush();
  obd_read_id(id, arrayID);
  //CAN.flush();
  if ((data[arrayID][0]) > 9)// Sind mehr als 7 Datenbits gesendet will OBD nochmals ein Telegram zusenden.
  {
    //delay(20);
    ack_more_data(can_id_sender);
    obd_read_id(id, arrayID + 1);
  }

  if ((data[arrayID][1]) == 0x7F)  // ist im zweiten Byte eine 7F, dann ist falsche Antwort gekommen
  {
    obd_read_id(id, arrayID);
  }
}


void connect_to_stg(uint8_t stg_adresse, uint16_t can_id_sender, uint16_t can_id_filter) { // werden mehr als 7 Byte gesendet, muss der Scanner dies bestätigen

  int id1, id2, init_200, ack;

  switch (stg_adresse) {
    case v_engine: id1 = 0xF19E; id2 = 0xF1A2; init_200 = true;  break;
    case v_engine_II: id1 = 0xF19E; id2 = 0xF1A2; init_200 = false;  break;
    case v_gateway: id1 = 0x2A2A; id2 = 0x2A2E; init_200 = true, ack = true; break;
    case v_batcharger: id1 = 0xF19E; id2 = 0xF1A2; init_200 = false;  break;

  }
  delay(3000);
  information = false;   // Zeige nach der Init die Daten an
  obd_init(stg_adresse, can_id_sender, init_200);

  //delay(5);
  //obd_read_id(0, 0);
  //delay(5);
  obd_get_id(id1, 0, can_id_sender);
  obd_get_id(id2, 0, can_id_sender);
  if (ack)
  {
    delay(10);
    ack_more_data(can_id_sender);
  }
  //delay(5);
  failure_code = failurecode::OK_COMMUNICATION;
  //CAN.filter(can_id_filter);
  //ack_more_data(can_id_sender);
}
