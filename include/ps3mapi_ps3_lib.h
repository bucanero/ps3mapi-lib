/*PS3 MANAGER API
 * Copyright (c) 2014 _NzV_.
 * Updated in 2020 by Bucanero (www.bucanero.com.ar)
 *
 * This code is written by _NzV_ <donm7v@gmail.com>.
 * It may be used for any purpose as long as this notice remains intact on all
 * source code distributions.
 */

#ifndef __PS3MAPI_H__
#define __PS3MAPI_H__

#define process_id_t							uint32_t
#define sys_prx_id_t							int32_t

#define SYSCALL8_OPCODE_PS3MAPI			 		0x7777

#define PS3MAPI_PS3_LIB_VERSION					0x0120

#define PS3MAPI_CORE_MINVERSION					0x0120

//-----------------------------------------------
//CORE
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_CORE_VERSION			0x0011
#define PS3MAPI_OPCODE_GET_CORE_MINVERSION		0x0012
#define PS3MAPI_OPCODE_GET_FW_TYPE				0x0013
#define PS3MAPI_OPCODE_GET_FW_VERSION			0x0014

int ps3mapi_get_core_version(void);
int ps3mapi_get_core_minversion(void);
int ps3mapi_get_fw_type(char *fw);
int ps3mapi_get_fw_version(void);
int has_ps3mapi(void);

//-----------------------------------------------
//PROCESSES
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_ALL_PROC_PID			0x0021
#define PS3MAPI_OPCODE_GET_PROC_NAME_BY_PID		0x0022
#define PS3MAPI_OPCODE_GET_PROC_BY_PID			0x0023
#define PS3MAPI_OPCODE_GET_CURRENT_PROC			0x0024
#define PS3MAPI_OPCODE_GET_CURRENT_PROC_CRIT	0x0025

typedef struct
{
	void *unk_00; // 0
	char name[24]; // 8
	// ...
} __attribute__((packed)) UnkProcessStruct;

typedef struct _process_t
{
	void *syscall_table; // 0
	uint64_t unk_8[4]; // 8
	uint32_t pid; // 0x28
	int status; // 0x2C
	void *mem_object; // 0x30
	UnkProcessStruct *unk_38; // 0x38
	uint64_t unk_40; // 0x40
	void *first_thread; // 0x48 
	uint64_t unk_50; // 0x50
	uint64_t unk_58; // 0x58
	void *unk_60; // 0x60
	void *unk_68; // 0x68 vshprocess -> mios2_SPU_Service.elf
	void *unk_70; // 0x70 vshprocess -> mios2_SPU_Service.elf
	uint64_t unk_78; // 0x78
	uint64_t unk_80; // 0x80
	uint64_t unk_88[4]; // 0x88
	uint64_t unk_A8; // 0xA8  user address?
	struct _process_t *parent; // 0xB0
	struct _process_t *first_child; // 0xB8  
	struct _process_t *next_sibling; // 0xC0
	uint64_t num_children; // 0xC8
	void *unk_D0; // 0xD0
	uint64_t unk_D8; // 0xD8
	uint64_t unk_E0; // 0xE0
	uint64_t unk_E8; // 0xE8
	uint64_t unk_F0[2]; // 0xF0
	uint64_t unk_100; // 0x100
	uint64_t unk_108; // 0x108
	void *unk_110; // 0x110
	void *unk_118; // 0x118  vshprocess -> pointer to unk_D0
	uint64_t unk_120; // 0x120
	void *unk_128; // 0x128  only on vshprocess -> same as first_thread
	void *unk_130; // 0x130 only on vsh process -> same as first thread
	uint64_t unk_138; // 0x138
	uint64_t unk_140[4]; // 0x140
	char *process_image; // 0x160
	void *unk_168; // 0x168
	uint64_t unk_170; // 0x170
	uint64_t unk_178; // 0x178
	uint64_t unk_180; // 0x180
	uint64_t unk_188[4]; // 0x188
	uint64_t unk_1A8; // 0x1A8
	uint64_t unk_1B0; // 0x1B0
	uint64_t unk_1B8; // 0x1B8
	uint64_t unk_1C0; // 0x1C0
	uint64_t unk_1C8; // 0x1C8
	uint64_t unk_1D0; // 0x1D0
	uint64_t unk_1D8; // 0x1D8
	uint64_t unk_1E0; // 0x1E0
	uint64_t unk_1E8[4]; // 0x1E8
	void *object_table; // 0x208 waiting for a better name...
	// ...?
	// 0x26C -> sdk version 32bits
} __attribute__((packed)) *process_t;

int ps3mapi_get_all_processes_pid(process_id_t *pid_list);
int ps3mapi_get_process_name_by_pid(process_id_t pid, char *name);
int ps3mapi_get_process_by_pid(process_id_t pid, process_t process);
int ps3mapi_get_current_process_critical(process_t process);
int ps3mapi_get_current_process(process_t process);

//-----------------------------------------------
//MEMORY
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_PROC_MEM			0x0031
#define PS3MAPI_OPCODE_SET_PROC_MEM			0x0032
#define PS3MAPI_OPCODE_PROC_PAGE_ALLOCATE	0x0033
#define PS3MAPI_OPCODE_PROC_PAGE_FREE		0x0034

int set_process_mem(process_id_t pid, uint64_t addr, char * buf, int size, int isDEX, int isCCAPI);
int get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size, int isDEX, int isCCAPI);
int dex_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int ccapi_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int ps3mapi_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int ps3mapi_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int dex_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int ccapi_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size);
int ps3mapi_process_page_allocate(process_id_t pid, uint64_t size, uint64_t page_size, uint64_t flags, uint64_t is_executable, uint64_t *page_table);
int ps3mapi_process_page_free(process_id_t pid, uint64_t flags, uint64_t *page_table);

//-----------------------------------------------
//DYNAREC
//-----------------------------------------------
#define PAGE_SIZE_AUTO 0

#define NOP __asm__("nop")  // a nop is 4 bytes

#define DYN8B(a)	a;a
#define DYN16B(a)	a;a;a;a
#define DYN24B(a)	a;a;a;a;a;a
#define DYN32B(a)	a;a;a;a;a;a;a;a
#define DYN40B(a)	a;a;a;a;a;a;a;a;a;a
#define DYN48B(a)	a;a;a;a;a;a;a;a;a;a;a;a
#define DYN56B(a)	a;a;a;a;a;a;a;a;a;a;a;a;a;a
#define DYN64B(a)	a;a;a;a;a;a;a;a;a;a;a;a;a;a;a;a
#define DYN128B(a) 	DYN32B(DYN16B(a)) // 32 nop
#define DYN256B(a) 	DYN64B(DYN16B(a)) // 64 nop
#define DYN512B(a) 	DYN64B(DYN32B(a)) // 128 nop
#define DYN1K(a) 	DYN128B(DYN32B(a)) // 256 nop
#define DYN2K(a) 	DYN256B(DYN32B(a)) // 512 nop
#define DYN4K(a) 	DYN512B(DYN32B(a)) // 1024 nop
#define DYN8K(a) 	DYN1K(DYN32B(a)) // 2048 nop
#define DYN16K(a) 	DYN2K(DYN32B(a)) // 4096 nop
#define DYN32K(a) 	DYN4K(DYN32B(a)) // 8192 nop
#define DYN64K(a) 	DYN8K(DYN32B(a)) // 16384 nop
#define DYN128K(a) 	DYN16K(DYN32B(a)) // 32768 nop
#define DYN256K(a) 	DYN32K(DYN32B(a)) // 65536 nop
#define DYN512K(a) 	DYN64K(DYN32B(a)) // 131072 nop
#define DYN1M(a) 	DYN128K(DYN32B(a)) // 262144 nop
#define DYN2M(a) 	DYN256K(DYN32B(a)) // 524288 nop
#define DYN4M(a) 	DYN512K(DYN32B(a)) // 1048576 nop

#define DYNAREC_ADDRESS_SHIFT 				12

#ifdef DYN_SIZE
void DYN_SIZE_FAKEFUN(void) 
{
	DYN_SIZE(NOP);
}
#endif

int ps3mapi_dynarec_init(void *fakefun, void **start_dyn_buff, int *len_dyn_buff);
int ps3mapi_dynarec_write_bytecode(void *start_dyn_buff, int len_dyn_buff, int offset, char *buff, int len);

//-----------------------------------------------
//MODULES
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_ALL_PROC_MODULE_PID		0x0041
#define PS3MAPI_OPCODE_GET_PROC_MODULE_NAME			0x0042
#define PS3MAPI_OPCODE_GET_PROC_MODULE_FILENAME		0x0043
#define PS3MAPI_OPCODE_LOAD_PROC_MODULE				0x0044
#define PS3MAPI_OPCODE_UNLOAD_PROC_MODULE			0x0045
#define PS3MAPI_OPCODE_UNLOAD_VSH_PLUGIN			0x0046
#define PS3MAPI_OPCODE_GET_VSH_PLUGIN_INFO			0x0047
#define PS3MAPI_OPCODE_GET_PROC_MODULE_INFO			0x0048

typedef struct
{
	uint64_t size; /* struct size, ignored in kernel version of the function */
	char name[30];
	char version[2];
	uint32_t modattribute;
	uint32_t start_entry;
	uint32_t stop_entry;
	uint32_t all_segments_num;
	uint32_t filename; /* User: user pointer to receive filename; Kernel: ignored */
	uint32_t filename_size;
	uint32_t segments; /* User: user pointer to receive segments; Kernel: ignored */
	uint32_t segments_num;
} __attribute__((packed)) sys_prx_module_info_t;

int ps3mapi_get_all_process_modules_prx_id(process_id_t pid, sys_prx_id_t *prx_id_list);
int ps3mapi_get_process_module_name_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *name);
int ps3mapi_get_process_module_filename_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *filename);
int ps3mapi_get_process_module_info(process_id_t pid, sys_prx_id_t prx_id, sys_prx_module_info_t *info);
int ps3mapi_load_process_modules(process_id_t pid, char *path, void *arg, uint32_t arg_size);
int ps3mapi_unload_process_modules(process_id_t pid, sys_prx_id_t prx_id);
int ps3mapi_unload_vsh_plugin(char *name);
int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename);
int ps3mapi_get_vsh_plugin_slot_by_name(const char *name);
int ps3mapi_get_vsh_plugin_slot_by_filename(const char *filename);
int ps3mapi_get_vsh_plugin_free_slot(void);

//-----------------------------------------------
//THREAD
//-----------------------------------------------

#define SYSCALL8_OPCODE_PROC_CREATE_THREAD			0x6E03 // not enough params for PS3MAPI_OPCODE

typedef struct
{
	void *unk_0; // ptr to some funcs
	uint64_t unk_8;
	uint32_t unk_10;
	uint32_t unk_14;
	void *unk_18;
	void *unk_20; // same as unk_18? :S
	uint64_t unk_28[3];
	void *unk_40; // same as unk_0?
	// ...
} *thread_t;

int ps3mapi_create_process_thread(process_id_t pid, thread_t *thread, void *entry, uint64_t arg, int prio, size_t stacksize, char *threadname);

//-----------------------------------------------
//CLEAN SYSCALL
//-----------------------------------------------

#define PS3MAPI_OPCODE_CHECK_SYSCALL			0x0091
#define PS3MAPI_OPCODE_DISABLE_SYSCALL			0x0092
#define PS3MAPI_OPCODE_PDISABLE_SYSCALL8 		0x0093
#define PS3MAPI_OPCODE_PCHECK_SYSCALL8 			0x0094

int ps3mapi_check_syscall(int num);
int ps3mapi_disable_syscall(int num);
int ps3mapi_pdisable_syscall8(int mode);
int ps3mapi_pcheck_syscall8(void);

//-----------------------------------------------
//PSID/IDPS
//-----------------------------------------------

#define PS3MAPI_OPCODE_GET_IDPS 		0x0081
#define PS3MAPI_OPCODE_SET_IDPS 		0x0082
#define PS3MAPI_OPCODE_GET_PSID 		0x0083
#define PS3MAPI_OPCODE_SET_PSID			0x0084

int ps3mapi_get_idps(uint64_t *idps);
int ps3mapi_set_idps(uint64_t part1, uint64_t part2);
int ps3mapi_get_psid(uint64_t *psid);
int ps3mapi_set_psid(uint64_t part1, uint64_t part2);

//-----------------------------------------------
//REMOVE COBRA/MAMBA HOOK
//-----------------------------------------------

#define PS3MAPI_OPCODE_REMOVE_HOOK			0x0101

int ps3mapi_remove_hook(void);

//-----------------------------------------------
//PEEK & POKE
//-----------------------------------------------

#define PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE	0x1000
#define PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE_OK	0x6789
#define PS3MAPI_OPCODE_LV2_PEEK					0x1006
#define PS3MAPI_OPCODE_LV2_POKE					0x1007
#define PS3MAPI_OPCODE_LV1_PEEK					0x1008
#define PS3MAPI_OPCODE_LV1_POKE					0x1009

int ps3mapi_support_sc8_peek_poke(void);
int ps3mapi_lv1_poke(uint64_t addr, uint64_t value);
int ps3mapi_lv2_poke(uint64_t addr, uint64_t value);
uint64_t ps3mapi_lv1_peek(uint64_t addr);
uint64_t ps3mapi_lv2_peek(uint64_t addr);

//-----------------------------------------------
//SECURITY
//-----------------------------------------------

#define PS3MAPI_OPCODE_SET_ACCESS_KEY			0x2000
#define PS3MAPI_OPCODE_REQUEST_ACCESS			0x2001

int ps3mapi_set_access_key(uint64_t key);
int ps3mapi_request_access(uint64_t key);

//-----------------------------------------------
//EXTRA
//-----------------------------------------------

#define LED_COLOR_RED		0
#define LED_COLOR_GREEN		1
#define LED_COLOR_YELLOW	2

#define LED_MODE_OFF		0
#define LED_MODE_ON			1
#define LED_MODE_BLINK		2

int led(uint64_t color, uint64_t mode);
int ps3_shutdown(void);
int ps3_quick_restart(void);
int ps3_hard_restart(void);
int ps3_soft_restart(void);
int ring_buzzer_simple(void);
int ring_buzzer_double(void);
int ring_buzzer_triple(void);
int get_temperature_celcius(uint32_t *cpu_temp, uint32_t *rsx_temp);

//----------------------------------------
//COBRA/MAMBA
//----------------------------------------

#define SYSCALL8_OPCODE_GET_VERSION         0x7000
#define SYSCALL8_OPCODE_GET_MAMBA           0x7FFF
#define SYSCALL8_OPCODE_IS_HEN              0x1337
#define SYSCALL8_OPCODE_HEN_REV             0x1339
#define SYSCALL8_OPCODE_LOAD_VSH_PLUGIN     0x1EE7
#define SYSCALL8_OPCODE_UNLOAD_VSH_PLUGIN   0x364F
#define SYSCALL8_OPCODE_STEALTH_TEST        0x3993
#define SYSCALL8_OPCODE_STEALTH_ACTIVATE    0x3995
#define SYSCALL8_STEALTH_OK                 0x5555

int sys8_get_version(uint32_t *version);
int sys8_get_hen_version(void);
int has_cobra_mamba(void);
int is_cobra(void);
int is_mamba(void);
int is_ps3hen(void);
int cobra_mamba_load_prx_module(uint32_t slot, char * path, void * arg, uint32_t arg_size);
int cobra_mamba_unload_prx_module(uint32_t slot);
int cobra_mamba_stealth_test(void);
int cobra_mamba_stealth_activate(void);
int lv2_poke(uint64_t addr, uint64_t value);
int lv2_poke32(uint64_t addr, uint32_t value);
uint64_t lv2_peek(uint64_t addr);

#endif /* __PS3MAPI_H__ */
