# $Id$

DIRHISTORY_PWD="${PWD}"

function dirhistory_check () {
  local status=$?

  if [ "${PWD}" != "${DIRHISTORY_PWD}" ] ; then
    /home/cjm/apps/dirhistory/dirchange /dev/shm/cjm-dirs \
	"${DIRHISTORY_PWD}" "${PWD}"
    DIRHISTORY_PWD="${PWD}"
  fi

  return ${status}
} # end dirhistory_check

function cd_menu () {
  local dest=`/home/cjm/apps/dirhistory/dirpick /dev/shm/cjm-dirs /dev/shm/cjm-dir-list`
  if [ -d "${dest}" ]; then
    cd "${dest}"
#    echo "Now in ${PWD}"
#    echo -en "\\033]0;Testing ${USER}@${HOSTNAME}:${PWD}(${dest})\\007"
  fi
} # end cd_menu

#bind -x $'"\201":cd_menu'
#bind '"\e[6;5~":'$'"\201"'

# Install dirhistory_check into $PROMPT_COMMAND:
[[ "${PROMPT_COMMAND}" =~ "dirhistory_check" ]] \
 || PROMPT_COMMAND="dirhistory_check ; ${PROMPT_COMMAND}"

if [ "$TERM" == "cygwin" ] ; then
  bind '"\e[5~":'$'"\C-E \C-A\C-Kcd_menu\n\C-Y\b"'
else
  bind '"\e[5;5~":'$'"\C-E \C-A\C-Kcd_menu\n\C-Y\b"'
  bind '"\e[6;5~":'$'"\C-E \C-A\C-Kcd_menu\n\C-Y\b"'
fi
