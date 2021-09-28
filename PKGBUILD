# Maintainer: Gabriel Matthews <axyl.os.linux.com>

pkgname=axyl-dwm
pkgver=1.0
pkgrel=1
pkgdesc="dwm configuration for Axyl OS"
arch=('x86_64')
url="https://github.com/axyl-os/axyl-dwm"
license=('MIT')
depends=('gcr' 'webkit2gtk' 'sh' 'glibc' 'coreutils' 'libx11' 'libxinerama' 'libxft')
makedepends=('git')
provides=("${pkgname}")
options=(!strip !emptydirs)

prepare() {
    cp -af ../files/. ${srcdir}
}

build() {
    cd "${srcdir}/dwm"
    make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
    local _skeldir=${pkgdir}/etc/skel
    local _dwmdir=${_skeldir}/.dwm

    # make the directories
    mkdir -p "${_skeldir}" && mkdir -p "${_dwmdir}"

    # Copies dwm configurations
    cp -r ${srcdir}/dwm-configs/*       "${_dwmdir}"
    
    # Copies dwm
    mkdir -p ${pkgdir}/opt/${pkgname}
    cp -rf ${srcdir}/dwm/* ${pkgdir}/opt/${pkgname}
}
