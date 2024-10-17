DESCRIPTION = "Simple C application to read/write i2c device registers"
SUMMARY = "Rafal's test application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Where to find source files (can be local, GitHub, etc.)
SRC_URI = "file://src"

# Where to keep downloaded source files (in tmp/work/...)
S = "${WORKDIR}/src"

# Pass arguments to linker
TARGET_CC_ARCH += "${LDFLAGS}"

# Cross-compile source code
do_compile() {
    ${CC} -o rafal-i2c main.c
}

# Create /usr/bin in rootfs and copy program to it
do_install() {
    install -d ${D}${bindir}
    install -m 0755 rafal-i2c ${D}${bindir}
}