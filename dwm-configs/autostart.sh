#!/bin/env bash

# sets wallpaper using feh
bash $HOME/.dwm/.fehbg

# kill if already running
killall -9 picom xfce4-power-manager ksuperkey dunst sxhkd dwmblocks

# sets superkey
ksuperkey -e 'Super_L=Alt_L|F1' &
ksuperkey -e 'Super_R=Alt_L|F1' &

# starts dwmblocks
dwmblocks &

# start hotkey daemon
sxhkd &

# Launch notification daemon
dunst \
-geom "280x50-10+38" -frame_width "1" -font "Source Code Pro Medium 10" \
-lb "#080F1CFF" -lf "#c7c8c8FF" -lfr "#943934FF" \
-nb "#080F1CFF" -nf "#c7c8c8FF" -nfr "#943934FF" \
-cb "#080F1CFF" -cf "#BF616AFF" -cfr "#BF616AFF" &

# start compositor and power manager
xfce4-power-manager &
picom --config $HOME/.dwm/picom.conf &

# start polkit
if [[ ! `pidof xfce-polkit` ]]; then
    /usr/lib/xfce-polkit/xfce-polkit &
fi

# start udiskie
udiskie &
