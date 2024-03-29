/*!\file assimp.h
 *
 * \brief fonctionalit�s pour utilisation de lib Assimp sous GL4Dummies.
 * \author Far�s BELHADJ, amsi@ai.univ-paris8.fr
 * \date February 14, 2017
 */

#ifndef _ASSIMP_H

#define _ASSIMP_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void assimpInit2(const char * filename);
  extern void assimpDrawScene2(void);
  extern void assimpQuit2(void);
  
#ifdef __cplusplus
}
#endif

#endif

