# mlx_lab: Quick Reference Guide

## What is mlx_lab?
A comprehensive tutorial and laboratory for learning the **MiniLibX** graphics library on Linux. Covers everything from basic setup to advanced optimization techniques with practical examples and performance benchmarks.

---

## Quick Start

### Installation
```bash
git clone https://github.com/alterGNU/mlx_lab.git && cd mlx_lab && ./install_mlx.sh
```
The script installs dependencies, clones minilibx, compiles it, and sets up documentation.

### Basic Compilation Pattern
```bash
cc -Wall -Wextra -Werror -Imlx your_file.c mlx/libmlx.a -o your_binary -lXext -lX11 -lm
```

---

## Core Concepts

### 1. MLX Initialization (The Trinity)
```c
void *mlx_ptr = mlx_init();                              // Display connection
void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Hi"); // Window
void *img_ptr = mlx_new_image(mlx_ptr, 800, 600);        // Image buffer
```

**Critical**: Always check return values (NULL = failure). Destroy in reverse order.

### 2. Event Loop
```c
mlx_loop(mlx_ptr);  // Infinite loop, handles events
```
Exit cleanly with `mlx_loop_end(mlx_ptr)` or by destroying all windows.

### 3. Image Buffer Architecture
**DON'T**: Use `mlx_pixel_put()` directly on window (slow, causes tearing)  
**DO**: Draw to image buffer → push to window once per frame

```c
char *addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
// Calculate pixel position:
int pixel_offset = (y * size_line) + (x * bpp/8);
*(int*)(addr + pixel_offset) = 0x00RRGGBB;
mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
```

---

## Key Technical Details

### Image Memory Layout
- **BPP** (bits per pixel): Usually 32 (24 for RGB + 8 unused/alpha)
- **Line length** ≠ width × BPP due to **padding** (alignment to 4-byte boundaries)
- **Endianness**: Little-endian on x86 (BB GG RR TT in memory for 0xTTRRGGBB)

### Color Encoding
```c
int color = (r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF);  // Safe masking
```

### Event Hooks
```c
mlx_hook(win_ptr, event_id, mask, function, param);  // Generic
mlx_key_hook(win_ptr, func, param);                  // Key release
mlx_loop_hook(mlx_ptr, func, param);                 // Every frame (no event)
```

---

## Progressive Projects Overview

### Level 1: Static Display (Sections C-D)
- Basic window creation and image display
- Understanding MLX initialization lifecycle
- **Problem**: No event handling → must kill with Ctrl+C

### Level 2: Interactive + Clean Exit (Section E)
- Keyboard/mouse event handling
- Two exit patterns:
  - `mlx_loop_end()` in hook → clean up in main after loop
  - Flag-based `mlx_destroy_window()` in `mlx_loop_hook()` (safer)

### Level 3: Efficient Drawing (Section F)
- **Slow**: `mlx_pixel_put()` per pixel directly to window
- **Fast**: Buffer entire frame in image → single `mlx_put_image_to_window()`
- **Result**: 100× speed improvement for complex scenes

### Level 4: File Formats (Section G)
- XPM file loading with `mlx_xpm_file_to_image()`
- Building grid-based mazes from XPM tiles
- **Problem**: Fixed tile sizes, inflexible

### Level 5: Real Game Loop (Section H.1-H.2)
**H.1**: Grid-based player movement with Bresenham circle rendering
- **Problem**: Busy-spin loop → 30k allocs/second when idle

**H.2**: FPS limiter implementation
- Target: 60 FPS using `gettimeofday()` busy-wait
- **Result**: Stable ~1000 allocs per second at 60 FPS

### Level 6: Performance Optimization (Section H.3)
**Problem**: Copying entire grid buffer every frame = 10-65ms → bottleneck

**Solution**: Benchmark different memory copy strategies:

| Method | Implementation | Time/Frame | FPS | Speed vs Bit-by-Bit |
|--------|---------------|------------|-----|---------------------|
| **Bit-by-bit** | `while` loop byte-by-byte | ~65ms | ~20 | 1× (baseline) |
| **4-byte chunks** | `int*` copying + remainder | ~25ms | ~60 | 2.6× faster |
| **8-byte chunks** | `size_t*` copying + remainder | ~20ms | ~60 | 3.25× faster |
| **memcpy()** | Standard library (SIMD) | ~10ms | ~60 | **6.5× faster** |

**Key Finding**: Standard `memcpy()` uses CPU vectorized instructions (SSE/AVX) to copy 16-64 bytes per instruction vs. 1 byte for manual loops.

**For 42 Projects** (no `memcpy()` allowed): Use 8-byte word copying as best manual implementation.

---

## Performance Best Practices

### ✅ DO
- Use image buffers, never `mlx_pixel_put()` in loops
- Implement FPS limiting (prevents wasted CPU)
- Copy memory in largest chunks possible (words > bytes > bits)
- Use `memcpy()` when allowed (6× faster than manual)
- Validate all MLX function returns
- Destroy resources in reverse creation order

### ❌ DON'T
- Draw pixel-by-pixel directly to window
- Call `mlx_destroy_window()` inside `mlx_hook()` callback (use-after-free risk)
- Forget padding when calculating pixel positions
- Assume `size_line == width * (bpp/8)` (wrong due to padding)
- Use busy-spin without FPS limit (wastes CPU)
- Copy full frames when only small regions changed

### Next-Level Optimizations (Not Implemented in Lab)
1. **Dirty Rectangles**: Only redraw changed regions (16× faster than full copy)
2. **Multi-layer Compositing**: Multiple `mlx_put_image_to_window()` calls instead of merging
3. **Double Buffering**: Swap between two complete buffers (no rebuild needed)

---

## Valgrind Tips
```bash
valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all \
         --undef-value-errors=no ./your_binary
```
**Note**: `--undef-value-errors=no` suppresses false positives from `mlx_new_window()`.

---

## Common Pitfalls

1. **Memory Leaks from Early Exit**
   - Solution: Hook window close (`event_id=17`) and ESC key
   
2. **Tearing/Flickering**
   - Solution: Draw complete frame to buffer before pushing to window

3. **Performance Degradation**
   - Cause: Full-frame copies every loop
   - Solution: Only update changed regions or limit FPS

4. **Segfaults in Event Handlers**
   - Cause: Destroying window during event processing
   - Solution: Set flag in `mlx_hook()`, destroy in `mlx_loop_hook()`

---

## Project Structure Patterns

### Recommended Struct Organization
```c
typedef struct s_img {
    void *img_ptr;
    char *addr;
    int  width, height;
    int  bpp, size_line, endian;
} t_img;

typedef struct s_data {
    void   *mlx_ptr;
    void   *win_ptr;
    t_img  buffer;
    // Game state...
} t_data;
```

### Typical Main Pattern
```c
int main(void) {
    t_data dt = init_data();
    if (check_errors(&dt)) return (cleanup(&dt), 1);
    
    mlx_hook(dt.win_ptr, 17, 0, &handle_close, &dt);      // [X] button
    mlx_hook(dt.win_ptr, 2, 1L<<0, &handle_key, &dt);     // Key press
    mlx_loop_hook(dt.mlx_ptr, &draw_frame, &dt);          // Render loop
    
    mlx_loop(dt.mlx_ptr);
    cleanup(&dt);
    return (0);
}
```

---

## Key Takeaways

1. **MiniLibX is a thin wrapper** around X11—understanding memory layout is critical
2. **Performance = minimizing work per frame**: buffer, batch, limit FPS
3. **Standard library functions are heavily optimized**—reinventing wheels is educational but slower
4. **Event-driven architecture is cleaner** than polling for responsive applications
5. **Memory alignment matters**—always use `size_line`, never assume it equals `width * bpp/8`

---

## References

- [Official MLX Man Pages](https://harm-smits.github.io/42docs/libs/minilibx) (via `man mlx` after sourcing `env_file`)
- [X11 Event Documentation](https://tronche.com/gui/x/xlib/events/)
- Full examples: `mlx_lab/src/` (c, d, e, f, g, h1-h3 subdirectories)

---

**Last Updated**: Based on README.md analysis (January 2026)  
**Target Audience**: 42 School students working on graphical projects (so_long, cub3D, etc.)
