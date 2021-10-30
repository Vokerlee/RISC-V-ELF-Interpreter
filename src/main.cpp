#include <iostream>
#include <elf.h>
#include <gelf.h>
#include <libelf.h> 
#include <err.h>
#include <fcntl.h>
#include <sysexits.h>
#include <unistd.h>
#include "virtual_mem.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
        err(EX_USAGE, "error: too few arguments");
    else if (argc > 3)
        err(EX_USAGE, "error: too many arguments");

    // INITIALIZATION
    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EX_SOFTWARE, "ELF library initialization failed: %s ", elf_errmsg(-1));

    int elf_fd = open(argv[1], O_RDONLY);
    if (elf_fd == -1)
        err(EX_NOINPUT, "open \"%s\" failed ", argv[1]);

    Elf *elf = elf_begin(elf_fd, ELF_C_READ, nullptr);
    if (elf == nullptr)
        errx(EX_SOFTWARE, "elf_begin() failed : %s. ", elf_errmsg (-1));

    // CHECKING FOR BEING ELF OBJECT
    if (elf_kind(elf) != ELF_K_ELF)
        errx(EX_DATAERR, "\"%s\" is not an ELF object. ", argv[1]);

    // GET ELF HEADER
    GElf_Ehdr ehdr = {0};
    if (gelf_getehdr (elf, &ehdr) == nullptr)
        errx(EX_SOFTWARE, "getehdr() failed : %s. ", elf_errmsg(-1));

    // CHECKING FOR BEING 32 BITS OBJECT
    int elf_class = gelf_getclass(elf);
    if (elf_class == ELFCLASSNONE)
        errx(EX_SOFTWARE, "getclass() failed: %s. ", elf_errmsg(-1));
    else if (elf_class != ELFCLASS32)
        errx(EX_NOINPUT, "elf file must be of 32 bits version.");

    GElf_Phdr* phdrs = new GElf_Phdr[ehdr.e_phnum];
    if (phdrs == nullptr)
        errx(EX_NOUSER, "cannot allocate memory for program headers.");

    for (size_t i = 0; i < ehdr.e_phnum; ++i)
    {
        if (gelf_getphdr(elf, i, phdrs + i) != (phdrs + i))
            errx(EX_SOFTWARE, "getphdr() failed: %s. ", elf_errmsg(-1));
    }

    risc::VirtualMem memory;
    bool mem_load_success = memory.load_elf_file(elf_fd, phdrs, ehdr.e_phnum);
    if (mem_load_success == false)
        errx(EX_SOFTWARE, "memory loading in virtual space failed: %s. ", elf_errmsg(-1));

    // NOW NOTHING WORKS, NEED TO BE DEBUGGED


    
    // EVERUTHING IS SUCCESSFUL, JUST FINISH AND EXIT
    delete [] phdrs;
    elf_end(elf);
    close(elf_fd);

    exit(EXIT_SUCCESS);
}
