/** Default keymap, Colemak-DHm as the base layer, with some MacOS utility functions. */
#include QMK_KEYBOARD_H

enum layers {
	_COLEMAK,
	_LOWER,
	_RAISE,
	_NAVI,
};

// Readability keycodes
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NAVI MO(_NAVI)
#define NAV_ESC LT(_NAVI, KC_ESC)
// MacOS Screen Shot
#define SCROT LCTL(LSFT(LCMD(KC_4)))
// MacOS Paste as Text
#define PTEXT RSFT(ROPT(RCMD(KC_V)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_COLEMAK] = LAYOUT(
		KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,   KC_B,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
		NAV_ESC, KC_A,    KC_R,    KC_S,    KC_T,   KC_G,   KC_M,   KC_N,  KC_E,    KC_I,    KC_O,    RCTL_T(KC_QUOT),
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,   KC_V,   KC_K,   KC_H,  KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
		KC_CAPS, KC_LCTL, KC_LALT, KC_LGUI, LOWER,  KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	),

	[_LOWER] = LAYOUT(
		KC_TRNS, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_MINS, XXXXXXX, KC_TRNS,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
		KC_TRNS, XXXXXXX, KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NAVI,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[_RAISE] = LAYOUT(
		KC_TRNS, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_EQL,  XXXXXXX, KC_DEL,
		KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
		KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NAVI,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[_NAVI] = LAYOUT(
		RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,
        KC_TRNS, XXXXXXX, KC_LCTL, KC_LALT, KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, SCROT,   XXXXXXX, XXXXXXX, PTEXT,   XXXXXXX, XXXXXXX, KC_HOME, KC_END,  XXXXXXX, XXXXXXX,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};