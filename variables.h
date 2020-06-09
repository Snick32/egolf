#define e_rotate                            1
#define e_draw_state                        2

// --------------------------------------------
// Menu defines
// --------------------------------------------

// --------------------------------------------
// Display
// --------------------------------------------
// 20 , 5      |   80 , 5
// 20 , 26     |   80 , 26
// 20 , 50     |   80 , 50
// --------------------------------------------
// Gateway Information
// --------------------------------------------
#define v_SOH                           0x1205
#define v_Batterietemperatur            0x2A0B
#define v_charge_state                  0x1DD0
#define v_energy_storage                0x2AB8
#define v_low_current                   0x2A53

#define v_gateway                       0x1F
#define v_gateway_can_id_sender         0x710
#define v_gateway_can_id_filter         0x77A

// --------------------------------------------
// Engine I Information
// --------------------------------------------
#define v_acceleration                  0x12B0
#define v_airtemp_batterie              0x1169
#define v_coolant_temperatur            0x1613
#define v_torque                        0x147F
#define v_SOC                           0x1618

#define v_engine                        0x01
#define v_engine_can_id_sender          0x7E0
#define v_engine_can_id_filter          0x7E8

// --------------------------------------------
// Engine II Information
// --------------------------------------------

#define v_engine_II                     0x51
#define v_engine_II_can_id_sender       0x7E6
#define v_engine_II_can_id_filter       0x7EE

#define v_machine_temperatur            0x3E94
#define v_machine_speed                 0x4659
#define v_machine_el_power              0x4656
#define v_machine_mech_power            0x4658
#define v_machine_max_power             0x100A
#define v_machine_min_power             0x100B

// --------------------------------------------
// Battery Charger Information
// --------------------------------------------

#define v_batcharger                    0xC6
#define v_batcharger_can_id_sender      0x744
#define v_batcharger_can_id_filter      0x7AE

#define v_l1_l2_current                 0x41FB
#define v_charging_efficiency           0x15D6
#define v_charging_power                0x15D5


enum failurecode {
  NO_FAIL,
  CAN_FAIL,
  NO_COMMUNICATION,
  OK_COMMUNICATION,
  WRONG_RESPONSE_COMMUNICATION 
};

enum buttoninformation {
  long_press,
  short_press 
};

enum menu_position {
  menu_main,
  menu_settings,
  menu_data
};

enum menu_main_position {
  read_data,
  read_fault,
  sprint,
  settings,
  power_off
};

enum menu_sub_position {
  power,
  rotate,
  test1,
  test2,
  back
};
enum display_info {
  draw_data_1 = 1,
  draw_menu = 6,
  draw_settings = 7

};
