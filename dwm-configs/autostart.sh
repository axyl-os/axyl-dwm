#!/bin/env bash

# sets wallpaper using feh
bash $HOME/.dwm/.fehbg

# starts dwmblocks
dwmblocks &

# kill if already running
killall -9 picom xfce4-power-manager dunst

# Launch notification daemon
dunst \
-geom "280x50-10+38" -frame_width "1" -font "Source Code Pro Medium 10" \
-lb "#0b0d0aFF" -lf "#d2e9f0FF" -lfr "#9D9a5DFF" \
-nb "#0b0d0aFF" -nf "#d2e9f0FF" -nfr "#9D9a5DFF" \
-cb "#2E3440FF" -cf "#BF616AFF" -cfr "#BF616AFF" &

# start compositor and power manager
xfce4-power-manager &
picom --config $HOME/.config/picom.conf &

# start polkit
if [[ ! `pidof xfce-polkit` ]]; then
    /usr/lib/xfce-polkit/xfce-polkit &
fi

# start mpd
exec mpd &

# start udiskie
udiskie &
