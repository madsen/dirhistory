#---------------------------------------------------------------------
# Install dirhistory into Bash
#
# Source this in your .bashrc or .bash_profile.  I use this line:
#
#     # Load dirhistory only if line editing is enabled:
#     shopt -q -o emacs && . ~/apps/dirhistory/cd.sh
#
# You'll also need to ensure that dirhistoryd is running (see
# startd.sh) in order for the history to actually be collected.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#---------------------------------------------------------------------

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
