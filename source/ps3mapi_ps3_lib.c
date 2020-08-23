/*PS3 MANAGER API
 * Copyright (c) 2014 _NzV_.
 * Updated in 2020 by Bucanero (www.bucanero.com.ar)
 *
 * This code is written by _NzV_ <donm7v@gmail.com>.
 * It may be used for any purpose as long as this notice remains intact on all
 * source code distributions.
 */

#include <ppu-lv2.h>
#include <sys/file.h>
#include <string.h>
#include "ps3mapi_ps3_lib.h"

#define KB 1024ULL

//-----------------------------------------------
//CORE
//-----------------------------------------------

int ps3mapi_get_core_version(void)
{
	lv2syscall2(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CORE_VERSION);
	return_to_user_prog(int);						
}

int ps3mapi_get_core_minversion(void)
{
	lv2syscall2(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CORE_MINVERSION);
	return_to_user_prog(int);						
}

int ps3mapi_get_fw_type(char *fw) 
{
	lv2syscall3(8, (uint64_t)SYSCALL8_OPCODE_PS3MAPI, (uint64_t)PS3MAPI_OPCODE_GET_FW_TYPE, (uint64_t)fw);
	return_to_user_prog(int);						
}

int ps3mapi_get_fw_version(void)
{
	lv2syscall2(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_FW_VERSION);
	return_to_user_prog(int);						
}

int has_ps3mapi(void)
{
	return (ps3mapi_get_core_version() >= PS3MAPI_CORE_MINVERSION);
}

//-----------------------------------------------
//PROCESSES
//-----------------------------------------------

int ps3mapi_get_all_processes_pid(process_id_t *pid_list)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_ALL_PROC_PID, (uint64_t)pid_list);
	return_to_user_prog(int);						
}

int  ps3mapi_get_process_name_by_pid(process_id_t pid, char *name)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_NAME_BY_PID, (uint64_t)pid, (uint64_t)name);
	return_to_user_prog(int);						
}

int ps3mapi_get_process_by_pid(process_id_t pid, process_t process)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_BY_PID, (uint64_t)pid, (uint64_t)process);
	return_to_user_prog(int);						
}

int ps3mapi_get_current_process_critical(process_t process)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CURRENT_PROC_CRIT, (uint64_t)process);
	return_to_user_prog(int);
}

int ps3mapi_get_current_process(process_t process)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_CURRENT_PROC, (uint64_t)process);
	return_to_user_prog(int);						
}

//-----------------------------------------------
//MEMORY
//-----------------------------------------------

int set_process_mem(process_id_t pid, uint64_t addr, char * buf, int size, int isDEX, int isCCAPI)
{
	if (isDEX)
	{
		return dex_set_process_mem(pid, addr, buf, size);
	}
	else if (isCCAPI)
	{
		return ccapi_set_process_mem(pid, addr, buf, size);
	}
	
	return ps3mapi_set_process_mem(pid, addr, buf, size);
}

int get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size, int isDEX, int isCCAPI)
{
	if (isDEX)
	{
		return dex_get_process_mem(pid, addr, buf, size);
	}
	else if (isCCAPI)
	{
		return ccapi_get_process_mem(pid, addr, buf, size);
	}
	
	return ps3mapi_get_process_mem(pid, addr, buf, size);
}

int ps3mapi_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size )
{
	lv2syscall6(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_PROC_MEM, (uint64_t)pid, (uint64_t)addr, (uint64_t)buf, (uint64_t)size);
	return_to_user_prog(int);
}

int dex_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size )
{
	lv2syscall4(905, (uint64_t)pid, (uint64_t)addr, (uint64_t)size, (uint64_t)buf);
	return_to_user_prog(int);
}

int ccapi_set_process_mem(process_id_t pid, uint64_t addr, char *buf, int size )
{
	lv2syscall4(201, (uint64_t)pid, (uint64_t)addr, (uint64_t)size, (uint64_t)buf);
	return_to_user_prog(int);
}

int ps3mapi_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size)
{
	lv2syscall6(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MEM, (uint64_t)pid, (uint64_t)addr, (uint64_t)buf, (uint64_t)size);
	return_to_user_prog(int);						
}
	
int dex_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size)
{
	lv2syscall4(904, (uint64_t)pid, (uint64_t)addr, (uint64_t)size, (uint64_t)buf);
	return_to_user_prog(int);
}

int ccapi_get_process_mem(process_id_t pid, uint64_t addr, char *buf, int size)
{
	lv2syscall4(200, (uint64_t)pid, (uint64_t)addr, (uint64_t)size, (uint64_t)buf);
	return_to_user_prog(int);
}

int ps3mapi_process_page_allocate(process_id_t pid, uint64_t size, uint64_t page_size, uint64_t flags, uint64_t is_executable, uint64_t *page_address)
{
	lv2syscall8(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PROC_PAGE_ALLOCATE, (uint64_t)pid, (uint64_t)size, (uint64_t)page_size, (uint64_t)flags, (uint64_t)is_executable, (uint64_t)page_address);
	return_to_user_prog(int);						
}

//-----------------------------------------------
//MODULES
//-----------------------------------------------

int ps3mapi_get_all_process_modules_prx_id(process_id_t pid, sys_prx_id_t *prx_id_list)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_ALL_PROC_MODULE_PID, (uint64_t)pid, (uint64_t)prx_id_list);
	return_to_user_prog(int);						
}

int ps3mapi_get_process_module_name_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *name)
{
	lv2syscall5(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MODULE_NAME, (uint64_t)pid, (uint64_t)prx_id, (uint64_t)name);
	return_to_user_prog(int);						
}

int ps3mapi_get_process_module_filename_by_prx_id(process_id_t pid, sys_prx_id_t prx_id, char *filename)
{
	lv2syscall5(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MODULE_FILENAME, (uint64_t)pid, (uint64_t)prx_id, (uint64_t)filename);
	return_to_user_prog(int);						
}

int ps3mapi_load_process_modules(process_id_t pid, char *path, void *arg, uint32_t arg_size)
{
	lv2syscall6(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LOAD_PROC_MODULE, (uint64_t)pid, (uint64_t)path, (uint64_t)arg, (uint64_t)arg_size);
	return_to_user_prog(int);						
}

int ps3mapi_unload_process_modules(process_id_t pid, sys_prx_id_t prx_id)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_UNLOAD_PROC_MODULE, (uint64_t)pid, (uint64_t)prx_id);
	return_to_user_prog(int);						
}

int ps3mapi_unload_vsh_plugin(char *name)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_UNLOAD_VSH_PLUGIN, (uint64_t)name);
	return_to_user_prog(int);						
}

int ps3mapi_get_vsh_plugin_info(unsigned int slot, char *name, char *filename)
{
	lv2syscall5(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_VSH_PLUGIN_INFO, (uint64_t)slot, (uint64_t)name, (uint64_t)filename);
	return_to_user_prog(int);						
}

int ps3mapi_get_process_module_info(process_id_t pid, sys_prx_id_t prx_id, sys_prx_module_info_t *info)
{
	lv2syscall5(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PROC_MODULE_INFO, (uint64_t)pid, (uint64_t)prx_id, (uint64_t)info);
	return_to_user_prog(int);						
}

int ps3mapi_get_vsh_plugin_slot_by_name(const char *name)
{
    char tmp_name[30];
    char tmp_filename[256];
    unsigned int slot;

    for (slot = 1; slot < 7; slot++)
    {
        ps3mapi_get_vsh_plugin_info(slot, tmp_name, tmp_filename);
        if(strcmp(tmp_name, name) == 0)
            return slot;
    }

    return 0;
}

int ps3mapi_get_vsh_plugin_slot_by_filename(const char *filename)
{
    char tmp_name[30];
    char tmp_filename[256];
    unsigned int slot;

    for (slot = 1; slot < 7; slot++)
    {
        ps3mapi_get_vsh_plugin_info(slot, tmp_name, tmp_filename);
        if(strcmp(tmp_filename, filename) == 0)
            return slot;
    }

    return 0;
}

int ps3mapi_get_vsh_plugin_free_slot(void)
{
    char tmp_name[30];
    char tmp_filename[256];
    unsigned int slot;

    for (slot = 1; slot < 7; slot++)
    {
        memset(tmp_name, 0, sizeof(tmp_name));
        memset(tmp_filename, 0, sizeof(tmp_filename));
        ps3mapi_get_vsh_plugin_info(slot, tmp_name, tmp_filename);
        if(strlen(tmp_filename) == 0 && strlen(tmp_name) == 0)
            return slot;
    }

    return 0;
}

//-----------------------------------------------
//THREAD
//-----------------------------------------------

int ps3mapi_create_process_thread(process_id_t pid, thread_t *thread, void *entry, uint64_t arg, int prio, size_t stacksize, char *threadname)
{
	lv2syscall8(8, SYSCALL8_OPCODE_PROC_CREATE_THREAD, (uint64_t)pid, (uint64_t)thread, (uint64_t)entry, (uint64_t)arg, (uint64_t)prio, (uint64_t)stacksize, (uint64_t)threadname);
	return_to_user_prog(int);						
}

//-----------------------------------------------
//CLEAN SYSCALL
//-----------------------------------------------

int ps3mapi_check_syscall(int num)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_CHECK_SYSCALL, (uint64_t)num);
	return_to_user_prog(int);						
}

int ps3mapi_disable_syscall(int num)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_DISABLE_SYSCALL, (uint64_t)num);
	return_to_user_prog(int);						
}

int ps3mapi_pdisable_syscall8(int mode)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PDISABLE_SYSCALL8, (uint64_t)mode);
	return_to_user_prog(int);						
}

int ps3mapi_pcheck_syscall8()
{
	lv2syscall2(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PCHECK_SYSCALL8);
	return_to_user_prog(int);						
}

//-----------------------------------------------
//PSID/IDPS
//-----------------------------------------------

int ps3mapi_get_idps(uint64_t *idps)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_IDPS, (uint64_t)idps);
	return_to_user_prog(int);						
}

int ps3mapi_set_idps(uint64_t part1, uint64_t part2)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_IDPS, (uint64_t)part1, (uint64_t)part2);
	return_to_user_prog(int);						
}

int ps3mapi_get_psid(uint64_t *psid)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_GET_PSID, (uint64_t)psid);
	return_to_user_prog(int);						
}

int ps3mapi_set_psid(uint64_t part1, uint64_t part2)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_PSID, (uint64_t)part1, (uint64_t)part2);
	return_to_user_prog(int);						
}

//-----------------------------------------------
//DISABLE COBRA/MAMBA
//-----------------------------------------------

int ps3mapi_remove_hook(void)
{
	lv2syscall2(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_REMOVE_HOOK);
	return_to_user_prog(int);						
}

//-----------------------------------------------
//PEEK & POKE
//-----------------------------------------------

int ps3mapi_support_sc8_peek_poke(void)
{
	lv2syscall2(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SUPPORT_SC8_PEEK_POKE);
	return_to_user_prog(int);
}

uint64_t ps3mapi_lv1_peek(uint64_t addr)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV1_PEEK, (uint64_t)addr);
	return_to_user_prog(uint64_t);
}

uint64_t ps3mapi_lv2_peek(uint64_t addr)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV2_PEEK, (uint64_t)addr);
	return_to_user_prog(uint64_t);
}

int ps3mapi_lv1_poke(uint64_t addr, uint64_t value)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV1_POKE, (uint64_t)addr, (uint64_t)value);
	return_to_user_prog(int);
}

int ps3mapi_lv2_poke(uint64_t addr, uint64_t value)
{
	lv2syscall4(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_LV2_POKE, (uint64_t)addr, (uint64_t)value);
	return_to_user_prog(int);
}

//-----------------------------------------------
//SECURITY
//-----------------------------------------------

int ps3mapi_set_access_key(uint64_t key)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_SET_ACCESS_KEY, (uint64_t)key);
	return_to_user_prog(int);
}

int ps3mapi_request_access(uint64_t key)
{
	lv2syscall3(8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_REQUEST_ACCESS, (uint64_t)key);
	return_to_user_prog(int);
}

//-----------------------------------------------
//EXTRA (NO PS3 MANAGER SYSCALL)
//-----------------------------------------------

int ps3_shutdown(void)
{
	sysLv2FsUnlink((char*)"/dev_hdd0/tmp/turnoff");
	lv2syscall4(379, 0x1100, 0, 0, 0);
	return_to_user_prog(int);						
}

int ps3_quick_restart(void)
{
	sysLv2FsUnlink((char*)"/dev_hdd0/tmp/turnoff");
	lv2syscall3(379, 0x8201 , 0, 0);
	return_to_user_prog(int);						
}

int ps3_hard_restart(void)
{
	sysLv2FsUnlink((char*)"/dev_hdd0/tmp/turnoff");
	lv2syscall3(379, 0x1200 , 0, 0);
	return_to_user_prog(int);						
}

int ps3_soft_restart(void)
{
	sysLv2FsUnlink((char*)"/dev_hdd0/tmp/turnoff");
	lv2syscall3(379, 0x200 , 0, 0);
	return_to_user_prog(int);						
}

int led(uint64_t color, uint64_t mode)
{
	lv2syscall2(386, (uint64_t)color, (uint64_t)mode);
	return_to_user_prog(int);	
}

int ring_buzzer_simple(void)
{
	lv2syscall3(392, 0x1004, 0x4, 0x6);
	return_to_user_prog(int);	
}

int ring_buzzer_double(void)
{
	lv2syscall3(392, 0x1004, 0x7, 0x36);
	return_to_user_prog(int);	
}

int ring_buzzer_triple(void)
{
	lv2syscall3(392, 0x1004, 0xa, 0x1b6);
	return_to_user_prog(int);	
}

int sys_game_get_temperature(uint32_t _dev, uint32_t *temperature)
{
	lv2syscall2(383, (uint64_t)_dev, (uint64_t)temperature);
	return_to_user_prog(int);
}

int get_temperature_celcius(uint32_t *cpu_temp, uint32_t *rsx_temp)
{
	sys_game_get_temperature(0, cpu_temp);
	sys_game_get_temperature(1, rsx_temp);
	*cpu_temp>>=24;
	*rsx_temp>>=24;
    return 0;
}
