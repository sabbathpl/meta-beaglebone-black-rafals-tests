DESCRIPTION = "PI4IOE5V64XX Library for Linux"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://src"

S = "${WORKDIR}/src"

inherit autotools
inherit logging

DEPENDS = ""

do_compile:append() {
    bbwarn "Debug message: Compiling PI4IOE5V64XX library"
}

# Prevent race condition in parallel make
PARALLEL_MAKE = ""
