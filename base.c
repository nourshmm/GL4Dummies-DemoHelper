#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>


extern void assimpInit3(const char * filename);
extern void assimpDrawScene3(void);
extern void assimpQuit3(void);

 void resize2(int w, int h);


/* from makeLabyrinth.c */
extern unsigned int * labyrinth(int w, int h);

/*!\brief opened window width and height */
static int _wW = 1250, _wH = 750;
/*!\brief mouse position (modified by pmotion function) */
// static int _xm = 600, _ym = 300;
/*!\brief labyrinth to generate */
static GLuint * _labyrinth = NULL;
/*!\brief labyrinth side */
static GLuint _lab_side = 15;
/*!\brief Quad geometry Id  */
static GLuint _plane = 0;
/*!\brief Cube geometry Id  */
static GLuint _cube = 0;
/*!\brief GLSL program Id */
static GLuint _pId = 0;
static GLuint _pId2 = 0;
/*!\brief plane texture Id */
static GLuint _planeTexId = 0;
static GLuint Tex = 0;
static GLuint Tex1 = 0;
static GLuint TexS2 = 0;
static GLuint _sphere = 0;

/*!\brief compass texture Id */
static GLuint _compassTexId = 0;

/*!\brief plane scale factor */
static GLfloat _planeScale = 100.0f;

 void initGL2(void) {
  glClearColor(0.0f, 0.4f, 0.9f, 0.3f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  _pId  = gl4duCreateProgram("<vs>shaders/laby.vs", "<fs>shaders/laby.fs", NULL);
  _pId2 = gl4duCreateProgram("<vs>shaders/model.vs", "<fs>shaders/model.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelMatrix");
  gl4duGenMatrix(GL_FLOAT, "viewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  // resize(_wW, _wH);
}

/*!\brief initializes data : 
 *
 * creates 3D objects (plane and sphere) and 2D textures.
 */

 void initDataL2(void) {
  initGL2();
  /* a red-white texture used to draw a compass */
  GLuint northsouth[] = {(255 << 24) + 255, -1};
  /* generates a quad using GL4Dummies */
  _plane = gl4dgGenQuadf();
  /* generates a cube using GL4Dummies */
  _cube = gl4dgGenCubef();

  _sphere = gl4dgGenSpheref(100, 50);

  // assimpInit3("5eegg1grjq-HN48 Flying Car/HN 48 Flying Car/HN 48 Flying Car.obj");
  // assimpInit3("co9kpzsnza4g-m/MRX22 Recon Flyer/MRX22 Recon Flyer.obj");
  // assimpInit3("x1c216p87ta8-T/Titan class II cargo ship/Titan class II cargo ship flying.obj");
  assimpInit3("obj/Airplane/11803_Airplane_v1_l1.obj");


  /* creation and parametrization of the plane texture */
  glGenTextures(1, &_planeTexId);
  glBindTexture(GL_TEXTURE_2D, _planeTexId);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  _labyrinth = labyrinth(_lab_side, _lab_side);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _lab_side, _lab_side, 0, GL_RGBA, GL_UNSIGNED_BYTE, _labyrinth);

  /* creation and parametrization of the compass texture */
  glGenTextures(1, &_compassTexId);
  glBindTexture(GL_TEXTURE_2D, _compassTexId);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, northsouth);

  
  // GLint t[] = {RGB(255, 100, 0)};
  // glGenTextures(1, &Tex);
  // glBindTexture(GL_TEXTURE_2D, Tex);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, t);
  // IMG_Init(IMG_INIT_JPG);
    SDL_Surface * t;
    glGenTextures(1, &Tex);
  // for(i = 0; i < 2; i++) {
    glBindTexture(GL_TEXTURE_2D, Tex);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t = IMG_Load("images/redd-angelo-61210-unsplash.jpg")) != NULL ) {
#ifdef __APPLE__
      int mode = t->format->BytesPerPixel == 4 ? GL_BGRA : GL_RGB;
#else
      int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
#endif       
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
      SDL_FreeSurface(t);
    } else {
      fprintf(stderr, "can't %s\n", SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }


  // }
    SDL_Surface * t1;
    glGenTextures(1, &Tex1);
  // for(i = 0; i < 2; i++) {
    glBindTexture(GL_TEXTURE_2D, Tex1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t1 = IMG_Load("images/Gruen-Dunkelgruen.jpg")) != NULL ) {
#ifdef __APPLE__
      int mode = t1->format->BytesPerPixel == 4 ? GL_BGRA : GL_RGB;
#else
      int mode = t1->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
#endif       
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t1->w, t1->h, 0, mode, GL_UNSIGNED_BYTE, t1->pixels);
      SDL_FreeSurface(t1);
    } else {
      fprintf(stderr, "can't %s\n", SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }

    SDL_Surface * t2;
    glGenTextures(1, &TexS2);
  // for(i = 0; i < 2; i++) {
    glBindTexture(GL_TEXTURE_2D, TexS2);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if( (t2 = IMG_Load("images/nuages.jpg")) != NULL ) {
#ifdef __APPLE__
      int mode = t2->format->BytesPerPixel == 4 ? GL_BGRA : GL_RGB;
#else
      int mode = t2->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
#endif       
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t2->w, t2->h, 0, mode, GL_UNSIGNED_BYTE, t2->pixels);
      SDL_FreeSurface(t2);
    } else {
      fprintf(stderr, "can't %s\n", SDL_GetError());
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }

  glBindTexture(GL_TEXTURE_2D, 0);
}

/*!\brief function called by GL4Dummies' loop at resize. Sets the
 *  projection matrix and the viewport according to the given width
 *  and height.
 * \param w window width
 * \param h window height
 */
 void resize2(int w, int h) {
  _wW = w; 
  _wH = h;
  glViewport(0, 0, _wW, _wH);
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.05, 0.05, -0.05 * _wH / _wW, 0.05 * _wH / _wW, 0.05, _planeScale + 1.0);
  gl4duBindMatrix("modelViewMatrix");
}


static GLfloat _radius = 80, _x0 = 20, _z0 = -20;
/*!\brief paramètres de l'avion */
static GLfloat _x = 0, _y = 200.0, _z = 0, _alpha = 0;

void idle2(void) {
  double dt;
  static Uint32 t0 = 0, t;
  dt = ((t = SDL_GetTicks()) - t0) / 1000.0;
  t0 = t;
  _alpha -= 0.3f * dt;
  _x = _x0 + _radius * cos(_alpha);
  _z = _z0 - _radius * sin(_alpha);
  _y += 0.1;

}


 
/*!\brief function called by GL4Dummies' loop at draw.*/
 void drawLaby2(void) {
  // GLfloat lum[4] = {0.0, 0.0, 5.0, 1.0};
  /* clears the OpenGL color buffer and depth buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.4f, 0.5f, 0.0f);
  /* sets the current program shader to _pId */
  glUseProgram(_pId);

  glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, _tId);
  glUniform1i(glGetUniformLocation(_pId2, "tex"), 0);

  gl4duBindMatrix("viewMatrix");
  /* loads the identity matrix in the current GL4Dummies matrix ("viewMatrix") */
  gl4duLoadIdentityf();

  /* modifies the current matrix to simulate camera position and orientation in the scene */
  /* see gl4duLookAtf documentation or gluLookAt documentation */
  gl4duLookAtf(-0 , _y, 2,     -10, -_y, -_z,           -15.0, 1.0, -3.0);
      gl4duBindMatrix("modelMatrix");
      gl4duLoadIdentityf();
      gl4duPushMatrix(); {
        gl4duTranslatef(1, 16, 1);
        gl4duScalef(600, 600, 600);
        gl4duRotatef(180, 1, 1, 0);
        gl4duRotatef(-360*_alpha, 0,1, 0);
        gl4duSendMatrices();
      } gl4duPopMatrix();
  glDisable(GL_CULL_FACE);

  /* sets the current texture stage to 0 */
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, TexS2);
  /* tells the pId program that "tex" is set to stage 0 */
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);

  gl4dgDraw(_sphere);

  glUniform1f(glGetUniformLocation(_pId, "texRepeat"), 1.0);

  gl4duTranslatef(20, 200, 20);
  gl4duRotatef(60, 0, 1, 0);
  gl4duRotatef(180, 1, 0, 0);
  gl4duRotatef(90, 0, 0, 1);
  gl4duScalef(100,100,100);

  glUniform1i(glGetUniformLocation(_pId, "inv"), 1);
  assimpDrawScene3();
  glUniform1i(glGetUniformLocation(_pId, "inv"), 0);

  /* enables cull facing and depth testing */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}


