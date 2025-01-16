// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"
#include "os_detection.h"

// レイヤー名
enum layer_number {
    BASE = 0,
    ONOFF, OFFON, ONON,                       // トグルスイッチで変更するレイヤー
    LOWER, UPPER, UTIL,                       // 長押しで変更するレイヤー
    MOUSE, BALL_SETTINGS, LIGHT_SETTINGS // 自動マウスレイヤー切り替えや設定用のレイヤー
};

// キーマップの設定
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
        // 左手
        // 天面スイッチ
        KC_ESC,  KC_1,         KC_2,            KC_3, LT(BALL_SETTINGS, KC_4), LT(LIGHT_SETTINGS, KC_5),
        KC_TAB,  KC_Q,         KC_W,            KC_E, KC_R, KC_T,
        CMD_CTL, KC_A,         LT(MOUSE, KC_S), KC_D, KC_F, KC_G,
                 LSFT_T(KC_Z), KC_X,            KC_C, KC_V, KC_B,
                               MOD_SCRL,
        // 側面スイッチ
        KC_LNG2, KC_SPC,
        // 十字キーorジョイスティック                // ジョイスティックスイッチ
        KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT,         L_CHMOD,
        // 追加スイッチ                             // トグルスイッチ
        KC_MS_BTN2, KC_MS_BTN1,                    MO(ONOFF),
        // 右手
        LT(LIGHT_SETTINGS, KC_6), LT(BALL_SETTINGS, KC_7), KC_8, KC_9, KC_0, KC_BSPC,
        KC_Y, KC_U, KC_I,    KC_O,             KC_P,    KC_ENT,
        KC_H, KC_J, KC_K,    LT(MOUSE, KC_L),  KC_SCLN, KC_RSFT,
        KC_N, KC_M, KC_COMM, KC_DOT,           KC_SLSH,
                             MOD_SCRL,
        KC_SPACE, KC_LNG1,
        KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT,         R_CHMOD,
        KC_MS_BTN1, KC_MS_BTN2,                    MO(OFFON)
    ),
    [ONOFF] = LAYOUT(
        // 左手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,
                          _______,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______,
        // 右手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
                                   _______,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______
    ),
    [OFFON] = LAYOUT(
        // 左手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,
                          _______,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______,
        // 右手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
                                   _______,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______
    ),
    [ONON] = LAYOUT(
        // 左手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,
                          _______,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______,
        // 右手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
                                   _______,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______
    ),
    [MOUSE] = LAYOUT(
        // 左手
        _______, _______, _______, _______, _______,    _______,
        _______, _______, _______, _______, _______,    _______,
        _______, _______, _______, KC_MS_BTN2, KC_MS_BTN1, MOD_SCRL,
                 QK_USER_4, _______, _______, _______, _______,
                          MOD_SCRL,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______,
        // 右手
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        MOD_SCRL, KC_MS_BTN1, KC_MS_BTN2, _______, _______, _______,
        _______, _______, _______, _______, QK_USER_4,
                                   MOD_SCRL,
        _______, _______,
        _______, _______, _______, _______,          _______,
        _______, _______,                            _______
    ),
    [BALL_SETTINGS] = LAYOUT(
        // 左手
        XXXXXXX,    XXXXXXX, XXXXXXX, QK_USER_14, _______, L_CHMOD,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, L_SPD_I, XXXXXXX,
        AUTO_MOUSE, XXXXXXX, XXXXXXX, L_ANG_D, L_INV,   L_ANG_I,
                    XXXXXXX, XXXXXXX,XXXXXXX, L_SPD_D, XXXXXXX,
                             INV_SCRL,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, INV_SCRL,                           XXXXXXX,
        // 右手
        R_CHMOD, _______, QK_USER_14, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, R_SPD_I,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        R_ANG_D, R_INV,   R_ANG_I, XXXXXXX, XXXXXXX, AUTO_MOUSE,
        XXXXXXX, R_SPD_D,   XXXXXXX, XXXXXXX, XXXXXXX,
                                     INV_SCRL,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    ),
    [LIGHT_SETTINGS] = LAYOUT(
        // 左手
        XXXXXXX, XXXXXXX, XXXXXXX, UG_NEXT, UG_PREV, _______,
        XXXXXXX, UG_SPDU, UG_VALU, UG_SATU, UG_HUEU, UG_TOGG,
        OLED_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 UG_SPDD, UG_VALD, UG_SATD, UG_HUED, XXXXXXX,
                          QK_USER_15,
        UG_NEXT, UG_PREV,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX,
        // 右手
        _______, UG_NEXT, UG_PREV, XXXXXXX, XXXXXXX, XXXXXXX,
        UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, UG_SPDU, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, OLED_MOD,
        XXXXXXX, UG_HUED, UG_SATD, UG_VALD, UG_SPDD,
                                   QK_USER_15,
        UG_PREV, UG_NEXT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   {
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
    },
    [LIGHT_SETTINGS] =   {
        ENCODER_CCW_CW(UG_SPDU, UG_SPDD),
        ENCODER_CCW_CW(UG_VALU, UG_VALD),
        ENCODER_CCW_CW(UG_SATU, UG_SATD),
        ENCODER_CCW_CW(UG_HUEU, UG_HUED),
        ENCODER_CCW_CW(UG_SPDU, UG_SPDD),
        ENCODER_CCW_CW(UG_VALU, UG_VALD),
        ENCODER_CCW_CW(UG_SATU, UG_SATD),
        ENCODER_CCW_CW(UG_HUEU, UG_HUED),
    },
};

// [Kounotori カスタマイズ]
// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#hold-on-other-key-press
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_GRAVE):
        case LT(MOUSE, KC_ENT):
        case LCTL_T(KC_SPACE):
            return true;
        default:
            return false;
    }
}

// [Kounotori カスタマイズ]
// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#tapping-term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(UTIL, KC_E):
            return 300;
        default:
            return TAPPING_TERM;
    }
}

// [Kounotori カスタマイズ]
// https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md#permissive-hold
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(UTIL, KC_E):
        case LT(MOUSE, KC_LNG2):
            return true;
        default:
            return false;
    }
}

// [Kounotori カスタマイズ]
// https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md#programming-the-behavior-of-any-keycode-idprogramming-the-behavior-of-any-keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
        return true; // Mac では今のところ手を加えるものはない
    }

    switch (keycode) {
        case LCTL_T(KC_SPACE):
            if (record->tap.count) {
                return true; // Tap の場合はそのまま処理
            }

            // Hold の場合は Control 再現レイヤー扱いにする
            if (record->event.pressed) {
                layer_on(UPPER);
            } else {
                layer_off(UPPER);
            }
            return false;
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                register_code(KC_LWIN);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_LWIN);
            }
            return false;
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                register_code(KC_LWIN);
            } else {
                unregister_code(KC_LWIN);
            }
            return false;
        // KC_GRAVE/KC_BACKSLASH を KC_BACKSLASH/KC_INTERNATIONAL_3 扱いにする対応は Windows 10 では必要だったが 11 では入力文字がキーコードと一致するため不要になった (なお KC_INTERNATIONAL_3 は何も入力されなくなった)
        // case LT(LOWER, KC_GRAVE):
        //     if (!record->tap.count) {
        //         return true; // Hold の場合はそのまま処理
        //     }
        
        //     // Tap の場合は日本語配列設定の Windows でキーコードと入力されるキーを一致させる
        //     if (record->event.pressed) {
        //         register_code(KC_BACKSLASH);
        //     } else {
        //         unregister_code(KC_BACKSLASH);
        //     }
        //     return false; // Skip all further processing of this key
        // case KC_BACKSLASH:
        //     if (record->event.pressed) {
        //         register_code(KC_INTERNATIONAL_3); // 日本語配列設定の Windows でキーコードと入力されるキーを一致させる
        //     } else {
        //         unregister_code(KC_INTERNATIONAL_3);
        //     }
        //     return false;
        default:
            return true; // Process all other keycodes normally
    }
}
