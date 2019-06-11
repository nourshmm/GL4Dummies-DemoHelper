#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void assimpInit(const char * filename);
  extern void assimpDrawScene(void);
  extern void assimpQuit(void);

  extern void assimpInit1(const char * filename);
  extern void assimpDrawScene1(void);
  extern void assimpQuit1(void);

  extern void assimpInit2(const char * filename);
  extern void assimpDrawScene2(void);
  extern void assimpQuit2(void);

  extern void assimpInit3(const char * filename);
  extern void assimpDrawScene3(void);
  extern void assimpQuit3(void);

  extern void assimpInit4(const char * filename);
  extern void assimpDrawScene4(void);
  extern void assimpQuit4(void);

  extern void initNoiseTextures(void);
  extern void useNoiseTextures(GLuint pid, int shift);
  extern void unuseNoiseTextures(int shift);
  extern void freeNoiseTextures(void);


  extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void animation_flash(int state);
  extern void animation_vide(int state);
  extern void animation_damier(int state);
  extern void animation_base(int state);
  extern void animation_earth(int state);
  extern void animationsInit(void);
  extern void animation_laby(int state);
  extern void animation_Arrte(int state);
  extern void animation_nature(int state);
  /* Dans base.c */
  extern void initDataL2(void);
  extern void drawLaby2(void);
  extern void idle2(void);
  
  /*Dans char*/
  extern void initNature1(void);
  extern void drawNature1(void);
  extern void idleNature1(void);
  // extern void earth_init(void);
  // extern void earth_draw(void);


  extern void initDataL(void);
  extern void drawLaby(void);
  extern void idle(void);




  extern void credits2(int state);
#ifdef __cplusplus
}
#endif

#endif
