#define MENU_SUB_ITEMS 5
const char *menu_sub_strings[MENU_ITEMS] = { "Power:", "Rotate:", "Contrast:", "Test", "Back" };

void u8g_menu_settings(uint8_t a) {
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();

  h = u8g.getFontAscent() - u8g.getFontDescent();
  w = u8g.getWidth();
  for ( i = 0; i < MENU_SUB_ITEMS; i++ ) {
    d = (w - u8g.getStrWidth(menu_sub_strings[i])) / 2;
    u8g.setDefaultForegroundColor();
    if ( i == menu_current ) {
      u8g.drawBox(0, i * h + 1, w, h);
      u8g.setDefaultBackgroundColor();
    }
    u8g.drawStr(d, i * h, menu_sub_strings[i]);
  }
}
