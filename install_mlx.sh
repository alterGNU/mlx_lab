#!/bin/bash -e

# ============================================================================================================
# Script to install minilibx on linux
#
# - step 0: Check and install this script's dependancies (yes command)
# - step 1: Update and Upgrade the system (good practice before any installation)
# - step 2: Check and install mlx's dependancies (PACK_LIST var. , check minilibx README to update list)
# - step 3: Clone and Make minilibx (MLX_PATH var. can be change to modify path and mlx folder's name)
# - step 4: Create a tmp_env_file, sourcing this file will add mlx's doc to man cmd (using MANPATH env-var)
#
#                                                                                                 by alterGNU
# ============================================================================================================

# ============================================================================================================
# VARIABLES
# ============================================================================================================
 
# -[ List of MLX's dependancies to installed ]----------------------------------------------------------------
PACK_LIST=("git" "gcc" "clang" "make" "xorg" "libbsd-dev" "libx11-dev" "libxext-dev")

# -[ URL to minilibx-linux's github repo ]--------------------------------------------------------------------
MLX_URL="https://github.com/42paris/minilibx-linux.git"

# -[ Minilibx folders path (and name) ]-----------------------------------------------------------------------
MLX_PATH=${PWD}"/mlx"

# -[ COLOR BALISE ]-------------------------------------------------------------------------------------------
E="\033[0m"
B="\033[1;36m"
R="\033[1;31m"
HG="\033[0;47m"
G="\033[0m\033[2;37m"
V="\033[2;32m"
UB="\033[4;36m"
M="\033[1;33m"
UG="\033[4;37m"

# -[ Script absolute path ]-----------------------------------------------------------------------------------
SCRIPT_ABS_PATH=$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)

# -[ tmp file created to be source ]--------------------------------------------------------------------------
tmp_env_file=${SCRIPT_ABS_PATH}/tmp_env_file

# ============================================================================================================
# UTILITY FUNCTIONS
# ============================================================================================================
 
# -[ print title one(step name) ]-----------------------------------------------------------------------------
title_1(){ echo -e "\n${HG}${B}${@}${E}" ; }
# -[ print title two(step name) ]-----------------------------------------------------------------------------
title_2(){ echo -en "${UB}${@}${E}" ; }
# -[ Check if a command exist ]-------------------------------------------------------------------------------
cmd_exist(){ command -v "${1}" > /dev/null 2>&1 ; }
# -[ Check if command:${1} is installed, else install the corresponding package:${2} ]------------------------
install_cmd()
{
    local cmd_name=${1}
    local pck_name=${1}
    [[ ${#} -eq 2 ]] && local pck_name=${2}
    if cmd_exist "${cmd_name}";then
        echo -e "❎ command ${V}${cmd_name}${E} in package ${B}${pck_name} ${G}(already installed)"${E}
    else
        sudo apt-get install -y ${pck_name} \
            && echo -e "✅ cmd ${V}${cmd_name}${E} in pck ${B}${pck_name}${E} ${V}successfully installed.${E}" \
            || echo -e "❌ cmd ${V}${cmd_name}${E} in pck ${B}${pck_name}${E} ${R}Failed to install.${E}"
    fi
}

# -[ Check if a package was installed ]-----------------------------------------------------------------------
pck_installed(){ dpkg-query -W -f='${Status}' "${1}" 2>/dev/null | grep -q "install ok installed" ; }
# -[ Check if a package is installed, else install it ]-------------------------------------------------------
install_pck()
{
    if pck_installed "${1}";then
        echo -e "❎ package ${B}${1} ${G}(already installed)"${E}
    else
        sudo apt-get install -y ${1} \
            && echo -e "✅ package ${B}${pck_name}${E} ${V}successfully installed.${E}" \
            || echo -e "❌ package ${B}${pck_name}${E} ${R}Failed to install.${E}"
    fi
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ 0 | Check 'yes' is installed ]===========================================================================
title_1 "0  |" Check script dependancies:
install_cmd yes coreutils

# =[ 1 | Update system ]======================================================================================
title_1 "1  |" Update System:
title_2 "1.1| Update:\n" && yes | sudo apt-get update 
title_2 "1.2| Upgrade:\n" && yes | sudo apt-get upgrade
title_2 "1.3| Autoremove:\n" && yes | sudo apt-get autoremove

# =[ 2 | Install MLX's dependancies packages: ]===============================================================
title_1 "2  |" Check Minilibx dependancies:
for pkg in ${PACK_LIST[@]};do install_pck ${pkg};done

# =[ 3 | Git clone and Make minilibx if mlx folder not at $PWD ]==============================================
title_1 "3  |" Clone and Make minilibx:
title_2 "3.1| Git clone:"
[[ ! -d ${MLX_PATH} ]] && git clone ${MLX_URL} ${MLX_PATH} || echo -e "${G}(Already cloned)"${E}
title_2 "3.2| Make mlx:\n"
if [ -d ${MLX_PATH} ];then cd ./mlx && ./configure;fi

# =[ 4 | Add mlx's doc to man command ]=======================================================================
title_1 "4  | Add mlx's doc to man command (temporarly)"
title_2 "4.1| Create tmp file :\n"
echo "export MANPATH=\"${MLX_PATH}/man:\$MANPATH\"" > ${tmp_env_file}
echo -e "To add mlx's man to your MANPATH, do:${R} \`${UG}source ${tmp_env_file}${E}${R}\`${E}\nThen to test, do:${R} \`${UG}man mlx${E}${R}\`${E}"
title_2 "4.2| Permanently add mlx's man:\n"
echo -e "This changes are temporary. To make them permanent, add these line:\n '${M}export MANPATH=\"${MLX_PATH}/man:\$MANPATH\"${E}'\ninto a startup dotfile (e.g. .zshrc, .bashrc, .profile) (then manually source this dotfile once, or just restart the session)"
