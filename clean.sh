#!/usr/bin/env bash

# ============================================================================================================
# Clean mlx_lab folder
#
# - step 1: Remove scripts generated files (`env_file` and `*.log` files)
# - step 2: Remove sub-folders in list `SUB_FOLDERS_TO_DEL=( "mlx" )`
#
#                                                                                                 by alterGNU
# ============================================================================================================

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
Y="\033[0;93m"
# -[ max line size ]------------------------------------------------------------------------------------------
LEN=80
# -[ separator symbole ]--------------------------------------------------------------------------------------
SEP="."
# -[ Script absolute path ]-----------------------------------------------------------------------------------
PARENT_DIR=$(cd $(dirname ${0}) && pwd)
# -[ tmp file created to be source ]--------------------------------------------------------------------------
env_file=${PARENT_DIR}/env_file
# -[ sub-folder to delete ]-----------------------------------------------------------------------------------
SUB_FOLDERS_TO_DEL=( "mlx" )

# ============================================================================================================
# UTILITY FUNCTIONS
# ============================================================================================================
# -[ GET_LEN ]------------------------------------------------------------------------------------------------
# return real len, handle emoticon that need space after to avoid overlapping display in terminal
get_len()
{
    local str=${1}
    local LIST_EMOTIC_DOUBLE_OCT=( "☑️" "⚙️" "⚠️" "✖️" )
    local clean_str=$(echo -en "${str}" | sed 's/\x1b\[[0-9;]*m//g')
    for emo in "${LIST_EMOTIC_DOUBLE_OCT[@]}"; do clean_str="${clean_str//${emo} /${emo}}"; done
    local nb_emo=$(echo -n "${clean_str}" | perl -CSD -lne 'print scalar(() = /\p{Extended_Pictographic}/g)')
    clean_str=$(echo -n "${clean_str}" | perl -CSD -pe 's/\p{Extended_Pictographic}//g')
    local count=$(echo -n "${clean_str}" | perl -CSD -lne 'print scalar(() = /\X/g)')
    echo $(( count + nb_emo + nb_emo ))
}
# -[ PRINT N TIMES ]------------------------------------------------------------------------------------------
# print $arg1 $arg2 times
pnt() { for i in $(seq 0 $((${2})));do echo -en ${1};done ; }
# -[ print title one(step name) ]-----------------------------------------------------------------------------
title_1(){ echo -en "\n${HG}${B}${@}${E}\n" ; }
# -[ print title two(step name) ]-----------------------------------------------------------------------------
title_2(){ echo -en "${@}" ; }

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ Remove scripts generated files ]=========================================================================
title_1 "1  | Remove scripts generated files:"
title_2 "1.1| rm env_file:"
if [[ -f ${env_file} ]];then
    pnt "${SEP}" $((LEN - 20))
	rm -rf ${env_file} && echo -e " ✅" || echo -e " ❌"
else
    pnt "${SEP}" $((LEN - 33))
    echo -e ${G}"(no env_file) ✖️ "${E}
fi
title_2 "1.2| rm log files:"
log_files=( *.log )
if [[ "${log_files[0]}" == "*.log" ]];then
    pnt "${SEP}" $((LEN - 35))
    echo -e ${G}"(no log files) ✖️ "${E}
else
    echo -e ""
    for log_file in "${log_files[@]}";do
        txt_log_file="   ⤷ rm ${log_file}"
        len_log_file=$(get_len "${txt_log_file}")
        echo -en "${txt_log_file}" && pnt "${SEP}" $((LEN - len_log_file - 3))
        rm -rf ${log_file} && echo -e " ✅" || echo -e " ❌"
    done
fi

# =[ Remove sub-folders ]=====================================================================================
title_1 "2  | Remove sub-folders:"
for sub_fold in "${SUB_FOLDERS_TO_DEL[@]}";do
    txt_sub_fold="1.2| rm sub-fold '${sub_fold}':"
    len_sub_fold=$(get_len "${txt_sub_fold}")
    echo -en "${txt_sub_fold}"
    if [[ -d "${sub_fold}" ]];then
        pnt "${SEP}" $((LEN - len_sub_fold - 3))
        rm -rf ${sub_fold} && echo -e " ✅" || echo -e " ❌"
    else
        pnt "${SEP}" $((LEN - len_sub_fold - 14))
        echo -e ${G}"(not found) ✖️ "${E}
    fi
done

