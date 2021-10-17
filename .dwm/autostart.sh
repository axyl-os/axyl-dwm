#!/bin/env bash

# sets wallpaper using feh
bash $HOME/.dwm/.fehbg

# sets superkey
ksuperkey -e 'Super_L=Alt_L|F1' &
ksuperkey -e 'Super_R=Alt_L|F1' &

# kill if already running
killall -9 picom xfce4-power-manager ksuperkey dunst sxhkd dwmblocks

# starts dwmblocks
dwmblocks &

# start hotkey daemon
sxhkd &

# Launch notification daemon
dunst \
-geom "280x50-10+38" -frame_width "1" -font "Source Code Pro Medium 10" \
-lb "#1E222AFF" -lf "#ABB2BFFF" -lfr "#56B6C2FF" \
-nb "#1E222AFF" -nf "#ABB2BFFF" -nfr "#56B6C2FF" \
-cb "#1E222AFF" -cf "#BF616AFF" -cfr "#BF616AFF" &

# start compositor and power manager
xfce4-power-manager &
picom --config $HOME/.dwm/picom.conf &

# start polkit
if [[ ! `pidof xfce-polkit` ]]; then
    /usr/lib/xfce-polkit/xfce-polkit &
fi

# start udiskie
udiskie &
