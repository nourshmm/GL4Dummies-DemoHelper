#version 330
uniform sampler2D tex0;
in  vec2 vsoTexCoord;
out vec4 fragColor;

void main(void) {
  vec4 c = texture(tex0, vsoTexCoord);
  fragColor = vec4(c.rgb, length(c.rgb) > 0.0 ? 1.0 : 0.0);
}
