// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/add_keycodes.h"
#include "os_detection.h"

// キーマップの設定
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_J, KC_K, KC_L, KC_M,
        KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S,
              KC_T, KC_U, KC_V, KC_W, KC_X,
                    KC_Y,
        // 側面スイッチ
        KC_1, KC_2,
        // 十字キーorジョイスティック     // ジョイスティックスイッチ
        KC_3, KC_4, KC_5, KC_6,       KC_7,
        // 追加スイッチ                 // トグルスイッチ
        KC_8, KC_9,                   XXXXXXX,
        // 右手
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_J, KC_K, KC_L, KC_M,
        KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S,
              KC_T, KC_U, KC_V, KC_W, KC_X,
                    KC_Y,
        // 側面スイッチ
        KC_1, KC_2,
        // 十字キーorジョイスティック     // ジョイスティックスイッチ
        KC_3, KC_4, KC_5, KC_6,       KC_7,
        // 追加スイッチ                 // トグルスイッチ
        KC_8, KC_9,                   XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   {
        ENCODER_CCW_CW(KC_1, KC_2),
        ENCODER_CCW_CW(KC_3, KC_4),
        ENCODER_CCW_CW(KC_5, KC_6),
        ENCODER_CCW_CW(KC_7, KC_8),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX),
        ENCODER_CCW_CW(KC_1, KC_2),
        ENCODER_CCW_CW(KC_3, KC_4),
        ENCODER_CCW_CW(KC_5, KC_6),
        ENCODER_CCW_CW(KC_7, KC_8),
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)
    }
};


// [Kounotori カスタマイズ]
// 0.23.9 にはあったが消されているレイヤーの列挙型定義の復活
enum layer_number {
    BASE = 0,
    ONOFF, OFFON, ONON,                  // トグルスイッチで変更するレイヤー
    LOWER, UPPER, UTIL,                  // 長押しで変更するレイヤー
    MOUSE, BALL_SETTINGS, LIGHT_SETTINGS // 自動マウスレイヤー切り替えや設定用のレイヤー
};

// [Kounotori カスタマイズ]
// https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md#programming-the-behavior-of-any-keycode-idprogramming-the-behavior-of-any-keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
        return true; // Mac では今のところ手を加えるものはない
    }

    switch (keycode) {
        case LT(LOWER, KC_GRAVE):
            if (!record->tap.count) {
                return true; // Hold の場合はそのまま処理
            }

            // Tap の場合は日本語配列設定の Windows でキーコードと入力されるキーを一致させる
            if (record->event.pressed) {
                register_code(KC_BACKSLASH);
            } else {
                unregister_code(KC_BACKSLASH);
            }
            return false; // Skip all further processing of this key
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
        case KC_BACKSLASH:
            if (record->event.pressed) {
                register_code(KC_INTERNATIONAL_3); // 日本語配列設定の Windows でキーコードと入力されるキーを一致させる
            } else {
                unregister_code(KC_INTERNATIONAL_3);
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
        default:
            return true; // Process all other keycodes normally
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
