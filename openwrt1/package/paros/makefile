include $(TOPDIR)/rules.mk

PKG_NAME:=paros
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/kernel.mk

define KernelPackage/paros
  SUBMENU:=Other modules
  TITLE:=paros
  FILES:=$(PKG_BUILD_DIR)/paros.ko
  AUTOLOAD:=$(call AutoLoad,99,paros)
endef

define KernelPackage/paros/description
  paros
endef

$(eval $(call KernelPackage,paros))
