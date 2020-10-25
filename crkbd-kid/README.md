# Introduction

Corne keymap and OLED display customization.

This directory is not submitted to the QMK main repo. To 
compile this code, you need to setup [QMK](https://docs.qmk.fm/#/)
as described in their doc. Then you can either copy or make
a symlink of this directory into the `keyboards/crkbd/keymaps/`
folder in QMK source tree. Then you can compile with the follwoing
command:

```
qmk compile -kb crkbd -km crkbd-kid
```

# Bootloader

I use Elite-C, so I defined the bootloader to be `atmel-dfu`. If you
use Pro Micro, you can change it to `caterina` in `rules.mk`.

# The Keymap

The keymap uses Colemak-DHm as the base layer. The `keymap.c` was auto-generated
by QMK's `json2c` tool. I use the same layout on my Planck, Corne and Reviung41,
and uses a tool (see [ortho-keymap](../ortho-keymap/)) to convert one source 4x12
keymap to the target layout for all the keyboards.

# OLED

The left OLED will show a layer indicator, and the right OLED will show
an indicator for each modifier. Check out the [demo](https://imgur.com/gallery/LaMWv8K).

The OLED font file `glcdfont.c` was generated using 
[Helix Font Editor](https://helixfonteditor.netlify.app/). I found the
following resources very helpful:

* [QMK documents on OLED driver](https://docs.qmk.fm/#/feature_oled_driver)
* QMK OLED driver implementation at [drivers/oled/oled_driver.c](https://github.com/qmk/qmk_firmware/blob/master/drivers/oled/oled_driver.c)
* Gotham's OLED [demo](https://www.reddit.com/r/olkb/comments/fnkwsr/qmk_custom_oled/) and [related code](https://github.com/qmk/qmk_firmware/tree/master/keyboards/crkbd/keymaps/gotham)