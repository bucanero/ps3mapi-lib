/* COBRA/MAMBA PSL1GHT
 * Copyright (c) 2020 Bucanero (www.bucanero.com.ar)
 *
 * It may be used for any purpose as long as this notice remains intact on all
 * source code distributions.
 */

#include <ppu-lv2.h>
#include "ps3mapi_ps3_lib.h"

//----------------------------------------
//COBRA/MAMBA
//----------------------------------------

int sys8_get_version(uint32_t *version)
{
    lv2syscall2(8, SYSCALL8_OPCODE_GET_VERSION, (uint64_t)version);
    return_to_user_prog(int);
}

int sys8_get_mamba(void)
{
    lv2syscall1(8, SYSCALL8_OPCODE_GET_MAMBA);
    return_to_user_prog(int);
}

int sys8_get_hen(void)
{
    lv2syscall1(8, SYSCALL8_OPCODE_IS_HEN);
    return_to_user_prog(int);
}

int sys8_get_hen_version(void)
{
    lv2syscall1(8, SYSCALL8_OPCODE_HEN_REV);
    return_to_user_prog(int);
}

int has_cobra_mamba(void)
{
    u32 version = 0x99999999;
    if (sys8_get_version(&version) < 0)
        return 0;

    return (version != 0x99999999);
}

int is_cobra(void)
{
    return (has_cobra_mamba() && (sys8_get_mamba() != 0x666));
}

int is_mamba(void)
{
    return (has_cobra_mamba() && (sys8_get_mamba() == 0x666));
}

int is_ps3hen(void)
{
    return (sys8_get_hen() == 0x1337);
}

int cobra_mamba_load_prx_module(uint32_t slot, char * path, void * arg, uint32_t arg_size)
{
	lv2syscall5(8, SYSCALL8_OPCODE_LOAD_VSH_PLUGIN, (uint64_t)slot, (uint64_t)path, (uint64_t)arg, (uint64_t)arg_size);
	return_to_user_prog(int);
}

int cobra_mamba_unload_prx_module(uint32_t slot)
{
	lv2syscall2(8, SYSCALL8_OPCODE_UNLOAD_VSH_PLUGIN, (uint64_t)slot);
	return_to_user_prog(int);
}

int cobra_mamba_stealth_test(void)
{
    lv2syscall1(8, SYSCALL8_OPCODE_STEALTH_TEST);
    return_to_user_prog(int);
}

int cobra_mamba_stealth_activate(void)
{
    lv2syscall1(8, SYSCALL8_OPCODE_STEALTH_ACTIVATE);
    return_to_user_prog(int);
}

uint64_t lv2_peek(uint64_t addr)
{ 
    lv2syscall1(6, (uint64_t) addr >> 0ULL);
    return_to_user_prog(uint64_t);
}

int lv2_poke(uint64_t addr, uint64_t value)
{ 
    lv2syscall2(7, (uint64_t) addr, (uint64_t) value); 
    return_to_user_prog(int);
}

int lv2_poke32(uint64_t addr, uint32_t val)
{
    if(addr==0) return (-1);
    uint32_t next = lv2_peek(addr) & 0xffffffff;
    return lv2_poke(addr, (((uint64_t) val) << 32) | next);
}
