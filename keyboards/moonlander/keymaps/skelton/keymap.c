#include QMK_KEYBOARD_H
#include "version.h"
#include "process_auto_shift.h"
#include "process_audio.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  TOG_CAPS,
  TOG_NUMS,
  TOG_SCRL,
  TOG_LEDS,
  TOG_ASHF,
  TOG_AUDI,
};

enum indicators {
  IND_CAPS = 0,
  IND_NUMS,
  IND_SCRL,
  IND_LEDS,
  IND_ASHF,
  IND_AUDI,
};

enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           TOG_LEDS,       	TOG_CAPS,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MEH,         
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           TOG_ASHF,           TOG_NUMS,       KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_SLASH,       
    KC_BSPACE,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           TOG_AUDI,           TOG_SCRL,       KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,       
    KC_LSHIFT,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           	KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_BSLASH,      KC_UP,          
    KC_LCTRL,       TD(DANCE_0),    KC_LALT,        KC_NONUS_BSLASH,KC_GRAVE,                       TO(2),              TO(1),          KC_LBRACKET,    KC_RBRACKET,    KC_LEFT,        KC_RIGHT,       KC_DOWN,        
	                                                                KC_SPACE,       KC_MINUS,       MO(2),              MO(2),          KC_EQUAL,       KC_ENTER
  ),
  [1] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,     KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           KC_TRANSPARENT,     KC_TRANSPARENT, KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCOLON,      KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_A,           KC_R,           KC_S,           KC_T,           KC_G,           KC_TRANSPARENT,     KC_TRANSPARENT, KC_M,           KC_N,           KC_E,           KC_I,           KC_O,           KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,                                               KC_K,           KC_H,           KC_COMMA,       KC_DOT,         KC_BSLASH,      KC_UP,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 TO(0),              TO(2),                          KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT,        KC_RIGHT,       KC_DOWN,        
                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,     KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_LBRACKET,    KC_RBRACKET,    KC_LCBR,        KC_RCBR,        KC_EXLM,        KC_TRANSPARENT,     KC_TRANSPARENT, KC_KP_PLUS,     KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    KC_F11,         
    KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_AT,          KC_HASH,        KC_PIPE,        KC_TRANSPARENT,     KC_TRANSPARENT, KC_KP_DOT,      KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_ASTERISK, KC_F12,         
    KC_TRANSPARENT, KC_TILD,        KC_CIRC,        KC_PERC,        KC_DLR,         KC_AMPR,                                            KC_KP_0,        KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_SLASH,    KC_PGUP,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_1),    KC_HYPR,                        TO(1),              TO(0),                          KC_DELETE,      KC_INSERT,      KC_HOME,        KC_END,         KC_PGDOWN,      
                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

extern rgb_config_t rgb_matrix_config;

const uint8_t locations[6] = {
    65, 66, 67, 29, 30, 31
};

bool toggles[6];

uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {152,255,255}, {152,255,255}, {152,255,255}, {118,255,255}, {118,255,255},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {41,255,255},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {41,255,255},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,240,213},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,240,213},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255},
			{0,0,0}, {0,0,0}, {0,0,0},
			{86,255,255}, {86,255,255}, {86,255,255}, {0,0,255},
			
			{152,255,255}, {152,255,255}, {152,255,255}, {118,255,255}, {118,255,255},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {41,255,255},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {41,255,255},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,240,213},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,240,213},
			{228,255,255}, {0,0,255}, {0,0,255}, {0,0,255},
			{0,0,0}, {0,0,0}, {0,0,0},
			{86,255,255}, {86,255,255}, {86,255,255}, {0,0,255} },

    [1] = { {22,255,255}, {22,255,255}, {22,255,255}, {53,255,255}, {53,255,255},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {188,210,233},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {188,210,233},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {152,255,255},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {152,255,255},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255},
			{0,0,0}, {0,0,0}, {0,0,0},
			{0,255,255}, {0,255,255}, {0,255,255}, {0,0,255},
			
			{22,255,255}, {22,255,255}, {22,255,255}, {53,255,255}, {53,255,255},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {188,210,233},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {188,210,233},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {152,255,255},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {152,255,255},
			{129,255,255}, {0,0,255}, {0,0,255}, {0,0,255},
			{0,0,0}, {0,0,0}, {0,0,0},
			{0,255,255}, {0,255,255}, {0,255,255}, {0,0,255} },

    [2] = { {0,0,255}, {0,0,255}, {0,0,255}, {188,210,233}, {152,255,255},
			{43,211,255}, {191,119,255}, {191,119,255}, {30,117,255}, {118,255,255},
			{43,211,255}, {191,119,255}, {191,119,255}, {30,117,255}, {74,255,255},
			{43,211,255}, {191,119,255}, {30,117,255}, {30,117,255}, {22,255,255},
			{43,211,255}, {191,119,255}, {30,117,255}, {30,117,255}, {0,240,213},
			{43,211,255}, {0,116,255}, {0,116,255}, {0,116,255},
			{0,0,0}, {0,0,0}, {0,0,0},
			{172,255,255}, {172,255,255}, {172,255,255}, {0,0,255},
			
			{0,0,255}, {0,0,255}, {0,0,255}, {188,210,233}, {152,255,255},
			{43,211,255}, {67,127,255}, {67,127,255}, {67,127,255}, {118,255,255},
			{43,211,255}, {129,131,255}, {129,131,255}, {129,131,255}, {74,255,255},
			{43,211,255}, {129,131,255}, {129,131,255}, {129,131,255}, {22,255,255},
			{43,211,255}, {129,131,255}, {129,131,255}, {129,131,255}, {0,240,213},
			{43,211,255}, {67,127,255}, {67,127,255}, {129,131,255},
			{0,0,0}, {0,0,0}, {0,0,0},
			{172,255,255}, {172,255,255}, {172,255,255}, {0,0,255} },
};

void set_toggle_indicator(uint8_t indicator) {
    uint8_t totalLayers = 3;
    uint8_t l = locations[indicator];
    uint8_t c = 70;
    
    if (toggles[indicator]) {
        for (uint8_t i = 0; i < totalLayers; i++) {
            memcpy(ledmap[i][l], ledmap[i][c], sizeof(ledmap[i][c]));
        }
    } else {
        uint8_t colour[3] = {0,0,255};
        for (uint8_t i = 0; i < totalLayers; i++) {
            memcpy(ledmap[i][l], colour, sizeof(colour));
        }
    }
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  toggles[0] = false;
  toggles[1] = true;
  toggles[2] = false;
  toggles[3] = false;
  toggles[4] = true;
  toggles[5] = false;
  for (uint8_t i = 0; i < 6; i++) {
    set_toggle_indicator(i);
  }
}

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case TOG_CAPS:
      if (record->event.pressed) {
        tap_code(KC_CAPS_LOCK);
        toggles[IND_CAPS] = !toggles[IND_CAPS];
        set_toggle_indicator(IND_CAPS);
      }
      return false;
    case TOG_NUMS:
      if (record->event.pressed) {
        tap_code(KC_NUM_LOCK);
        toggles[IND_NUMS] = !toggles[IND_NUMS];
        set_toggle_indicator(IND_NUMS);
      }
      return false;
    case TOG_SCRL:
      if (record->event.pressed) {
        tap_code(KC_SCROLLLOCK);
        toggles[IND_SCRL] = !toggles[IND_SCRL];
        set_toggle_indicator(IND_SCRL);
      }
      return false;
    case TOG_LEDS:
      if (record->event.pressed) {
        process_record_kb(MOON_LED_LEVEL, record);
        toggles[IND_LEDS] = !toggles[IND_LEDS];
        set_toggle_indicator(IND_LEDS);
      }
      return false;
    case TOG_ASHF:
      if (record->event.pressed) {
        autoshift_toggle();
        toggles[IND_ASHF] = !toggles[IND_ASHF];
        set_toggle_indicator(IND_ASHF);
      }
      return false;
    case TOG_AUDI:
      if (record->event.pressed) {
        process_audio(AU_TOG, record);
        toggles[IND_AUDI] = !toggles[IND_AUDI];
        set_toggle_indicator(IND_AUDI);
      }
      return false;
  }
  return true;
}

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[2];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_HOLD: register_code16(KC_LGUI); break;
        case DOUBLE_TAP: register_code16(KC_LGUI); break;
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case DOUBLE_TAP: unregister_code16(KC_LGUI); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_PSCREEN);
        tap_code16(KC_PSCREEN);
        tap_code16(KC_PSCREEN);
    }
    if(state->count > 3) {
        tap_code16(KC_PSCREEN);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_PSCREEN); break;
        case SINGLE_HOLD: register_code16(KC_PSCREEN); break;
        case DOUBLE_TAP: register_code16(KC_PSCREEN); register_code16(KC_PSCREEN); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_PSCREEN); register_code16(KC_PSCREEN);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_PSCREEN); break;
        case SINGLE_HOLD: unregister_code16(KC_PSCREEN); break;
        case DOUBLE_TAP: unregister_code16(KC_PSCREEN); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_PSCREEN); break;
    }
    dance_state[1].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
};
