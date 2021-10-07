#!/bin/env bash

# sets superkey
ksuperkey -e 'Super_L=Alt_L|F1' &
ksuperkey -e 'Super_R=Alt_L|F1' &

# sets wallpaper using feh
bash $HOME/.dwm/.fehbg

# starts dwmblocks
dwmblocks &

# kill if already running
killall -9 picom xfce4-power-manager ksuperkey dunst sxhkd

# start hotkey daemon
sxhkd &

# Launch notification daemon
dunst \
-geom "280x50-10+38" -frame_width "1" -font "Source Code Pro Medium 10" \
-lb "#080F1CFF" -lf "#c7c8c8FF" -lfr "#943934FF" \
-nb "#080F1CFF" -nf "#c7c8c8FF" -nfr "#943934FF" \
-cb "#2E3440FF" -cf "#BF616AFF" -cfr "#BF616AFF" &

# start compositor and power manager
xfce4-power-manager &
picom --config $HOME/.dwm/picom.conf &

# start polkit
if [[ ! `pidof xfce-polkit` ]]; then
    /usr/lib/xfce-polkit/xfce-polkit &
fi

# start udiskie
udiskie &
