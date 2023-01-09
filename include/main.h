#ifndef _MAIN_H
#define _MAIN_H

#include <stdbool.h>

#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include "glextloader.h"
#include "helpers.h"

// Shader paths
#define VERTEX_FILE_PATH "shaders/quad.vert"
#define VORONOI_FRAGMENT_FILE_PATH "shaders/voronoi.frag"
#define ATOMS_FRAGMENT_FILE_PATH "shaders/atoms.frag"
#define BUBBLES_FRAGMENT_FILE_PATH "shaders/bubbles.frag"

// Macros
#define UNREACHABLE(message)                                                      \
    do {                                                                          \
        fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, message); \
        exit(1);                                                                  \
    } while (0)

// Constants
// ---------------------
// Window properties
#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_SCREEN_HEIGHT 1080
#define MANUAL_TIME_STEP 0.05

// Seed properties
#define DEFAULT_SEED_COUNT 20
#define DEFAULT_SEED_RADIUS 15

#define SEED_MAX_COUNT 500
#define SEED_MIN_RADIUS 5
#define SEED_MAX_RADIUS 150

// Simulation properties
#define SUB_STEPS 8

typedef enum {
    VORONOI_FRAGMENT = 0,
    ATOMS_FRAGMENT,
    BUBBLES_FRAGMENT,
    COUNT_FRAGMENTS
} Fragment;

typedef enum {
    GENERAL_VERTEX = 0,
    COUNT_VERTICES
} Vertex;

typedef enum {
    ATTRIB_POS = 0,
    ATTRIB_COLOR,
    ATTRIB_RADIUS,
    COUNT_ATTRIBS,
} Attrib;

typedef enum {
    MODE_VORONOI = 0,
    MODE_ATOMS,
    MODE_BUBBLES,
    COUNT_MODES
} Mode;

typedef enum {
    RESOLUTION_UNIFORM = 0,
    COUNT_UNIFORMS
} Uniform;

extern const char* uniform_names[COUNT_UNIFORMS];
extern const char* mode_names[COUNT_MODES];
extern const char* vertex_files[COUNT_VERTICES];
extern const char* fragment_files[COUNT_FRAGMENTS];

extern vec2* seed_positions;
extern vec2* seed_velocities;
extern vec4* seed_colors;
extern GLint* seed_mark_radii;

extern int SEED_RADIUS;
extern size_t SEED_COUNT;

extern Mode SIM_MODE;
extern double DELTA_TIME;
extern bool IS_PAUSE;
extern bool IS_RUNNING;
extern bool IS_DRAG_MODE;

extern GLint uniforms[COUNT_UNIFORMS];
extern GLuint vbos[COUNT_ATTRIBS];

extern void (*render_frame)(GLFWwindow*, double, int, int);

// Function declarations
// ---------------------
void render_loop(GLFWwindow* window);
void init_sim_mode(Mode mode);
void free_sim_mode();

void init_glfw_settings();
GLFWwindow* init_glfw_window();
void init_glfw_callbacks(GLFWwindow* window);
void init_gl_settings();
void init_gl_uniforms(GLuint program);
void init_shaders(GLuint* program, const char* vert_file_path, const char* frag_file_path);
void update_gl_uniforms(int width, int height);

#endif  // MAIN_H