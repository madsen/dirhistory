# $Id$

function cd_with_history () {
  builtin cd "$@"
  local status=$?

  /home/cjm/apps/dirhistory/dirchange /dev/shm/cjm-dirs "${OLDPWD}" "${PWD}"

  return ${status}
} # end cd_with_history

function cd_menu () {
  local dest=`/home/cjm/apps/dirhistory/dirpick /dev/shm/cjm-dirs /dev/shm/cjm-dir-list`
  if [ -d "${dest}" ]; then
    cd_with_history "${dest}"
#    echo "Now in ${PWD}"
#    echo -en "\\033]0;Testing ${USER}@${HOSTNAME}:${PWD}(${dest})\\007"
  fi
} # end cd_menu

alias cd=cd_with_history

#bind -x $'"\201":cd_menu'
#bind '"\e[6;5~":'$'"\201"'

bind '"\e[5;5~":'$'"\C-E \C-A\C-Kcd_menu\n\C-Y\b"'
bind '"\e[6;5~":'$'"\C-E \C-A\C-Kcd_menu\n\C-Y\b"'
