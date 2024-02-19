#!/bin/sh

setxkbmap fr
mons -e right
picom -b &
# xwallpaper --zoom /home/quentin/walls/dracula/arch.png &
random_wall
xrdb /home/quentin/.Xresources
/usr/bin/prime-offload
sleep 0.5 && dwm-suscribe > /tmp/dwm.log &
sleep 0.5 && eww open-many bar:s1 bar:s0 --arg s0:screen=0 --arg s1:screen=1 &

exec dwm >> /home/$USER/.logs/dwm/$(date +%Y-%m-%d_%H.dwm.log) 2>&1
