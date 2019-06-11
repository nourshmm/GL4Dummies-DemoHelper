/*!\file assimp.h
 *
 * \brief fonctionalités pour utilisation de lib Assimp sous GL4Dummies.
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date February 14, 2017
 */

#ifndef _ASSIMP1_H

#define _ASSIMP1_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void assimpInit1(const char * filename);
  extern void assimpDrawScene1(void);
  extern void assimpQuit1(void);
  
#ifdef __cplusplus
}
#endif

#endif

