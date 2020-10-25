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