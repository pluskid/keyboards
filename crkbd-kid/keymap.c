/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
  //Following line allows macro to read current RGB settings
  extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
#define _NAVI 3

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  NAVI,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3( \
  // -------------------------------------------------------------------------
  // row1 left:
                 KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,            KC_B, \
  // row1 right:
                   KC_J,   KC_L,    KC_U,    KC_Y, KC_SCLN,         KC_BSPC, \
  // -------------------------------------------------------------------------
  // row2 left:
      LT(_NAVI, KC_ESC),   KC_A,    KC_R,    KC_S,    KC_T,            KC_G, \
  // row2 right:
                   KC_M,   KC_N,    KC_E,    KC_I,    KC_O, RCTL_T(KC_QUOT), \
  // -------------------------------------------------------------------------
  // row3 left:
                KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_D,            KC_V, \
  // row3 right:
                   KC_K,   KC_H, KC_COMM,  KC_DOT, KC_SLSH,       KC_SFTENT, \
  // -------------------------------------------------------------------------
  // bottom row:
                KC_LGUI,   LOWER,  KC_SPC,     KC_SPC,  RAISE,  KC_RALT \
  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_UNDS, KC_MINS, XXXXXXX, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_PLUS,  KC_EQL, XXXXXXX,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAVI] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, XXXXXXX, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, LCTL(LSFT(LCMD(KC_4))), XXXXXXX, XXXXXXX, RSFT(ROPT(RCMD(KC_V))), \
                                                                                 XXXXXXX, XXXXXXX, KC_HOME, KC_END, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

////////////////////////////////////////////////////////////////////////////////
// OLED related functions
////////////////////////////////////////////////////////////////////////////////
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
    return OLED_ROTATION_180;
  } else {
    return OLED_ROTATION_90;
  }
}

// OLED render main callback
void oled_task_user(void) {
  if (is_master) {
    // render_mod_status();
    // Host Keyboard Layer Status
    // oled_write_P(PSTR("Layer: "), false);
    render_mod_status();
  } else {
    oled_write_P(PSTR("Slave"), false);
  }
}
#endif // OLED_DRIVE_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _NAVI);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _NAVI);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _NAVI);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _NAVI);
      }
      return false;
    case NAVI:
        if (record->event.pressed) {
          layer_on(_NAVI);
        } else {
          layer_off(_NAVI);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}


