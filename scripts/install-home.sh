#!/bin/sh

declare username="${username:-$USER}"
declare home="${home:-/home/$username}"


if [ ! -d $home/.dwm ];then
  mkdir $home/.dwm
fi

declare dwm="${dwm:-$home/.dwm}"

if [ ! -f $dwm/monitors.sh ];then
  touch $dwm/monitors.sh
  chmod +x $dwm/monitors.sh
fi

if [ ! -f $dwm/autostart.sh ];then
  touch $dwm/autostart.sh
  chmod +x $dwm/autostart.sh
fi

if [ ! -f $dwm/keylayouts.sh ];then
  touch $dwm/keylayouts.sh
  chmod +x $dwm/keylayouts.sh
fi
