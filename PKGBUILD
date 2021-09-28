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
source=("git+$url.git")
md5sums=('SKIP')

build() {
    cd "${pkgname}"
    make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
    cd "${pkgname}"

    mkdir -p ${pkgdir}/opt/${pkgname}
    mkdir -p ${pkgdir}/usr/share/xsessions/
    mkdir -p ${pkgdir}/etc/skel/
    mv dwm-configs/ ${pkgdir}/etc/skel/.dwm/
    cp -rf * ${pkgdir}/opt/${pkgname}
    make PREFIX=/usr DESTDIR="${pkgdir}" install
    install -Dm644 "${srcdir}/${pkgname}/dwm.desktop" "$pkgdir/usr/share/xsessions/dwm.desktop"
}
