# Ortholinear Keymap and Converter

I use a unified layout on a few different ortholinear keyboards:

* Planck
* Corne
* Reviung41

To make it easy to manage the keymap across different keyboard, I define
my keymap in a Planck 4x12 grid layout using
[QMK configurator](https://config.qmk.fm/#/planck/rev6/LAYOUT_planck_grid),
and then use this script to convert to the keymap for different keyborad.
My current keymap is in [planck-colemak-dhm.json](planck-colemak-dhm.json),
which can be viewed by uploading to the
[QMK configurator](https://config.qmk.fm/#/planck/rev6/LAYOUT_planck_grid).

The converted json file can be uploaded to QMK configurator to build the
firmware online, or if you need to do other modifications, you can also
call run `qmk json2c` on the json files to generate C code that you can
copy into your `keymap.c`.

## Existing layouts

* `planck-colemak-dhm.json`: default keymap with Colemak-dhm as the base layer.
  I used this layout in 2020.
* `placnk-qwer.json`: default keymap with QWER as the base layer.
* `placnk-qwer-rshift-symbol.json`: similar to `planck-qwer.json`, except that
  for all the shifted symbols, I manually defined them to be using rshift. This
  avoid conflicting with using left-shift to switch Chinese/English state of my
  Chinese input software.
* `corne-art.json`: layout for corne that support use with drawing tablet. It is
  similar to `planck-qwer-rshift-symbol.json`, except when LOWER+RAISE+H is pressed,
  it switch to a *half* mode (layer 5), where the left half has enough modifiers
  for art use. Most of the buttons on the right still functions. However, the LOWER
  and RAISE buttons will no longer work as usual, so you cannot type numbers
  or symbols. To switch back to normal mode, press RAISE+H.

