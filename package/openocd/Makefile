#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=openocd
PKG_VERSION:=0.6.1
PKG_RELEASE:=1
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/openocd
PKG_MD5SUM:=624d0133ae67350f13e5410df05c28e8

include $(INCLUDE_DIR)/package.mk

define Package/openocd
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=OpenOCD / Open On-Chip Debugger
  URL:=http://openocd.sourceforge.net
  DEPENDS:=+libftdi +libusb
endef

define Package/openocd/description
 Free and Open On-Chip Debugging, In-System Programming and Boundary-Scan Testing
endef

CONFIGURE_ARGS+= \
	--prefix=$(STAGING_DIR)/usr \
	--enable-dummy \
	--enable-parport \
	--enable-ft2232_libftdi

TARGET_CFLAGS += -std=gnu99 \
	-I$(PKG_BUILD_DIR)/jimtcl \
	-I$(STAGING_DIR)/usr/include \
	-Wno-error=maybe-uninitialized

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
