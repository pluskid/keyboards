# Flanck

![Flanck](https://user-images.githubusercontent.com/3542/97387739-d358bf80-1893-11eb-99b9-f6d4b9965780.JPG)
![Flanck and Corne](https://user-images.githubusercontent.com/3542/97387844-013e0400-1894-11eb-8e51-198a5168ffaf.JPG)
![Flanck and Reviung41 Height Comparison](https://user-images.githubusercontent.com/3542/97387768-e2d80880-1893-11eb-985a-2822bd54e030.JPG)

Flanck is the "Fat Planck". It is a low profile 4x12 grid style keypoard using Kailh Choc Switch. The outer most columns are modified to be 1.5U wide to make it easier to hit without stretching the wrist too much. The two sides are also made 1U apart to make it more ergonomic. It also makes room for the Elite-C on the top side of the PCB, which allows us to reduce the height of the board.

* Keyboard Maintainer: [pluskid](https://pluskid.org)
* Hardware Supported: Flanck V1
* Hardware Availability: PCB can be self ordered, see [pcb files](https://github.com/pluskid/keyboards/tree/main/flanck).

Note this firmware is not merged into the QMK main repo. To compile this firmware, you need to setup the QMK environment first.
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) 
for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

After setting up the QMK environment, you need to copy (or make a symlink) this directory into the `keyboards` directory under the QMK source tree:

```
$ cd /path/to/qmk/keyboards
$ ln -s /path/to/flanck/qmk flanck
```

Then
you can use

```
$ qmk compile -kb flanck/v1 -km default
```

to compile the firmware with the default keymap. The default keymap is converted from [my 4x12 ortho linear keymap](https://github.com/pluskid/keyboards/tree/main/ortho-keymap),
which uses [Colemak DHm](https://colemakmods.github.io/mod-dh/keyboards.html) as the base layer. You can create your own keymap 
by making a new directory under `keymaps` and create a `keymap.c`. You can manually edit `keymap.c`. Or if you prefer using
[QMK Configurator](https://config.qmk.fm/#/planck/rev6/LAYOUT_ortho_4x12), you can use a 4x12 ortho keyboard
(e.g. [Planck 4x12](https://config.qmk.fm/#/planck/rev6/LAYOUT_ortho_4x12)) as a starting point to edit your keymap. Then
you can export the keymap as a json file, and use `qmk json2c` to convert this json file to a `keymap.c` file and build it 
locally under the flanck firmware directory. Note you cannot directly compile a firmware online with QMK configurator, because
our firmware code is not merged into the QMK main repo.
