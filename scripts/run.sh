#!/bin/sh

# compositor
picom &

# setup home directory
sh /usr/share/dwm/scripts/install-home.sh

# setup monitors
sh /home/$USER/.dwm/monitors.sh &

# setup keyboard layouts
sh /home/$USER/.dwm/keylayouts.sh &

#setup autostart applications
sleep 4 && sh /home/$USER/.dwm/autostart.sh &

# dynamic change background
nitrogen --restore &

# running dwm
while type dwm >> /dev/null; do dwm && continue || break; done
