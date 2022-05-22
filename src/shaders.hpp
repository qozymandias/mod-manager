
namespace shaders {
    // NOLINTNEXTLINE
    float points[] = {0.0F, 0.5F, 0.0F, 0.5F, -0.5F, 0.0F, -0.5F, -0.5F, 0.0F};
    auto const n_points = 9;

    // NOLINTNEXTLINE
    const char* vertex_shader = "#version 400\n"
                                "in vec3 vp;"
                                "void main() {"
                                "  gl_Position = vec4(vp, 1.0);"
                                "}";

    // NOLINTNEXTLINE
    const char* fragment_shader = "#version 400\n"
                                  "out vec4 frag_colour;"
                                  "void main() {"
                                  "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
                                  "}";

} // namespace shaders
