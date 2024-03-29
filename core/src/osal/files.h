/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-core - osal/files.h                                       *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2009 Richard Goedeken                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       * 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
                       
/* This file contains the declarations for OS-dependent file handling
 * functions
 */

#if !defined (OSAL_FILES_H)
#define OSAL_FILES_H

/* some file-related preprocessor definitions */
#if defined(WIN32)
  #define OSAL_DIR_SEPARATOR           '\\'
#else  /* Not WIN32 */
  #define OSAL_DIR_SEPARATOR           '/'
#endif

extern int osal_mkdirp(const char *dirpath, int mode);

extern const char * osal_get_shared_filepath(const char *filename, const char *firstsearch, const char *secondsearch);
extern const char * osal_get_user_configpath(void);
extern const char * osal_get_user_datapath(void);
extern const char * osal_get_user_cachepath(void);

#endif /* OSAL_FILES_H */

