/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-core - m64p_types.h                                       *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2012 CasualJames                                        *
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

#ifndef M64P_TYPES_H
#define M64P_TYPES_H

#include <stdint.h>
#include <stddef.h>

#ifdef ONLY_VULKAN
#define NAME_PREFIX "parallel"
#else
#define NAME_PREFIX "mupen64"
#endif

/* ----------------------------------------- */
/* Platform-specific stuff                   */
/* ----------------------------------------- */

/* necessary headers */
#if defined(WIN32)
  #include <windows.h>
#endif

/* DLL handles and function declaration specifiers */
#define IMPORT
#define EXPORT
#define CALL
typedef void * m64p_dynlib_handle;

/* ----------------------------------------- */
/* Structures and Types for Core library API */
/* ----------------------------------------- */

typedef void * m64p_handle;

typedef void (*m64p_frame_callback)(unsigned int FrameIndex);
typedef void (*m64p_input_callback)(void);
typedef void (*m64p_audio_callback)(void);
typedef void (*m64p_vi_callback)(void);

typedef enum
{
   M64TYPE_INT = 1,
   M64TYPE_FLOAT,
   M64TYPE_BOOL,
   M64TYPE_STRING
} m64p_type;

typedef enum
{
   M64MSG_ERROR = 1,
   M64MSG_WARNING,
   M64MSG_INFO,
   M64MSG_STATUS,
   M64MSG_VERBOSE
} m64p_msg_level;

typedef enum
{
   M64ERR_SUCCESS = 0,
   M64ERR_NOT_INIT,        /* Function is disallowed before InitMupen64Plus() is called */
   M64ERR_ALREADY_INIT,    /* InitMupen64Plus() was called twice */
   M64ERR_INCOMPATIBLE,    /* API versions between components are incompatible */
   M64ERR_INPUT_ASSERT,    /* Invalid parameters for function call, such as ParamValue=NULL for GetCoreParameter() */
   M64ERR_INPUT_INVALID,   /* Invalid input data, such as ParamValue="maybe" for SetCoreParameter() to set a BOOL-type value */
   M64ERR_INPUT_NOT_FOUND, /* The input parameter(s) specified a particular item which was not found */
   M64ERR_NO_MEMORY,       /* Memory allocation failed */
   M64ERR_FILES,           /* Error opening, creating, reading, or writing to a file */
   M64ERR_INTERNAL,        /* Internal error (bug) */
   M64ERR_INVALID_STATE,   /* Current program state does not allow operation */
   M64ERR_PLUGIN_FAIL,     /* A plugin function returned a fatal error */
   M64ERR_SYSTEM_FAIL,     /* A system function call, such as an SDL or file operation, failed */
   M64ERR_UNSUPPORTED,     /* Function call is not supported (ie, core not built with debugger) */
   M64ERR_WRONG_TYPE       /* A given input type parameter cannot be used for desired operation */
} m64p_error;

typedef enum
{
   M64CAPS_DYNAREC = 1,
   M64CAPS_DEBUGGER = 2,
   M64CAPS_CORE_COMPARE = 4
} m64p_core_caps;

typedef enum
{
   M64PLUGIN_NULL = 0,
   M64PLUGIN_RSP = 1,
   M64PLUGIN_GFX,
   M64PLUGIN_AUDIO,
   M64PLUGIN_INPUT,
   M64PLUGIN_CORE
} m64p_plugin_type;

typedef enum
{
   M64EMU_STOPPED = 1,
   M64EMU_RUNNING,
   M64EMU_PAUSED
} m64p_emu_state;

typedef enum
{
   M64VIDEO_NONE = 1,
   M64VIDEO_WINDOWED,
   M64VIDEO_FULLSCREEN
} m64p_video_mode;

typedef enum
{
   M64VIDEOFLAG_SUPPORT_RESIZING = 1
} m64p_video_flags;

typedef enum
{
   M64CORE_EMU_STATE = 1,
   M64CORE_VIDEO_SIZE,
   M64CORE_INPUT_GAMESHARK,
   M64CORE_STATE_LOADCOMPLETE,
   M64CORE_STATE_SAVECOMPLETE
} m64p_core_param;

typedef enum {
   M64CMD_NOP = 0,
   M64CMD_ROM_OPEN,
   M64CMD_ROM_CLOSE,
   M64CMD_ROM_GET_HEADER,
   M64CMD_ROM_GET_SETTINGS,
   M64CMD_EXECUTE,
   M64CMD_STOP,
   M64CMD_PAUSE,
   M64CMD_RESUME,
   M64CMD_CORE_STATE_QUERY,
   M64CMD_SET_FRAME_CALLBACK,
   M64CMD_CORE_STATE_SET,
   M64CMD_READ_SCREEN,
   M64CMD_RESET,
   M64CMD_ADVANCE_FRAME,
   M64CMD_DDROM_OPEN,
   M64CMD_DISK_OPEN,
   M64CMD_DISK_CLOSE
} m64p_command;

typedef struct
{
   uint32_t     address;
   int          value;
} m64p_cheat_code;

/* ----------------------------------------- */
/* Structures to hold ROM image information  */
/* ----------------------------------------- */

typedef enum
{
   SYSTEM_NTSC = 0,
   SYSTEM_PAL,
   SYSTEM_MPAL
} m64p_system_type;

typedef struct
{
   uint8_t init_PI_BSB_DOM1_LAT_REG;  /* 0x00 */
   uint8_t init_PI_BSB_DOM1_PGS_REG;  /* 0x01 */
   uint8_t init_PI_BSB_DOM1_PWD_REG;  /* 0x02 */
   uint8_t init_PI_BSB_DOM1_PGS_REG2; /* 0x03 */
   uint32_t     ClockRate;                  /* 0x04 */
   uint32_t     PC;                         /* 0x08 */
   uint32_t     Release;                    /* 0x0C */
   uint32_t     CRC1;                       /* 0x10 */
   uint32_t     CRC2;                       /* 0x14 */
   uint32_t     Unknown[2];                 /* 0x18 */
   uint8_t       Name[20];                  /* 0x20 to 0x33 */
   uint32_t unknown;
   uint32_t     Manufacturer_ID;            /* 0x3B */
   uint16_t       Cartridge_ID;             /* 0x3C to 0x3D  */
   char destination_code;                    /* 0x3E */
   unsigned char mask_ROM_version;           /* 0x3F */
} m64p_rom_header;

typedef struct
{
   char goodname[256];
   char MD5[33];
   unsigned char savetype;
   unsigned char status;  /* Rom status on a scale from 0-5. */
   unsigned char players; /* Local players 0-4, 2/3/4 way Netplay indicated by 5/6/7. */
   unsigned char rumble;  /* 0 - No, 1 - Yes boolean for rumble support. */
} m64p_rom_settings;

/* ----------------------------------------- */
/* Structures and Types for the Debugger     */
/* ----------------------------------------- */

typedef enum
{
   M64P_DBG_RUN_STATE = 1,
   M64P_DBG_PREVIOUS_PC,
   M64P_DBG_NUM_BREAKPOINTS,
   M64P_DBG_CPU_DYNACORE,
   M64P_DBG_CPU_NEXT_INTERRUPT
} m64p_dbg_state;

typedef enum
{
   M64P_DBG_RUNSTATE_PAUSED = 0,
   M64P_DBG_RUNSTATE_STEPPING,
   M64P_DBG_RUNSTATE_RUNNING
} m64p_dbg_runstate;

typedef enum
{
   M64P_DBG_MEM_TYPE = 1,
   M64P_DBG_MEM_FLAGS,
   M64P_DBG_MEM_HAS_RECOMPILED,
   M64P_DBG_MEM_NUM_RECOMPILED,
   M64P_DBG_RECOMP_OPCODE = 16,
   M64P_DBG_RECOMP_ARGS,
   M64P_DBG_RECOMP_ADDR
} m64p_dbg_mem_info;

typedef enum {
   M64P_MEM_NOMEM = 0,
   M64P_MEM_NOTHING,
   M64P_MEM_RDRAM,
   M64P_MEM_RDRAMREG,
   M64P_MEM_RSPMEM,
   M64P_MEM_RSPREG,
   M64P_MEM_RSP,
   M64P_MEM_DP,
   M64P_MEM_DPS,
   M64P_MEM_VI,
   M64P_MEM_AI,
   M64P_MEM_PI,
   M64P_MEM_RI,
   M64P_MEM_SI,
   M64P_MEM_FLASHRAMSTAT,
   M64P_MEM_ROM,
   M64P_MEM_PIF,
   M64P_MEM_MI,
   M64P_MEM_BREAKPOINT,
   M64P_MEM_DD
} m64p_dbg_mem_type;

typedef enum
{
   M64P_MEM_FLAG_READABLE = 0x01,
   M64P_MEM_FLAG_WRITABLE = 0x02,
   M64P_MEM_FLAG_READABLE_EMUONLY = 0x04,  /* the EMUONLY flags signify that emulated code can read/write here, but debugger cannot */
   M64P_MEM_FLAG_WRITABLE_EMUONLY = 0x08
} m64p_dbg_mem_flags;

typedef enum {
   M64P_DBG_PTR_RDRAM = 1,
   M64P_DBG_PTR_PI_REG,
   M64P_DBG_PTR_SI_REG,
   M64P_DBG_PTR_VI_REG,
   M64P_DBG_PTR_RI_REG,
   M64P_DBG_PTR_AI_REG
} m64p_dbg_memptr_type;

typedef enum {
   M64P_CPU_PC = 1,
   M64P_CPU_REG_REG,
   M64P_CPU_REG_HI,
   M64P_CPU_REG_LO,
   M64P_CPU_REG_COP0,
   M64P_CPU_REG_COP1_DOUBLE_PTR,
   M64P_CPU_REG_COP1_SIMPLE_PTR,
   M64P_CPU_REG_COP1_FGR_64,
   M64P_CPU_TLB
} m64p_dbg_cpu_data;

typedef enum {
   M64P_BKP_CMD_ADD_ADDR = 1,
   M64P_BKP_CMD_ADD_STRUCT,
   M64P_BKP_CMD_REPLACE,
   M64P_BKP_CMD_REMOVE_ADDR,
   M64P_BKP_CMD_REMOVE_IDX,
   M64P_BKP_CMD_ENABLE,
   M64P_BKP_CMD_DISABLE,
   M64P_BKP_CMD_CHECK
} m64p_dbg_bkp_command;

#define M64P_MEM_INVALID        0xFFFFFFFF  /* invalid memory read will return this */

#define BREAKPOINTS_MAX_NUMBER  128

typedef enum
{
  M64P_BKP_FLAG_ENABLED = 0x01,
  M64P_BKP_FLAG_READ = 0x02,
  M64P_BKP_FLAG_WRITE = 0x04,
  M64P_BKP_FLAG_EXEC = 0x08,
  M64P_BKP_FLAG_LOG = 0x10 /* Log to the console when this breakpoint hits */
} m64p_dbg_bkp_flags;

#define BPT_CHECK_FLAG(a, b)  ((a.flags & b) == b)
#define BPT_SET_FLAG(a, b)    a.flags = (a.flags | b);
#define BPT_CLEAR_FLAG(a, b)  a.flags = (a.flags & (~b));
#define BPT_TOGGLE_FLAG(a, b) a.flags = (a.flags ^ b);

typedef struct
{
   uint32_t address; 
   uint32_t endaddr;
   unsigned int flags;
} m64p_breakpoint;

/* ------------------------------------------------- */
/* Structures and Types for Core Video Extension API */
/* ------------------------------------------------- */

typedef struct {
   unsigned int uiWidth;
   unsigned int uiHeight;
} m64p_2d_size;

typedef enum {
   M64P_GL_DOUBLEBUFFER = 1,
   M64P_GL_BUFFER_SIZE,
   M64P_GL_DEPTH_SIZE,
   M64P_GL_RED_SIZE,
   M64P_GL_GREEN_SIZE,
   M64P_GL_BLUE_SIZE,
   M64P_GL_ALPHA_SIZE,
   M64P_GL_SWAP_CONTROL,
   M64P_GL_MULTISAMPLEBUFFERS,
   M64P_GL_MULTISAMPLESAMPLES,
   M64P_GL_CONTEXT_MAJOR_VERSION,
   M64P_GL_CONTEXT_MINOR_VERSION,
   M64P_GL_CONTEXT_PROFILE_MASK,
} m64p_GLattr;


typedef enum
{
  M64P_GL_CONTEXT_PROFILE_CORE,
  M64P_GL_CONTEXT_PROFILE_COMPATIBILITY,
  M64P_GL_CONTEXT_PROFILE_ES
} m64p_GLContextType;

typedef struct
{
   unsigned int Functions;
   m64p_error (*VidExtFuncInit)(void);
   m64p_error (*VidExtFuncQuit)(void);
   m64p_error (*VidExtFuncListModes)(m64p_2d_size *, int *);
   m64p_error (*VidExtFuncSetMode)(int, int, int, int, int);
   void *     (*VidExtFuncGLGetProc)(const char*);
   m64p_error (*VidExtFuncGLSetAttr)(m64p_GLattr, int);
   m64p_error (*VidExtFuncGLGetAttr)(m64p_GLattr, int *);
   m64p_error (*VidExtFuncGLSwapBuf)(void);
   m64p_error (*VidExtFuncSetCaption)(const char *);
   m64p_error (*VidExtFuncToggleFS)(void);
   m64p_error (*VidExtFuncResizeWindow)(int, int);
} m64p_video_extension_functions;

/* ------------------------------------------ */
/* Structures and Types for Audio Backend API */
/* ------------------------------------------ */
/* Audio backend object
 *
 * user_data is a pointer which will ba passed as the first argument of audio backend functions.
 * Frontend writers are free to use it as they please.
 *
 * set_audio_format function allow the audio backend to be notified of the format of incoming samples.
 * 2nd parameter frequency is the sample rate of incoming samples.
 * 3rd parameter bits is the sample resolution (usually 16 bits)
 *
 * This function should be called by the core at least one time before any call to "push_audio_samples".
 * Audio backends are expected to handle gracefully eventual changes of audio format
 * even after this"initial" setup. Though in practice, very few game, if any,
 * changes the audio format after the initial setup.
 *
 * push_audio_samples function notify the audio backend of new samples ready to be played.
 * 2nd parameter buffer is a pointer to the beginning of the incoming samples.
 * 3rd parameter size is the size in bytes of the buffer.
 *
 * Samples are in stereo interleaved format (LR LR LR ...) and their resolution (bits per channel)
 * is specified by prior calls of set_audio_format.
 * Audio backends are expected not to block during the servicing of this function.
 * We invite audio backends writers to buffer (and maybe resample) the incoming samples
 * and return control to the core as soon as possible.
 */

struct m64p_audio_backend
{
   void* user_data;
   void (*set_audio_format)(void*, unsigned int, unsigned int);
   void (*push_audio_samples)(void*, const void*, size_t);
};

#endif /* define M64P_TYPES_H */

