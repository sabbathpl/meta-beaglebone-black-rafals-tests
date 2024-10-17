SUMMARY = "Rafal's test minimal image"

IMAGE_INSTALL = "\
    packagegroup-core-boot \
    packagegroup-core-full-cmdline \
    ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image
# inherit extrausers

# Set rootfs to 100 MiB by default
IMAGE_OVERHEAD_FACTOR ?= "1.0"
IMAGE_ROOTFS_SIZE ?= "102400"
IMAGE_ROOTFS_EXTRA_SPACE:append = "${@bb.utils.contains("DISTRO_FEATURES", "systemd", " + 4096", "", d)}"


IMAGE_INSTALL:append = " libgpiod libgpiod-dev libgpiod-tools"
IMAGE_INSTALL:append = " rafal-i2c"
IMAGE_INSTALL:append = " rafal-oled"
# IMAGE_INSTALL:append = " led-display-lib"

# To add static lib to ...(created image?)
# TOOLCHAIN_TARGET_TASK:append = " led-display-lib-staticdev"

# Enable SSH connection and SCP feature
CORE_IMAGE_BASE_INSTALL:append = "\
    openssh \
    openssh-sftp \
    openssh-sftp-server"

# (Probably) Another method to enable SSH
# IMAGE_FEATURES:append = " ssh-server-dropbear"

# EXTRA_USERS_PARAMS = "\
#     usermod -p '\$1\$lI.jNNnj$ga9VEs76BrIOuFM45PoOn0' root; \
#     useradd -p '' tester; \
#     "
