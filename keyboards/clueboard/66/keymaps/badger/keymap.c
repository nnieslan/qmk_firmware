#include QMK_KEYBOARD_H
#include "keycodes.h"

enum layers {
  _QWERTY,
  _ADJUST,
  _MOVE
};

bool _capsLockState                    = false;
float capsOnSong[][2]                  = SONG(CAPS_ON);
float capsOffSong[][2]                 = SONG(CAPS_OFF);
/* float defaultLayerSong[][2]            = SONG(QWERTY_LAYER_SONG);
float moveLayerSong[][2]               = SONG(MOVE_LAYER_SONG);
float macLayerSong[][2]                = SONG(MAC_LAYER_SONG);
float raiseLayerSong[][2]              = SONG(RAISE_LAYER_SONG);
float lowerLayerSong[][2]              = SONG(LOWER_LAYER_SONG); */
float agSwapSong[][2]                  = SONG(LONG_AG_SWAP);
float agNormSong[][2]                  = SONG(LONG_AG_NORM);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY]   = LAYOUT_66_ansi(\
      KC_GRV,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,  KC_HOME, \
      KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,  KC_END, \
      MOVE,      KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT, \
      KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   KC_UP,  \
      KC_LCTL,   KC_LALT,  KC_LGUI,  KC_SPC,   ADJUST,   KC_RGUI,  KC_LALT,  KC_LEFT,  KC_DOWN,  KC_RGHT),

  [_ADJUST]   = LAYOUT_66_ansi(\
      KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,   KC_VOLU, \
      _______,   NK_ON,    NK_OFF,   EEP_RST,  RESET,     KC_MSTP, KC_MPLY,  KC_PGUP,  KC_HOME,  KC_END,   KC_PGDN,  AG_SWAP,   AG_NORM,  KC_INS,   KC_VOLD, \
      _______,   GE_SWAP,  GE_NORM,  DEBUG,    AG_SWAP,   AG_NORM, KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,   _______, \
      _______,   _______,  _______,  KC_CAPS,  _______,   KC_MPRV, KC_MNXT,  KC_MUTE,  KC_WBAK,  KC_WFWD,  _______,  _______,   KC_BRIU, \
      _______,   _______,  _______,  _______,  _______,   _______, _______,  KC_HOME,  KC_BRID,  KC_END),

  [_MOVE]    = LAYOUT_66_ansi(\
     KC_ESC,     M_VD1,    M_VD2,    M_VD3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,   KC_PGUP, \
     _______,    MM_ULCN,  MM_UH,    MM_URCN,  RESET,    KC_MSTP,  KC_MPLY,  KC_PGUP,  KC_HOME,  KC_END,   KC_PGDN,  IJ_BACK,   IJ_FWD,   KC_INS,   KC_PGDN, \
     _______,    MM_LH,    MM_MAX,   MM_RH,    MAC_POP,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,   _______, \
     _______,    MM_LLCN,  MM_BH,    MM_LRCN,  _______,  KC_MPRV,  KC_MNXT,  KC_MUTE,  IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______,   KC_BRIU, \
     _______,    _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_BRID,  KC_END)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  dprintf("Key event recorded.  KEYCODE: %u, event: %u\n", keycode, record->event.pressed);
  switch (keycode) {
    case AG_SWAP:
      PLAY_SONG(agSwapSong);
      return true;
      break;
    case AG_NORM:
      PLAY_SONG(agNormSong);
      return true;
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        dprintf("CAPS STATE: %u\n", _capsLockState);
        _capsLockState = !_capsLockState;
        _capsLockState ? PLAY_SONG(capsOnSong) : PLAY_SONG(capsOffSong);
      }
      return true;
      break;
  }
  return true;
}
