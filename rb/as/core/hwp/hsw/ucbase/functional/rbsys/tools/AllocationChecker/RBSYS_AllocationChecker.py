import RBSYS_SymbolTable
import sys


ELF_PATH = sys.argv[1]
GHS_PATH = sys.argv[2]
DEVICE   = sys.argv[3]
exit_value = 0

section_checks = None

# Attention: When changing the position of BURAM, you always have to change the RBSYS_ClearxRAM-functions inside RBSYS_CoreInit.h

if( DEVICE == "M2" ):
  section_checks = [
      # section_name,                     address_lowerlimit,  address_upperlimit  
      (".lram0_stack_noclear",            0xFDC00000,          0xFDC00000), # Stack shall be placed on LRAM
      (".lram1_stack_noclear",            0xFDA00000,          0xFDA00000), # Stack shall be placed on LRAM
      (".buram_fsw_noclear",              0xFE81FC00,          0xFE81FFFF), # Buram shall be placed on last 1KB of CRAM3
      (".buram_bb_noclear",               0xFE81FC00,          0xFE81FFFF), # Buram shall be placed on last 1KB of CRAM3
      (".buram_bb_fsw_interface_noclear", 0xFE81FC00,          0xFE81FFFF), # Buram shall be placed on last 1KB of CRAM3
      # DMA used dirty RAM: lower address limit = End Of CRAM0 - Size DMA RAM - Maximum Size HSM RAM
      (".DMA_SHARED_RAM_BSS",             0xFE076000,          0xFE07FFFF), # DMA used RAM shall be placed on CRAM0 -> has to fit guard config
      # HSM used dirty RAM: lower address limit = End of CRAM0 - Maximum Size HSM RAM
      (".HSM_SHARED_RAM_DATA",            0xFE078000,          0xFE07FFFF), # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config
      (".HSM_SHARED_RAM_BSS",             0xFE078000,          0xFE07FFFF)  # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config
  ]
elif( DEVICE == "M3" ):
  section_checks = [
      # section_name,                     address_lowerlimit,  address_upperlimit  
      (".lram0_stack_noclear",            0xFDC00000,          0xFDC00000), # Stack shall be placed on LRAM
      (".lram1_stack_noclear",            0xFDA00000,          0xFDA00000), # Stack shall be placed on LRAM
      (".buram_fsw_noclear",              0xFE4FFC00,          0xFE4FFFFF), # Buram shall be placed on last 1KB of CRAM2
      (".buram_bb_noclear",               0xFE4FFC00,          0xFE4FFFFF), # Buram shall be placed on last 1KB of CRAM2
      (".buram_bb_fsw_interface_noclear", 0xFE4FFC00,          0xFE4FFFFF), # Buram shall be placed on last 1KB of CRAM2
      # DMA used dirty RAM: lower address limit = End Of CRAM0 - Size DMA RAM - Maximum Size HSM RAM
      (".DMA_SHARED_RAM_BSS",             0xFE076000,          0xFE07FFFF), # DMA used RAM shall be placed on CRAM0 -> has to fit guard config
      # HSM used dirty RAM: lower address limit = End of CRAM0 - Maximum Size HSM RAM
      (".HSM_SHARED_RAM_DATA",            0xFE078000,          0xFE07FFFF), # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config
      (".HSM_SHARED_RAM_BSS",             0xFE078000,          0xFE07FFFF)  # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config
  ]
elif( DEVICE == "M6" ):
  section_checks = [
      # section_name,                     address_lowerlimit,  address_upperlimit  
      (".lram0_stack_noclear",            0xFDC00000,          0xFDC00000), # Stack shall be placed on LRAM
      (".lram1_stack_noclear",            0xFDA00000,          0xFDA00000), # Stack shall be placed on LRAM
      (".lram2_stack_noclear",            0xFD800000,          0xFD800000), # Stack shall be placed on LRAM
      (".lram3_stack_noclear",            0xFD600000,          0xFD600000), # Stack shall be placed on LRAM
      (".buram_fsw_noclear",              0xFE5FFC00,          0xFE5FFFFF), # Buram shall be placed on last 1KB of CRAM2
      (".buram_bb_noclear",               0xFE5FFC00,          0xFE5FFFFF), # Buram shall be placed on last 1KB of CRAM2
      (".buram_bb_fsw_interface_noclear", 0xFE5FFC00,          0xFE5FFFFF), # Buram shall be placed on last 1KB of CRAM2
      # DMA used dirty RAM: lower address limit = End Of CRAM0 - Size DMA RAM - Maximum Size HSM RAM
      (".DMA_SHARED_RAM_BSS",             0xFE076000,          0xFE07FFFF), # DMA used RAM shall be placed on CRAM0 -> has to fit guard config
      # HSM used dirty RAM: lower address limit = End of CRAM0 - Maximum Size HSM RAM
      (".HSM_SHARED_RAM_DATA",            0xFE078000,          0xFE07FFFF), # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config
      (".HSM_SHARED_RAM_BSS",             0xFE078000,          0xFE07FFFF)  # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config
  ]
elif( DEVICE == "P6" ):
  section_checks = [
      # section_name,                     address_lowerlimit,  address_upperlimit
      (".lram0_stack_noclear",            0x68000000,          0x68204000), # Stack shall be placed on Core0 TCMs (affects order of clearing RAM during Startup)
      (".lram1_stack_noclear",            0x68400000,          0x68604000), # Stack shall be placed on Core1 TCMs (affects order of clearing RAM during Startup)
      (".buram_fsw_noclear",              0x60400000,          0x60400400), # Buram shall be placed on first 1KB of CRAM0_1
      (".buram_bb_noclear",               0x60400000,          0x60400400), # Buram shall be placed on first 1KB of CRAM0_1
      (".buram_bb_fsw_interface_noclear", 0x60400000,          0x60400400), # Buram shall be placed on first 1KB of CRAM0_1
      # DMA used dirty RAM: lower address limit = End Of CRAM0 - Size DMA RAM - Maximum Size HSM RAM
      # (".DMA_SHARED_RAM_BSS",             0xFE076000,          0xFE07FFFF), # DMA used RAM shall be placed on CRAM0 -> has to fit guard config -> todo
      # HSM used dirty RAM: lower address limit = End of CRAM0 - Maximum Size HSM RAM
    #   (".HSM_SHARED_RAM_DATA",            0xFE078000,          0xFE07FFFF), # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config -> todo
    #   (".HSM_SHARED_RAM_BSS",             0xFE078000,          0xFE07FFFF)  # HSM shared RAM shall be placed on CRAM0 -> has to fit guard config -> todo
  ]


symbol_checks = []

symbols = RBSYS_SymbolTable.getSymbols(ELF_PATH, GHS_PATH)

def error_log(name, actual_address, required_lower_address, required_upper_address):
    global exit_value
    print("AllocationCheck: " + name + " with address " + str(hex(actual_address)) + 
        " is not allocated correctly to address range [" + str(hex(required_lower_address)) + 
        " - " + str(hex(required_upper_address)) + ".")
    exit_value += 1
    

for section_check in section_checks:
    (name, address_lower, address_upper) = section_check
    if name in symbols:
        for found_section in symbols[name]:
            if( found_section.address >= address_lower and found_section.address <= address_upper ):
                pass # Correct Allocation
            else:
                error_log( name, found_section.address, address_lower, address_upper)

#for symbol_check in symbol_checks:
#    (name, address) = symbol_check
#    for found_symbol in symbols[name]:
#        if( found_symbol.address != address ):
#            error_log( name, found_symbol.address, address )


sys.exit(exit_value)