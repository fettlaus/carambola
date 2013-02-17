#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=freejtag
PKG_VERSION:=0.0.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/freejtag
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=FreeJTAG
  DEPENDS:=+boost-program_options +boost-thread +boost-system +boost-date_time +boost-chrono +io
endef

define Package/freejtag/description
 Free and Open On-Chip Debugging, In-System Programming and Boundary-Scan Testing
endef

define Package/freejtag/conffiles
/etc/openocd.cfg
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
	$(call Build/Configure/Default)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/freejtag/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/freejtag $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/bin
	ln -sf ../sbin/freejtag $(1)/usr/bin/freejtag
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DATA) ./files/openocd.cfg $(1)/etc/openocd.cfg
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/conf/freejtag.cfg $(1)/etc/freejtag.cfg
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_BIN) ./files/freejtag.uci-defaults $(1)/etc/uci-defaults/XX_freejtag
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/openocd.init $(1)/etc/init.d/openocd
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/conf/freejtag $(1)/etc/init.d/freejtag

	
endef

$(eval $(call BuildPackage,freejtag))
