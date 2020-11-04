# Flanck

Flanck is the "Fat Planck". It is a low profile 4x12 grid style keypoard using Kailh Choc Switch. The outer most columns are modified to be 1.5U wide to make it easier to hit without stretching the wrist too much. The two sides are also made 1U apart to make it more ergonomic. It also makes room for the Elite-C on the top side of the PCB, which allows us to reduce the height of the board.

## Flanck v1.1

![Flanck](https://user-images.githubusercontent.com/3542/97387739-d358bf80-1893-11eb-99b9-f6d4b9965780.JPG)
![Flanck and Corne](https://user-images.githubusercontent.com/3542/97387844-013e0400-1894-11eb-8e51-198a5168ffaf.JPG)
![Flanck and Reviung41 Height Comparison](https://user-images.githubusercontent.com/3542/97387768-e2d80880-1893-11eb-985a-2822bd54e030.JPG)

The first built of Flanck (on Oct. 27, 2020). If you are interested in building this keyboard yourself, you will need the followings:

- The garber files of the PCB, the top plate and bottom plate can be found in the [Flanck v1.1 Release page](https://github.com/pluskid/keyboards/releases/tag/flanck-v1.1). You can order PCBs using those files from manufactures like [JLCPCB](https://jlcpcb.com/).
- The firmware is based on [QMK](https://docs.qmk.fm/), and can be found under [qmk/v1](qmk/v1/).
- The following table list the remaining components that are needed. The links are only provided for conveinence. You can collect your parts from any sources.

| Item        | Qty| Links | Remarks |
|-------------|---:|-------|---------|
| Elite-C     |  1 | [BoardSource](https://boardsource.xyz/store/5ef67ea66786dc1e65a80708), [Keeb.io](https://keeb.io/products/elite-c-low-profile-version-usb-c-pro-micro-replacement-atmega32u4) | Can also use Pro Micro and compatible clones -- then don't forget to update `BOOTLOADER` in [qmk/v1/rules.mk](qmk/v1/rules.mk) of the firmware accordinly. |
| Diode (1N4148 SMD) | 48 | [BoardSource](https://boardsource.xyz/store/5ec9fc5d64caf04f83aa646c) | |
| Choc Hotswap Socket| 48 | [BoardSource](https://boardsource.xyz/store/5eca381464caf04f83aa6482) | |
| Kailh Choc Switch  | 48 | [BoardSource](https://boardsource.xyz/store/5ef6eff1de8f0374b7347742), [AliExperss](https://www.aliexpress.com/item/4000907409650.html) | Both V1 and V2 should work, though I only tested Choc V1 |
| Choc Keycap 1U | 40 | [BoardSource MBK keycaps](https://boardsource.xyz/store/5f6ef2d68e3bf05ab838f918)| Get 2x home-scooped 1U keycaps as well |
| Choc Keycap 1.5U | 8 | [BoardSource MBK keycaps](https://boardsource.xyz/store/5f6ef2d68e3bf05ab838f918)| |
| Tact Switch |  1 | [Amazon](https://www.amazon.com/gp/product/B0819VWGX8/ref=ppx_yo_dt_b_asin_title_o09_s00?ie=UTF8&psc=1), [AliExperss](https://www.aliexpress.com/item/32914876022.html) | For the reset button |
| Rubber Feet |  6 | [Amazon](https://www.amazon.com/gp/product/B07LGK6RWN/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1), [AliExperss](https://www.aliexpress.com/item/32289191938.html) | |
| M2 4mm spacer | 7 | [Amazon](https://www.amazon.com/gp/product/B07H3VN9Y9/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1) | Longer spacers also work, though board will be higher |
| M2 screws     | 14 | [BoardSource](https://boardsource.xyz/store/5ecad681e7e0515b382b553e) | 4mm screws work for 4mm spacers. You can get some M2 washers (1mm thick) to fine tune if your spacers do not have enough room for the screws to go all the way in. |
| USB-C cable |  1 | [Amazon](https://www.amazon.com/gp/product/B07X8FNQ6K/ref=ppx_yo_dt_b_asin_title_o02_s01?ie=UTF8&psc=1) | USB-2 is enougn |
| Washers or O rings | | | Optional. See below. |

## Washers / O rings between PCB and Bottom Plate

When using Choc switches, there is ~2mm space between the PCB and the bottom plate. The PCB is held together with the top plate by the switches. If you frequently change the switches or want extra support for the PCB, you can put washers or O rings around each M2 spacer between the PCB and the bottom plate. See the illustration below:

![O ring illustration](https://user-images.githubusercontent.com/3542/98069327-55f0fa00-1e13-11eb-9d34-672807562ab9.png)

## Wireless Flanck with nice!nano

You can use any Pro Micro compatible MCU board in place of Elite-C. In particular, I built a [nice!nano](https://docs.nicekeyboards.com/#/nice!nano/) based Flanck keyboard that support bluetooth. I use [this 3.7V 100mAh Lithium Ion Polymer Battery](https://www.amazon.com/gp/product/B0137KTPP0/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1), which is small enough to sit below the nice!nano. The [ZMK](https://zmkfirmware.dev/) based firmware can be found [here](https://github.com/pluskid/flanck-zmk-config).

![Flanck Wired and Wireless](https://user-images.githubusercontent.com/3542/98070456-0fe96580-1e16-11eb-9069-8433277cd1bb.JPG)
