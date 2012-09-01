#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=openocd
PKG_VERSION:=0.6.0-rc2
PKG_RELEASE:=1
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/openocd
PKG_MD5SUM:=a2c809b1f94be2d6f93980c564038994

include $(INCLUDE_DIR)/package.mk

define Package/openocd
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=OpenOCD / Open On-Chip Debugger
  URL:=http://openocd.sourceforge.net
  DEPENDS:=+kmod-usb-serial +kmod-usb-serial-ftdi
endef

define Package/openocd/description
 Free and Open On-Chip Debugging, In-System Programming and Boundary-Scan Testing
endef

CONFIGURE_ARGS+= \
	--enable-dummy \
	--enable-buspirate

TARGET_CFLAGS += -std=gnu99 -Wall -I$(PKG_BUILD_DIR)/jimtcl

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) CFLAGS="$(TARGET_CFLAGS) -I$(LINUX_DIR)/include"
endef

define Package/openocd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/openocd $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/bin
	ln -sf ../sbin/openocd $(1)/usr/bin/openocd	
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/src/libopenocd.la $(1)/usr/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/src/.libs/libopenocd.a $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/share/openocd/scripts
	$(CP) $(PKG_BUILD_DIR)/tcl/* $(1)/usr/share/openocd/scripts/
	$(INSTALL_DIR) $(1)/usr/share/openocd/contrib
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/contrib/openocd.udev $(1)/usr/share/openocd/contrib
	
endef

$(eval $(call BuildPackage,openocd))
