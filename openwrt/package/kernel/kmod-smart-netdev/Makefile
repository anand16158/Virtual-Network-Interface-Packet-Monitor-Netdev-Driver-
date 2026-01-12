include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=smart-netdev
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/smart-netdev
  SUBMENU:=Network Support
  TITLE:=Smart Virtual Network Interface
  FILES:=$(PKG_BUILD_DIR)/smart_netdev.ko
  AUTOLOAD:=$(call AutoLoad,70,smart_netdev)
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

$(eval $(call KernelPackage,smart-netdev))
