#include <bitset>
#include <cstdint>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  std::uint8_t instruction{};
  std::ifstream binary(argv[1], std::ios::binary);
  std::string asm_instruction{};
  
  while (binary.read(reinterpret_cast<char *>(&instruction), 1)) {
    // std::bitset<8> instruction_binary{instruction};
    // std::cout << instruction_binary << '\t';

    if (((instruction & 0xFC) >> 2) == 0x22) {
      bool d{static_cast<bool>(instruction & 0x02)}; // 0 = source in REG, 1 = destination in REG
      bool w{static_cast<bool>(instruction & 0x01)}; // 0 = byte operands, 1 = word

      binary.read(reinterpret_cast<char *>(&instruction), 1);

      // instruction_binary = instruction;
      // std::cout << instruction_binary << '\n';

      asm_instruction += "mov ";
      int mod{(instruction & 0xC0) >> 6};            // mode field (memory mode no displacement, 8-bit displacement, 16-bit, register mode)
      int reg{(instruction & 0x38) >> 3};            // register encoding
      int rm{instruction & 0x07};                    // register or memory encoding

      // std::cout << reg << '\t' << rm << '\n';
      std::string register_field{};
      if (w) {
        switch (reg) {
        case 0:
          register_field = "AX";
          break;
        case 1:
          register_field = "CX";
          break;
        case 2:
          register_field = "DX";
          break;
        case 3:
          register_field = "BX";
          break;
        case 4:
          register_field = "SP";
          break;
        case 5:
          register_field = "BP";
          break;
        case 6:
          register_field = "SI";
          break;
        case 7:
          register_field = "DI";
          break;
        default:
          register_field = "REG";
          break;
        }
      } else {
        switch (reg) {
        case 0:
          register_field = "AL";
          break;
        case 1:
          register_field = "CL";
          break;
        case 2:
          register_field = "DL";
          break;
        case 3:
          register_field = "BL";
          break;
        case 4:
          register_field = "AH";
          break;
        case 5:
          register_field = "CH";
          break;
        case 6:
          register_field = "DH";
          break;
        case 7:
          register_field = "BH";
          break;
        default:
          register_field = "REG";
          break;
        }
      }

      std::string rm_field{};
      if (w) {
        switch (reg) {
        case 0:
          rm_field = "AX";
          break;
        case 1:
          rm_field = "CX";
          break;
        case 2:
          rm_field = "DX";
          break;
        case 3:
          rm_field = "BX";
          break;
        case 4:
          rm_field = "SP";
          break;
        case 5:
          rm_field = "BP";
          break;
        case 6:
          rm_field = "SI";
          break;
        case 7:
          rm_field = "DI";
          break;
        default:
          rm_field = "REG";
          break;
        }
      } else {
        switch (reg) {
        case 0:
          rm_field = "AL";
          break;
        case 1:
          rm_field = "CL";
          break;
        case 2:
          rm_field = "DL";
          break;
        case 3:
          rm_field = "BL";
          break;
        case 4:
          rm_field = "AH";
          break;
        case 5:
          rm_field = "CH";
          break;
        case 6:
          rm_field = "DH";
          break;
        case 7:
          rm_field = "BH";
          break;
        default:
          rm_field = "REG";
          break;
        }
      }

      if (d) {
        asm_instruction += register_field;
        asm_instruction.push_back(' ');
        asm_instruction += rm_field;
      } else {
        asm_instruction += rm_field;
        asm_instruction.push_back(' ');
        asm_instruction += register_field;
      }

      std::cout << asm_instruction << '\n';
      asm_instruction.clear();
    }
  }
}
