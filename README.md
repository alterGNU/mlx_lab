# mlx_lab: Minilibx laboratory

## Install minilibx on linux

```bash
git clone https://github.com/alterGNU/mlx_lab.git && cd mlx_lab && ./install_mlx.sh
```
- step 0: Check and install this script's dependancies (yes command)
- step 1: Update and Upgrade the system (good practice before any installation)
- step 2: Check and install mlx's dependancies (PACK_LIST var. , check minilibx README to update list)
- step 3: Clone and Make minilibx (MLX_PATH var. can be change to modify path and mlx folder's name)
- step 4: Create a tmp_env_file, sourcing this file will add mlx's doc to man cmd (using MANPATH env-var)
