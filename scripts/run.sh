#!/bin/sh

# setup home directory
setup_home_dirs(){
  exec sh /usr/share/dwm/scripts/install-home.sh
}

# compositor
picom &

# setup monitors
sh /home/$USER/.dwm/monitors.sh || setup_home_dirs && break &

# setup keyboard layouts
sh /home/$USER/.dwm/keylayouts.sh || setup_home_dirs && break &

#setup autostart applications
sleep 4 && sh /home/$USER/.dwm/autostart.sh || setup_home_dirs && break &

# dynamic change background
nitrogen --restore &

# running dwm
while type dwm >> /dev/null; do dwm && continue || break; done
