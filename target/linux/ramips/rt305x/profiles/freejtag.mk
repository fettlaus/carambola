#
# Copyright (C) 2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/FREEJTAG
	NAME:=FreeJTAG profile
	PACKAGES:=kmod-rt2800-pci openocd freejtag
endef

define Profile/FREEJTAG/Description
	Profile of FreeJTAG
endef
$(eval $(call Profile,FREEJTAG))
