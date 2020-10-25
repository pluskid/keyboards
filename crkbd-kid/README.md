Corne keymap and OLED display customization. The left OLED
will show a layer indicator, and the right OLED will show
an indicator for each modifier. The keymap uses Colemak-DHm
as the base layer.

This directory is not submitted to the QMK main repo. To 
compile this code, you need to setup [QMK](https://docs.qmk.fm/#/)
as described in their doc. Then you can either copy or make
a symlink of this directory into the `keyboards/crkbd/keymaps/`
folder in QMK source tree. Then you can compile with the follwoing
command:

```
qmk compile -kb crkbd -km crkbd-kid
```