#include QMK_KEYBOARD_H

#ifdef OLED_DRIVER_ENABLE
#define MOD_ICON_WIDTH 4
#define MOD_ICON_HEIGHT 3
void render_mod_icon(uint8_t loc, bool enabled, const char *icon, bool invert) {
  uint8_t col = 1 + loc * (MOD_ICON_WIDTH + 1);
  for (uint8_t i=0; i < MOD_ICON_HEIGHT; ++i) {
    oled_set_cursor(col, i);
    for (uint8_t j=0; j < MOD_ICON_WIDTH; ++j) {
      if (enabled)
        oled_write_char(icon[i*MOD_ICON_WIDTH+j], invert);
      else
        oled_write_char(' ', false);
    }
  }
}
void render_mod_gui(bool enabled) {
  static const char icon_gui[] = {
    0x80, 0x81, 0x82, 0x83,
    0xA0, 0xA1, 0xA2, 0xA3,
    0xC0, 0xC1, 0xC2, 0xC3,
  };
  render_mod_icon(0, enabled, icon_gui, false);
}
void render_mod_alt(bool enabled) {
  static const char icon_alt[] = {
    0x84, 0x85, 0x86, 0x87,
    0xA4, 0xA5, 0xA6, 0xA7,
    0xC4, 0xC5, 0xC6, 0xC7,
  };
  render_mod_icon(1, enabled, icon_alt, false);
}
void render_mod_shift(bool enabled, bool caps_lock) {
  static const char icon_shift[] = {
    0x88, 0x89, 0x8A, 0x8B,
    0xA8, 0xA9, 0xAA, 0xAB,
    0xC8, 0xC9, 0xCA, 0xCB,
  };
  if (caps_lock)
    render_mod_icon(2, true, icon_shift, true);
  else
    render_mod_icon(2, enabled, icon_shift, false);
}
void render_mod_ctrl(bool enabled) {
  static const char icon_ctrl[] = {
    0x8C, 0x8D, ' ', ' ',
    0xAC, 0xAD, ' ', ' ',
    0xCC, 0xCD, ' ', ' ',
  };
  render_mod_icon(3, enabled, icon_ctrl, false);
}

void render_qmk_logo(void) {
  // this assumes the OLED is rotated vertically, 5 char wide
  static const char PROGMEM font_logo[] = {
    ' ', 0x8E, 0x8F, 0x90, 0x91,
    ' ', 0xAE, 0xAF, 0xB0, 0xB1,
    ' ', 0xCE, 0xCF, 0xD0, 0xD1, 0,
  };
  oled_set_cursor(0, 0);
  oled_write_ln_P(font_logo, false);
}

int get_frame_number(int total_time, int n_frames) {
  return (timer_read() % total_time) / (total_time / n_frames);
}

void render_layer_lower(int frame_number) {
  static const char PROGMEM font_icon[] = {
    ' ', ' ', 0x92, 0x93, ' ', 0,
    ' ', ' ', 0xB2, 0xB3, ' ', 0,
    ' ', ' ', 0xD2, 0xD3, ' ', 0,
    ' ', 0x9F, 0xBF, 0xBF, 0xDF, 0,
  };
  oled_write_ln_P(&font_icon[(frame_number % 3) * 6], false);
  oled_write_ln_P(&font_icon[3 * 6], false);
}

void render_layer_state(void) {
  static const char PROGMEM font_up[] = {
    ' ', ' ', 0xD2, 0xD3, ' ', 0,
    ' ', ' ', 0xB2, 0xB3, ' ', 0,
    ' ', ' ', 0x92, 0x93, ' ', 0,
  };
  static const char PROGMEM font_down[] = {
    ' ', ' ', 0x94, 0x95, ' ', 0,
    ' ', ' ', 0xB4, 0xB5, ' ', 0,
    ' ', ' ', 0xD4, 0xD5, ' ', 0,
  };
  static const char PROGMEM font_blank[] = {
    ' ', ' ', ' ', ' ', ' ', 0
  };

  int frame_number = get_frame_number(800, 4);
  int layer = get_highest_layer(layer_state);

  oled_write_ln_P(font_blank, false);
  if (layer == 2 || layer == 3) {
    // Raise or Nav
    oled_write_ln_P(&font_up[(frame_number % 3) * 6], false);
  } else {
    oled_write_ln_P(font_blank, false);
  }

  switch (layer) {
    case 0:
      oled_write_ln_P(PSTR(" > \x96\x96"), false);
      break;
    case 1:
      oled_write_ln_P(PSTR(" > 01"), false);
      break;
    case 2:
      oled_write_ln_P(PSTR(" > #@"), false);
      break;
    case 3:
      oled_write_ln_P(PSTR(" >><<"), false);
      break;
  }

  if (layer == 1 || layer == 3) {
    // Lower or Nav
    oled_write_ln_P(&font_down[(frame_number % 3) * 6], false);
  } else {
    oled_write_ln_P(font_blank, false);
  }
}

void render_mod_status(void) {
#ifdef NO_ACTION_ONESHOT
  uint8_t modifiers = get_mods();
#else
  uint8_t modifiers = get_mods() | get_oneshot_mods();
#endif
  led_t led_state = host_keyboard_led_state();
  render_mod_gui(modifiers & MOD_MASK_GUI);
  render_mod_alt(modifiers & MOD_MASK_ALT);
  render_mod_shift(modifiers & MOD_MASK_SHIFT, led_state.caps_lock);
  render_mod_ctrl(modifiers & MOD_MASK_CTRL);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_180;
  }
}

// OLED render main callback
void oled_task_user(void) {
  if (is_master) {
    render_qmk_logo();
    render_layer_state();
  } else {
    render_mod_status();
  }
}
#endif // OLED_DRIVE_ENABLE