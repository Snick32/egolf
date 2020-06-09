uint8_t draw_state;
bool information;
int id_sender;
uint8_t menu_current = 0;

#include "U8glib.h"
#include <CAN.h>
#include "variables.h"
#include "obd_function.h"
#include <EEPROM.h>

#include "u8g_value_screen1.h"
#include "u8g_value_screen2.h"
#include "u8g_value_screen3.h"
#include "u8g_value_screen4.h"
#include "u8g_start_screen.h"
#include "u8g_menu.h"
#include "u8g_menu_settings.h"

void u8g_prepare(void) {
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
  if (EEPROM.read(e_rotate))
  {
    u8g.setRot180();
  }
}

void(* resetFunc) (void) = 0;


void draw(void) {
  u8g_prepare();
  switch (draw_state) {
    case 0: u8g_start_screen(draw_state & 7); break;
    case display_info::draw_data_1: u8g_value_screen1(draw_state & 7); break;
    case 2: u8g_value_screen2(draw_state & 7); break;
    case 3: u8g_value_screen3(draw_state & 7); break;
    case 4: u8g_value_screen4(draw_state & 7); break;
    case display_info::draw_menu: u8g_menu(draw_state & 7); break;
    case display_info::draw_settings: u8g_menu_settings(draw_state & 7); break;
  }
}

void setup(void) {

  failure_code = failurecode::NO_FAIL;
  if (!CAN.begin(500E3)) {
    failure_code = failurecode::CAN_FAIL;
  }
  pinMode(PC1, INPUT);
  digitalWrite(PC1, LOW);
  delay(200);
  if (analogRead(PC1) < 4)
  {
    EEPROM.write(e_draw_state, 1);

  }
  EEPROM.write(e_draw_state, 5);

  draw_state = display_info::draw_menu;

draw_state = 1;
 // information = true;
}

void loop(void) {
  failure_code = failurecode::NO_COMMUNICATION;
  unsigned long time;
  byte button, menu;
  menu = menu_position::menu_main;
  while (1)
  {
    u8g.firstPage();
    do {
      draw();
    } while ( u8g.nextPage() );


    if (draw_state == 1)
    {
      if (failure_code == failurecode::NO_COMMUNICATION)
      {
        connect_to_stg(v_gateway,  v_gateway_can_id_sender, v_gateway_can_id_filter);
        CAN.filter(v_gateway_can_id_filter);
      }
      obd_get_id(v_charge_state, 1, v_gateway_can_id_sender);
      obd_get_id(v_Batterietemperatur , 3, v_gateway_can_id_sender);
      obd_get_id(v_SOH, 2, v_gateway_can_id_sender);
      obd_get_id(v_energy_storage, 4, v_gateway_can_id_sender);
      obd_get_id(v_low_current, 6, v_gateway_can_id_sender);
    }

    if (draw_state == 2)
    {
      if (failure_code == failurecode::NO_COMMUNICATION)
      {
        connect_to_stg(v_engine, v_engine_can_id_sender, v_engine_can_id_filter);
        CAN.filter(v_engine_can_id_filter );
      }
      obd_get_id(v_acceleration, 1, v_engine_can_id_sender);
      obd_get_id(v_airtemp_batterie, 2, v_engine_can_id_sender);
      obd_get_id(v_torque, 3, v_engine_can_id_sender);
      obd_get_id(v_coolant_temperatur, 4, v_engine_can_id_sender);
      obd_get_id(v_SOC, 5, v_engine_can_id_sender);
    }

    if (draw_state == 3)
    {
      if (failure_code == failurecode::NO_COMMUNICATION)
      {
        connect_to_stg(v_engine_II, v_engine_II_can_id_sender, v_engine_II_can_id_filter);
        CAN.filter(v_engine_II_can_id_filter);
      }
      obd_get_id(v_machine_temperatur , 1, v_engine_II_can_id_sender);
      obd_get_id(v_machine_speed, 2, v_engine_II_can_id_sender);
      obd_get_id(v_machine_el_power, 3, v_engine_II_can_id_sender);
      obd_get_id(v_machine_mech_power, 4, v_engine_II_can_id_sender);
      obd_get_id(v_machine_max_power, 5, v_engine_II_can_id_sender);
      obd_get_id(v_machine_min_power, 6, v_engine_II_can_id_sender);
    }

    if (draw_state == 4)
    {
      if (failure_code == failurecode::NO_COMMUNICATION)
      {
        connect_to_stg(v_batcharger, v_batcharger_can_id_sender, v_batcharger_can_id_filter);
        CAN.filter(v_batcharger_can_id_filter);
      }
      obd_get_id(v_l1_l2_current , 1, v_batcharger_can_id_sender);
      obd_get_id(v_charging_efficiency, 2, v_batcharger_can_id_sender);
      obd_get_id(v_charging_power, 3, v_batcharger_can_id_sender);
    }

 //   if (analogRead(PC1) < 4)
       if (0)
    {
      u8g.sleepOff();
      time = millis();
   //   while (analogRead(PC1) < 4);
      time = millis() - time;
      if (time > 1000)          // Lang gedrückt
      {
        button = buttoninformation::long_press;
      }
      else
      {
        button = buttoninformation::short_press;
      }

      switch (menu) {
        //---------------------------------------------------------------------------------------------------
        // Fahre durch das Hauptmenu durch
        //---------------------------------------------------------------------------------------------------
        case menu_position::menu_main:
          if (button == buttoninformation::short_press)   // Fahre durch das Hauptmenu durch
          {
            menu_current++;
            if ( menu_current >= MENU_ITEMS )
              menu_current = 0;
          }
          else                                            // Es wurde eine menupunkt ausgewählt, welcher?
          {
            switch (menu_current) {
              case menu_main_position::read_fault:        // Wurde Read Data ausgewählt
                draw_state = display_info::draw_data_1;
                menu = menu_position::menu_data;
                menu_current = 0;
                break;
              case menu_main_position::settings:
                draw_state = display_info::draw_settings;
                menu_current = 0;
                break;
              case menu_main_position::power_off:
                u8g.sleepOn(); while (1);
                break;
            }
          }
          break;

        //---------------------------------------------------------------------------------------------------
        // Fahre durch das Settings durch
        //---------------------------------------------------------------------------------------------------
        case menu_position::menu_settings:
          if (button == buttoninformation::short_press)   // Fahre durch das Hauptmenu durch
          {
            menu_current++;
            if ( menu_current >= MENU_ITEMS )
              menu_current = 0;
          }
          else                                            // Es wurde eine sub menupunkt ausgewählt, welcher?
          {
            switch (menu_current) {
              case menu_sub_position::back:
                draw_state = display_info::draw_menu;
                menu = menu_position::menu_main;
                menu_current = 0;
                break;

            }
          }
          break;
      }
      /*
        switch (menu) {
        case menu_settings: draw_state = menu_sub ; menu_current = 0; break;
        case menu_power_off: u8g.sleepOn(); while (1); break;
        // --------------------------------------------
        // Submenu
        // --------------------------------------------
        case menu_sub: // ist im submenu
          {
            switch (menu_current) {
              case menu_sub_rotate:
                if (EEPROM.read(e_rotate))
                {
                  u8g.undoRotation();
                  EEPROM.write(e_rotate, false);
                }
                else
                {
                  u8g.setRot180();
                  EEPROM.write(e_rotate, true);
                }
                break;
              case menu_sub_back: draw_state = menu; menu_current = 0; break;
            }
            break;
          }
        }
      */

      information = true;


      failure_code = failurecode::NO_COMMUNICATION;

    }
  }
}
