#!/bin/sh

# setup home directory
sh /usr/share/dwm/scripts/install-home.sh

# setup monitors
sh /home/$USER/.dwm/monitors.sh &

# setup autostart applications
sleep 3 && sh /home/$USER/.dwm/autostart.sh &

# running dwm
while type dwm >> /dev/null; do dwm && continue || break; done
