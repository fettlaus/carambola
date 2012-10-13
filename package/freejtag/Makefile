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

define Package/freejtag
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=FreeJTAG
  DEPENDS:=+glib2
endef

define Package/freejtag/description
 Free and Open On-Chip Debugging, In-System Programming and Boundary-Scan Testing
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
endef

define Package/freejtag/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/freejtag $(1)/bin/
endef

$(eval $(call BuildPackage,freejtag))
