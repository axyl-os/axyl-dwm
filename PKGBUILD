# Maintainer: Gabriel Matthews <axyl.os.linux.com>

pkgname=axyl-dwm
pkgver=6.2
pkgrel=1
pkgdesc="dwm configuration for Axyl OS"
arch=('x86_64')
url="https://github.com/axyl-os/axyl-dwm"
license=('MIT')
depends=(gcr webkit2gtk sh glibc coreutils libx11 libxinerama libxft freetype2 axyl-fonts)
makedepends=(git make)
conflicts=(dwm)
provides=("${pkgname}")
options=(!strip !emptydirs)
source=(${pkgname}::"git+$url.git")
md5sums=('SKIP')

build() {
    cd "${pkgname}"
    make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
    cd "${pkgname}"

    local _skeldir=${pkgdir}/etc/skel
    local _dwmdir=${_skeldir}/.dwm

    # make the directories
    mkdir -p "${_skeldir}" && mkdir -p "${_dwmdir}"

    # Copies dwm.desktop xsession entry
    mkdir -p ${pkgdir}/usr/share/xsessions
    install -Dm644 ${srcdir}/dwm.desktop         "${pkgdir}/usr/share/xsessions/"

    # Moves dwm configurations
    mv ${srcdir}/dwm-configs/*       "${_dwmdir}"
    
    # Copies dwm
    mkdir -p ${pkgdir}/opt/${pkgname}
    cp -rf ${srcdir}/* ${pkgdir}/opt/${pkgname}
    make PREFIX=/usr DESTDIR="${pkgdir}" install    
}
