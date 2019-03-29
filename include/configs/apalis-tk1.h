/*
 * Copyright (c) 2012-2016 Toradex, Inc.
 *
 * Configuration settings for the Toradex Apalis TK1 modules.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

/* enable PMIC */
#define CONFIG_AS3722_POWER

#include "tegra124-common.h"

#define CONFIG_ARCH_MISC_INIT

/* High-level configuration options */
#define V_PROMPT			"Apalis TK1 # "
#define CONFIG_CUSTOM_BOARDINFO		/* not from device-tree model node */
#undef CONFIG_DISPLAY_BOARDINFO
#define CONFIG_DISPLAY_BOARDINFO_LATE

/* Board-specific serial config */
#define CONFIG_SERIAL_MULTI
#define CONFIG_TEGRA_ENABLE_UARTA
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTA_BASE

/* Make the HW version stuff available in U-Boot env */
#define CONFIG_VERSION_VARIABLE		/* ver environment variable */
#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
#define CONFIG_CMD_ASKENV

/* I2C */
#define CONFIG_SYS_I2C_TEGRA
#define CONFIG_CMD_I2C

/* SD/MMC support */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_TEGRA_MMC
#define CONFIG_CMD_MMC
#define CONFIG_SUPPORT_EMMC_BOOT	/* eMMC specific */

/* Environment in eMMC, before config block at the end of 1st "boot sector" */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_OFFSET		(-CONFIG_ENV_SIZE)
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_ENV_PART		2

/* USB client support */
#define CONFIG_G_DNL_MANUFACTURER	"Toradex"
/* Toradex is 0x1b67. Fastboot requires Google's VID */
#define CONFIG_G_DNL_VENDOR_NUM		0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM	0xffff /* Fallback, set using fixup */

/* USB host support */
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_TEGRA
#define CONFIG_USB_MAX_CONTROLLER_COUNT	3
#define CONFIG_USB_STORAGE
#define CONFIG_CMD_USB

/* Android boot images */
#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_CMD_BOOTA
#define CONFIG_OF_LIBFDT

/* Android Fastboot */
#define CONFIG_CMD_FASTBOOT
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_FASTBOOT_STORAGE_MMC
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 0

#define CONFIG_ANDROID_BOOT_PARTITION_MMC 1
#define CONFIG_ANDROID_RECOVERY_PARTITION_MMC 2
#define CONFIG_ANDROID_SYSTEM_PARTITION_MMC 3
#define CONFIG_ANDROID_DATA_PARTITION_MMC 6

#define CONFIG_USB_FASTBOOT_BUF_ADDR 0x90000000
#define CONFIG_USB_FASTBOOT_BUF_SIZE 0x20000000

/* GPT support */
#define CONFIG_EFI_PARTITION
#define CONFIG_CMD_GPT

/* Reading raw partitions */
#define CONFIG_CMD_READ

/* PCI host support */
#define CONFIG_PCI
#undef CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCI_TEGRA
#define CONFIG_PCI_PNP
#define CONFIG_CMD_PCI
#define CONFIG_CMD_PCI_ENUM

/* PCI networking support */
#define CONFIG_E1000
#define CONFIG_E1000_NO_NVM

/* General networking support */
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_IP_DEFRAG
#define CONFIG_TFTP_BLOCKSIZE		16384
#define CONFIG_TFTP_TSIZE

/* Miscellaneous commands */
#define CONFIG_CMD_SETEXPR
#define CONFIG_FAT_WRITE

#undef CONFIG_BOOTDELAY
#define CONFIG_BOOTDELAY	1
#define CONFIG_ZERO_BOOTDELAY_CHECK
#undef CONFIG_IPADDR
#define CONFIG_IPADDR		192.168.10.2
#define CONFIG_NETMASK		255.255.255.0
#undef CONFIG_SERVERIP
#define CONFIG_SERVERIP		192.168.10.1

/* Increase console I/O buffer size */
#undef CONFIG_SYS_CBSIZE
#define CONFIG_SYS_CBSIZE		1024

/* Increase arguments buffer size */
#undef CONFIG_SYS_BARGSIZE
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

/* Increase print buffer size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/* Increase maximum number of arguments */
#undef CONFIG_SYS_MAXARGS
#define CONFIG_SYS_MAXARGS		32

#define CONFIG_CMD_TIME
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_ALT_MEMTEST

#define CONFIG_OF_SYSTEM_SETUP

#define CONFIG_SUPPORT_RAW_INITRD
#define CONFIG_SYS_BOOT_RAMDISK_HIGH

#include "tegra-common-usb-gadget.h"
#undef CONFIG_SYS_DFU_DATA_BUF_SIZE
#include "tegra-common-post.h"

#undef CONFIG_BOOTCOMMAND
#undef CONFIG_EXTRA_ENV_SETTINGS

#define CONFIG_BOOTCOMMAND "ext2load mmc 0:1 ${kernel_addr_r} ${boot_file};ext2load mmc 0:1 ${fdt_addr_r} ${fdt_file};ext2load mmc 0:1 ${ramdisk_addr_r} ${ramdisk_file};bootm ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r}"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"soc=tegra-tk1\0" \
	"vendor=toradex\0" \
	"bootcmd_install=mmc rescan;mmc dev 0 1;mmc write ${boot_img_addr} 0 ${boot_img_len};mmc dev 0 2;mw.b $loadaddr 0 200;mmc write ${loadaddr} 0x3FF0 0x10 || mmc write ${loadaddr} 0x1FF0 0x10 || mmc write ${loadaddr} 0xFF0 0x10 || mmc write ${loadaddr} 0x7F0 0x10;mmc dev 0 0;gpt write mmc 0 \"${parts}\";ums 0 mmc 0\0" \
	"fdt_file=devicetree.dtb\0" \
	"baudrate=115200\0" \
	"serverip=192.168.1.1\0" \
	"fdt_high=0xffffffff\0" \
	"netmask=255.255.255.0\0" \
	"fdt_addr_r=0x82000000\0" \
	"kernel_addr_r=0x81000000\0" \
	"ramdisk_addr_r=0x82100000\0" \
	"arch=arm\0" \
	"loadaddr=0x80408000\0" \
	"bootargs=tegraid=40.0.0.00.00 vmalloc=384M video=tegrafb touch_id=0@0 board_info=0x0177:0x0000:0x02:0x43:0x00 commchip_id=0 otf_key=c75e5bb91eb3bd947560357b64422f85 modem_id=0 fbcon=map:1 console=ttyS0,115200n8 ip=off usbcore.old_scheme_first=1 usb_port_owner_info=0 lane_owner_info=6 root=/dev/ram0 rw rootwait init=/init androidboot.hardware=tegra androidboot.serialno=antmicro-aosp-dev-0001 androidboot.selinux=permissive selinux=1\0" \
	"ramdisk_file=ramdisk.img\0" \
	"bootdelay=1\0" \
	"initrd_high=0xffffffff\0" \
	"ipaddr=192.168.1.2\0" \
	"parts=uuid_disk=84d59c54-d677-45dc-a528-e0762a07171e;uuid=ea4db0cf-2577-4f90-bc63-0b7de8f57482,size=16MiB  ,name=boot       ,start=1M;uuid=096e6fc2-5393-40d9-9f36-21e69ca8ecc9,size=16MiB  ,name=recovery;uuid=a67d19f4-58b7-49f7-86ed-6e5c7635caa1,size=768MiB   ,name=system;uuid=0baa56cd-ef61-49d0-92d6-a89e46485a3a,size=0      ,name=userdata;\0" \
	"boot_img_len=0x00000800\0" \
	"boot_img_addr=0x80208000\0" \
	"boot_file=uImage\0" \
	"cpu=armv7\0"

#endif /* __CONFIG_H */
